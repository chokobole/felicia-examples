// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXAMPLES_LEARN_TOPIC_STEREO_CAMERA_CC_ZED_ZED_CAMERA_PUBLISHING_NODE_H_
#define EXAMPLES_LEARN_TOPIC_STEREO_CAMERA_CC_ZED_ZED_CAMERA_PUBLISHING_NODE_H_

#include "felicia/core/communication/publisher.h"
#include "felicia/core/node/node_lifecycle.h"
#include "zed/zed_camera.h"

#include "examples/learn/topic/stereo_camera/cc/stereo_camera_flag.h"

namespace felicia {

class ZedCameraPublishingNode : public NodeLifecycle {
 public:
  ZedCameraPublishingNode(
      const StereoCameraFlag& stereo_camera_flag,
      const drivers::ZedCameraDescriptor& camera_descriptor);

  // NodeLifecycle methods
  void OnInit() override;
  void OnDidCreate(NodeInfo node_info) override;

 private:
  void RequestPublish();
  void RequestUnpublish();

  void StartCamera();
  void StopCamera();

  void OnRequestPublish(Status s);
  void OnRequestUnpublish(Status s);

  void OnLeftCameraFrame(drivers::CameraFrame&& camera_frame);
  void OnRightCameraFrame(drivers::CameraFrame&& camera_frame);
  void OnDepthFrame(drivers::DepthCameraFrame&& depth_camera_frame);
  void OnPointcloud(map::Pointcloud&& pointcloud);

  void OnCameraError(Status s);

  NodeInfo node_info_;
  const StereoCameraFlag& stereo_camera_flag_;
  const std::string left_camera_topic_;
  const std::string right_camera_topic_;
  const std::string depth_topic_;
  const std::string pointcloud_topic_;
  drivers::ZedCameraDescriptor camera_descriptor_;
  Publisher<drivers::CameraFrameMessage> left_camera_publisher_;
  Publisher<drivers::CameraFrameMessage> right_camera_publisher_;
  Publisher<drivers::DepthCameraFrameMessage> depth_publisher_;
  Publisher<map::PointcloudMessage> pointcloud_publisher_;
  std::unique_ptr<drivers::ZedCamera> camera_;
};

}  // namespace felicia

#endif  // EXAMPLES_LEARN_TOPIC_STEREO_CAMERA_CC_ZED_ZED_CAMERA_PUBLISHING_NODE_H_