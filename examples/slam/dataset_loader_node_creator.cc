// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "felicia/core/felicia_init.h"
#include "felicia/core/master/master_proxy.h"
#include "felicia/core/thread/main_thread.h"

#include "examples/slam/dataset_flag.h"
#include "examples/slam/dataset_loader_node.h"

namespace felicia {

int RealMain(int argc, char* argv[]) {
  FeliciaInit();

  DatasetFlag delegate;
  FlagParser parser;
  parser.set_program_name("dataset_loader_node_creator");
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
  master_proxy.RequestRegisterNode<DatasetLoaderNode>(node_info, delegate);

  MainThread& main_thread = MainThread::GetInstance();
  main_thread.Run();

  return 0;
}

}  // namespace felicia

int main(int argc, char* argv[]) { return felicia::RealMain(argc, argv); }