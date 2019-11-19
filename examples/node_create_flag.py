# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

from felicia.python.command_line_interface.flag_parser_delegate import FlagParserDelegate
import felicia_py.command_line_interface as cli


class NodeCreateFlag(FlagParserDelegate):
    def __init__(self):
        super().__init__()
        self.name_flag = cli.StringFlagBuilder().set_short_name(
            "-n").set_long_name("--name").set_help("name for node").build()

    def parse(self, flag_parser):
        return self.parse_optional_flags(flag_parser)
