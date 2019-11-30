// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXAMPLES_LEARN_SERVICE_ROS_SRV_CC_ROS_SRV_SERVER_NODE_H_
#define EXAMPLES_LEARN_SERVICE_ROS_SRV_CC_ROS_SRV_SERVER_NODE_H_

#include "felicia/core/communication/service_server.h"
#include "felicia/core/node/node_lifecycle.h"

#include "examples/learn/service/ros_srv/SimpleService.h"
#include "examples/learn/service/simple_service_flag.h"

namespace felicia {

class RosSrvSimpleService : public rpc::Service<SimpleService> {
 public:
  void Handle(const SimpleServiceRequest* request,
              SimpleServiceResponse* response,
              StatusOnceCallback callback) override;
};

class RosSrvServerNode : public NodeLifecycle {
 public:
  explicit RosSrvServerNode(const SimpleServiceFlag& simple_service_flag);

  // NodeLifecycle methods
  void OnDidCreate(NodeInfo node_info) override;

 private:
  void RequestRegister();
  void RequestUnregister();

  NodeInfo node_info_;
  const std::string service_;
  ServiceServer<RosSrvSimpleService> server_;
};

}  // namespace felicia

#endif  // EXAMPLES_LEARN_SERVICE_GRPC_CC_ROS_SRV_SERVER_NODE_H_