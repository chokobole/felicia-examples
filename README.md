# Felicia examples

## Prerequisites

please go to [Prerequisites](https://github.com/chokobole/felicia#prerequisites) and make `bazel`, `python` and `python dependencies` ready.

## How to build

### Use Static Library

Build examples.
```bash
# On mac add --cpu darwin_x86_64
bazel //examples/...
```

### Use Shared Library

1. First follow the [How To Pakcage](https://github.com/chokobole/felicia/blob/master/README.md#how-to-package).
2. Copy the library and headers.

   ```bash
   mkdir include lib
   # Common
   cp /path/to/felicia/bazel-bin/felicia/felicia_hdrs.tar include/
   tar -xf feilcia_hdrs.tar -C include/

   # For linux
   cp /path/to/felicia/bazel-bin/felicia/libfelicia.so lib/
   # For windows
   cp /path/to/felicia/bazel-bin/felicia/felicia.dll lib/
   cp /path/to/felicia/bazel-bin/felicia/felicia.lib lib/
   # For mac
   cp /path/to/felicia/bazel-bin/felicia/libfelicia.dylib lib/
   ```
3. Build examples. **NOTE:** Watch out the `compilation_mode`, if you build library with `dbg`, then you should put `dbg` to build. It depends on how you build shared library.

    ```bash
    # On mac add --cpu darwin_x86_64
    bazel --define use_shared_library=true //examples/...
    ```