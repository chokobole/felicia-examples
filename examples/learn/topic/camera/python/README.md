# Camera

In this example, you will learn how to communicate between nodes using `camera`.

Here you need three terminals, each for running the master server, publisher and subscriber.

Before beginning, let's build the binary.

```bash
bazel build @com_github_chokobole_felicia//felicia/core/master/rpc:master_server_main
bazel build //examples/learn/topic/camera/python:camera_node_creator
```

Done. Now let's begin and run the server!

```bash
bazel-bin/external/com_github_chokobole_felicia/felicia/core/master/rpc/master_server_main
```

We don't explain the same we had in [README.md](/examples/learn/topic/protobuf/python/README.md). Here we introduce new arguments to use camera! Because every camera device has a unique id, you have to pass it and it can be different per OS. For convenience, we give you a way to pass it by index. To know which index you want to run with, you should pass `-l` to the program.

```bash
bazel-bin/examples/learn/topic/camera/python/camera_node_creator -l
# For example on linux
device_list is on, it just shows a list of camera devices. If you pass -i(--device_index) with the -l then you can iterate the camera formats the device supports.
[0] display_name: UVC Camera (046d:0825) device_id: /dev/video0 model_id: 046d:0825
```

Now we know that there is an only one camera connected and let's run with it by passing `-i` with `0`.

```bash
bazel-bin/examples/learn/topic/camera/python/camera_node_creator -t message -p -i 0
```

On the subscriber side, if you type a command below, then you are successful to communicate.

```bash
bazel-bin/examples/learn/topic/camera/python/camera_node_creator -t message
```

Now look into the [camera_publishing_node.py](camera_publishing_node.py). In order to use camera, you should make a new camera instance using `CameraFactory.new_camera()` and call `init()`.

```python
def on_init(self):
    print("CameraPublishingNode.on_init()")
    self.camera = fel.drivers.CameraFactory.new_camera(self.camera_descriptor)
    fel.check(self.camera.init().ok())
```

And then you should call `start()`. **NOTE** On Windows, you should run on the `MainThread` where COM is initialized, or you have to initialize COM yourself.

```python
def on_request_publish(self, status):
    print("CameraPublishingNode.on_request_publish()")
    if status.ok():
        fel.main_thread.post_task(self.start_camera)
    else:
        fel.log(fel.ERROR, status.error_message())

def start_camera(self):
    pixel_format = PixelFormat.Value(
        self.camera_flag.pixel_format_flag.value)
    s = self.camera.start(
        fel.drivers.CameraFormat(self.camera_flag.width_flag.value,
                                 self.camera_flag.height_flag.value,
                                 pixel_format,
                                 self.camera_flag.fps_flag.value),
        self.on_camera_frame, self.on_camera_error)
```

And here you can request a `CameraFormat` you want to capture. You can check the supported formats of your camera by running command below or `CameraFactory.get_supported_camera_formats()`.

```bash
bazel-bin/examples/learn/topic/camera/python/node_creator -l -i 0
[0] 640x480(PIXEL_FORMAT_YUY2) 30.00Hz
[1] 640x480(PIXEL_FORMAT_YUY2) 25.00Hz
[2] 640x480(PIXEL_FORMAT_YUY2) 20.00Hz
[3] 640x480(PIXEL_FORMAT_YUY2) 15.00Hz
[4] 640x480(PIXEL_FORMAT_YUY2) 10.00Hz
[5] 640x480(PIXEL_FORMAT_YUY2) 5.00Hz
[6] 160x120(PIXEL_FORMAT_YUY2) 30.00Hz
[7] 160x120(PIXEL_FORMAT_YUY2) 25.00Hz
[8] 160x120(PIXEL_FORMAT_YUY2) 20.00Hz
....
[192] 1280x960(PIXEL_FORMAT_MJPEG) 30.00Hz
[193] 1280x960(PIXEL_FORMAT_MJPEG) 25.00Hz
[194] 1280x960(PIXEL_FORMAT_MJPEG) 20.00Hz
[195] 1280x960(PIXEL_FORMAT_MJPEG) 15.00Hz
[196] 1280x960(PIXEL_FORMAT_MJPEG) 10.00Hz
[197] 1280x960(PIXEL_FORMAT_MJPEG) 5.00Hz
```

In order to stop the camera, you should call `stop()`. `stop()` also apply same rule above. You should obey the rule that `start()` and `stop()` should be called on the same thread `init()`.

```python
def on_request_unpublish(self, status):
    print("CameraPublishingNode.on_request_unpublish()")
    fel.log_if(fel.ERROR, not status.ok(), status.error_message())

def stop_camera(self):
    s = self.camera.stop()
    fel.log_if(fel.ERROR, not status.ok(), status.error_message())
```
