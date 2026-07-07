# Ubuntu/WSL2 C++ Setup Reference

Use this reference for the camera control project described in `docs/requirements.md`.

## Required Tools

Host tools:

- `g++`
- `make`
- `cmake`
- `gdb`
- `pkg-config`
- `git`
- `curl`
- `unzip`
- `tar`

Optional but recommended:

- `docker`
- `docker compose`
- VS Code CLI: `code`

Libraries:

- OpenCV
- Qt6
- Google Test

## Native Ubuntu/WSL2 Install

Run with user approval:

```bash
sudo apt update
sudo apt install -y build-essential cmake gdb pkg-config git curl unzip tar
sudo apt install -y libopencv-dev qt6-base-dev libgtest-dev
```

For RTSP/H.264 work, add multimedia packages:

```bash
sudo apt install -y ffmpeg libavcodec-dev libavformat-dev libavutil-dev libswscale-dev
```

Verify:

```bash
g++ --version
cmake --version
gdb --version
pkg-config --modversion opencv4
pkg-config --modversion Qt6Core
```

## vcpkg Install

Project-local install location:

```bash
git clone https://github.com/microsoft/vcpkg.git packages/vcpkg
./packages/vcpkg/bootstrap-vcpkg.sh
./packages/vcpkg/vcpkg install opencv4 qtbase gtest
```

Use with CMake:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=packages/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build
ctest --test-dir build --output-on-failure
```

If vcpkg is installed globally:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
```

## Docker Install

Install Docker only with explicit user approval:

```bash
sudo apt update
sudo apt install -y docker.io docker-compose-v2
sudo usermod -aG docker "$USER"
```

The group change requires a new login session. Verify after reopening the shell:

```bash
docker --version
docker compose version
docker run --rm hello-world
```

Recommended project container packages:

```dockerfile
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        cmake \
        gdb \
        git \
        curl \
        pkg-config \
        libopencv-dev \
        qt6-base-dev \
        libgtest-dev \
        ffmpeg \
        libavcodec-dev \
        libavformat-dev \
        libavutil-dev \
        libswscale-dev \
    && rm -rf /var/lib/apt/lists/*
```

## VS Code Setup

Recommended extensions:

```bash
code --install-extension ms-vscode.cpptools
code --install-extension ms-vscode.cmake-tools
```

Recommended `.vscode/settings.json`:

```json
{
  "cmake.configureOnOpen": true,
  "cmake.buildDirectory": "${workspaceFolder}/build",
  "C_Cpp.default.compileCommands": "${workspaceFolder}/build/compile_commands.json",
  "C_Cpp.default.cppStandard": "c++17"
}
```

Recommended `.vscode/tasks.json` tasks:

- Configure: `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`
- Build: `cmake --build build`
- Test: `ctest --test-dir build --output-on-failure`

Recommended debugger launch settings:

- debugger type: `cppdbg`
- MIMode: `gdb`
- miDebuggerPath: `/usr/bin/gdb`
- preLaunchTask: CMake build task
- program: project executable under `build`

## Verification Checklist

Use these checks after setup:

```bash
command -v g++
command -v cmake
command -v gdb
command -v make
command -v pkg-config
pkg-config --exists opencv4
pkg-config --exists Qt6Core
```

If CMake files exist:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

If only a Makefile exists:

```bash
make
make run
```
