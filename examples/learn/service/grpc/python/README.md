# Grpc Service

A 'Hello World' example of ***Python*** service programming.

In this example, you will learn how to make your own custom service and initiate communication between nodes.

Here you need three terminals, each for running the master server, publisher and subscriber.

Before beginning, let's build the binary.

```bash
bazel build @com_github_chokobole_felicia//felicia/core/master/rpc:master_server_main
bazel build //examples/learn/service/grpc/python:grpc_node_creator
```

Done. Now let's begin and run the server!

```bash
bazel-bin/external/com_github_chokobole_felicia/felicia/core/master/rpc/master_server_main
```

On the second and third shell prompts, execute the ***service client*** and ***service server***. In order to run an example node in server mode, you need to pass `-s`, a service name to serve, with an additional argument `--server` to indicate we want to make it a server. You can also pass `--name` argument to the command. Then, the master server will try to generate a node with the name unless there is an already registered node with the name.

Running a grpc_node_creator in ***server*** mode:
```bash
bazel-bin/examples/learn/service/grpc/python/grpc_node_creator -s message --server
```

Running a node grpc_node_creator in ***client*** mode (without `--server` option):
```bash
bazel-bin/examples/learn/service/grpc/python/grpc_node_creator -s message -a 1 -b 2
```

For further details, take a look at [grpc_node_creator.py](grpc_node_creator.py).

At the very first time, you have to start `MasterProxy`.

```python
master_proxy = fel.master_proxy
master_proxy.start()
```

Inside `Start()`, Do 4 things.
* Connect to grpc server.
* Start `HeartBeatSignaller`, which is responsible to make it alive by signalling heart beat to the server.
* Start `MasterNotificationWatcher`, which is responsible to watch any service source, if a node wants to request.
* Lastly if the 3 aboves are completed, then register itself to server.

If you pass `--name` to the command line, then set the name.

```python
node_info = NodeInfo()
node_info.name = delegate.name_flag.value
```

Now register Node. It depends on whether you pass the `--server` flag.

```python
if delegate.is_server_flag.value:
    master_proxy.request_register_node(
        GrpcServerNode, node_info, delegate)
else:
    master_proxy.request_register_node(
        GrpcClientNode, node_info, delegate)
```

Lastly Run MainThread. This will blocks until `stop()` is called.

```python
fel.main_thread.run()
```

Now look into the [grpc_server_node.py](grpc_server_node.py). Because `felicia` is designed with life cycle model, while registering 3 callbacks would be called. Maybe 2, if an error doens't happen.

```python
import felicia_py as fel

class GrpcServerNode(fel.NodeLifecycle):
    def __init__(self, simple_service_flag):
        super().__init__()
        self.service = simple_service_flag.service_flag.value
        grpc_simple_server = GrpcSimplerServer(1)
        self.server = fel.communication.ServiceServer(grpc_simple_server)

    def on_init(self):
        ...

    def on_did_create(self, node_info):
        ...
        self.node_info = node_info
        ...

    def on_error(self, status):
        ...
    ...
```

Inside `felicia_py.MasterProxy.request_register_node`, it tries to request grpc to register node.
Before requiest, `on_init(self)` will be called. If the given `node_info` doesn't have a name, then Server register node with a random unique name. If it succeeds to register the node, then `on_did_create(self, node_info)` is called. While this process, if it happens an error, `on_error(self, status)` will be called.


Then how is possibly serve services? If you want to serve a service, you have to use `felicia_py.ServiceServer` and it is very simple to use. Very first, you have to request to the master server that we hope to serve a service.

```python
def request_register(self):
    self.server.request_register(
        self.node_info, self.service, self.on_request_register)
```

If request is successfully delivered to the master server, then callback `on_request_publish(self, status)` will be called

```python
def on_request_register(self, status):
    print("GrpcServerNode.on_request_register()")
    fel.log_if(fel.ERROR, not status.ok(), status.error_message())
```

Okay, now we know how to request a service server to the master server, then how can we control our logic for a service? For this, you should define 2 classes, `Service` and `Server`. The one is for your custom service, and the other is for your grpc server.

```python
from felicia.python.rpc.server import Server

import examples.learn.service.grpc.simple_service_pb2_grpc as simple_service_pb2_grpc

class GrpcSimpleService(simple_service_pb2_grpc.SimpleServiceServicer):
    def Add(self, request, context):
        return simple_service_pb2.AddResponse(
            sum=request.a + request.b
        )


class SimplerServer(Server):
    def __init__(self, max_workers):
        super().__init__(max_workers)
        simple_service_pb2_grpc.add_SimpleServiceServicer_to_server(
            GrpcSimpleService(), self.server)

    def service_name(self):
        return simple_service_pb2.DESCRIPTOR.services_by_name['SimpleService'].full_name
```

To use `unregister` method, you have to do like below.

```python
def request_unregister(self):
    self.server.request_unregister(
        self.node_info, self.service, self.on_request_unregister)
```

Same with above, if request is successfully delivered to the server, then callback
will be called, too.

```python
def on_request_unregister(self, status):
        print("GrpcServerNode.on_request_unregister()")
        fel.log_if(fel.ERROR, not status.ok(), status.error_message())
```

[grpc_client_node.py](grpc_client_node.py) is very similar to above. First let's figure out how to define your client for service. It's simple you just define 2 types of methods. The one is for make `stub`, the other is to call `rpc` methods via `self.stub`.

```python
class GrpcSimpleClient(Client):
    @classmethod
    def new_stub(cls, channel):
        return simple_service_pb2_grpc.SimpleServiceStub(channel)

    def Add(self, request):
        return self.stub.Add(request)
```

Also unlike `service server` you have to pass one more callback, for inform you whether the `service client` is connected to the `service server`.

```python
def on_connect(self, service_info_status):
    print("GrpcClientNode.on_connect()")
    if (service_info_status == ServiceInfo.REGISTERED):
        self.request_add()
    else:
        print("disconnected...")

def request_register(self):
    self.client.request_register(
        self.node_info, self.service, self.on_connect, self.on_request_register)
```

If it is succesfully connected, then we have to request service! Response will be sent you back synchronously.

```python
def request_add(self):
    a = self.simple_service_flag.a_flag.value
    b = self.simple_service_flag.b_flag.value
    response = self.simple_client.Add(
        simple_service_pb2.AddRequest(a=a, b=b))
    print('{} + {} = {}'.format(a, b,
                                cli.TextStyle.green(str(response.sum))))
```

To `unregister`, it's also very similar.

```python
def on_request_unregister(self, status):
    print("GrpcClientNode.on_request_unregister()")
    fel.log_if(fel.ERROR, not status.ok(), status.error_message())

def request_unregister(self):
    self.client.request_unregister(
        self.node_info, self.service, self.on_request_unregister)
```

