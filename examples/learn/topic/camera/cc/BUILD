# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

load(
    "@com_github_chokobole_felicia//bazel:felicia_cc.bzl",
    "fel_cc_native_binary",
    "fel_cc_native_library",
)

fel_cc_native_library(
    name = "camera_flag",
    srcs = ["camera_flag.cc"],
    hdrs = ["camera_flag.h"],
    visibility = ["//:internal"],
    deps = ["//examples/learn/topic:topic_create_flag_cc"],
)

fel_cc_native_binary(
    name = "camera_node_creator",
    srcs = [
        "camera_node_creator.cc",
        "camera_publishing_node.cc",
        "camera_publishing_node.h",
        "camera_subscribing_node.cc",
        "camera_subscribing_node.h",
    ],
    deps = [":camera_flag"],
)
