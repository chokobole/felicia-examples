// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXAMPLES_LEARN_TOPIC_STEREO_CAMERA_CC_STEREO_CAMERA_FLAG_H_
#define EXAMPLES_LEARN_TOPIC_STEREO_CAMERA_CC_STEREO_CAMERA_FLAG_H_

#include "examples/learn/topic/camera/cc/camera_flag.h"

namespace felicia {

class StereoCameraFlag : public CameraFlag {
 public:
  StereoCameraFlag(int default_width = kDefaultWidth,
                   int default_height = kDefaultHeight,
                   float default_fps = kDefaultFps,
                   int pixel_format = kDefaultPixelFormat);
  ~StereoCameraFlag();

  const StringFlag* left_camera_topic_flag() const {
    return left_camera_topic_flag_.get();
  }
  const StringFlag* right_camera_topic_flag() const {
    return right_camera_topic_flag_.get();
  }
  const StringFlag* depth_topic_flag() const { return depth_topic_flag_.get(); }
  const StringFlag* pointcloud_topic_flag() const {
    return pointcloud_topic_flag_.get();
  }

  bool Parse(FlagParser& parser) override;

  bool Validate() const override;

  AUTO_DEFINE_USAGE_AND_HELP_TEXT_METHODS(
      name_flag_, device_list_flag_, device_index_flag_, width_flag_,
      height_flag_, fps_flag_, pixel_format_flag_, left_camera_topic_flag_,
      right_camera_topic_flag_, depth_topic_flag_, pointcloud_topic_flag_)

 protected:
  std::string left_camera_topic_;
  std::string right_camera_topic_;
  std::string depth_topic_;
  std::string pointcloud_topic_;
  std::unique_ptr<StringFlag> left_camera_topic_flag_;
  std::unique_ptr<StringFlag> right_camera_topic_flag_;
  std::unique_ptr<StringFlag> depth_topic_flag_;
  std::unique_ptr<StringFlag> pointcloud_topic_flag_;
};

}  // namespace felicia

#endif  // EXAMPLES_LEARN_TOPIC_STEREO_CAMERA_CC_STEREO_CAMERA_FLAG_H_