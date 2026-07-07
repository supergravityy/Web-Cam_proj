# 프로젝트 요약

## 1. 프로젝트 개요

이 프로젝트는 Client-Server 구조의 카메라 관제 시스템을 개발하기 위한 프로젝트이다.

주요 목표:

- Client는 Server에 접속하여 RTSP 영상 스트림을 수신한다.
- Client는 Server로 카메라 제어 명령을 송신한다.
- Server는 영상 스트리밍과 제어 명령 처리를 담당한다.
- 신규 Server 요구사항은 Windows, Java, Gradle, Spring Boot, MediaMTX, Web UI 기반을 기준으로 한다.
- 제품 Server production path는 Java/Gradle/Spring Boot/MediaMTX/Web UI 기준으로 진행한다.
- 기존 C++/CMake `camera_server_core`는 세션 및 명령 처리 도메인 프로토타입과 참조 구현으로 보존한다.
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
│   │   │   └── camera/common/
│   │   │       ├── build_info.h
│   │   │       ├── command.h
│   │   │       ├── error.h
│   │   │       └── video_policy.h
│   │   └── src/
│   │       ├── build_info.cpp
│   │       ├── command.cpp
│   │       ├── error.cpp
│   │       └── video_policy.cpp
│   ├── Server/
│   │   ├── include/
│   │   │   └── camera/server/
│   │   │       └── session_controller.h
│   │   └── src/
│   │       ├── main.cpp
│   │       └── session_controller.cpp
│   ├── Inc/
│   └── Src/
├── docs/
│   ├── adr/
│   │   ├── ADR-001-client-connection-policy.md
│   │   ├── ADR-002-video-resolution-policy.md
│   │   └── ADR-003-server-technology-stack-transition.md
│   ├── product-backlog.md
│   ├── project-summary.md
│   ├── requirements.md
│   └── sprints/
│       ├── sprint-1.md
│       ├── sprint-2.md
│       ├── sprint-3.md
│       ├── sprint-4.md
│       └── sprint-5.md
├── packages/
│   └── vcpkg/
├── tests/
│   ├── integration/
│   │   └── server_session_controller_test.cpp
│   └── unit/
│       ├── common_build_info_test.cpp
│       ├── common_command_test.cpp
│       ├── common_error_test.cpp
│       └── common_video_policy_test.cpp
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
- `code/Server`: Server 실행 파일 및 Server core session/controller 코드
- `tests/unit`: 단위 테스트
- `tests/integration`: 통합 테스트
- `code/Inc`, `code/Src`: 이전 구조 호환을 위한 전환용 디렉터리
- `build`: CMake 빌드 산출물과 `compile_commands.json`
- `packages`: vcpkg 및 외부 라이브러리 위치
- `.vscode`: VS Code IntelliSense, build task, debug 설정
- `.codex/skills`: 반복 가능한 개발환경 설정 절차

## 3. 빌드 및 실행 구조

현재 C++ Client/Common 및 C++ Server reference implementation 빌드 기준은 CMake이다.

생성된 CMake target:

- `camera_common`: 공통 라이브러리
- `camera_server_core`: Server 세션 및 명령 처리 core 라이브러리
- `camera_client`: Client 실행 파일
- `camera_server`: Server 실행 파일
- `camera_tests`: Google Test 기반 테스트 실행 파일

제품 Server production 구현은 PB-033부터 D 드라이브의 기존 Java/Gradle/Spring Boot 골격을 검증 및 정리하면서 진행한다. Sprint 5에서는 실제 Server repository와 산출물 위치를 문서화했으며 D 드라이브 파일 생성 또는 수정은 수행하지 않았다.

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

Sprint 3에서 완료된 항목:

- PB-022 명령 타입 확장 안전성 보강
- PB-023 RTSP 고정 URL 규칙
- PB-024 Video Format 및 Codec 정책
- PB-028 Client 접속 수 정책 결정
- PB-030 최대 해상도 목표 결정

Sprint 4에서 완료된 항목:

- PB-006 Client 접속 처리
- PB-007 명령 처리

Sprint 5에서 완료된 항목:

- PB-032 Server 기술 스택 전환 의사결정

남은 주요 항목:

- PB-025 Latency 요구사항 검증 기준
- PB-026 스트리밍 오류 감지
- PB-027 자동 재접속 정책
- PB-029 얼굴 인식 처리 위치 결정
- PB-031 Server 명령 정책과 영상 정책 정합성 정리
- PB-033 Java/Gradle Server 프로젝트 골격 검증 및 정리
- PB-034 Spring Boot 제어 명령 API
- PB-035 MediaMTX 기반 RTSP/H.264 Streaming 연동
- PB-036 관리자 Web UI
- PB-037 Java Server OpenCV/JUnit 개발환경 검증
- PB-008 RTSP/H.264 스트리밍 Endpoint
- PB-010 영상 스트림 표시

다음 Sprint 후보:

- PB-033 Java/Gradle Server 프로젝트 골격 검증 및 정리
- PB-037 Java Server OpenCV/JUnit 개발환경 검증
- PB-031 Server 명령 정책과 영상 정책 정합성 정리

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

## 8. Sprint 2 결과

Sprint 2 문서: `docs/sprints/sprint-2.md`

상태: 완료

완료 내용:

- Common 명령 모델 정의
- 구조화된 오류 모델 정의
- vcpkg manifest 작성
- 설정 검증 script 실패 코드 정책 보강

검증 결과:

- `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`: 통과
- `cmake --build build`: 통과
- `ctest --test-dir build --output-on-failure`: 통과, 8/8 passed
- `make test`: 통과, 8/8 passed
- `git diff --check`: 통과

검토 결과:

- Blocking finding: 없음
- Non-blocking finding: 없음
- 후속 조치: PB-022 명령 타입 확장 안전성 보강 등록

## 9. Sprint 3 결과

Sprint 3 문서: `docs/sprints/sprint-3.md`

상태: 완료

완료 내용:

- Common 영상 정책 API 추가
- RTSP 고정 URL 정책 코드화 및 문서화
- 기본 영상 format과 지원 해상도, codec 정책 코드화
- 명령 타입 확장 시 compile-time 누락 감지 보강
- Client 접속 수 정책 ADR 작성
- 최대 해상도 정책 ADR 작성

검증 결과:

- `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`: 통과
- `cmake --build build`: 통과
- `ctest --test-dir build --output-on-failure`: 통과, 13/13 passed
- `make test`: 통과, 13/13 passed
- `git diff --check`: 통과

검토 결과:

- Blocking finding: 없음
- Non-blocking finding: 없음
- 검토 에이전트 권고: 완료

## 10. Sprint 4 결과

Sprint 4 문서: `docs/sprints/sprint-4.md`

상태: 완료

완료 내용:

- `camera_server_core` 라이브러리 추가
- `camera::server::SessionController` 추가
- 단일 active Client connect/disconnect 상태 추적 구현
- 중복 connect, 다른 Client 접속 거부, inactive Client disconnect 거부 구현
- active Client의 frame rate 및 resolution 명령 처리 구현
- Server core 통합 테스트 추가

검증 결과:

- `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`: 통과
- `cmake --build build`: 통과
- `ctest --test-dir build --output-on-failure`: 통과, 21/21 passed
- `make test`: 통과, 22/22 passed
- `git diff --check`: 통과

검토 결과:

- Blocking finding: 없음
- Non-blocking finding: Server command validation과 video policy의 허용 범위 경계가 불명확함
- 조치: PB-031 Server 명령 정책과 영상 정책 정합성 정리 등록
- 추가 조치: inactive Client disconnect 회귀 테스트 추가
- 검토 에이전트 권고: 완료

## 11. Sprint 5 결과

Sprint 5 문서: `docs/sprints/sprint-5.md`

상태: 완료

완료 내용:

- Server 기술 스택 전환 ADR 작성
- 제품 Server production path를 Java/Gradle/Spring Boot/MediaMTX/Web UI 기준으로 확정
- 기존 C++/CMake `camera_server_core`를 세션 및 명령 처리 도메인 프로토타입과 참조 구현으로 보존 결정
- C++ Client/Common 작업은 별도 Client 및 공통 개념 검증 자산으로 유지 결정
- D 드라이브 실제 Server repository, Gradle 산출물 위치, 현재 Codex workspace 관계 문서화
- 다음 Sprint 우선 후보를 PB-033 Java/Gradle Server 프로젝트 골격 검증 및 정리와 PB-037 Java Server 개발환경 검증으로 정리

검증 결과:

- `git diff --check`: 통과
- `make test`: 통과, 22/22 passed

구현 검증 결과:

- Blocking finding: 없음
- Non-blocking finding: 없음

검토 결과:

- 1차 Blocking finding: D 드라이브 위치가 후보로만 기록됨, 기존 D 드라이브 Java/Gradle 작업물의 Sprint 5 범위 여부가 불명확함
- 조치: 실제 Server repository와 산출물 위치를 확정하고, D 드라이브 작업물은 Sprint 5에서 생성하지 않은 기존 외부 작업물로 문서화
- 재검토 결과: Blocking finding 없음, Non-blocking finding 없음
- 검토 에이전트 권고: 완료

## 12. 주요 문서

- `docs/requirements.md`: 요구사항 문서
- `instruction.md`: 프로젝트 전체 규칙, 디렉터리 구조, Scrum 프로세스, 템플릿
- `docs/product-backlog.md`: Product Backlog
- `docs/sprints/sprint-1.md`: Sprint 1 기록 및 종료 보고서
- `docs/sprints/sprint-2.md`: Sprint 2 기록 및 종료 보고서
- `docs/sprints/sprint-3.md`: Sprint 3 기록 및 종료 보고서
- `docs/sprints/sprint-4.md`: Sprint 4 기록 및 종료 보고서
- `docs/sprints/sprint-5.md`: Sprint 5 기록 및 종료 보고서
- `docs/adr/ADR-001-client-connection-policy.md`: Client 접속 수 정책 결정
- `docs/adr/ADR-002-video-resolution-policy.md`: 영상 해상도 정책 결정
- `docs/adr/ADR-003-server-technology-stack-transition.md`: Server 기술 스택 전환 결정
- `agent/scrum-master.md`: Scrum Master Agent 정의
- `agent/developer.md`: 구현 에이전트 정의
- `agent/reviewer.md`: 검토 에이전트 정의
- `agent/setup-manager.md`: Setup Manager Agent 정의
- `.codex/skills/setup-development-environment/SKILL.md`: 개발환경 설정 스킬

## 13. Server 추가 요구사항 요약

서버 기능:

- Client로부터 제어 명령을 수신하고 수행한다.
- Client와 접속 및 접속 해제를 처리한다.
- 화면 제어 명령으로 frame range 또는 frame rate와 resolution을 처리한다.
- Client 접속 시 카메라로부터 비디오 스트리밍을 수신한다.
- Client로 비디오 스트리밍을 송출한다.
- 문제 발생 시 관리자 Web UI 또는 Client에 메시지를 표시한다.

Server 실행 환경:

- OS: Windows
- Package/Deployment Tool: Gradle
- Server Interface: RTSP/H.264
- UI: Web UI
- Framework/Media: Spring Boot, MediaMTX

Server 개발 환경:

- OS: Windows
- 현재 Codex workspace: `/home/sungsu/workspace/KOSTA_260707`
- WSL D 드라이브 mount: `/mnt/d`
- Windows Server 실제 작업 위치: `/mnt/d/WindowServer_20260707/untitled`
- Windows 표기: `D:\WindowServer_20260707\untitled`
- Gradle build 산출물: `/mnt/d/WindowServer_20260707/untitled/build`
- Spring Boot 실행 산출물: `/mnt/d/WindowServer_20260707/untitled/build/libs`
- JUnit test result: `/mnt/d/WindowServer_20260707/untitled/build/test-results/test`
- JUnit report: `/mnt/d/WindowServer_20260707/untitled/build/reports/tests/test`
- MediaMTX config: `/mnt/d/WindowServer_20260707/untitled/config/mediamtx.yml`
- 실제 Java Server project 검증 및 구조 정리: PB-033에서 진행
- IDE: IntelliJ 또는 JetBrains 계열 IDE, Codex 또는 Claude
- Programming Language: Java
- Build Tool: Gradle
- Vision Library: OpenCV
- UI: Web
- Test: JUnit

주의 사항:

- 기존 Sprint 1-4는 C++/CMake 기반 Server core를 구축했다.
- PB-032에서 제품 Server production path는 Java/Gradle/Spring Boot/MediaMTX/Web UI 기준으로 결정했다.
- 기존 C++/CMake `camera_server_core`는 즉시 삭제하지 않고 참조 구현으로 보존한다.
- D 드라이브의 `/mnt/d/WindowServer_20260707/untitled`는 Sprint 5에서 생성하지 않은 기존 외부 작업 디렉터리이며, PB-033에서 제품 Server 골격으로 검증한다.

## 14. 기존 Video/Interface 추가 요구사항 요약

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

결정 완료 이슈:

- 초기 Client 접속 정책은 단일 active Client로 확정한다.
- 최대 해상도 목표는 기본 1080p, 최대 4K 지원으로 확정한다.
- 제품 Server production path는 Java/Gradle/Spring Boot/MediaMTX/Web UI 기준으로 확정한다.
- 기존 C++/CMake `camera_server_core`는 참조 구현으로 보존한다.

남은 미결 이슈:

- 얼굴 인식 기능을 Client에서 수행할지 여부
