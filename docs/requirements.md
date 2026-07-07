# 카메라 관제 시스템 요구사항 문서

## 1. 개요

본 프로젝트는 카메라 영상 스트리밍을 기반으로 하는 Client-Server 구조의 카메라 관제 시스템을 개발하는 것을 목표로 한다.

Client는 Server에 접속하여 영상 스트리밍을 수신하고, 카메라 제어 명령을 Server로 송출한다. Server는 RTSP/H.264 기반 영상 스트리밍 인터페이스를 제공하며, Client의 제어 명령에 따라 접속 제어, 화면 제어, 프레임레이트 및 해상도 제어를 수행한다.

## 2. 시스템 구조

### 2.1 전체 구조

- 시스템은 Client-Server 구조로 구성한다.
- Client는 사용자 인터페이스를 제공하고 Server와 통신한다.
- Server는 카메라 영상 스트림을 제공하고 Client의 제어 명령을 처리한다.
- 영상 스트리밍 인터페이스는 RTSP/H.264를 기준으로 한다.

### 2.2 주요 구성 요소

- Client
  - 사용자 조작 UI
  - Server 접속 및 접속 해제 요청
  - 영상 스트리밍 수신 및 표시
  - 카메라 제어 명령 송출
  - 오류 메시지 표시
- Server
  - Client 접속 처리
  - RTSP/H.264 영상 스트리밍 제공
  - Client 제어 명령 수신 및 처리
  - 카메라 프레임레이트 및 해상도 제어
  - 카메라로부터 영상 스트리밍 수신
  - 관리자 Web UI 또는 Client로 오류 메시지 표시
  - 제품 Server 구현은 Java, Gradle, Spring Boot, MediaMTX, Web UI 기반으로 진행

## 3. 기능 요구사항

### 3.1 Client 기능

#### FR-C-001 Server 접속

- Client는 사용자의 요청에 따라 Server에 접속할 수 있어야 한다.
- Client는 Server 주소 및 접속 정보를 이용하여 연결을 시도해야 한다.
- 접속 실패 시 사용자에게 오류 메시지를 표시해야 한다.

#### FR-C-002 Server 접속 해제

- Client는 사용자의 요청에 따라 Server와의 연결을 해제할 수 있어야 한다.
- 접속 해제 후 영상 수신 및 제어 명령 송출을 중단해야 한다.
- 접속 해제 결과를 UI 상태에 반영해야 한다.

#### FR-C-003 영상 스트리밍 표시

- Client는 Server 접속 후 Server로부터 송출되는 비디오 스트리밍을 화면에 표시해야 한다.
- Client는 RTSP 기반 영상 스트림 수신을 지원해야 한다.
- Client는 H.264 및 MJPEG codec 수신을 고려해야 한다.
- 영상 수신 중 오류가 발생하면 화면에 오류 메시지를 표시해야 한다.

#### FR-C-004 화면 제어

- Client는 Server에 화면 제어 명령을 송출할 수 있어야 한다.
- 화면 제어 항목에는 프레임레이트와 해상도 설정이 포함되어야 한다.
- 화면 제어 명령 처리 결과는 UI에 반영되어야 한다.

#### FR-C-005 프레임레이트 제어

- Client는 영상 프레임레이트 변경 명령을 Server에 송출할 수 있어야 한다.
- Server가 명령을 처리할 수 없는 경우 Client는 오류 메시지를 표시해야 한다.

#### FR-C-006 해상도 제어

- Client는 영상 해상도 변경 명령을 Server에 송출할 수 있어야 한다.
- 지원하지 않는 해상도 또는 변경 실패 시 Client는 오류 메시지를 표시해야 한다.

#### FR-C-007 오류 메시지 표시

- Client는 접속 실패, 스트리밍 실패, 명령 처리 실패 등 문제 발생 시 화면에 오류 메시지를 표시해야 한다.
- 오류 메시지는 사용자가 문제 상황을 이해할 수 있도록 명확하게 표현해야 한다.

#### FR-C-008 스트리밍 오류 감지

- Client는 RTSP 연결 실패를 감지해야 한다.
- Client는 스트림 끊김을 감지해야 한다.
- Client는 Frame Timeout을 감지해야 한다.
- Client는 Codec 오류를 감지해야 한다.
- Client는 재접속이 필요한 상태를 감지해야 한다.

#### FR-C-009 자동 재접속

- Client는 스트리밍 오류 또는 연결 오류 발생 시 자동 재접속을 시도해야 한다.
- 재접속 시도 간격은 3초를 기준으로 한다.
- 재접속 시도 중 UI에 현재 상태를 표시해야 한다.

### 3.2 Server 기능

#### FR-S-001 Client 접속 처리

- Server는 Client의 접속 요청을 수락할 수 있어야 한다.
- Server는 Client 접속 상태를 관리해야 한다.

#### FR-S-002 영상 스트리밍 제공

- Server는 Client에게 RTSP/H.264 기반 영상 스트리밍을 제공해야 한다.
- Server는 H.264 및 MJPEG codec 제공을 고려해야 한다.
- Server는 Client 접속 중 안정적으로 영상 스트림을 송출해야 한다.
- Server는 고정 RTSP URL 규칙을 따라야 한다.

#### FR-S-003 제어 명령 처리

- Server는 Client로부터 접속 해제, 화면 제어, 프레임레이트 제어, 해상도 제어 명령을 수신해야 한다.
- Server는 수신한 명령을 처리하고 처리 결과를 Client에 전달해야 한다.

#### FR-S-004 오류 응답

- Server는 처리할 수 없는 명령 또는 실패한 요청에 대해 오류 응답을 반환해야 한다.
- 오류 응답은 Client가 사용자에게 표시할 수 있는 형태여야 한다.

#### FR-S-005 카메라 영상 스트림 수신

- Server는 Client 접속 시 카메라로부터 영상 스트리밍을 수신해야 한다.
- Server는 수신한 카메라 영상을 Client로 스트리밍해야 한다.
- 카메라 스트림 수신 실패는 구조화된 오류로 처리해야 한다.

#### FR-S-006 관리자 Web UI 오류 표시

- Server는 문제 발생 시 관리자 Web UI 또는 Client에 오류 메시지를 표시할 수 있어야 한다.
- 오류 메시지는 접속, 명령 처리, 카메라 스트림 수신, Client 스트리밍 송출 실패를 구분해야 한다.
- 관리자 Web UI는 운영자가 Server 상태를 확인할 수 있는 형태여야 한다.

## 4. 비기능 요구사항

### 4.1 실행 환경

- 운영체제는 Ubuntu를 기준으로 한다.
- 패키지/배포 도구는 vcpkg 또는 Docker를 사용한다.
- Server 인터페이스는 RTSP/H.264를 사용한다.
- Client UI는 Qt 기반으로 구현한다.

### 4.1.1 Server 실행 환경 추가 요구사항

- Server 운영체제는 Windows를 기준으로 한다.
- Server 패키지/배포 및 빌드 도구는 Gradle을 사용한다.
- Server 인터페이스는 RTSP/H.264를 사용한다.
- Server UI는 Web UI를 사용한다.
- Server framework는 Spring Boot를 사용한다.
- RTSP streaming relay 또는 media server 구성 요소로 MediaMTX를 사용한다.
- 향후 제품 Server production path는 Java/Spring Boot Server를 기준으로 한다.
- 기존 C++/CMake `camera_server_core`는 삭제하지 않고 세션 및 명령 처리 도메인 프로토타입과 참조 구현으로 보존한다.

### 4.2 개발 환경

- 개발 운영체제는 Ubuntu 또는 WSL2를 기준으로 한다.
- IDE는 VS Code를 기준으로 하며, Copilot, Codex 또는 Claude 같은 개발 보조 도구를 사용할 수 있다.
- 프로그래밍 언어는 C++를 사용한다.
- 빌드 도구는 CMake를 사용한다.
- 패키지/배포 도구는 vcpkg 또는 Docker를 사용한다.
- 컴파일러는 g++를 사용한다.
- 디버깅 도구는 gdb를 사용한다.
- 비전 라이브러리는 OpenCV를 사용한다.
- UI 프레임워크는 Qt를 사용한다.
- 단위 테스트 프레임워크는 Google Test를 사용한다.

### 4.2.1 Server 개발 환경 추가 요구사항

- Server 개발 운영체제는 Windows를 기준으로 한다.
- 현재 작업 위치는 Windows D 드라이브 작업 환경을 고려한다.
- 현재 Codex workspace는 `/home/sungsu/workspace/KOSTA_260707`이다.
- WSL에서 확인된 D 드라이브 mount는 `/mnt/d`이다.
- Windows Server 실제 작업 위치는 WSL 기준 `/mnt/d/WindowServer_20260707/untitled`, Windows 표기 기준 `D:\WindowServer_20260707\untitled`이다.
- Gradle build 산출물은 `/mnt/d/WindowServer_20260707/untitled/build` 아래에 생성한다.
- Spring Boot 실행 산출물은 `/mnt/d/WindowServer_20260707/untitled/build/libs` 아래에 생성한다.
- Sprint 5에서는 해당 D 드라이브 작업 디렉터리를 새로 생성하거나 수정하지 않았으며, PB-033에서 기존 Java/Gradle/Spring Boot 골격을 검증 및 정리한다.
- Server IDE는 IntelliJ 또는 JetBrains 계열 IDE를 기준으로 하며, Codex 또는 Claude 같은 개발 보조 도구를 사용할 수 있다.
- Server 프로그래밍 언어는 Java를 사용한다.
- Server 빌드 도구는 Gradle을 사용한다.
- Server 비전 라이브러리는 OpenCV를 사용한다.
- Server UI는 Web 기반으로 구현한다.
- Server 테스트 프레임워크는 JUnit을 사용한다.

### 4.3 유지보수성

- Client, Server, Common 모듈은 분리하여 관리한다.
- 공통 데이터 구조와 명령 정의는 Common 모듈에 배치한다.
- 빌드 산출물은 `build` 디렉터리에 생성한다.
- 외부 라이브러리 또는 패키지는 `packages` 디렉터리 또는 vcpkg/Docker 환경으로 관리한다.
- C++ Client/Common 자산은 Client 및 공통 개념 검증 자산으로 유지한다.
- Server production 구현의 언어와 build tool은 Java/Gradle을 기준으로 한다.

### 4.4 테스트

- 주요 명령 데이터 구조와 제어 로직은 Google Test로 단위 테스트를 작성한다.
- Client와 Server의 접속, 영상 수신, 명령 처리 흐름은 통합 테스트 대상으로 관리한다.
- 오류 상황에 대한 테스트 케이스를 포함한다.

### 4.5 Video 요구사항

- Protocol: RTSP
- Codec: H.264, MJPEG
- 기본 format: 1920x1080, 30FPS, H.264
- 지원 해상도 범위:
  - 최소: 1280x720
  - 기본: 1920x1080
  - 최대: 3840x2160
- Latency 요구사항:
  - 최소 요구: 500ms 이하
  - 권장 요구: 200ms 이하
  - 실시간 제어 요구: 100ms 이하
- 제어 인터페이스는 영상 인터페이스와 분리한다.
  - Video: RTSP
  - Control: TCP JSON 또는 REST

### 4.6 Interface URL 요구사항

- RTSP Server port는 `8554`로 고정한다.
- RTSP path는 `/camera`로 고정한다.
- RTSP URL 형식은 `rtsp://<server-ip>:8554/camera`를 따른다.

### 4.7 오류 처리 및 재접속 정책

- Client는 다음 오류를 감지해야 한다.
  - RTSP 연결 실패
  - 스트림 끊김
  - Frame Timeout
  - Codec 오류
  - 재접속 필요 상태
- Client는 오류 발생 시 3초 간격으로 자동 재시도해야 한다.
- Client는 재시도 중인 상태와 최종 실패 상태를 사용자에게 표시해야 한다.

## 5. 미결 이슈

다음 항목은 구현 전 의사결정 또는 추적이 필요하다.

- 얼굴 인식 기능을 Client에서 수행할 것인지 결정해야 한다.

결정 완료 항목:

- Client 접속 수 정책은 초기 단일 active Client 지원으로 결정한다.
- 최대 해상도 목표는 기본 1080p, 최대 4K 지원으로 결정한다.
- Server production path는 Java/Gradle/Spring Boot/MediaMTX/Web UI 기반으로 결정하고, 기존 C++ `camera_server_core`는 참조 구현으로 보존한다.
- 위 결정은 `docs/adr/ADR-001-client-connection-policy.md`, `docs/adr/ADR-002-video-resolution-policy.md`, `docs/adr/ADR-003-server-technology-stack-transition.md`에서 추적한다.

## 6. 초기 개발 범위

초기 개발 단계에서는 다음 범위를 우선 구현한다.

- CMake 기반 빌드 환경 구성
- VS Code IntelliSense, build task, gdb debugger 연동
- Client/Server/Common 모듈 구조 구성
- Client의 Server 접속 및 접속 해제 명령 구조 정의
- 프레임레이트 및 해상도 제어 명령 구조 정의
- RTSP/H.264 스트리밍 수신 및 표시 기능의 최소 동작 구현
- 오류 메시지 표시 흐름 구현
- Google Test 기반 기본 단위 테스트 작성

## 7. 용어

- RTSP: Real Time Streaming Protocol
- H.264: 영상 압축 표준
- MJPEG: Motion JPEG 기반 영상 압축 방식
- Client: 영상 확인 및 제어 명령을 수행하는 사용자 프로그램
- Server: 영상 스트리밍을 제공하고 제어 명령을 처리하는 프로그램
- Frame Rate: 초당 표시되는 영상 프레임 수
- Resolution: 영상의 가로 및 세로 픽셀 크기
- Latency: 입력, 전송, 표시 사이의 지연 시간
