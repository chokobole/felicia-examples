// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "examples/learn/topic/lidar/cc/rplidar/rplidar_flag.h"

#include <iostream>

#include "felicia/core/util/command_line_interface/text_style.h"

namespace felicia {

RPLidarFlag::RPLidarFlag() {
  {
    StringFlag::Builder builder(MakeValueStore(&scan_mode_));
    auto flag = builder.SetLongName("--scan_mode").Build();
    scan_mode_flag_ = std::make_unique<StringFlag>(flag);
  }
}

RPLidarFlag::~RPLidarFlag() = default;

bool RPLidarFlag::Parse(FlagParser& parser) {
  return LidarFlag::Parse(parser) || scan_mode_flag_->Parse(parser);
}

}  // namespace felicia