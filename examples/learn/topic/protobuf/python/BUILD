# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

py_binary(
    name = "protobuf_node_creator",
    srcs = [
        "protobuf_node_creator.py",
        "protobuf_publishing_node.py",
        "protobuf_subscribing_node.py",
    ],
    data = [
        "//examples/cert",
    ],
    main = "protobuf_node_creator.py",
    deps = [
        "//examples/learn/topic:topic_create_flag_py",
        "//examples/learn/topic/protobuf:simple_message_proto_py",
    ],
)
