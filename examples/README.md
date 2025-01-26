I will clean this up later with some scripts/makefiles, but build an example with (for example):

```shell
cd basic
BUILD_TYPE=Debug; cmake -B build -DCMAKE_TOOLCHAIN_FILE=../../build/$BUILD_TYPE/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE .
make -C build
```

Then run:

```shell
./build/basic_orchestrator
./build/basic_pool_orchestrator
```

