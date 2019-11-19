// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXAMPLES_LEARN_TOPIC_ROS_MSG_CC_ROS_MSG_PUBLISHING_NODE_H_
#define EXAMPLES_LEARN_TOPIC_ROS_MSG_CC_ROS_MSG_PUBLISHING_NODE_H_

#include "felicia/core/communication/publisher.h"
#include "felicia/core/node/node_lifecycle.h"
#include "felicia/core/util/timestamp/timestamper.h"

#include "examples/learn/topic/ros_msg/SimpleMessage.h"
#include "examples/learn/topic/topic_create_flag.h"

namespace felicia {

class RosMsgPublishingNode : public NodeLifecycle {
 public:
  RosMsgPublishingNode(const TopicCreateFlag& topic_create_flag);

  // NodeLifecycle methods
  void OnDidCreate(NodeInfo node_info) override;

 private:
  void OnRequestPublish(Status s);

  void RequestPublish();

  void RepeatingPublish();
  SimpleMessage GenerateMessage();

  NodeInfo node_info_;
  const TopicCreateFlag& topic_create_flag_;
  const std::string topic_;
  Publisher<SimpleMessage> publisher_;
  Timestamper timestamper_;
};

}  // namespace felicia

#endif  // EXAMPLES_LEARN_TOPIC_ROS_MSG_CC_ROS_MSG_PUBLISHING_NODE_H_