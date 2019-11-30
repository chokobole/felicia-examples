# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def load_deps():
    native.bind(
        name = "felicia",
        actual = "@com_github_chokobole_felicia//felicia:felicia",
    )

    native.bind(
        name = "felicia_py",
        actual = "@com_github_chokobole_felicia//felicia/python:felicia_py",
    )

    native.bind(
        name = "import_order_resolver",
        actual = "@com_github_chokobole_felicia//felicia/python:import_order_resolver",
    )

    # felicia libraries
    native.bind(
        name = "felicia_hector_slam",
        actual = "@com_github_chokobole_felicia_hector_slam//:hector_slam",
    )

    native.bind(
        name = "felicia_realsense",
        actual = "@com_github_chokobole_felicia_realsense//:realsense",
    )

    native.bind(
        name = "felicia_rplidar",
        actual = "@com_github_chokobole_felicia_rplidar//:rplidar",
    )

    native.bind(
        name = "felicia_zed",
        actual = "@com_github_chokobole_felicia_zed//:zed",
    )

    git_repository(
        name = "com_github_chokobole_felicia",
        remote = "https://github.com/chokobole/felicia.git",
        commit = "80dbb992529d8f2bbd059e477e0d6f09795fe359",
    )

    git_repository(
        name = "com_github_chokobole_felicia_hector_slam",
        remote = "https://github.com/chokobole/felicia-hector-slam.git",
        commit = "59575606fa166488ca67fcc2b65f0444e423336a",
    )

    git_repository(
        name = "com_github_chokobole_felicia_realsense",
        remote = "https://github.com/chokobole/felicia-realsense.git",
        commit = "8dd8e87c16df95921ef369c650aac82049b6b272",
    )

    git_repository(
        name = "com_github_chokobole_felicia_rplidar",
        remote = "https://github.com/chokobole/felicia-rplidar.git",
        commit = "cc738aa025eb284b50e63a4038cad84712593d7c",
    )

    git_repository(
        name = "com_github_chokobole_felicia_zed",
        remote = "https://github.com/chokobole/felicia-zed.git",
        commit = "85f3ce9c1fbaa97193418929a3849936ce0173ba",
    )

    http_archive(
        name = "bazel_skylib",
        sha256 = "bbccf674aa441c266df9894182d80de104cabd19be98be002f6d478aaa31574d",
        strip_prefix = "bazel-skylib-2169ae1c374aab4a09aa90e65efe1a3aad4e279b",
        urls = ["https://github.com/bazelbuild/bazel-skylib/archive/2169ae1c374aab4a09aa90e65efe1a3aad4e279b.tar.gz"],
    )
