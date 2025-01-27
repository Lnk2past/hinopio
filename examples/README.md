I will clean this up later with some scripts/makefiles whenever, but for now just pass paths to these to `hinopio`. Lots to automate here and lots to improve in the `hinopio` executable to configure things better.

The `slang` example can be built with (assuming at root of repo):

```shell
slangc examples/example_slang/hello-world.slang -profile glsl_430 -target glsl -o examples/example_slang/hello-world.glsl -entry computeMain
```
