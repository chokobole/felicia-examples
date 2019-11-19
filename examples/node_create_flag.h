// Copyright (c) 2019 The Felicia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXAMPLES_NODE_CREATE_FLAG_H_
#define EXAMPLES_NODE_CREATE_FLAG_H_

#include <memory>

#include "chromium/base/macros.h"
#include "felicia/core/util/command_line_interface/flag.h"

namespace felicia {

class NodeCreateFlag : public FlagParser::Delegate {
 public:
  NodeCreateFlag();
  ~NodeCreateFlag();

  const StringFlag* name_flag() const { return name_flag_.get(); }

  bool Parse(FlagParser& parser) override;

  AUTO_DEFINE_USAGE_AND_HELP_TEXT_METHODS(name_flag_)

 protected:
  std::string name_;
  std::unique_ptr<StringFlag> name_flag_;
};

}  // namespace felicia

#endif  // EXAMPLES_NODE_CREATE_FLAG_H_