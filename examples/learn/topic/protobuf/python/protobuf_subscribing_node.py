# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import felicia_py as fel
from felicia.core.protobuf.channel_pb2 import ChannelDef

from examples.learn.topic.protobuf.simple_message_pb2 import SimpleMessage


class ProtobufSubscribingNode(fel.NodeLifecycle):
    def __init__(self, topic_create_flag):
        super().__init__()
        self.topic = topic_create_flag.topic_flag.value
        self.topic_create_flag = topic_create_flag
        self.subscriber = fel.communication.Subscriber(SimpleMessage)

    def on_init(self):
        print("ProtobufSubscribingNode.on_init()")

    def on_did_create(self, node_info):
        print("ProtobufSubscribingNode.on_did_create()")
        self.node_info = node_info
        self.request_subscribe()

    def on_error(self, status):
        print("ProtobufSubscribingNode.on_error()")
        fel.log(fel.ERROR, status.error_message())

    def on_message(self, message):
        print("ProtobufSubscribingNode.on_message()")
        print("message : {}".format(message))

    def on_message_error(self, status):
        print("ProtobufSubscribingNode.on_message_error()")
        fel.log_if(fel.ERROR, not status.ok(), status.error_message())

    def on_request_subscribe(self, status):
        print("ProtobufSubscribingNode.on_request_subscribe()")
        fel.log_if(fel.ERROR, not status.ok(), status.error_message())

    def on_request_unsubscribe(self, status):
        print("ProtobufSubscribingNode.on_request_unsubscribe()")
        fel.log_if(fel.ERROR, not status.ok(), status.error_message())

    def request_subscribe(self):
        settings = fel.communication.Settings()
        size = fel.Bytes.from_bytes(512)
        settings.buffer_size = size
        settings.channel_settings.tcp_settings.use_ssl = self.topic_create_flag.use_ssl_flag.value
        settings.channel_settings.shm_settings.shm_size = size

        self.subscriber.request_subscribe(self.node_info, self.topic,
                                          ChannelDef.CHANNEL_TYPE_TCP |
                                          ChannelDef.CHANNEL_TYPE_UDP |
                                          ChannelDef.CHANNEL_TYPE_UDS |
                                          ChannelDef.CHANNEL_TYPE_SHM,
                                          settings,
                                          self.on_message, self.on_message_error,
                                          self.on_request_subscribe)

        # fel.main_thread.post_delayed_task(
        #         self.request_unsubscribe, fel.from_seconds(10))

    def request_unsubscribe(self):
        self.subscriber.request_unsubscribe(
            self.node_info, self.topic, self.on_request_unsubscribe)
