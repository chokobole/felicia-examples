// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "examples/learn/topic/lidar/cc/lidar_subscribing_node.h"

namespace felicia {

LidarSubscribingNode::LidarSubscribingNode(const LidarFlag& lidar_flag)
    : lidar_flag_(lidar_flag), topic_(lidar_flag_.topic_flag()->value()) {}

// NodeLifecycle methods
void LidarSubscribingNode::OnDidCreate(NodeInfo node_info) {
  node_info_ = std::move(node_info);
  RequestSubscribe();
}

void LidarSubscribingNode::OnMessage(drivers::LidarFrameMessage&& message) {
  std::cout << "LidarSubscribingNode::OnMessage()" << std::endl;
}

void LidarSubscribingNode::RequestSubscribe() {
  communication::Settings settings;
  settings.queue_size = 1;
  settings.period = base::TimeDelta::FromMilliseconds(100);
  settings.is_dynamic_buffer = true;

  subscriber_.RequestSubscribe(
      node_info_, topic_,
      ChannelDef::CHANNEL_TYPE_TCP | ChannelDef::CHANNEL_TYPE_UDP |
          ChannelDef::CHANNEL_TYPE_SHM,
      settings,
      base::BindRepeating(&LidarSubscribingNode::OnMessage,
                          base::Unretained(this)));
}

}  // namespace felicia