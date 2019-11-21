// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "examples/learn/topic/ros_msg/cc/ros_msg_publishing_node.h"

#include "felicia/core/master/master_proxy.h"
#include "felicia/core/thread/main_thread.h"

namespace felicia {

RosMsgPublishingNode::RosMsgPublishingNode(
    const TopicCreateFlag& topic_create_flag)
    : topic_create_flag_(topic_create_flag),
      topic_(topic_create_flag_.topic_flag()->value()) {}

void RosMsgPublishingNode::OnDidCreate(NodeInfo node_info) {
  node_info_ = std::move(node_info);
  RequestPublish();
}

void RosMsgPublishingNode::OnRequestPublish(Status s) {
  LOG_IF(ERROR, !s.ok()) << s;
  RepeatingPublish();
}

void RosMsgPublishingNode::RequestPublish() {
  communication::Settings settings;
  settings.buffer_size = Bytes::FromBytes(512);

  ChannelDef::Type channel_type;
  ChannelDef::Type_Parse(topic_create_flag_.channel_type_flag()->value(),
                         &channel_type);

  publisher_.RequestPublish(
      node_info_, topic_, channel_type, settings,
      base::BindOnce(&RosMsgPublishingNode::OnRequestPublish,
                     base::Unretained(this)));
}

void RosMsgPublishingNode::RepeatingPublish() {
  publisher_.Publish(GenerateMessage());

  if (!publisher_.IsUnregistered()) {
    MainThread& main_thread = MainThread::GetInstance();
    main_thread.PostDelayedTask(
        FROM_HERE,
        base::BindOnce(&RosMsgPublishingNode::RepeatingPublish,
                       base::Unretained(this)),
        base::TimeDelta::FromSeconds(1));
  }
}

SimpleMessage RosMsgPublishingNode::GenerateMessage() {
  static int id = 0;
  base::TimeDelta timestamp = timestamper_.timestamp();
  SimpleMessage message;
  message.id = id++;
  message.timestamp = timestamp.InMicroseconds();
  message.content = "hello world";
  return message;
}

}  // namespace felicia