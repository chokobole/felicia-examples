# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import sys
from platform import system

import import_order_resolver  # Should be before import felicia_py
import felicia_py as fel
from felicia.core.protobuf.master_data_pb2 import NodeInfo
import felicia_py.command_line_interface as cli

from examples.learn.topic.camera.python.camera_flag import CameraFlag
from camera_publishing_node import CameraPublishingNode
from camera_subscribing_node import CameraSubscribingNode


def main():
    fel.felicia_init()

    delegate = CameraFlag()
    parser = cli.FlagParser()
    parser.set_program_name('camera_node_creator')
    if not parser.parse(len(sys.argv), sys.argv, delegate):
        sys.exit(1)

    camera_descriptors = []
    s = fel.drivers.CameraFactory.get_camera_descriptors(camera_descriptors)
    if not s.ok():
        print("{} {}.".format(cli.RED_ERROR, s), file=sys.stderr)
        sys.exit(1)

    if delegate.device_index_flag.is_set():
        if len(camera_descriptors) <= delegate.device_index_flag.value:
            print("{} {}".format(cli.RED_ERROR,
                                 "Please set device_index among them.."))
            for i in range(len(camera_descriptors)):
                print("[{}] {}".format(i, camera_descriptors[i]), file=sys.stderr)
            sys.exit(1)

    if delegate.device_list_flag.value:
        if delegate.device_index_flag.is_set():
            camera_formats = []
            s = fel.drivers.CameraFactory.get_supported_camera_formats(
                camera_descriptors[delegate.device_index_flag.value],
                camera_formats)
            if not s.ok():
                print("{} {}.".format(cli.RED_ERROR, s), file=sys.stderr)
                sys.exit(1)
            for i in range(len(camera_formats)):
                print("[{}] {}".format(i, camera_formats[i]))
        else:
            for i in range(len(camera_descriptors)):
                print("[{}] {}".format(i, camera_descriptors[i]))
        sys.exit(0)

    master_proxy = fel.master_proxy
    s = master_proxy.start()
    if not s.ok():
        print("{} {}.".format(cli.RED_ERROR, s), file=sys.stderr)
        sys.exit(1)

    node_info = NodeInfo()
    node_info.name = delegate.name_flag.value

    if delegate.is_publshing_node_flag.value:
        master_proxy.request_register_node(
            CameraPublishingNode, node_info, delegate,
            camera_descriptors[delegate.device_index_flag.value])
    else:
        master_proxy.request_register_node(
            CameraSubscribingNode, node_info, delegate)

    main_thread = fel.main_thread
    if system() == 'Windows':
        main_thread.init_com(True)
    main_thread.run()


if __name__ == '__main__':
    main()
