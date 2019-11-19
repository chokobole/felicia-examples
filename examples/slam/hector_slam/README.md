# Hector SLAM

## Build

```bash
bazel build --define has_hector_slam=true //examples/slam:slam_node_creator
```

## Run

```bash
bazel-bin/examples/slam/slam_node_creator --slam_kind HectorSlam --lidar_topic lidar --pose_topic pose --map_topic map
```