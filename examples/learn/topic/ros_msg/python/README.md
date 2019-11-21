# ROS Message

In this example, you will learn how to communicate between nodes using `ROS Message`.

Here you need three terminals, each for running the master server, publisher and subscriber.

Before beginning, let's build the binary.

```bash
bazel build @com_github_chokobole_felicia//felicia/core/master/rpc:master_server_main
bazel build --define has_ros=true //examples/learn/topic/ros_msg/python:ros_msg_node_creator
```

Done. Now let's begin and run the server!

```bash
bazel-bin/external/com_github_chokobole_felicia/felicia/core/master/rpc/master_server_main
```

Running a ros_msg_node_creator in ***publisher*** mode:
```bash
bazel-bin/examples/learn/topic/ros_msg/python/ros_msg_node_creator -p -t message
```

Running a node ros_msg_node_creator in ***subscriber*** mode (without `-p` option):
```bash
bazel-bin/examples/learn/topic/ros_msg/python/ros_msg_node_creator -t message
```

We don't explain the same we had in [README.md](/examples/learn/topic/protobuf/python/README.md).

If you want to subscribe message from ROS, then add prefix `ros://` to topic. But in this case, topic should be resolved with namespace.

You maybe find the difference around declaration of `publisher` and `subscriber`. Because there has a difference between `protobuf` and `ROS Message` of serialization and deserialization. You have to tell `felicia` what type of implemenation you are trying. Other than that the way of using API will be perfectly same!

```python
# ros_msg_publishing_node.py
class RosMsgPublishingNode(fel.NodeLifecycle):
    def __init__(self, topic_create_flag):
        ...
        self.publisher = fel.communication.Publisher(
            SimpleMessage, TopicInfo.ROS)
        ...

# ros_msg_subscribing_node.py
class RosMsgSubscribingNode(fel.NodeLifecycle):
    def __init__(self, topic_create_flag):
        ...
        self.subscriber = fel.communication.Subscriber(
            SimpleMessage, TopicInfo.ROS)
```

We just want to explain more about bazel rule `fel_ros_msg_library`. At [BUILD](/examples/learn/topic/ros_msg/BUILD), you can see like below.

```python
fel_ros_msg_library(
    name = "simple_message_ros_msg",
    srcs = [
        "SimpleMessage.msg",
    ],
    package = "felicia",
    visibility = ["//examples:internal"],
)
```

Here `package` is mandatory. In case that your message depends on native message, such as `std_msgs`, you have to add `native_deps = ["std_msgs"]`. And if you want to let your message export to other message, then you have to add `includes=["."]`, so that bazel can tell any other mesages which depend on the messages whose package named `felicia` are here.