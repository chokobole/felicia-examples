# Object Detection

## Prerequisite

```bash
git clone https://github.com/tensorflow/models.git
```

Follow the [instructions](https://github.com/tensorflow/models/blob/master/research/object_detection/g3doc/installation.md).

```bash
pip install seaborn
```

## Build

```bash
bazel build @com_github_chokobole_felicia//felicia/core/master/rpc:master_server_main
bazel build //examples/deep_learning/object_detection:object_detection_from_camera
```

## Run

```bash
bazel-bin/examples/deep_learning/object_detection/object_detection_from_camera
```