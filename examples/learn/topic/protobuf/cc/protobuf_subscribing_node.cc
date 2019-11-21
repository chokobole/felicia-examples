// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "examples/learn/topic/protobuf/cc/protobuf_subscribing_node.h"

#include "felicia/core/master/master_proxy.h"
#include "felicia/core/thread/main_thread.h"

namespace felicia {

ProtobufSubscribingNode::ProtobufSubscribingNode(
    const TopicCreateFlag& topic_create_flag)
    : topic_create_flag_(topic_create_flag),
      topic_(topic_create_flag_.topic_flag()->value()) {}

void ProtobufSubscribingNode::OnInit() {
  std::cout << "ProtobufSubscribingNode::OnInit()" << std::endl;
}

void ProtobufSubscribingNode::OnDidCreate(NodeInfo node_info) {
  std::cout << "ProtobufSubscribingNode::OnDidCreate()" << std::endl;
  node_info_ = std::move(node_info);
  RequestSubscribe();

  // MainThread& main_thread = MainThread::GetInstance();
  // main_thread.PostDelayedTask(
  //     FROM_HERE,
  //     base::BindOnce(&ProtobufSubscribingNode::RequestUnsubscribe,
  //                      base::Unretained(this)),
  //     base::TimeDelta::FromSeconds(10));
}

void ProtobufSubscribingNode::OnError(Status s) {
  std::cout << "ProtobufSubscribingNode::OnError()" << std::endl;
  LOG(ERROR) << s;
}

void ProtobufSubscribingNode::OnMessage(SimpleMessage&& message) {
  std::cout << "ProtobufSubscribingNode::OnMessage()" << std::endl;
  std::cout << "message : " << message.DebugString() << std::endl;
}

void ProtobufSubscribingNode::OnMessageError(Status s) {
  std::cout << "ProtobufSubscribingNode::OnMessageError()" << std::endl;
  LOG(ERROR) << s;
}

void ProtobufSubscribingNode::OnRequestSubscribe(Status s) {
  std::cout << "ProtobufSubscribingNode::OnRequestSubscribe()" << std::endl;
  LOG_IF(ERROR, !s.ok()) << s;
}

void ProtobufSubscribingNode::OnRequestUnsubscribe(Status s) {
  std::cout << "ProtobufSubscribingNode::OnRequestUnsubscribe()" << std::endl;
  LOG_IF(ERROR, !s.ok()) << s;
}

void ProtobufSubscribingNode::RequestSubscribe() {
  communication::Settings settings;
  Bytes size = Bytes::FromBytes(512);
  settings.buffer_size = size;
  settings.channel_settings.tcp_settings.use_ssl =
      topic_create_flag_.use_ssl_flag()->value();
  settings.channel_settings.shm_settings.shm_size = size;

  subscriber_.RequestSubscribe(
      node_info_, topic_,
      ChannelDef::CHANNEL_TYPE_TCP | ChannelDef::CHANNEL_TYPE_UDP |
          ChannelDef::CHANNEL_TYPE_UDS | ChannelDef::CHANNEL_TYPE_SHM,
      settings,
      base::BindRepeating(&ProtobufSubscribingNode::OnMessage,
                          base::Unretained(this)),
      base::BindRepeating(&ProtobufSubscribingNode::OnMessageError,
                          base::Unretained(this)),
      base::BindOnce(&ProtobufSubscribingNode::OnRequestSubscribe,
                     base::Unretained(this)));
}

void ProtobufSubscribingNode::RequestUnsubscribe() {
  subscriber_.RequestUnsubscribe(
      node_info_, topic_,
      base::BindOnce(&ProtobufSubscribingNode::OnRequestUnsubscribe,
                     base::Unretained(this)));
}

}  // namespace felicia