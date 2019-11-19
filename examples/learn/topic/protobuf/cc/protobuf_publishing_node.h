// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXAMPLES_LEARN_TOPIC_PROTOBUF_CC_PROTOBUF_PUBLISHING_NODE_H_
#define EXAMPLES_LEARN_TOPIC_PROTOBUF_CC_PROTOBUF_PUBLISHING_NODE_H_

#include "felicia/core/channel/socket/ssl_server_context.h"
#include "felicia/core/communication/publisher.h"
#include "felicia/core/node/node_lifecycle.h"
#include "felicia/core/util/timestamp/timestamper.h"

#include "examples/learn/topic/protobuf/simple_message.pb.h"
#include "examples/learn/topic/topic_create_flag.h"

namespace felicia {

class ProtobufPublishingNode : public NodeLifecycle {
 public:
  ProtobufPublishingNode(const TopicCreateFlag& topic_create_flag,
                         SSLServerContext* ssl_server_context);

  // NodeLifecycle methods
  void OnInit() override;
  void OnDidCreate(NodeInfo node_info) override;
  void OnError(Status s) override;

 private:
  void OnPublish(ChannelDef::Type type, Status s);
  void OnRequestPublish(Status s);
  void OnRequestUnpublish(Status s);
#if defined(OS_POSIX)
  bool OnAuth(const UnixDomainServerSocket::Credentials& credentials);
#endif

  void RequestPublish();
  void RequestUnpublish();

  void RepeatingPublish();
  SimpleMessage GenerateMessage();

  NodeInfo node_info_;
  const TopicCreateFlag& topic_create_flag_;
  const std::string topic_;
  Publisher<SimpleMessage> publisher_;
  Timestamper timestamper_;
  SSLServerContext* ssl_server_context_;
};

}  // namespace felicia

#endif  // EXAMPLES_LEARN_TOPIC_PROTOBUF_CC_PROTOBUF_PUBLISHING_NODE_H_