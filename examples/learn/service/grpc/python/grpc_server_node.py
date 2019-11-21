# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import felicia_py as fel
from felicia.python.rpc.server import Server

import examples.learn.service.grpc.simple_service_pb2 as simple_service_pb2
import examples.learn.service.grpc.simple_service_pb2_grpc as simple_service_pb2_grpc


class GrpcSimpleService(simple_service_pb2_grpc.SimpleServiceServicer):
    def Add(self, request, context):
        return simple_service_pb2.AddResponse(
            sum=request.a + request.b
        )


class GrpcSimplerServer(Server):
    def __init__(self, max_workers):
        super().__init__(max_workers)
        simple_service_pb2_grpc.add_SimpleServiceServicer_to_server(
            GrpcSimpleService(), self.server)

    def get_service_type_name(self):
        return simple_service_pb2.DESCRIPTOR.services_by_name['SimpleService'].full_name


class GrpcServerNode(fel.NodeLifecycle):
    def __init__(self, simple_service_flag):
        super().__init__()
        self.service = simple_service_flag.service_flag.value
        grpc_simple_server = GrpcSimplerServer(1)
        self.server = fel.communication.ServiceServer(grpc_simple_server)

    def on_init(self):
        print("GrpcServerNode.on_init()")

    def on_did_create(self, node_info):
        print("GrpcServerNode.on_did_create()")
        self.node_info = node_info
        self.request_register()

    def on_error(self, status):
        print("GrpcServerNode.on_error()")
        fel.log(fel.ERROR, status.error_message())

    def on_request_register(self, status):
        print("GrpcServerNode.on_request_register()")
        fel.log_if(fel.ERROR, not status.ok(), status.error_message())

    def on_request_unregister(self, status):
        print("GrpcServerNode.on_request_unregister()")
        fel.log_if(fel.ERROR, not status.ok(), status.error_message())

    def request_register(self):
        self.server.request_register(
            self.node_info, self.service, self.on_request_register)

    def request_unregister(self):
        self.server.request_unregister(
            self.node_info, self.service, self.on_request_unregister)
