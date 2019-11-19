# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import sys

import import_order_resolver  # Should be before import felicia_py
import felicia_py as fel
from felicia.core.protobuf.master_data_pb2 import NodeInfo
import felicia_py.command_line_interface as cli

from grpc_client_node import GrpcClientNode
from grpc_server_node import GrpcServerNode
from examples.learn.service.simple_service_flag import SimpleServiceFlag


def main():
    fel.felicia_init()

    delegate = SimpleServiceFlag()
    parser = cli.FlagParser()
    parser.set_program_name('grpc_node_creator')
    if not parser.parse(len(sys.argv), sys.argv, delegate):
        sys.exit(1)

    master_proxy = fel.master_proxy
    s = master_proxy.start()
    if not s.ok():
        print("{} {}.".format(cli.RED_ERROR, s), file=sys.stderr)
        sys.exit(1)

    node_info = NodeInfo()
    node_info.name = delegate.name_flag.value

    if delegate.is_server_flag.value:
        master_proxy.request_register_node(
            GrpcServerNode, node_info, delegate)
    else:
        master_proxy.request_register_node(
            GrpcClientNode, node_info, delegate)

    fel.main_thread.run()


if __name__ == '__main__':
    main()
