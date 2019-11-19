// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXAMPLE_LEARN_SERVICE_SIMPLE_SERVICE_FLAG_H_
#define EXAMPLE_LEARN_SERVICE_SIMPLE_SERVICE_FLAG_H_

#include "examples/learn/service/service_create_flag.h"

namespace felicia {

class SimpleServiceFlag : public ServiceCreateFlag {
 public:
  SimpleServiceFlag();
  ~SimpleServiceFlag();

  const IntFlag* a_flag() const { return a_flag_.get(); }
  const IntFlag* b_flag() const { return b_flag_.get(); }

  bool Parse(FlagParser& parser) override;

  bool Validate() const override;

  AUTO_DEFINE_USAGE_AND_HELP_TEXT_METHODS(name_flag_, is_server_flag_,
                                          service_flag_, a_flag_, b_flag_)

 private:
  int a_;
  int b_;
  std::unique_ptr<IntFlag> a_flag_;
  std::unique_ptr<IntFlag> b_flag_;

  DISALLOW_COPY_AND_ASSIGN(SimpleServiceFlag);
};

}  // namespace felicia

#endif  // EXAMPLE_LEARN_SERVICE_SIMPLE_SERVICE_FLAG_H_