# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

load(
    "@com_github_chokobole_felicia//bazel:felicia_cc.bzl",
    "fel_cc_native_binary",
    "fel_cc_native_library",
)
load(
    "//:util.bzl",
    "if_has_hector_slam",
    "if_has_orb_slam2",
)

fel_cc_native_binary(
    name = "dataset_loader_node_creator",
    srcs = [
        "dataset_flag.cc",
        "dataset_flag.h",
        "dataset_loader_node.cc",
        "dataset_loader_node.h",
        "dataset_loader_node_creator.cc",
    ],
    deps = select({
        "//:use_shared_library": ["//:felicia"],
        "//conditions:default": ["//external:felicia"],
    }),
)

fel_cc_native_library(
    name = "slam_node_create_flag",
    srcs = [
        "slam_node_create_flag.cc",
    ] + if_has_hector_slam([
        "hector_slam_flag.cc",
    ]) + if_has_orb_slam2([
        "orb_slam2_flag.cc",
    ]),
    hdrs = [
        "slam_node_create_flag.h",
    ] + if_has_hector_slam([
        "hector_slam_flag.h",
    ]) + if_has_orb_slam2([
        "orb_slam2_flag.h",
    ]),
    defines = if_has_hector_slam([
        "HAS_HECTOR_SLAM",
    ]) + if_has_orb_slam2([
        "HAS_ORB_SLAM2",
    ]),
    visibility = ["//:internal"],
    deps = ["//examples:node_create_flag_cc"],
)

fel_cc_native_binary(
    name = "slam_node_creator",
    srcs = ["slam_node_creator.cc"],
    deps = [
        ":slam_node_create_flag",
    ] + if_has_hector_slam([
        "//examples/slam/hector_slam:hector_slam_node",
    ]) + if_has_orb_slam2([
        "//examples/slam/orb_slam2:orb_slam2_node",
    ]),
)
