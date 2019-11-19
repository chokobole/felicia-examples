# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

py_binary(
    name = "grpc_node_creator",
    srcs = [
        "grpc_client_node.py",
        "grpc_node_creator.py",
        "grpc_server_node.py",
    ],
    main = "grpc_node_creator.py",
    deps = [
        "//examples/learn/service:simple_service_flag_py",
        "//examples/learn/service/grpc:simple_service_proto_py",
    ],
)
