// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXAMPLES_LEARN_SERVICE_ROS_SRV_CC_ROS_SRV_CLIENT_NODE_H_
#define EXAMPLES_LEARN_SERVICE_ROS_SRV_CC_ROS_SRV_CLIENT_NODE_H_

#include "felicia/core/communication/service_client.h"
#include "felicia/core/node/node_lifecycle.h"
#include "felicia/core/rpc/client.h"

#include "examples/learn/service/ros_srv/SimpleService.h"
#include "examples/learn/service/simple_service_flag.h"

namespace felicia {

class RosSrvClientNode : public NodeLifecycle {
 public:
  explicit RosSrvClientNode(const SimpleServiceFlag& simple_service_flag);

  // NodeLifecycle methods
  void OnDidCreate(NodeInfo node_info) override;

 private:
  void OnConnect(ServiceInfo::Status s);
  void OnRequestAdd(const SimpleServiceRequest* request,
                    SimpleServiceResponse* response, Status s);

  void RequestRegister();
  void RequestUnregister();
  void RequestAdd();

  NodeInfo node_info_;
  const SimpleServiceFlag& simple_service_flag_;
  const std::string service_;
  ServiceClient<rpc::Client<SimpleService>> client_;
};

}  // namespace felicia

#endif  // EXAMPLES_LEARN_SERVICE_ROS_SRV_CC_ROS_SRV_CLIENT_NODE_H_