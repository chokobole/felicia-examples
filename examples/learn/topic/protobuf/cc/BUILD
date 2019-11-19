# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

load("@com_github_chokobole_felicia//bazel:felicia_cc.bzl", "fel_cc_native_binary")

fel_cc_native_binary(
    name = "protobuf_node_creator",
    srcs = [
        "protobuf_node_creator.cc",
        "protobuf_publishing_node.cc",
        "protobuf_publishing_node.h",
        "protobuf_subscribing_node.cc",
        "protobuf_subscribing_node.h",
    ],
    data = [
        "//examples/cert",
    ],
    deps = [
        "//examples/learn/topic:topic_create_flag_cc",
        "//examples/learn/topic/protobuf:simple_message_proto_cc",
    ],
)
