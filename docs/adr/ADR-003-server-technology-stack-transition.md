# ADR-003 Server 기술 스택 전환

## 상태

승인

## 맥락

Sprint 1-4에서는 Ubuntu/WSL2, C++, CMake 기반으로 Client, Common, Server 골격을 구성했고, `camera_server_core`에서 단일 active Client 세션과 제어 명령 처리 흐름을 검증했다.

이후 신규 Server 요구사항은 Windows 실행 환경, Java, Gradle, Spring Boot, MediaMTX, Web UI를 기준으로 정의되었다. 따라서 기존 C++ Server 구현을 계속 production Server로 확장할지, 폐기할지, 또는 Java Server 구현의 참조 자산으로 보존할지 결정이 필요하다.

현재 Codex workspace는 `/home/sungsu/workspace/KOSTA_260707`이며, WSL에서 확인된 D 드라이브 mount는 `/mnt/d`이다.

검토 중 D 드라이브에 이미 존재하는 Windows Server 작업 디렉터리 `/mnt/d/WindowServer_20260707/untitled`를 확인했다. Windows 표기는 `D:\WindowServer_20260707\untitled`이다. 해당 디렉터리에는 `build.gradle`, `settings.gradle`, Spring Boot application entrypoint, JUnit test, `docker-compose.yml`, `config/mediamtx.yml`이 존재한다. Sprint 5에서는 이 외부 디렉터리를 생성하거나 수정하지 않고, 실제 Server 작업 위치로 식별 및 문서화한다.

## 결정

앞으로 제품 Server production path는 Java, Gradle, Spring Boot 기반 Server로 진행한다.

RTSP/H.264 streaming relay 또는 media server 구성은 MediaMTX를 기준으로 검토하고, Server 운영 및 오류 확인 UI는 Web UI를 기준으로 한다. Java Server 개발환경 검증은 Windows, Gradle, JUnit, OpenCV, IntelliJ 또는 JetBrains 계열 IDE 기준으로 수행한다.

기존 C++/CMake `camera_server_core`는 즉시 삭제하지 않는다. Sprint 4까지 검증된 단일 active Client 세션, connect/disconnect, frame rate/resolution 명령 처리 도메인 프로토타입 및 참조 구현으로 보존한다. 이 구현은 Java Server API와 도메인 모델을 설계할 때 동작 기준으로 참고하되, production Server 구현 경로로 확장하지 않는다.

C++ Client/Common 작업은 별도 Client 및 공통 개념 검증 자산으로 유지한다. Client, 공통 명령 모델, 영상 정책의 C++ 검증 결과는 Java Server 요구사항 정리와 테스트 설계에 참고할 수 있지만, Server production path의 언어와 build tool은 Java/Gradle로 고정한다.

Java/Gradle Server repository 위치는 WSL 기준 `/mnt/d/WindowServer_20260707/untitled`, Windows 기준 `D:\WindowServer_20260707\untitled`로 결정한다.

Java/Gradle 산출물 위치는 다음 기준을 따른다.

- Gradle build directory: `/mnt/d/WindowServer_20260707/untitled/build`
- Spring Boot 실행 산출물: `/mnt/d/WindowServer_20260707/untitled/build/libs`
- JUnit test result: `/mnt/d/WindowServer_20260707/untitled/build/test-results/test`
- JUnit report: `/mnt/d/WindowServer_20260707/untitled/build/reports/tests/test`
- MediaMTX config: `/mnt/d/WindowServer_20260707/untitled/config/mediamtx.yml`
- MediaMTX compose file: `/mnt/d/WindowServer_20260707/untitled/docker-compose.yml`

PB-033에서는 새 프로젝트를 처음부터 생성하는 대신, 이 기존 Java/Gradle/Spring Boot 작업 디렉터리를 제품 Server 골격으로 채택할 수 있는지 검증하고 필요한 구조 정리를 수행한다.

## 결과

- PB-032 Server 기술 스택 전환 의사결정은 완료로 처리한다.
- PB-033 Java/Gradle Server 프로젝트 골격 검증 및 정리는 다음 Sprint 우선 후보로 둔다.
- PB-037 Java Server OpenCV/JUnit 개발환경 검증은 PB-033과 함께 또는 직후에 수행할 우선 후보로 둔다.
- PB-034 Spring Boot 제어 명령 API, PB-035 MediaMTX 기반 RTSP/H.264 Streaming 연동, PB-036 관리자 Web UI는 Java/Spring Boot Server 경로를 기준으로 구현한다.
- PB-008 RTSP/H.264 streaming endpoint가 Server production 구현을 의미할 때는 Java/Spring Boot/MediaMTX 경로와 정합성을 맞춘다.
- 기존 C++ `camera_server_core`는 참조 구현으로 보존하며, 삭제 또는 archive 전환이 필요하면 별도 backlog에서 결정한다.
- D 드라이브 기존 작업물은 Sprint 5 산출물로 간주하지 않는다. Sprint 5 산출물은 ADR과 요구사항/백로그/요약 문서 갱신이다.
