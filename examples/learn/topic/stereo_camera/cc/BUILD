# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

load("@com_github_chokobole_felicia//bazel:felicia_cc.bzl", "fel_cc_native_binary")

fel_cc_native_binary(
    name = "stereo_camera_node_creator",
    srcs = [
        "stereo_camera_flag.cc",
        "stereo_camera_flag.h",
    ] + select({
        "//:has_zed_with_shared_library": ["@com_github_chokobole_felicia//felicia:only_main.cc"],
        "//:has_zed": [
            "zed/zed_camera_publishing_node.cc",
            "zed/zed_camera_publishing_node.h",
            "zed/zed_camera_node_creator.cc",
        ],
        "//conditions:default": ["@com_github_chokobole_felicia//felicia:only_main.cc"],
    }),
    deps = [
        "//examples/learn/topic/camera/cc:camera_flag",
    ] + select({
        "//:has_zed_with_shared_library": [],
        "//:has_zed": ["//external:felicia_zed"],
        "//conditions:default": [],
    }),
)
