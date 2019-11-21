# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import sys

import felicia_py as fel
import felicia_py.command_line_interface as cli
from felicia.core.protobuf.channel_pb2 import ChannelDef
from felicia.core.protobuf.ui_pb2 import PixelFormat
from felicia.drivers.camera.camera_frame_message_pb2 import CameraFrameMessage
from felicia.drivers.camera.camera_settings_message_pb2 import CameraSettingsInfoMessage


class CameraPublishingNode(fel.NodeLifecycle):
    def __init__(self, camera_flag, camera_descriptor):
        super().__init__()
        self.camera_flag = camera_flag
        self.topic = camera_flag.topic_flag.value
        self.camera_descriptor = camera_descriptor
        self.publisher = fel.communication.Publisher(CameraFrameMessage)

    def on_init(self):
        self.camera = fel.drivers.CameraFactory.new_camera(
            self.camera_descriptor)
        s = self.camera.init()
        if not s.ok():
            fel.log(fel.ERROR, s.error_message())
            sys.exit(1)

        # You can set camera settings here.
        camera_settings = fel.drivers.CameraSettings()
        s = self.camera.set_camera_settings(camera_settings)
        fel.log_if(fel.ERROR, not s.ok(), s.error_message())

        message = CameraSettingsInfoMessage()
        s = self.camera.get_camera_settings_info(message)
        if s.ok():
            print(message)
        else:
            fel.log(fel.ERROR, s.error_message())

    def on_did_create(self, node_info):
        self.node_info = node_info
        self.request_publish()

    def on_request_publish(self, status):
        if status.ok():
            fel.main_thread.post_task(self.start_camera)
        else:
            fel.log(fel.ERROR, status.error_message())

    def on_request_unpublish(self, status):
        if status.ok():
            fel.main_thread.post_task(self.stop_camera)
        else:
            fel.log(fel.ERROR, status.error_message())

    def request_publish(self):
        settings = fel.communication.Settings()
        settings.queue_size = 1
        settings.is_dynamic_buffer = True
        self.publisher.request_publish(self.node_info, self.topic,
                                       ChannelDef.CHANNEL_TYPE_TCP |
                                       ChannelDef.CHANNEL_TYPE_SHM |
                                       ChannelDef.CHANNEL_TYPE_WS,
                                       settings, self.on_request_publish)

    def request_unpublish(self):
        self.publisher.request_unpublish(self.node_info, self.topic,
                                         self.on_request_unpublish)

    def start_camera(self):
        pixel_format = PixelFormat.Value(
            self.camera_flag.pixel_format_flag.value)
        s = self.camera.start(
            fel.drivers.CameraFormat(self.camera_flag.width_flag.value,
                                     self.camera_flag.height_flag.value,
                                     pixel_format,
                                     self.camera_flag.fps_flag.value),
            self.on_camera_frame, self.on_camera_error)
        if s.ok():
            print("Camera format: {}".format(self.camera.camera_format()))
            # fel.main_thread.post_delayed_task(
            #     self.request_unpublish, fel.TimeDelta.from_seconds(10))
            pass
        else:
            fel.log(fel.ERROR, s.error_message())

    def stop_camera(self):
        s = self.camera.stop()
        fel.log_if(fel.ERROR, not s.ok(), s.error_message())

    def on_camera_frame(self, camera_frame):
        if self.publisher.is_unregistered():
            return

        self.publisher.publish(camera_frame.to_camera_frame_message(False))

    def on_camera_error(self, status):
        fel.log_if(fel.ERROR, not status.ok(), status.error_message())
