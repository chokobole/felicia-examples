// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXAMPLES_LEARN_TOPIC_LIDAR_CC_LIDAR_FLAG_H_
#define EXAMPLES_LEARN_TOPIC_LIDAR_CC_LIDAR_FLAG_H_

#include "examples/learn/topic/topic_create_flag.h"

namespace felicia {

class LidarFlag : public TopicCreateFlag {
 public:
  LidarFlag();
  ~LidarFlag();

  const StringFlag* serial_port_flag() const { return serial_port_flag_.get(); }
  const FloatFlag* baudrate_flag() const { return baudrate_flag_.get(); }
  const StringFlag* ip_flag() const { return ip_flag_.get(); }
  const Flag<uint16_t>* tcp_port_flag() const { return tcp_port_flag_.get(); }

  bool Parse(FlagParser& parser) override;

  bool Validate() const override;

  AUTO_DEFINE_USAGE_AND_HELP_TEXT_METHODS(is_publishing_node_flag_, name_flag_,
                                          topic_flag_, channel_type_flag_,
                                          serial_port_flag_, baudrate_flag_,
                                          ip_flag_, tcp_port_flag_)

 protected:
  std::string serial_port_;
  float buadrate_;
  std::string ip_;
  uint16_t tcp_port_;
  std::unique_ptr<StringFlag> serial_port_flag_;
  std::unique_ptr<FloatFlag> baudrate_flag_;
  std::unique_ptr<StringFlag> ip_flag_;
  std::unique_ptr<Flag<uint16_t>> tcp_port_flag_;
};

}  // namespace felicia

#endif  // EXAMPLES_LEARN_TOPIC_LIDAR_CC_LIDAR_FLAG_H_