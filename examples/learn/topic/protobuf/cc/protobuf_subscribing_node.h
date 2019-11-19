// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXAMPLES_LEARN_TOPIC_PROTOBUF_CC_PROTOBUF_SUBSCRIBING_NODE_H_
#define EXAMPLES_LEARN_TOPIC_PROTOBUF_CC_PROTOBUF_SUBSCRIBING_NODE_H_

#include "felicia/core/communication/subscriber.h"
#include "felicia/core/node/node_lifecycle.h"

#include "examples/learn/topic/protobuf/simple_message.pb.h"
#include "examples/learn/topic/topic_create_flag.h"

namespace felicia {

class ProtobufSubscribingNode : public NodeLifecycle {
 public:
  explicit ProtobufSubscribingNode(const TopicCreateFlag& topic_create_flag);

  // NodeLifecycle methods
  void OnInit() override;
  void OnDidCreate(NodeInfo node_info) override;
  void OnError(Status s) override;

 private:
  void OnMessage(SimpleMessage&& message);
  void OnMessageError(Status s);
  void OnRequestSubscribe(Status s);
  void OnRequestUnsubscribe(Status s);

  void RequestSubscribe();
  void RequestUnsubscribe();

  NodeInfo node_info_;
  const TopicCreateFlag& topic_create_flag_;
  const std::string topic_;
  Subscriber<SimpleMessage> subscriber_;
};
}  // namespace felicia

#endif  // EXAMPLES_LEARN_TOPIC_PROTOBUF_CC_PROTOBUF_SUBSCRIBING_NODE_H_