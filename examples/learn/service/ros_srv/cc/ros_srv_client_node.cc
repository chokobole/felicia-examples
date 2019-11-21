// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "examples/learn/service/ros_srv/cc/ros_srv_client_node.h"

#include "chromium/base/strings/string_number_conversions.h"
#include "felicia/core/util/command_line_interface/text_style.h"

namespace felicia {

RosSrvClientNode::RosSrvClientNode(const SimpleServiceFlag& simple_service_flag)
    : simple_service_flag_(simple_service_flag),
      service_(simple_service_flag.service_flag()->value()) {}

void RosSrvClientNode::OnDidCreate(NodeInfo node_info) {
  node_info_ = std::move(node_info);
  RequestRegister();
}

void RosSrvClientNode::OnConnect(ServiceInfo::Status s) {
  if (s == ServiceInfo::REGISTERED) {
    RequestAdd();
  } else {
    std::cout << "disconnected..." << std::endl;
  }
}

void RosSrvClientNode::RequestRegister() {
  client_.RequestRegister(node_info_, service_,
                          base::BindRepeating(&RosSrvClientNode::OnConnect,
                                              base::Unretained(this)));
}

void RosSrvClientNode::RequestUnregister() {
  client_.RequestUnregister(node_info_, service_);
}

void RosSrvClientNode::OnRequestAdd(const SimpleServiceRequest* request,
                                    SimpleServiceResponse* response, Status s) {
  if (s.ok()) {
    std::cout << base::NumberToString(request->a) << " + "
              << base::NumberToString(request->b) << " = "
              << TextStyle::Green(base::NumberToString(response->sum))
              << std::endl;
  } else {
    LOG(ERROR) << s;
  }
}

void RosSrvClientNode::RequestAdd() {
  SimpleServiceRequest* request = new SimpleServiceRequest();
  SimpleServiceResponse* response = new SimpleServiceResponse();
  request->a = simple_service_flag_.a_flag()->value();
  request->b = simple_service_flag_.b_flag()->value();
  client_->Call(
      request, response,
      base::BindOnce(&RosSrvClientNode::OnRequestAdd, base::Unretained(this),
                     base::Owned(request), base::Owned(response)));
}

}  // namespace felicia