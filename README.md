# Web-Cam_proj

## 프로젝트 문서

- [요구사항 문서](docs/requirements.md)
- [프로젝트 요약](docs/project-summary.md)
- [프로젝트 지침](instruction.md)
- [제품 백로그](docs/product-backlog.md)
- [스프린트 1 백로그](docs/sprints/sprint-1.md)
- [스프린트 2 백로그](docs/sprints/sprint-2.md)
- [스프린트 3 백로그](docs/sprints/sprint-3.md)
- [스프린트 4 백로그](docs/sprints/sprint-4.md)
- [구현 에이전트](agent/developer.md)
- [검토 에이전트](agent/reviewer.md)
- [스크럼 마스터 에이전트](agent/scrum-master.md)
- [셋업 매니저 에이전트](agent/setup-manager.md)
- [개발환경 설정 스킬](.codex/skills/setup-development-environment/SKILL.md)

## C/C++ 작업 공간

디렉터리 구조:

- `code/Common`: Client와 Server가 공유하는 공통 라이브러리 코드
- `code/Client`: Client 실행 파일 코드
- `code/Server`: Server 실행 파일 및 Server core session/controller 코드
- `tests/unit`: 단위 테스트 코드
- `tests/integration`: 통합 테스트 코드
- `code/Inc`, `code/Src`: 이전 구조 호환을 위한 전환용 디렉터리
- `build`: CMake 빌드 산출물과 `compile_commands.json`
- `packages`: OpenCV 같은 외부 라이브러리

CMake 빌드 및 테스트:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

vcpkg manifest 기반 의존성을 사용할 때는 로컬 또는 전역 vcpkg toolchain을 CMake에 전달한다. Toolchain을 지정하지 않으면 기존처럼 system package 환경의 `find_package` 결과를 사용한다.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=packages/vcpkg/scripts/buildsystems/vcpkg.cmake
```

Makefile wrapper 명령:

```bash
make
make test
make run-client
make run-server
make clean
```

VS Code 연동:

- IntelliSense: `build/compile_commands.json` 사용
- `Ctrl+Shift+B`: CMake 기반 빌드
- `F5`: gdb로 `build/bin/camera_client` 또는 `build/bin/camera_server` 디버그

## 영상 및 RTSP 정책

- RTSP URL 형식: `rtsp://<server-ip>:8554/camera`
- RTSP port: `8554`
- RTSP path: `/camera`
- 기본 영상 format: `1920x1080`, `30FPS`, `H.264`
- 지원 해상도: `1280x720`, `1920x1080`, `3840x2160`
- 지원 codec: `H.264`, `MJPEG`
- 초기 Client 접속 정책: 단일 active Client
- 최대 해상도 목표: 기본 1080p, 최대 4K 지원
- Server core는 단일 active Client의 connect/disconnect 상태를 추적하고, 연결된 active Client의 frame rate/resolution 명령만 처리한다.

외부 라이브러리는 다음과 같은 일반적인 구조로 `packages` 아래에 둘 수 있다.

```text
packages/opencv/include
packages/opencv/lib
packages/opencv/lib/pkgconfig
```
