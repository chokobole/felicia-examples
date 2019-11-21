# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import sys

import numpy as np

import import_order_resolver  # Should be before import felicia_py
import felicia_py as fel
import felicia_py.command_line_interface as cli
from felicia.core.protobuf.bounding_box_pb2 import ImageWithBoundingBoxesMessage
from felicia.core.protobuf.master_data_pb2 import NodeInfo
from felicia.core.protobuf.channel_pb2 import ChannelDef
from felicia.core.protobuf.ui_pb2 import PIXEL_FORMAT_RGB
from felicia.drivers.camera.camera_frame_message_pb2 import CameraFrameMessage
from tf_object_detection import ObjectDetection


class ObjectDetectionNode(fel.NodeLifecycle):
    def __init__(self, topic, camera_descriptor):
        super().__init__()
        self.topic = topic
        self.camera_descriptor = camera_descriptor
        self.draw_on_image = False
        if self.draw_on_image:
            self.publisher = fel.communication.Publisher(CameraFrameMessage)
        else:
            self.publisher = fel.communication.Publisher(
                ImageWithBoundingBoxesMessage)

    def on_init(self):
        self.camera = fel.drivers.CameraFactory.new_camera(
            self.camera_descriptor)
        s = self.camera.init()
        if not s.ok():
            fel.log(fel.ERROR, s.error_message())
            sys.exit(1)
        self.object_detection = ObjectDetection()

    def on_did_create(self, node_info):
        self.node_info = node_info
        self.request_publish()

    def on_request_publish(self, status):
        if status.ok():
            fel.main_thread.post_task(self.start_camera)
        else:
            fel.log(fel.ERROR, status.error_message())

    def request_publish(self):
        settings = fel.communication.Settings()
        settings.queue_size = 1
        settings.is_dynamic_buffer = True

        self.publisher.request_publish(self.node_info, self.topic,
                                       ChannelDef.CHANNEL_TYPE_TCP | ChannelDef.CHANNEL_TYPE_WS,
                                       settings, self.on_request_publish)

    def start_camera(self):
        # You should set the camera format if you have any you want to run with.
        s = self.camera.start(fel.drivers.CameraFormat(640, 480, PIXEL_FORMAT_RGB, 25),
                              self.on_camera_frame, self.on_camera_error)
        if not s.ok():
            fel.log(fel.ERROR, s.error_message())
            sys.exit(1)

    def on_camera_frame(self, camera_frame):
        if self.publisher.is_unregistered():
            return

        image_np = np.array(camera_frame, copy=False)

        if self.draw_on_image:
            detected_image = self.object_detection.run(
                image_np, self.draw_on_image)

            detected_camera_frame = fel.drivers.CameraFrame(
                detected_image, camera_frame.camera_format, camera_frame.timestamp)

            self.publisher.publish(
                detected_camera_frame.to_camera_frame_message(False))
        else:
            image_with_bounding_boxes = self.object_detection.run(
                image_np, self.draw_on_image)

            self.publisher.publish(image_with_bounding_boxes)

    def on_camera_error(self, status):
        fel.log_if(fel.ERROR, not status.ok(), status.error_message())


def main():
    fel.felicia_init()

    camera_descriptors = []
    s = fel.drivers.CameraFactory.get_camera_descriptors(camera_descriptors)
    if not s.ok():
        print("{} {}.".format(cli.RED_ERROR, s), file=sys.stderr)
        sys.exit(1)

    if len(camera_descriptors) == 0:
        print("{} {}.".format(cli.RED_ERROR, "No camera device"), file=sys.stderr)
        sys.exit(1)

    master_proxy = fel.master_proxy
    s = master_proxy.start()
    if not s.ok():
        print("{} {}.".format(cli.RED_ERROR, s), file=sys.stderr)
        sys.exit(1)

    node_info = NodeInfo()

    # Use the first camera
    master_proxy.request_register_node(
        ObjectDetectionNode, node_info, "message", camera_descriptors[0])

    fel.main_thread.run()


if __name__ == '__main__':
    main()
