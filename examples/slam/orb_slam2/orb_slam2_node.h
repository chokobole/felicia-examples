// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXAMPLES_SLAM_ORB_SLAM2_ORB_SLAM2_NODE_H_
#define EXAMPLES_SLAM_ORB_SLAM2_ORB_SLAM2_NODE_H_

#include "chromium/base/strings/strcat.h"
#include "felicia/core/communication/publisher.h"
#include "felicia/core/communication/subscriber.h"
#include "felicia/core/lib/unit/geometry/pose.h"
#include "felicia/core/message/message_filter.h"
#include "felicia/core/node/node_lifecycle.h"
#include "felicia/drivers/camera/camera_frame_message.pb.h"
#include "felicia/drivers/camera/depth_camera_frame_message.pb.h"
#include "felicia/map/map_message.pb.h"

#include "System.h"

#include "examples/slam/orb_slam2_flag.h"
#include "examples/slam/slam_node_create_flag.h"

namespace felicia {
namespace orb_slam2 {

class OrbSlam2Node : public NodeLifecycle {
 public:
  typedef TimeSyncrhonizerMF<drivers::CameraFrameMessage,
                             drivers::CameraFrameMessage>
      StereoSynchronizer;
  typedef TimeSyncrhonizerMF<drivers::CameraFrameMessage,
                             drivers::DepthCameraFrameMessage>
      RGBDSynchronizer;
  typedef MessageFilter<drivers::CameraFrameMessage,
                        drivers::CameraFrameMessage>
      StereoMessageFilter;
  typedef MessageFilter<drivers::CameraFrameMessage,
                        drivers::DepthCameraFrameMessage>
      RGBDMessageFilter;

  explicit OrbSlam2Node(const SlamNodeCreateFlag& slam_node_create_flag);

  // NodeLifecycle methods
  void OnInit() override;
  void OnDidCreate(NodeInfo node_info) override;

 private:
  void OnMonoFrameMessage(drivers::CameraFrameMessage&& mono_message);
  void OnRGBDFrameMessage(drivers::CameraFrameMessage&& rgb_message,
                          drivers::DepthCameraFrameMessage&& depth_message);
  void OnStereoFrameMessage(drivers::CameraFrameMessage&& left_color_message,
                            drivers::CameraFrameMessage&& right_color_message);

  void RequestSubscribe();
  void RequestPublish();

  void Publish(cv::Mat w2c, base::TimeDelta timestamp);

  Pose3fWithTimestampMessage Pose3fWithTimestampFromCvMat(
      cv::Mat w2c, base::TimeDelta timestamp) const;

  NodeInfo node_info_;
  const SlamNodeCreateFlag& slam_node_create_flag_;
  const std::string left_color_topic_;
  const std::string right_color_topic_;
  const std::string depth_topic_;
  const std::string frame_topic_;
  const std::string map_topic_;
  const std::string pose_topic_;
  const float color_fps_;
  const float depth_fps_;
  std::unique_ptr<ORB_SLAM2::System> orb_slam2_;
  Subscriber<drivers::CameraFrameMessage> left_color_subscriber_;
  Subscriber<drivers::CameraFrameMessage> right_color_subscriber_;
  Subscriber<drivers::DepthCameraFrameMessage> depth_subscriber_;
  Publisher<drivers::CameraFrameMessage> frame_publisher_;
  Publisher<Pose3fWithTimestampMessage> pose_publisher_;
  Publisher<map::PointcloudMessage> map_publisher_;
  StereoSynchronizer stereo_synchronizer;
  RGBDSynchronizer rgbd_synchronizer;
  StereoMessageFilter stereo_filter_;
  RGBDMessageFilter rgbd_filter_;
};

}  // namespace orb_slam2
}  // namespace felicia

#endif  // EXAMPLES_SLAM_ORB_SLAM2_ORB_SLAM2_NODE_H_