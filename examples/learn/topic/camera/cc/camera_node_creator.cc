// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "felicia/core/felicia_init.h"
#include "felicia/core/master/master_proxy.h"
#include "felicia/core/thread/main_thread.h"
#include "felicia/drivers/camera/camera_factory.h"

#include "examples/learn/topic/camera/cc/camera_flag.h"
#include "examples/learn/topic/camera/cc/camera_publishing_node.h"
#include "examples/learn/topic/camera/cc/camera_subscribing_node.h"

namespace felicia {

int RealMain(int argc, char* argv[]) {
  FeliciaInit();

  CameraFlag delegate;
  FlagParser parser;
  parser.set_program_name("camera_node_creator");
  if (!parser.Parse(argc, argv, &delegate)) {
    return 1;
  }

  drivers::CameraDescriptors camera_descriptors;
  Status s = drivers::CameraFactory::GetCameraDescriptors(&camera_descriptors);
  if (!s.ok()) {
    std::cerr << kRedError << s << std::endl;
    return 1;
  }

  if (delegate.device_index_flag()->is_set()) {
    if (camera_descriptors.size() <= delegate.device_index_flag()->value()) {
      std::cerr << kRedError << "Please set device_index among them.."
                << std::endl;
      std::cout << camera_descriptors;
      return 1;
    }
  }

  if (delegate.device_list_flag()->value()) {
    if (delegate.device_index_flag()->is_set()) {
      drivers::CameraFormats camera_formats;
      s = drivers::CameraFactory::GetSupportedCameraFormats(
          camera_descriptors[delegate.device_index_flag()->value()],
          &camera_formats);
      if (!s.ok()) {
        std::cerr << kRedError << s << std::endl;
        return 1;
      }
      std::cout << camera_formats;
    } else {
      std::cout << camera_descriptors;
    }
    return 0;
  }

  MasterProxy& master_proxy = MasterProxy::GetInstance();
  s = master_proxy.Start();
  if (!s.ok()) {
    std::cerr << kRedError << s << std::endl;
    return 1;
  }

  NodeInfo node_info;
  node_info.set_name(delegate.name_flag()->value());

  if (delegate.is_publishing_node_flag()->value()) {
    master_proxy.RequestRegisterNode<CameraPublishingNode>(
        node_info, delegate,
        camera_descriptors[delegate.device_index_flag()->value()]);
  } else {
    master_proxy.RequestRegisterNode<CameraSubscribingNode>(node_info,
                                                            delegate);
  }

  MainThread& main_thread = MainThread::GetInstance();
#if defined(OS_WIN)
  main_thread.InitCOM(true);
#endif
  main_thread.Run();

  return 0;
}

}  // namespace felicia

int main(int argc, char* argv[]) { return felicia::RealMain(argc, argv); }
