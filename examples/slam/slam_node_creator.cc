// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "felicia/core/felicia_init.h"
#include "felicia/core/master/master_proxy.h"
#include "felicia/core/thread/main_thread.h"

#if defined(HAS_HECTOR_SLAM)
#include "examples/slam/hector_slam/hector_slam_node.h"
#endif
#if defined(HAS_ORB_SLAM2)
#include "examples/slam/orb_slam2/orb_slam2_node.h"
#endif
#include "examples/slam/slam_node_create_flag.h"

namespace felicia {

int RealMain(int argc, char* argv[]) {
  FeliciaInit();

  SlamNodeCreateFlag delegate;
  FlagParser parser;
  parser.set_program_name("slam_node_creator");
  if (!parser.Parse(argc, argv, &delegate)) {
    return 1;
  }

  MasterProxy& master_proxy = MasterProxy::GetInstance();
  Status s = master_proxy.Start();
  if (!s.ok()) {
    std::cerr << kRedError << s << std::endl;
    return 1;
  }

  NodeInfo node_info;
  node_info.set_name(delegate.name_flag()->value());
#if defined(HAS_HECTOR_SLAM)
  if (delegate.slam_kind() == SlamNodeCreateFlag::SLAM_KIND_HECTOR_SLAM) {
    master_proxy.RequestRegisterNode<hector_slam::HectorSlamNode>(node_info,
                                                                  delegate);
  }
#endif
#if defined(HAS_ORB_SLAM2)
  else if (delegate.slam_kind() == SlamNodeCreateFlag::SLAM_KIND_ORB_SLAM2) {
    master_proxy.RequestRegisterNode<orb_slam2::OrbSlam2Node>(node_info,
                                                              delegate);
  }
#endif

  MainThread& main_thread = MainThread::GetInstance();
  main_thread.Run();

  return 0;
}

}  // namespace felicia

int main(int argc, char* argv[]) { return felicia::RealMain(argc, argv); }