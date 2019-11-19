# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

load("@com_github_chokobole_felicia//bazel:felicia.bzl", "if_has_ros")

py_binary(
    name = "ros_srv_node_creator",
    srcs = [
        "ros_srv_client_node.py",
        "ros_srv_node_creator.py",
        "ros_srv_server_node.py",
    ],
    main = "ros_srv_node_creator.py",
    deps = [
        "//examples/learn/service:simple_service_flag_py",
    ] + if_has_ros([
        "//examples/learn/service/ros_srv:simple_service_ros_srv_py",
    ]),
)
