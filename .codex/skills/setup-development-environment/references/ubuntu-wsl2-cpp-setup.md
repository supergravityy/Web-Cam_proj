# Ubuntu/WSL2 C++ 설정 참고 문서

이 문서는 `docs/requirements.md`에 설명된 카메라 관제 프로젝트에 사용한다.

## 필수 도구

Host 도구:

- `g++`
- `make`
- `cmake`
- `gdb`
- `pkg-config`
- `git`
- `curl`
- `unzip`
- `tar`

선택 사항이지만 권장:

- `docker`
- `docker compose`
- VS Code CLI: `code`

라이브러리:

- OpenCV
- Qt6
- Google Test

## Native Ubuntu/WSL2 설치

사용자 승인을 받은 뒤 실행한다.

```bash
sudo apt update
sudo apt install -y build-essential cmake gdb pkg-config git curl unzip tar
sudo apt install -y libopencv-dev qt6-base-dev libgtest-dev
```

RTSP/H.264 작업을 위해 multimedia package를 추가한다.

```bash
sudo apt install -y ffmpeg libavcodec-dev libavformat-dev libavutil-dev libswscale-dev
```

검증:

```bash
g++ --version
cmake --version
gdb --version
pkg-config --modversion opencv4
pkg-config --modversion Qt6Core
```

## vcpkg 설치

프로젝트 로컬 설치 위치:

```bash
git clone https://github.com/microsoft/vcpkg.git packages/vcpkg
./packages/vcpkg/bootstrap-vcpkg.sh
./packages/vcpkg/vcpkg install opencv4 qtbase gtest
```

CMake와 함께 사용:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=packages/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build
ctest --test-dir build --output-on-failure
```

vcpkg가 전역 설치되어 있다면 다음을 사용한다.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
```

## Docker 설치

명시적인 사용자 승인을 받은 경우에만 Docker를 설치한다.

```bash
sudo apt update
sudo apt install -y docker.io docker-compose-v2
sudo usermod -aG docker "$USER"
```

Group 변경은 새 login session이 필요하다. Shell을 다시 연 뒤 검증한다.

```bash
docker --version
docker compose version
docker run --rm hello-world
```

권장 project container package:

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

## VS Code 설정

권장 extension:

```bash
code --install-extension ms-vscode.cpptools
code --install-extension ms-vscode.cmake-tools
```

권장 `.vscode/settings.json`:

```json
{
  "cmake.configureOnOpen": true,
  "cmake.buildDirectory": "${workspaceFolder}/build",
  "C_Cpp.default.compileCommands": "${workspaceFolder}/build/compile_commands.json",
  "C_Cpp.default.cppStandard": "c++17"
}
```

권장 `.vscode/tasks.json` task:

- Configure: `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`
- Build: `cmake --build build`
- Test: `ctest --test-dir build --output-on-failure`

권장 debugger launch 설정:

- debugger type: `cppdbg`
- MIMode: `gdb`
- miDebuggerPath: `/usr/bin/gdb`
- preLaunchTask: CMake build task
- program: `build` 아래의 project executable

## 검증 점검표

설정 후 다음을 확인한다.

```bash
command -v g++
command -v cmake
command -v gdb
command -v make
command -v pkg-config
pkg-config --exists opencv4
pkg-config --exists Qt6Core
```

CMake 파일이 있으면 다음을 실행한다.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

Makefile만 있으면 다음을 실행한다.

```bash
make
make run
```
