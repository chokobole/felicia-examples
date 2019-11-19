// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXAMPLES_LEARN_SERVICE_GRPC_CC_GRPC_SERVER_NODE_H_
#define EXAMPLES_LEARN_SERVICE_GRPC_CC_GRPC_SERVER_NODE_H_

#include "felicia/core/communication/service_server.h"
#include "felicia/core/node/node_lifecycle.h"
#include "felicia/core/rpc/service.h"

#include "examples/learn/service/grpc/simple_service.grpc.pb.h"
#include "examples/learn/service/simple_service_flag.h"

namespace felicia {

class GrpcSimpleService : public rpc::Service<grpc::SimpleService> {
 public:
  explicit GrpcSimpleService(::grpc::ServerBuilder* builder);

 private:
  void EnqueueRequests() override;

  FEL_GRPC_SERVICE_METHOD_DECLARE(GrpcSimpleService, Add);

  void Add(const AddRequest* request, AddResponse* response,
           StatusOnceCallback callback);
};

class GrpcServerNode : public NodeLifecycle {
 public:
  explicit GrpcServerNode(const SimpleServiceFlag& simple_service_flag);

  // NodeLifecycle methods
  void OnInit() override;
  void OnDidCreate(NodeInfo node_info) override;
  void OnError(Status s) override;

 private:
  void OnRequestRegister(Status s);
  void OnRequestUnregister(Status s);

  void RequestRegister();
  void RequestUnregister();

  NodeInfo node_info_;
  const std::string service_;
  ServiceServer<GrpcSimpleService> server_;
};

}  // namespace felicia

#endif  // EXAMPLES_LEARN_SERVICE_GRPC_CC_GRPC_SERVER_NODE_H_