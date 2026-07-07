# 프로젝트 요약

## 1. 프로젝트 개요

이 프로젝트는 Client-Server 구조의 카메라 관제 시스템을 개발하기 위한 C++ 프로젝트이다.

주요 목표:

- Client는 Server에 접속하여 RTSP 영상 스트림을 수신한다.
- Client는 Server로 카메라 제어 명령을 송신한다.
- Server는 영상 스트리밍과 제어 명령 처리를 담당한다.
- Client UI는 Qt 기반으로 구현한다.
- 영상/비전 처리는 OpenCV와 FFmpeg 계열 라이브러리를 사용한다.
- 단위 테스트는 Google Test를 사용한다.
- 기본 RTSP URL은 `rtsp://<server-ip>:8554/camera` 규칙을 따른다.
- 기본 영상 format은 1920x1080, 30FPS, H.264이다.

## 2. 현재 개발 디렉터리 구조

```text
.
├── agent/
│   ├── developer.md
│   ├── reviewer.md
│   ├── scrum-master.md
│   └── setup-manager.md
├── build/
├── code/
│   ├── Client/
│   │   └── src/
│   │       └── main.cpp
│   ├── Common/
│   │   ├── include/
│   │   │   └── camera/common/build_info.h
│   │   └── src/
│   │       └── build_info.cpp
│   ├── Server/
│   │   └── src/
│   │       └── main.cpp
│   ├── Inc/
│   └── Src/
├── docs/
│   ├── product-backlog.md
│   ├── project-summary.md
│   ├── requirements.md
│   └── sprints/
│       └── sprint-1.md
├── packages/
│   └── vcpkg/
├── tests/
│   ├── integration/
│   │   └── .gitkeep
│   └── unit/
│       └── common_build_info_test.cpp
├── .codex/
│   └── skills/setup-development-environment/
├── .vscode/
│   ├── c_cpp_properties.json
│   ├── launch.json
│   └── tasks.json
├── CMakeLists.txt
├── CMakePresets.json
├── Makefile
├── README.md
├── instruction.md
└── vcpkg.json
```

디렉터리 역할:

- `code/Common`: Client와 Server가 공유하는 공통 라이브러리 코드
- `code/Client`: Client 실행 파일 코드
- `code/Server`: Server 실행 파일 코드
- `tests/unit`: 단위 테스트
- `tests/integration`: 통합 테스트
- `code/Inc`, `code/Src`: 이전 구조 호환을 위한 전환용 디렉터리
- `build`: CMake 빌드 산출물과 `compile_commands.json`
- `packages`: vcpkg 및 외부 라이브러리 위치
- `.vscode`: VS Code IntelliSense, build task, debug 설정
- `.codex/skills`: 반복 가능한 개발환경 설정 절차

## 3. 빌드 및 실행 구조

현재 빌드 기준은 CMake이다.

생성된 CMake target:

- `camera_common`: 공통 라이브러리
- `camera_client`: Client 실행 파일
- `camera_server`: Server 실행 파일
- `camera_tests`: Google Test 기반 테스트 실행 파일

CMake 명령:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

Makefile wrapper 명령:

```bash
make
make test
make run-client
make run-server
make clean
```

VS Code 설정:

- IntelliSense는 `build/compile_commands.json`을 사용한다.
- 기본 build task는 CMake build를 수행한다.
- debug config는 `camera_client`, `camera_server`를 gdb로 실행한다.

## 4. Agent 구조

Agent 정의는 `agent/` 디렉터리에 둔다.

### 4.1 Scrum Master Agent

파일: `agent/scrum-master.md`

역할:

- 요구사항에서 Product Backlog를 도출하고 유지한다.
- 우선순위와 의존성을 기준으로 Sprint Backlog를 선택한다.
- 구현 에이전트와 검토 에이전트에게 업무를 handoff한다.
- 구현 결과, 단위 테스트, 코드 리뷰, 통합 테스트, 인수 테스트 결과를 검증한다.
- Sprint 종료 보고서를 작성하고 사용자에게 다음 Sprint 진행 허락을 요청한다.
- 문제가 생기면 Product Backlog를 수정 및 재작성한 뒤 반복을 다시 시작한다.

### 4.2 구현 에이전트

파일: `agent/developer.md`

역할:

- Scrum Master가 명시적으로 handoff한 Sprint Backlog만 구현한다.
- 단위 테스트를 추가 또는 수정한다.
- 구현 결과와 단위 테스트 결과를 Scrum Master에게 보고한다.
- Product Backlog에서 스스로 업무를 선택하지 않는다.

### 4.3 검토 에이전트

파일: `agent/reviewer.md`

역할:

- Scrum Master가 handoff한 변경만 검토한다.
- 코드 리뷰, 통합 테스트, 인수 테스트를 수행한다.
- blocking finding, non-blocking finding, 테스트 결과를 Scrum Master에게 보고한다.
- 직접 수정하지 않고 검토 결과를 보고한다.

### 4.4 Setup Manager Agent

파일: `agent/setup-manager.md`

역할:

- Ubuntu/WSL2 기반 C++ 개발환경 설치와 검증을 담당한다.
- g++, CMake, gdb, OpenCV, Qt, Google Test, vcpkg, Docker, VS Code 설정을 점검한다.
- `.codex/skills/setup-development-environment` 스킬을 사용한다.

## 5. 개발 프로세스 정의

프로젝트 프로세스는 순수 agent 기반 Scrum이다.

기본 반복 흐름:

1. Scrum Master가 `docs/requirements.md`를 분석한다.
2. Scrum Master가 `docs/product-backlog.md`를 작성 또는 갱신한다.
3. 우선순위, 의존성, 준비 상태를 기준으로 Sprint Backlog를 선택한다.
4. 구현 에이전트가 Sprint Backlog를 구현하고 단위 테스트를 실행한다.
5. Scrum Master가 구현 결과와 단위 테스트 결과를 검증한다.
6. 검토 에이전트가 코드 리뷰, 통합 테스트, 인수 테스트를 수행한다.
7. Scrum Master가 검토 결과를 검증한다.
8. Sprint 종료 보고서를 작성한다.
9. 사용자에게 다음 Sprint 진행 허락을 요청한다.
10. 허락을 받으면 다음 Sprint를 반복한다.

중요 규칙:

- 구현, 단위 테스트, 검토, 통합 테스트, 인수 테스트는 사람 개입 없이 agent들이 수행한다.
- 사람에게 확인을 구하는 시점은 Sprint 종료 후 다음 Sprint 진행 승인 요청 시점이다.
- 모든 Product Backlog가 구현될 때까지 Sprint를 반복한다.
- 문제가 생기면 Product Backlog를 수정 및 재작성한 뒤 반복을 다시 시작한다.

## 6. Product Backlog 상태

Product Backlog 문서: `docs/product-backlog.md`

Sprint 1에서 완료된 항목:

- PB-001 CMake 프로젝트 구조
- PB-002 디렉터리 구조 전환
- PB-003 VS Code 빌드 및 디버그 연동
- PB-015 Google Test 기반 구성
- PB-020 설정 검증

Sprint 2에서 완료된 항목:

- PB-004 명령 모델 정의
- PB-005 구조화된 오류 모델
- PB-018 vcpkg Manifest
- PB-021 설정 검증 실패 코드 정책

새로 등록된 기술부채:

- PB-022 명령 타입 확장 안전성 보강

추가 요구사항으로 등록된 항목:

- PB-023 RTSP 고정 URL 규칙
- PB-024 Video Format 및 Codec 정책
- PB-025 Latency 요구사항 검증 기준
- PB-026 스트리밍 오류 감지
- PB-027 자동 재접속 정책
- PB-028 Client 접속 수 정책 결정
- PB-029 얼굴 인식 처리 위치 결정
- PB-030 최대 해상도 목표 결정

다음 Sprint 후보:

- PB-006 Client 접속 처리
- PB-007 명령 처리
- PB-023 RTSP 고정 URL 규칙
- PB-024 Video Format 및 Codec 정책
- PB-028 Client 접속 수 정책 결정
- PB-030 최대 해상도 목표 결정

## 7. Sprint 1 결과

Sprint 1 문서: `docs/sprints/sprint-1.md`

상태: 완료

완료 내용:

- CMake 기반 프로젝트 골격 생성
- `camera_common`, `camera_client`, `camera_server`, `camera_tests` target 구성
- Client, Server, Common, Tests 디렉터리 구조 생성
- Google Test 기반 baseline unit test 추가
- VS Code IntelliSense, build task, gdb launch config 구성
- Makefile을 CMake wrapper로 정리
- setup verification script 보강
- README를 현재 활성 구조 기준으로 갱신

검증 결과:

- `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`: 통과
- `cmake --build build`: 통과
- `ctest --test-dir build --output-on-failure`: 통과
- `make test`: 통과
- `bash .codex/skills/setup-development-environment/scripts/check_environment.sh`: 통과

검토 결과:

- Blocking finding: 없음
- Non-blocking finding: setup verification script가 누락 항목을 보고하지만 non-zero exit code를 반환하지 않음
- 후속 조치: PB-021로 등록

## 8. 주요 문서

- `docs/requirements.md`: 요구사항 문서
- `instruction.md`: 프로젝트 전체 규칙, 디렉터리 구조, Scrum 프로세스, 템플릿
- `docs/product-backlog.md`: Product Backlog
- `docs/sprints/sprint-1.md`: Sprint 1 기록 및 종료 보고서
- `agent/scrum-master.md`: Scrum Master Agent 정의
- `agent/developer.md`: 구현 에이전트 정의
- `agent/reviewer.md`: 검토 에이전트 정의
- `agent/setup-manager.md`: Setup Manager Agent 정의
- `.codex/skills/setup-development-environment/SKILL.md`: 개발환경 설정 스킬

## 9. 추가 요구사항 요약

Video:

- Protocol: RTSP
- Codec: H.264, MJPEG
- 기본 format: 1920x1080, 30FPS, H.264
- 지원 해상도 범위: 1280x720, 1920x1080, 3840x2160
- Latency:
  - 최소 요구: 500ms 이하
  - 권장 요구: 200ms 이하
  - 실시간 제어 요구: 100ms 이하

Interface URL:

- Port: `8554`
- Path: `/camera`
- 예: `rtsp://<server-ip>:8554/camera`

Control interface:

- Video와 Control은 분리한다.
- Video는 RTSP를 사용한다.
- Control은 TCP JSON 또는 REST를 사용한다.

오류 처리:

- Client는 RTSP 연결 실패, 스트림 끊김, Frame Timeout, Codec 오류, 재접속 필요 상태를 감지해야 한다.
- Client는 오류 발생 시 3초 간격으로 자동 재접속을 시도해야 한다.

미결 이슈:

- 단일 Client 또는 다중 Client 접속 지원 여부
- 얼굴 인식 기능을 Client에서 수행할지 여부
- 최대 해상도를 1080p로 제한할지 4K까지 고려할지 여부
