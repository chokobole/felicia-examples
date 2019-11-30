// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXAMPLES_LEARN_SERVICE_GRPC_CC_GRPC_CLIENT_NODE_H_
#define EXAMPLES_LEARN_SERVICE_GRPC_CC_GRPC_CLIENT_NODE_H_

#include "felicia/core/communication/service_client.h"
#include "felicia/core/node/node_lifecycle.h"

#include "examples/learn/service/grpc/simple_service.grpc.pb.h"
#include "examples/learn/service/simple_service_flag.h"

namespace felicia {

class GrpcSimpleClient : public rpc::Client<grpc::SimpleService> {
 public:
  FEL_GRPC_CLIENT_METHOD_DECLARE(Add);
};

class GrpcClientNode : public NodeLifecycle {
 public:
  explicit GrpcClientNode(const SimpleServiceFlag& simple_service_flag);

  // NodeLifecycle methods
  void OnInit() override;
  void OnDidCreate(NodeInfo node_info) override;
  void OnError(Status s) override;

 private:
  void OnRequestRegister(Status s);
  void OnRequestUnegister(Status s);
  void OnConnect(ServiceInfo::Status s);
  void OnRequestAdd(const AddRequest* request, const AddResponse* response,
                    Status s);

  void RequestRegister();
  void RequestUnregister();
  void RequestAdd();

  NodeInfo node_info_;
  const SimpleServiceFlag& simple_service_flag_;
  const std::string service_;
  ServiceClient<GrpcSimpleClient> client_;
};

}  // namespace felicia

#endif  // EXAMPLES_LEARN_SERVICE_GRPC_CC_GRPC_CLIENT_NODE_H_