# Copyright (c) 2019 The Felicia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

load("@com_github_bazelbuild_buildtools//buildifier:def.bzl", "buildifier")

package(default_visibility = [":internal"])

package_group(
    name = "internal",
    packages = [
        "//examples/...",
    ],
)

config_setting(
    name = "has_realsense",
    define_values = {
        "has_realsense": "true",
    },
    visibility = ["//visibility:public"],
)

# TODO: realsense should be built with shared library.
config_setting(
    name = "has_realsense_with_shared_library",
    define_values = {
        "has_realsense": "true",
        "use_shared_library": "true",
    },
    visibility = ["//visibility:public"],
)

config_setting(
    name = "has_rplidar",
    define_values = {
        "has_rplidar": "true",
    },
    visibility = ["//visibility:public"],
)

# TODO: rplidar should be built with shared library.
config_setting(
    name = "has_rplidar_with_shared_library",
    define_values = {
        "has_rplidar": "true",
        "use_shared_library": "true",
    },
    visibility = ["//visibility:public"],
)

config_setting(
    name = "has_zed",
    define_values = {
        "has_zed": "true",
    },
    visibility = ["//visibility:public"],
)

# TODO: zed should be built with shared library.
config_setting(
    name = "has_zed_with_shared_library",
    define_values = {
        "has_zed": "true",
        "use_shared_library": "true",
    },
    visibility = ["//visibility:public"],
)

config_setting(
    name = "has_hector_slam",
    define_values = {
        "has_hector_slam": "true",
    },
    visibility = ["//visibility:public"],
)

# TODO: hector_slam should be built with shared library.
config_setting(
    name = "has_hector_slam_with_shared_library",
    define_values = {
        "has_hector_slam": "true",
        "use_shared_library": "true",
    },
    visibility = ["//visibility:public"],
)

config_setting(
    name = "has_orb_slam2",
    define_values = {
        "has_orb_slam2": "true",
    },
    visibility = ["//visibility:public"],
)

config_setting(
    name = "use_shared_library",
    define_values = {
        "use_shared_library": "true",
    },
    visibility = ["//visibility:public"],
)

cc_import(
    name = "felicia_import_win",
    interface_library = "lib/felicia.lib",
    shared_library = "lib/felicia.dll",
)

cc_import(
    name = "felicia_import",
    shared_library = select({
        "@com_github_chokobole_felicia//felicia:mac_or_ios": "lib/libfelicia.dylib",
        "//conditions:default": "lib/libfelicia.so",
    }),
)

cc_library(
    name = "felicia",
    hdrs = glob([
        "include/felicia/**",
    ]),
    defines = [
        "COMPONENT_BUILD",
        "FEL_COMPONENT_BUILD",
    ],
    includes = [
        "include/felicia",
        "include/felicia/boringssl/src/include",
        "include/felicia/com_github_cares_cares",
        "include/felicia/com_github_eigenteam_eigen",
        "include/felicia/com_github_google_googletest/googlemock/include",
        "include/felicia/com_github_google_googletest/googletest/include",
        "include/felicia/com_github_grpc_grpc/include",
        "include/felicia/com_github_jbeder_yaml_cpp/include",
        "include/felicia/com_github_jbeder_yaml_cpp/src",
        "include/felicia/com_github_madler_zlib",
        "include/felicia/com_github_nanopb_nanopb",
        "include/felicia/com_google_libyuv/include",
        "include/felicia/com_google_protobuf/src",
        "include/felicia/jpeg_archive",
        "include/felicia/png_archive",
        "include/felicia/third_party",
        "include/felicia/third_party/chromium",
    ],
    deps = select({
        "@com_github_chokobole_felicia//felicia:windows": [
            ":felicia_import_win",
            "//external:protobuf",
        ],
        "//conditions:default": [":felicia_import"],
    }),
)

cc_library(
    name = "grpc++",
    visibility = ["//visibility:public"],
    deps = select({
        "@com_github_chokobole_felicia//felicia:s390x": ["//external:grpc++_unsecure"],
        "//conditions:default": ["//external:grpc++"],
    }),
)

buildifier(
    name = "buildifier",
)
