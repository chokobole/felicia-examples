# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

load("@com_github_chokobole_felicia//bazel:felicia_cc.bzl", "fel_cc_native_library")

fel_cc_native_library(
    name = "hector_slam_node",
    srcs = select({
        "//:has_hector_slam_with_shared_library": [],
        "//:has_hector_slam": ["hector_slam_node.cc"],
        "//conditions:default": [],
    }),
    hdrs = select({
        "//:has_hector_slam_with_shared_library": [],
        "//:has_hector_slam": ["hector_slam_node.h"],
        "//conditions:default": [],
    }),
    visibility = ["//:internal"],
    deps = select({
        "//:has_hector_slam_with_shared_library": [],
        "//:has_hector_slam": [
            "//examples/slam:slam_node_create_flag",
            "//external:felicia_hector_slam",
        ],
        "//conditions:default": [],
    }),
)
