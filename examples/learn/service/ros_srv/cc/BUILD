# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

load("@com_github_chokobole_felicia//bazel:felicia.bzl", "if_has_ros")
load("@com_github_chokobole_felicia//bazel:felicia_cc.bzl", "fel_cc_native_binary")

fel_cc_native_binary(
    name = "ros_srv_node_creator",
    srcs = select({
        "@com_github_chokobole_felicia//felicia:has_ros": [
            "ros_srv_client_node.cc",
            "ros_srv_client_node.h",
            "ros_srv_node_creator.cc",
            "ros_srv_server_node.cc",
            "ros_srv_server_node.h",
        ],
        "//conditions:default": ["@com_github_chokobole_felicia//felicia:only_main.cc"],
    }),
    deps = [
        "//examples/learn/service:simple_service_flag_cc",
    ] + if_has_ros([
        "//examples/learn/service/ros_srv:simple_service_ros_srv_cc",
    ]),
)
