# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

load("@com_github_chokobole_felicia//bazel:felicia_cc.bzl", "fel_cc_native_binary")

fel_cc_native_binary(
    name = "lidar_node_creator",
    srcs = [
        "lidar_flag.cc",
        "lidar_flag.h",
        "lidar_subscribing_node.cc",
        "lidar_subscribing_node.h",
    ] + select({
        "//:has_rplidar_with_shared_library": ["@com_github_chokobole_felicia//felicia:only_main.cc"],
        "//:has_rplidar": [
            "rplidar/rplidar_flag.cc",
            "rplidar/rplidar_flag.h",
            "rplidar/rplidar_node_creator.cc",
            "rplidar/rplidar_publishing_node.cc",
            "rplidar/rplidar_publishing_node.h",
        ],
        "//conditions:default": ["@com_github_chokobole_felicia//felicia:only_main.cc"],
    }),
    deps = [
        "//examples/learn/topic:topic_create_flag_cc",
    ] + select({
        "//:has_rplidar_with_shared_library": [],
        "//:has_rplidar": ["//external:felicia_rplidar"],
        "//conditions:default": [],
    }),
)
