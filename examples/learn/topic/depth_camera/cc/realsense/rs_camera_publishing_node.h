// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXAMPLES_LEARN_TOPIC_DEPTH_CAMERA_CC_REALSENSE_RS_CAMERA_PUBLISHING_NODE_H_
#define EXAMPLES_LEARN_TOPIC_DEPTH_CAMERA_CC_REALSENSE_RS_CAMERA_PUBLISHING_NODE_H_

#include "felicia/core/communication/publisher.h"
#include "felicia/core/node/node_lifecycle.h"
#include "realsense/rs_camera.h"

#include "examples/learn/topic/depth_camera/cc/realsense/rs_camera_flag.h"

namespace felicia {

class RsCameraPublishingNode : public NodeLifecycle {
 public:
  RsCameraPublishingNode(const RsCameraFlag& rs_camera_flag,
                         const drivers::CameraDescriptor& camera_descriptor);

  // NodeLifecycle methods
  void OnInit() override;
  void OnDidCreate(NodeInfo node_info) override;

 private:
  void OnRequestPublish(Status s);
  void OnRequestUnpublish(Status s);

  void RequestPublish();
  void RequestUnpublish();

  void StartCamera();
  void StopCamera();

  void OnColorFrame(drivers::CameraFrame&& color_frame);
  void OnDepthFrame(drivers::DepthCameraFrame&& depth_frame);
  void OnPointcloud(map::Pointcloud&& pointcloud);
  void OnImuFrame(const drivers::ImuFrame& imu_frame);

  void OnCameraError(Status s);

  NodeInfo node_info_;
  const RsCameraFlag& rs_camera_flag_;
  const std::string color_topic_;
  const std::string depth_topic_;
  const std::string pointcloud_topic_;
  const std::string imu_topic_;
  drivers::CameraDescriptor camera_descriptor_;
  Publisher<drivers::CameraFrameMessage> color_publisher_;
  Publisher<drivers::DepthCameraFrameMessage> depth_publisher_;
  Publisher<map::PointcloudMessage> pointcloud_publisher_;
  Publisher<drivers::ImuFrameMessage> imu_publisher_;
  std::unique_ptr<drivers::RsCamera> camera_;
};

}  // namespace felicia

#endif  // EXAMPLES_LEARN_TOPIC_DEPTH_CAMERA_CC_REALSENSE_RS_CAMERA_PUBLISHING_NODE_H_