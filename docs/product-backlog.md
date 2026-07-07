# 제품 백로그

이 백로그는 `docs/requirements.md`에서 도출했으며, `instruction.md`에 정의된 스크럼 프로세스를 따른다.

## 요구사항 추적성

- 개요 / Client-Server 카메라 관제 시스템: PB-001, PB-002, PB-004, PB-006, PB-009
- Client 접속 및 접속 해제: PB-004, PB-006, PB-009, PB-016
- Client 영상 스트리밍 표시: PB-008, PB-010, PB-017
- Frame rate 및 resolution 제어: PB-004, PB-007, PB-011, PB-012
- 사용자 오류 메시지: PB-005, PB-013
- Ubuntu/WSL2 개발환경: PB-003, PB-020
- CMake, g++, gdb, VS Code 작업 흐름: PB-001, PB-003, PB-015
- vcpkg 및 Docker 배포 지원: PB-018, PB-019
- OpenCV, Qt, Google Test 의존성: PB-015, PB-018, PB-020
- 설정 검증 품질 개선: PB-021
- 명령 모델 확장 안정성: PB-022
- RTSP URL 및 영상 규격: PB-023, PB-024, PB-025
- 스트리밍 오류 감지 및 자동 재접속: PB-026, PB-027
- 미결 이슈 의사결정: PB-028, PB-029, PB-030
- Server 명령 정책과 영상 정책 정합성: PB-031
- Windows/Java Server 전환 및 개발환경: PB-032, PB-033
- Spring Boot, MediaMTX, Web UI Server 구성: PB-034, PB-035, PB-036, PB-037

## 우선순위 기준

- P0: 기반 작업 또는 차단 해소 작업
- P1: 핵심 제품 동작
- P2: 중요하지만 핵심 흐름 이후에 진행 가능한 작업
- P3: 개선 또는 후순위 작업

## 에픽 PB-E01: 프로젝트 기반 구성

### PB-001 CMake 프로젝트 구조

- 상태: 완료
- 우선순위: P0
- 추정치: 5
- 모듈: Build
- 사용자 스토리: 개발자로서 Client, Server, Common, 테스트를 일관되게 빌드할 수 있도록 CMake 기반 프로젝트 구조가 필요하다.
- 인수 기준:
  - 저장소 root에 `CMakeLists.txt`가 존재한다.
  - `camera_common`, `camera_client`, `camera_server`, 테스트 target이 존재한다.
  - 빌드 산출물은 `build` 아래에 생성된다.
  - `compile_commands.json`이 생성된다.

### PB-002 디렉터리 구조 전환

- 상태: 완료
- 우선순위: P0
- 추정치: 3
- 모듈: Repository
- 사용자 스토리: 개발자로서 책임 경계가 명확하도록 codebase를 Client, Server, Common, tests로 분리하고 싶다.
- 인수 기준:
  - `code/Client`, `code/Server`, `code/Common`, `tests` 디렉터리가 존재한다.
  - 기존 `code/Inc`, `code/Src` 사용은 migration되거나 transition 상태로 문서화된다.
  - README가 실제 활성 구조를 반영한다.

### PB-003 VS Code 빌드 및 디버그 연동

- 상태: 완료
- 우선순위: P0
- 추정치: 3
- 모듈: Tooling
- 사용자 스토리: 개발자로서 로컬 개발을 효율적으로 수행하기 위해 VS Code IntelliSense, build task, gdb launch config가 필요하다.
- 인수 기준:
  - IntelliSense는 `build/compile_commands.json`을 사용한다.
  - Build task는 CMake를 호출한다.
  - Client와 Server용 Debug config가 존재한다.

## 에픽 PB-E02: Common 프로토콜 및 명령

### PB-004 명령 모델 정의

- 상태: 완료
- 우선순위: P1
- 추정치: 5
- 모듈: Common
- 사용자 스토리: 개발자로서 Client와 Server가 일관된 제어 메시지를 주고받도록 공통 명령 모델이 필요하다.
- 인수 기준:
  - connect, disconnect, frame rate, resolution 명령이 존재한다.
  - 명령 검증이 구현되어 있다.
  - 유효한 명령과 유효하지 않은 명령을 단위 테스트로 검증한다.

### PB-005 구조화된 오류 모델

- 상태: 완료
- 우선순위: P1
- 추정치: 3
- 모듈: Common
- 사용자 스토리: Client와 Server 개발자로서 실패 상황을 일관되게 전달하기 위해 공통 오류 모델이 필요하다.
- 인수 기준:
  - connection, streaming, command, unsupported setting 실패를 나타내는 오류 코드가 존재한다.
  - 오류 메시지를 사용자 표시용 문구로 변환할 수 있다.
  - 오류 변환을 단위 테스트로 검증한다.

## 에픽 PB-E03: Server

### PB-006 Client 접속 처리

- 상태: 완료
- 우선순위: P1
- 추정치: 5
- 모듈: Server
- 사용자 스토리: Server로서 연결된 Client가 stream을 수신하고 명령을 보낼 수 있도록 Client 접속을 수락하고 추적하고 싶다.
- 인수 기준:
  - Server는 Client 접속 요청을 수락한다.
  - Server는 접속 상태를 추적한다.
  - Server는 disconnect 요청을 처리한다.
  - connect 및 disconnect 흐름을 통합 테스트로 검증한다.

### PB-007 명령 처리

- 상태: 완료
- 우선순위: P1
- 추정치: 5
- 모듈: Server
- 사용자 스토리: Server로서 원격으로 카메라 설정을 제어할 수 있도록 Client 명령을 처리하고 싶다.
- 인수 기준:
  - Server는 frame rate 명령을 처리한다.
  - Server는 resolution 명령을 처리한다.
  - Server는 성공 응답 또는 구조화된 오류 응답을 반환한다.
  - 유효하지 않은 명령은 거부된다.

### PB-008 RTSP/H.264 스트리밍 Endpoint

- 우선순위: P1
- 추정치: 8
- 모듈: Server
- 사용자 스토리: Server로서 Client가 카메라 영상을 볼 수 있도록 RTSP/H.264 stream을 제공하고 싶다.
- 인수 기준:
  - Server는 stream endpoint를 제공한다.
  - Stream format은 RTSP/H.264이다.
  - Server는 stream start와 stop을 처리한다.
  - Stream 시작 실패는 구조화된 오류로 보고된다.

### PB-023 RTSP 고정 URL 규칙

- 상태: 완료
- 우선순위: P1
- 추정치: 3
- 모듈: Server
- 사용자 스토리: Client가 일관된 주소로 영상 stream에 접속할 수 있도록 Server는 고정 RTSP URL 규칙을 제공해야 한다.
- 인수 기준:
  - RTSP port는 `8554`를 사용한다.
  - RTSP path는 `/camera`를 사용한다.
  - URL 형식은 `rtsp://<server-ip>:8554/camera`이다.
  - README 또는 API 문서에 URL 규칙이 문서화되어 있다.

### PB-024 Video Format 및 Codec 정책

- 상태: 완료
- 우선순위: P1
- 추정치: 5
- 모듈: Server
- 사용자 스토리: Client가 예측 가능한 영상 stream을 수신할 수 있도록 Server는 영상 format과 codec 정책을 제공해야 한다.
- 인수 기준:
  - 기본 format은 1920x1080, 30FPS, H.264이다.
  - 지원 codec은 H.264와 MJPEG를 고려한다.
  - 지원 해상도 범위는 1280x720, 1920x1080, 3840x2160을 포함한다.
  - 지원하지 않는 format 요청은 구조화된 오류로 반환된다.

## 에픽 PB-E04: Client

### PB-009 Server 접속 UI

- 우선순위: P1
- 추정치: 5
- 모듈: Client
- 사용자 스토리: 사용자로서 카메라 세션을 제어하기 위해 Client UI에서 Server에 접속하고 접속 해제하고 싶다.
- 인수 기준:
  - UI에는 connect 및 disconnect control이 있다.
  - UI는 connection state를 표시한다.
  - UI는 connection error를 표시한다.

### PB-010 영상 스트림 표시

- 우선순위: P1
- 추정치: 8
- 모듈: Client
- 사용자 스토리: 사용자로서 카메라 feed를 모니터링하기 위해 Server 영상 stream을 보고 싶다.
- 인수 기준:
  - Client는 RTSP/H.264 stream을 수신한다.
  - Client는 Qt UI에 영상을 표시한다.
  - Stream error는 사용자에게 표시된다.

### PB-026 스트리밍 오류 감지

- 상태: 대기
- 우선순위: P1
- 추정치: 5
- 모듈: Client
- 사용자 스토리: 사용자로서 영상 표시 중 문제를 알 수 있도록 Client가 스트리밍 오류를 감지해야 한다.
- 인수 기준:
  - RTSP 연결 실패를 감지한다.
  - 스트림 끊김을 감지한다.
  - Frame Timeout을 감지한다.
  - Codec 오류를 감지한다.
  - 재접속 필요 상태를 식별한다.

### PB-027 자동 재접속 정책

- 상태: 대기
- 우선순위: P1
- 추정치: 3
- 모듈: Client
- 사용자 스토리: 사용자로서 일시적 연결 오류가 발생해도 Client가 자동으로 복구를 시도하기를 원한다.
- 인수 기준:
  - 오류 발생 시 3초 간격으로 자동 재접속을 시도한다.
  - 재접속 시도 중 UI 또는 상태 모델에 재시도 상태가 반영된다.
  - 재접속 성공과 최종 실패가 구분되어 보고된다.

### PB-011 Frame Rate 제어 UI

- 우선순위: P1
- 추정치: 3
- 모듈: Client
- 사용자 스토리: 사용자로서 stream 성능을 제어하기 위해 Client UI에서 frame rate를 변경하고 싶다.
- 인수 기준:
  - UI는 frame rate control을 제공한다.
  - Client는 frame rate command를 Server에 전송한다.
  - 성공 또는 실패가 UI에 반영된다.

### PB-012 Resolution 제어 UI

- 우선순위: P1
- 추정치: 3
- 모듈: Client
- 사용자 스토리: 사용자로서 영상 품질을 제어하기 위해 Client UI에서 stream resolution을 변경하고 싶다.
- 인수 기준:
  - UI는 resolution control을 제공한다.
  - Client는 resolution command를 Server에 전송한다.
  - 지원하지 않는 resolution 오류가 표시된다.

## 에픽 PB-E05: 오류 처리 및 관측성

### PB-013 사용자 오류 표시

- 우선순위: P1
- 추정치: 3
- 모듈: Client
- 사용자 스토리: 사용자로서 connection, stream, command 실패를 이해할 수 있도록 명확한 오류 메시지를 보고 싶다.
- 인수 기준:
  - Client는 connection error를 표시한다.
  - Client는 streaming error를 표시한다.
  - Client는 command error를 표시한다.

### PB-014 Server Logging

- 우선순위: P2
- 추정치: 3
- 모듈: Server
- 사용자 스토리: 개발자로서 문제를 빠르게 진단할 수 있도록 Server log가 concern별로 분리되기를 원한다.
- 인수 기준:
  - Log는 connection, command, streaming, device 오류를 구분한다.
  - Log에는 문제 분석에 충분한 context가 포함된다.

## 에픽 PB-E06: Testing

### PB-015 Google Test 기반 구성

- 상태: 완료
- 우선순위: P0
- 추정치: 3
- 모듈: Tests
- 사용자 스토리: 개발자로서 CMake에서 단위 테스트를 실행할 수 있도록 Google Test가 build에 연결되어야 한다.
- 인수 기준:
  - Test target이 존재한다.
  - `ctest`로 테스트를 실행할 수 있다.
  - Common 단위 테스트가 최소 1개 존재한다.

### PB-016 Client-Server 통합 테스트

- 우선순위: P2
- 추정치: 8
- 모듈: Tests
- 사용자 스토리: 개발자로서 regression을 조기에 감지하기 위해 Client-Server 흐름에 대한 통합 테스트가 필요하다.
- 인수 기준:
  - connect를 테스트한다.
  - disconnect를 테스트한다.
  - 유효한 command 1개를 테스트한다.
  - 유효하지 않은 command 1개를 테스트한다.

### PB-017 Mock Stream Test Source

- 우선순위: P2
- 추정치: 5
- 모듈: Tests
- 사용자 스토리: 개발자로서 카메라 하드웨어 없이 streaming 동작을 테스트하기 위해 mock stream source가 필요하다.
- 인수 기준:
  - Test stream source가 문서화되어 있다.
  - Client가 mock stream에 접속할 수 있다.
  - Stream failure case를 테스트할 수 있다.

### PB-025 Latency 요구사항 검증 기준

- 상태: 대기
- 우선순위: P2
- 추정치: 3
- 모듈: Tests
- 사용자 스토리: 영상 제어 품질을 판단할 수 있도록 latency 요구사항과 검증 기준이 필요하다.
- 인수 기준:
  - 최소 latency 요구는 500ms 이하로 문서화된다.
  - 권장 latency 요구는 200ms 이하로 문서화된다.
  - 실시간 제어 latency 요구는 100ms 이하로 문서화된다.
  - mock 또는 측정 가능한 테스트 전략이 정의된다.

## 에픽 PB-E07: 배포 및 설정

### PB-018 vcpkg Manifest

- 상태: 완료
- 우선순위: P1
- 추정치: 3
- 모듈: Tooling
- 사용자 스토리: 개발자로서 설정을 재현 가능하게 만들기 위해 `vcpkg.json`에 의존성이 선언되어야 한다.
- 인수 기준:
  - `vcpkg.json`은 OpenCV, Qt, GTest를 나열한다.
  - CMake는 vcpkg toolchain을 사용할 수 있다.

### PB-019 Docker 개발환경

- 우선순위: P2
- 추정치: 5
- 모듈: Tooling
- 사용자 스토리: 개발자로서 깨끗한 Ubuntu container에서 build를 수행할 수 있도록 Docker 기반 환경이 필요하다.
- 인수 기준:
  - `Dockerfile`은 필요한 build tool과 library를 설치한다.
  - `docker-compose.yml`로 dev shell을 시작할 수 있다.
  - README에 사용법이 문서화되어 있다.

### PB-020 설정 검증

- 상태: 완료
- 우선순위: P0
- 추정치: 2
- 모듈: Tooling
- 사용자 스토리: 개발자로서 누락된 tool을 조기에 감지하기 위해 setup verification script가 필요하다.
- 인수 기준:
  - Script는 compiler, CMake, gdb, pkg-config, Docker, vcpkg, OpenCV, Qt, GTest를 점검한다.
  - Script는 누락된 tool을 명확하게 보고한다.

### PB-021 설정 검증 실패 코드 정책

- 상태: 완료
- 우선순위: P2
- 추정치: 2
- 모듈: Tooling
- 사용자 스토리: Scrum Master로서 CI나 agent workflow에서 누락된 tool을 자동으로 실패 처리할 수 있도록 setup verification script의 exit code 정책이 필요하다.
- 인수 기준:
  - 필수 항목이 누락되면 script가 non-zero exit code를 반환한다.
  - 선택 항목 누락은 경고로 보고하되 필수 실패와 구분한다.
  - README 또는 setup skill 문서에 필수/선택 항목 기준이 문서화되어 있다.

### PB-022 명령 타입 확장 안전성 보강

- 상태: 완료
- 우선순위: P3
- 추정치: 2
- 모듈: Common
- 사용자 스토리: 구현 에이전트로서 향후 명령 타입이 추가될 때 `command_type()` 분기가 잘못 매핑되지 않도록 확장 안전성이 필요하다.
- 인수 기준:
  - 새 명령 타입 추가 시 compile-time 또는 test-time으로 누락 분기를 감지할 수 있다.
  - `command_type()`의 fallback성 분기가 명시적으로 제거되거나 테스트로 보호된다.
  - 명령 타입 추가 절차가 Common 테스트에 반영되어 있다.

## 에픽 PB-E08: 요구사항 의사결정

### PB-028 Client 접속 수 정책 결정

- 상태: 완료
- 우선순위: P1
- 추정치: 2
- 모듈: Architecture
- 사용자 스토리: 시스템 아키텍처를 확정하기 위해 단일 Client만 지원할지, 다중 Client 접속을 지원할지 결정해야 한다.
- 인수 기준:
  - 단일 Client 또는 다중 Client 정책이 문서화된다.
  - 결정에 따른 Server session 관리 영향이 기록된다.
  - Product Backlog의 Server 접속 처리 항목이 결정 내용에 맞게 갱신된다.

### PB-029 얼굴 인식 처리 위치 결정

- 상태: 대기
- 우선순위: P2
- 추정치: 2
- 모듈: Architecture
- 사용자 스토리: 기능 책임을 명확히 하기 위해 얼굴 인식을 Client에서 수행할지 여부를 결정해야 한다.
- 인수 기준:
  - 얼굴 인식 기능 포함 여부가 문서화된다.
  - Client 처리 또는 Server 처리 여부가 결정된다.
  - 결정 결과가 요구사항과 Product Backlog에 반영된다.

### PB-030 최대 해상도 목표 결정

- 상태: 완료
- 우선순위: P1
- 추정치: 2
- 모듈: Architecture
- 사용자 스토리: 영상 처리 성능 목표를 확정하기 위해 최대 해상도를 1080p로 제한할지 4K까지 고려할지 결정해야 한다.
- 인수 기준:
  - 최대 해상도 목표가 1080p 또는 4K로 결정된다.
  - 결정 결과가 video format 정책에 반영된다.
  - latency 요구사항과 성능 테스트 계획이 결정 결과에 맞게 갱신된다.

### PB-031 Server 명령 정책과 영상 정책 정합성 정리

- 상태: 대기
- 우선순위: P1
- 추정치: 3
- 모듈: Common, Server
- 사용자 스토리: Server 개발자로서 제어 명령으로 적용된 frame rate와 resolution이 실제 streaming video policy와 충돌하지 않도록 명령 검증과 영상 정책을 정렬해야 한다.
- 인수 기준:
  - Server command 처리에서 사용할 frame rate 및 resolution 허용 범위가 `video_policy`와 일관된다.
  - 지원하지 않는 영상 format 상태가 `SessionController::video_format()`에 저장되지 않는다.
  - PB-008 RTSP/H.264 streaming endpoint 구현 전에 정책 정합성 테스트가 존재한다.

## 에픽 PB-E09: Windows/Java Server

### PB-032 Server 기술 스택 전환 의사결정

- 상태: 완료
- 우선순위: P0
- 추정치: 3
- 모듈: Architecture
- 사용자 스토리: Scrum Master로서 기존 C++/Ubuntu Server 구현과 신규 Windows/Java/Spring Boot Server 요구사항의 관계를 확정해야 한다.
- 인수 기준:
  - 기존 C++ Server core를 유지, 폐기, 또는 Java Server로 이관할지 결정한다. 완료: C++ `camera_server_core`는 참조 구현으로 보존한다.
  - Windows D 드라이브 작업 환경 기준의 실제 repository 위치와 산출물 위치를 문서화한다. 완료: 실제 Server repository는 WSL 기준 `/mnt/d/WindowServer_20260707/untitled`, Windows 기준 `D:\WindowServer_20260707\untitled`이며 Gradle 산출물은 `build`, Spring Boot 산출물은 `build/libs`, JUnit 결과는 `build/test-results/test`와 `build/reports/tests/test`를 사용한다.
  - 다음 Sprint에서 사용할 Server 구현 언어와 build tool이 명확해야 한다. 완료: 제품 Server production path는 Java/Gradle/Spring Boot/MediaMTX/Web UI 기준이다.

### PB-033 Java/Gradle Server 프로젝트 골격 검증 및 정리

- 상태: 대기
- 우선순위: P0
- 추정치: 5
- 모듈: Server, Build
- 사용자 스토리: Server 개발자로서 Windows 환경에서 Spring Boot Server를 빌드하고 테스트할 수 있도록 D 드라이브의 기존 Java/Gradle 프로젝트 골격을 검증하고 정리해야 한다.
- 인수 기준:
  - `/mnt/d/WindowServer_20260707/untitled`의 Gradle 기반 Server project를 검증한다.
  - Spring Boot application entrypoint를 검증한다.
  - JUnit 기반 기본 테스트를 검증한다.
  - Gradle build 산출물 위치와 Spring Boot 실행 산출물 위치를 확인한다.
  - Windows D 드라이브 작업 환경 기준 실행 방법이 README 또는 별도 문서에 기록된다.

### PB-034 Spring Boot 제어 명령 API

- 상태: 대기
- 우선순위: P1
- 추정치: 5
- 모듈: Server
- 사용자 스토리: Client가 Server에 접속, 접속 해제, 화면 제어, frame rate, resolution 명령을 보낼 수 있도록 Spring Boot 기반 제어 API가 필요하다.
- 인수 기준:
  - Client connect 및 disconnect API가 존재한다.
  - frame rate 및 resolution 제어 API가 존재한다.
  - 성공 응답과 구조화된 오류 응답이 정의된다.
  - JUnit 테스트로 정상/오류 흐름을 검증한다.

### PB-035 MediaMTX 기반 RTSP/H.264 Streaming 연동

- 상태: 대기
- 우선순위: P1
- 추정치: 8
- 모듈: Server, Streaming
- 사용자 스토리: Server가 카메라로부터 영상 스트림을 수신하고 Client에 RTSP/H.264 스트림을 제공할 수 있도록 MediaMTX 연동이 필요하다.
- 인수 기준:
  - MediaMTX 실행 또는 연동 설정이 문서화된다.
  - Server는 카메라 영상 스트림 수신 상태를 추적한다.
  - Server는 Client가 접근할 RTSP/H.264 endpoint를 제공한다.
  - 스트림 시작 실패는 구조화된 오류로 보고된다.

### PB-036 관리자 Web UI

- 상태: 대기
- 우선순위: P1
- 추정치: 5
- 모듈: Server, UI
- 사용자 스토리: 관리자가 Server 상태와 오류를 확인할 수 있도록 Web UI가 필요하다.
- 인수 기준:
  - Web UI에서 Client 접속 상태를 확인할 수 있다.
  - Web UI에서 카메라 스트림 수신 상태를 확인할 수 있다.
  - Web UI에서 접속, 명령, 스트리밍 오류 메시지를 확인할 수 있다.

### PB-037 Java Server OpenCV/JUnit 개발환경 검증

- 상태: 대기
- 우선순위: P1
- 추정치: 3
- 모듈: Tooling
- 사용자 스토리: Server 개발자가 Windows/Java 환경에서 OpenCV와 JUnit을 안정적으로 사용할 수 있도록 개발환경 검증 절차가 필요하다.
- 인수 기준:
  - Java, Gradle, JUnit, OpenCV 설치 및 검증 방법이 문서화된다.
  - IntelliJ 또는 JetBrains IDE 기준 실행 방법이 문서화된다.
  - 개발환경 검증 명령이 성공/실패를 명확히 보고한다.

## 초기 제안 스프린트 1

스프린트 목표: Client-Server 기능 개발 전에 필요한 CMake 기반 프로젝트 골격과 개발 작업 흐름을 구축한다.

후보 항목:

- PB-001 CMake 프로젝트 구조
- PB-002 디렉터리 구조 전환
- PB-003 VS Code 빌드 및 디버그 연동
- PB-015 Google Test 기반 구성
- PB-020 설정 검증

## Sprint 1 완료 결과

- 완료 항목: PB-001, PB-002, PB-003, PB-015, PB-020
- 재개방 후 해결 항목: PB-002 README 활성 구조 반영
- 신규 기술부채 항목: PB-021 설정 검증 실패 코드 정책

## Sprint 2 완료 결과

- 완료 항목: PB-004, PB-005, PB-018, PB-021
- 신규 기술부채 항목: PB-022 명령 타입 확장 안전성 보강

## Sprint 3 완료 결과

- 완료 항목: PB-022, PB-023, PB-024, PB-028, PB-030
- 결정 사항: 초기 Client 접속 정책은 단일 active Client로 확정
- 결정 사항: 기본 해상도는 1080p, 최대 해상도 목표는 4K 지원으로 확정

## Sprint 4 완료 결과

- 완료 항목: PB-006, PB-007
- 신규 기술부채 항목: PB-031 Server 명령 정책과 영상 정책 정합성 정리

## Sprint 5 완료 결과

- 완료 항목: PB-032
- 결정 사항: 제품 Server production path는 Java, Gradle, Spring Boot, MediaMTX, Web UI 기반으로 확정
- 결정 사항: 기존 C++/CMake `camera_server_core`는 Sprint 4까지 검증된 세션/명령 처리 도메인 프로토타입 및 참조 구현으로 보존
- 결정 사항: C++ Client/Common 작업은 별도 Client 및 공통 개념 검증 자산으로 유지하되, Server production path에서는 Java/Gradle을 사용
- D 드라이브 문서화: 현재 Codex workspace는 `/home/sungsu/workspace/KOSTA_260707`, WSL D 드라이브 mount는 `/mnt/d`, 실제 Server repository는 `/mnt/d/WindowServer_20260707/untitled`, Windows 표기는 `D:\WindowServer_20260707\untitled`
- 산출물 문서화: Gradle build directory는 `build`, Spring Boot 산출물은 `build/libs`, JUnit 결과는 `build/test-results/test` 및 `build/reports/tests/test`, MediaMTX 설정은 `config/mediamtx.yml`을 사용
- D 드라이브 기존 작업물 상태: Sprint 5에서 생성 또는 수정하지 않았으며, 발견된 기존 Java/Gradle/Spring Boot/MediaMTX 작업 디렉터리로 기록
- 다음 Sprint 우선 후보: PB-033 Java/Gradle Server 프로젝트 골격 검증 및 정리, PB-037 Java Server OpenCV/JUnit 개발환경 검증

## Server 추가 요구사항 반영 결과

- 신규 항목: PB-032, PB-033, PB-034, PB-035, PB-036, PB-037
- PB-032 결정에 따라 PB-033 이후 Server production 구현은 Java/Gradle/Spring Boot/MediaMTX/Web UI 기준으로 진행한다.
- 기존 C++/Ubuntu/CMake Server core는 삭제하지 않고 참조 구현으로 보존한다.
