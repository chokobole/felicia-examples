# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

load("@com_github_chokobole_felicia//bazel:felicia.bzl", "if_has_ros")
load("@com_github_chokobole_felicia//bazel:felicia_cc.bzl", "fel_cc_native_binary")

fel_cc_native_binary(
    name = "ros_msg_node_creator",
    srcs = select({
        "@com_github_chokobole_felicia//felicia:has_ros": [
            "ros_msg_node_creator.cc",
            "ros_msg_publishing_node.cc",
            "ros_msg_publishing_node.h",
            "ros_msg_subscribing_node.cc",
            "ros_msg_subscribing_node.h",
        ],
        "//conditions:default": ["@com_github_chokobole_felicia//felicia:only_main.cc"],
    }),
    deps = [
        "//examples/learn/topic:topic_create_flag_cc",
    ] + if_has_ros([
        "//examples/learn/topic/ros_msg:simple_message_ros_msg_cc",
    ]),
)
