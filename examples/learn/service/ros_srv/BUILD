# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

load("@com_github_chokobole_felicia//bazel:felicia_ros.bzl", "fel_ros_msg_library")

fel_ros_msg_library(
    name = "simple_service_ros_srv",
    srcs = [
        "SimpleService.srv",
    ],
    gen_srv = True,
    package = "felicia",
    visibility = ["//:internal"],
)
