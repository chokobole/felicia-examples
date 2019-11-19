# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

load("@com_github_chokobole_felicia//bazel:felicia_cc.bzl", "fel_cc_native_library")

package(default_visibility = ["//:internal"])

fel_cc_native_library(
    name = "service_create_flag_cc",
    srcs = ["service_create_flag.cc"],
    hdrs = ["service_create_flag.h"],
    deps = ["//examples:node_create_flag_cc"],
)

fel_cc_native_library(
    name = "simple_service_flag_cc",
    srcs = ["simple_service_flag.cc"],
    hdrs = ["simple_service_flag.h"],
    deps = [":service_create_flag_cc"],
)

py_library(
    name = "service_create_flag_py",
    srcs = ["service_create_flag.py"],
    deps = ["//examples:node_create_flag_py"],
)

py_library(
    name = "simple_service_flag_py",
    srcs = ["simple_service_flag.py"],
    deps = [":service_create_flag_py"],
)
