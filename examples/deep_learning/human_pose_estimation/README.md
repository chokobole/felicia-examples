# Human Pose Estimation

**Tested on Linux**

## Prerequisite

```bash
git clone https://github.com/CMU-Perceptual-Computing-Lab/openpose.git
```

Follow the [instructions](https://github.com/CMU-Perceptual-Computing-Lab/openpose/blob/master/doc/installation.md#installation).

Don't forget to add option `-DBUILD_PYTHON=ON`.
```bash
mkdir build
cd build
# You can add optionally -DDOWNLOAD_BODY_MPI_MODEL=ON -DDOWNLOAD_BODY_COCO_MODEL=ON
cmake .. -DBUILD_PYTHON=ON
make -j
sudo make install
```

## Build

```bash
bazel build @com_github_chokobole_felicia//felicia/core/master/rpc:master_server_main
bazel build //examples/deep_learning/human_pose_estimation:human_pose_estimation_from_camera
```

## Run

```bash
export PYTHONPATH=$PYTHONPATH:/usr/local/python
LD_LIBRARY_PATH=/usr/local/lib bazel-bin/examples/deep_learning/human_pose_estimation/human_pose_estimation_from_camera --model /path/to/model
```