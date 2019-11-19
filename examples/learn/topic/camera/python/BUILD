# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

py_library(
    name = "camera_flag_py",
    srcs = ["camera_flag.py"],
    visibility = ["//:internal"],
    deps = ["//examples/learn/topic:topic_create_flag_py"],
)

py_binary(
    name = "camera_node_creator",
    srcs = [
        "camera_node_creator.py",
        "camera_publishing_node.py",
        "camera_subscribing_node.py",
    ],
    main = "camera_node_creator.py",
    deps = [":camera_flag_py"],
)
