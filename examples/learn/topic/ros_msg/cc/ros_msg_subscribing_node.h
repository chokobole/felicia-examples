// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXAMPLES_LEARN_TOPIC_ROS_MSG_CC_ROS_MSG_SUBSCRIBING_NODE_H_
#define EXAMPLES_LEARN_TOPIC_ROS_MSG_CC_ROS_MSG_SUBSCRIBING_NODE_H_

#include "felicia/core/communication/subscriber.h"
#include "felicia/core/node/node_lifecycle.h"

#include "examples/learn/topic/ros_msg/SimpleMessage.h"
#include "examples/learn/topic/topic_create_flag.h"

namespace felicia {

class RosMsgSubscribingNode : public NodeLifecycle {
 public:
  explicit RosMsgSubscribingNode(const TopicCreateFlag& topic_create_flag);

  // NodeLifecycle methods
  void OnDidCreate(NodeInfo node_info) override;

 private:
  void OnMessage(SimpleMessage&& message);

  void RequestSubscribe();

  NodeInfo node_info_;
  const TopicCreateFlag& topic_create_flag_;
  const std::string topic_;
  Subscriber<SimpleMessage> subscriber_;
};
}  // namespace felicia

#endif  // EXAMPLES_LEARN_TOPIC_ROS_MSG_CC_ROS_MSG_SUBSCRIBING_NODE_H_