# Lidar(RPLidar)

**Tested using A1**

Here you need three terminals, each for running the master server, publisher and subscriber.

Before beginning, let's build the binary.

```bash
bazel build --define has_rplidar=true @com_github_chokobole_felicia//felicia/core/master/rpc:master_server_main
bazel build --define has_rplidar=true //examples/learn/topic/lidar/cc:lidar_node_creator
```

Done. Now let's begin and run the server!

```bash
bazel-bin/external/com_github_chokobole_felicia/felicia/core/master/rpc/master_server_main
```

We don't explain the same we had in [README.md](/examples/learn/topic/protobuf/cc/README.md).

To start you need to input either `ip` and `tcp_port` or `serial_port` and `baudrate`.

Here try with serial communication! Maybe you should change the privilege of `serial_port` if you run on Linux.

```bash
sudo chmod 666 /dev/ttyUSB0
```

The default `baudrate` you should check out on the [web](http://www.slamtec.com/en/Support). On windows and mac, you should install the [driver](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers). The default `serial_port` might be ` /dev/cu.SLABSBtoUART` and `\\\\.\\com3` respectively.

```bash
bazel-bin/examples/learn/topic/lidar/cc/lidar_node_creator -t message -p --serial_port /dev/ttyUSB0 --baudrate 115200
```
