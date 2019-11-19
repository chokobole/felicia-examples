# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

load("@com_github_chokobole_felicia//bazel:felicia_cc.bzl", "fel_cc_native_library")

package(default_visibility = ["//:internal"])

cc_import(
    name = "lib_orb_slam2",
    interface_library = select({
        "@com_github_chokobole_felicia//felicia:windows": "not-exsiting.lib",
        "//conditions:default": "ORB_SLAM2/lib/libORB_SLAM2.so",
    }),
    shared_library = "ORB_SLAM2/lib/libORB_SLAM2.so",
)

cc_library(
    name = "@orb_slam2",
    hdrs = select({
        "//:has_orb_slam2": glob([
            "ORB_SLAM2/include/*.h",
            "ORB_SLAM2/Thirdparty/DBoW2/**/*.h",
            "ORB_SLAM2/Thirdparty/g2o/**/*.h",
            "ORB_SLAM2/Thirdparty/g2o/**/*.hpp",
        ]),
        "//conditions:default": [],
    }),
    includes = select({
        "//:has_orb_slam2": [
            "ORB_SLAM2",
            "ORB_SLAM2/include",
            "ORB_SLAM2/Thirdparty/DBoW2/DBoW2",
            "ORB_SLAM2/Thirdparty/DBoW2/DUtils",
            "ORB_SLAM2/Thirdparty/g2o",
            "ORB_SLAM2/Thirdparty/g2o/g2o/core",
            "ORB_SLAM2/Thirdparty/g2o/g2o/solvers",
            "ORB_SLAM2/Thirdparty/g2o/g2o/stuff",
            "ORB_SLAM2/Thirdparty/g2o/g2o/types",
        ],
        "//conditions:default": [],
    }),
    linkopts = select({
        "//:has_orb_slam2": [
            "-L/usr/local/lib",
            "-lpangolin",
            "-lGL",
            "-lGLEW",
        ],
        "//conditions:default": [],
    }),
    deps = [":lib_orb_slam2"],
)

fel_cc_native_library(
    name = "orb_slam2_node",
    srcs = select({
        "//:has_orb_slam2": ["orb_slam2_node.cc"],
        "//conditions:default": [],
    }),
    hdrs = ["orb_slam2_node.h"],
    deps = select({
        "//:has_orb_slam2": [
            ":@orb_slam2",
            "//examples/slam:slam_node_create_flag",
        ],
        "//conditions:default": [],
    }),
)
