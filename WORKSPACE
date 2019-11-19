workspace(name = "felicia_example")

load("//:deps.bzl", "load_deps")

load_deps()

load("@com_github_chokobole_felicia//bazel:felicia_deps.bzl", "felicia_deps")

felicia_deps()

bind(
    name = "grpc++_used",
    actual = "//:grpc++",
)

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load("@com_github_chokobole_felicia_realsense//:realsense_deps.bzl", "realsense_deps")

realsense_deps()

load("@com_github_chokobole_felicia_rplidar//:rplidar_deps.bzl", "rplidar_deps")

rplidar_deps()

load("@com_github_chokobole_felicia_zed//:zed_deps.bzl", "zed_deps")

zed_deps()

load("@io_bazel_rules_go//go:def.bzl", "go_register_toolchains", "go_rules_dependencies")
load("@com_github_bazelbuild_buildtools//buildifier:deps.bzl", "buildifier_dependencies")

go_rules_dependencies()

go_register_toolchains()

buildifier_dependencies()
