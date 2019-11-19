# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

load("@com_github_chokobole_felicia//bazel:felicia.bzl", "if_has_ros")

py_binary(
    name = "ros_msg_node_creator",
    srcs = [
        "ros_msg_node_creator.py",
        "ros_msg_publishing_node.py",
        "ros_msg_subscribing_node.py",
    ],
    main = "ros_msg_node_creator.py",
    deps = [
        "//examples/learn/topic:topic_create_flag_py",
    ] + if_has_ros([
        "//examples/learn/topic/ros_msg:simple_message_ros_msg_py",
    ]),
)
