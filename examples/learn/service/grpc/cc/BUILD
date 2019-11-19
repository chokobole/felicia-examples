# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

load("@com_github_chokobole_felicia//bazel:felicia_cc.bzl", "fel_cc_native_binary")

fel_cc_native_binary(
    name = "grpc_node_creator",
    srcs = [
        "grpc_client_node.cc",
        "grpc_client_node.h",
        "grpc_node_creator.cc",
        "grpc_server_node.cc",
        "grpc_server_node.h",
    ],
    deps = [
        "//examples/learn/service:simple_service_flag_cc",
        "//examples/learn/service/grpc:simple_service_proto_cc",
    ],
)
