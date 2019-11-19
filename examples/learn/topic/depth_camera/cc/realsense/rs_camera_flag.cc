// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "examples/learn/topic/depth_camera/cc/realsense/rs_camera_flag.h"

namespace felicia {

RsCameraFlag::RsCameraFlag(int default_width, int default_height,
                           float default_fps)
    : DepthCameraFlag(default_width, default_height, default_fps) {
  {
    StringFlag::Builder builder(MakeValueStore<std::string>(&imu_topic_));
    auto flag = builder.SetLongName("--imu_topic")
                    .SetHelp("topic to publish for imu")
                    .Build();
    imu_topic_flag_ = std::make_unique<StringFlag>(flag);
  }
}

RsCameraFlag::~RsCameraFlag() = default;

bool RsCameraFlag::Parse(FlagParser& parser) {
  return PARSE_OPTIONAL_FLAG(
      parser, name_flag_, device_list_flag_, device_index_flag_, width_flag_,
      height_flag_, fps_flag_, pixel_format_flag_, color_topic_flag_,
      depth_topic_flag_, pointcloud_topic_flag_, imu_topic_flag_);
}

}  // namespace felicia