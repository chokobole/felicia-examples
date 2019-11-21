// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "examples/learn/service/ros_srv/cc/ros_srv_server_node.h"

namespace felicia {

void RosSrvSimpleService::Handle(const SimpleServiceRequest* request,
                                 SimpleServiceResponse* response,
                                 StatusOnceCallback callback) {
  int a = request->a;
  int b = request->b;

  response->sum = a + b;
  std::move(callback).Run(Status::OK());
}

RosSrvServerNode::RosSrvServerNode(const SimpleServiceFlag& simple_service_flag)
    : service_(simple_service_flag.service_flag()->value()) {}

void RosSrvServerNode::OnDidCreate(NodeInfo node_info) {
  node_info_ = std::move(node_info);
  RequestRegister();
}

void RosSrvServerNode::RequestRegister() {
  server_.RequestRegister(node_info_, service_);
}

void RosSrvServerNode::RequestUnregister() {
  server_.RequestUnregister(node_info_, service_);
}

}  // namespace felicia