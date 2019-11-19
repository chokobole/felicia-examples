# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

load("@com_github_chokobole_felicia//bazel:felicia_cc.bzl", "fel_cc_native_binary")

fel_cc_native_binary(
    name = "depth_camera_node_creator",
    srcs = [
        "depth_camera_flag.cc",
        "depth_camera_flag.h",
    ] + select({
        "//:has_realsense_with_shared_library": ["@com_github_chokobole_felicia//felicia:only_main.cc"],
        "//:has_realsense": [
            "realsense/rs_camera_flag.cc",
            "realsense/rs_camera_flag.h",
            "realsense/rs_camera_publishing_node.cc",
            "realsense/rs_camera_publishing_node.h",
            "realsense/rs_camera_node_creator.cc",
        ],
        "//conditions:default": ["@com_github_chokobole_felicia//felicia:only_main.cc"],
    }),
    deps = [
        "//examples/learn/topic/camera/cc:camera_flag",
    ] + select({
        "//:has_realsense_with_shared_library": [],
        "//:has_realsense": ["//external:felicia_realsense"],
        "//conditions:default": [],
    }),
)
