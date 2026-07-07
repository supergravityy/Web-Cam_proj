# Web-Cam_proj

## C/C++ workspace

Directory layout:

- `code/Inc`: header files
- `code/Src`: C/C++ source files
- `build`: build outputs
- `packages`: external libraries such as OpenCV

Build and run:

```bash
make
make run
make clean
```

VS Code integration:

- `Ctrl+Shift+B`: build with Makefile
- `F5`: build and debug `build/webcam_app` with gdb

External libraries can be placed under `packages` with common layouts such as:

```text
packages/opencv/include
packages/opencv/lib
packages/opencv/lib/pkgconfig
```

The Makefile automatically scans package `include`, `lib`, `lib64`, and `pkgconfig` directories.
