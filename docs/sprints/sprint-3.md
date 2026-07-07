# 스프린트 3 백로그

## 상태

완료

## 스프린트 목표

RTSP 영상 전송 구현 전에 URL, 영상 포맷, Client 접속 수, 최대 해상도 정책을 확정하고, 공통 명령 모델의 확장 안정성을 보강한다.

## 선택 기준

Sprint 3는 새로 추가된 영상 요구사항과 미결 이슈 중 이후 Server/Client 구현을 직접 막는 정책 항목을 우선 선택한다.

선택 순서:

1. 실제 RTSP endpoint 구현의 기준이 되는 P1 Server 정책
2. Client 접속 모델과 해상도 목표처럼 아키텍처 영향을 주는 P1 결정 사항
3. Sprint 2 검토에서 등록된 명령 모델 기술부채

## 선택된 스프린트 백로그 항목

### PB-022 명령 타입 확장 안전성 보강

- 우선순위: P3
- 모듈: Common
- 구현 에이전트 인수인계: `Command` variant에 새 타입이 추가될 때 `command_type()`과 validation 분기가 묵시적으로 잘못 매핑되지 않도록 컴파일 타임 안전성을 보강한다.
- 필수 단위 테스트: 기존 명령 타입 테스트가 모두 유지되어야 한다.

### PB-023 RTSP 고정 URL 규칙

- 우선순위: P1
- 모듈: Common, Server
- 구현 에이전트 인수인계: port `8554`, path `/camera`, URL 형식 `rtsp://<server-ip>:8554/camera`를 공통 정책 API와 문서에 고정한다.
- 필수 단위 테스트: server IP 입력으로 고정 RTSP URL이 생성되는지 검증한다.

### PB-024 Video Format 및 Codec 정책

- 우선순위: P1
- 모듈: Common, Server
- 구현 에이전트 인수인계: 기본값 `1920x1080, 30FPS, H.264`, 지원 해상도 `1280x720`, `1920x1080`, `3840x2160`, 지원 codec `H.264`, `MJPEG` 정책을 공통 API와 문서에 반영한다.
- 필수 단위 테스트: 기본 format, 지원 해상도, 지원 codec 검증을 수행한다.

### PB-028 Client 접속 수 정책 결정

- 우선순위: P1
- 모듈: Architecture
- 구현 에이전트 인수인계: 초기 구현의 Client 접속 수 정책을 Architecture Decision Record로 확정하고 관련 backlog 의존성을 명시한다.
- 필수 인수 기준: 단일 Client 또는 다중 Client 중 하나가 명확히 결정되어야 한다.

### PB-030 최대 해상도 목표 결정

- 우선순위: P1
- 모듈: Architecture
- 구현 에이전트 인수인계: 기본 해상도와 최대 지원 해상도 정책을 Architecture Decision Record로 확정한다.
- 필수 인수 기준: 1080p와 4K 지원 여부가 명확히 결정되어야 한다.

## 구현 에이전트 인수인계

```text
스프린트: 3
백로그 항목 ID: PB-022, PB-023, PB-024, PB-028, PB-030
담당 에이전트: 구현 에이전트
대상 모듈: Common, Architecture Docs, Tests, Build
범위:
- Common video policy API
- RTSP fixed URL policy
- Video format, codec, resolution policy
- Client connection count ADR
- Maximum resolution ADR
- Command type compile-time safety improvement
범위 제외:
- 실제 RTSP server/client networking 구현
- 실제 H.264/MJPEG encoding 구현
- Latency 측정 구현
- Qt UI 구현
필수 보고 항목:
- 구현 요약
- 변경 파일
- 단위 테스트 명령
- 단위 테스트 결과
- 차단 이슈
```

## 검토 에이전트 인수인계

```text
스프린트: 3
백로그 항목 ID: PB-022, PB-023, PB-024, PB-028, PB-030
담당 에이전트: 검토 에이전트
리뷰 범위: Common video policy API, command type branching, ADR, tests, CMake integration
필수 통합 테스트:
- CMake configure
- CMake build
- CTest
- make test
필수 인수 테스트:
- 선택된 각 backlog item의 인수 기준 확인
필수 보고 항목:
- 코드 리뷰 발견사항
- 통합 테스트 명령과 결과
- 인수 테스트 명령과 결과
- 완료 또는 재개방 권고
```

## 스크럼 마스터 검증 Gate

- Gate 1 Product Backlog Ready: 완료
- Gate 2 Sprint Backlog Selected: 완료
- Gate 3 구현 에이전트 결과 검증 완료: 완료
- Gate 4 검토 에이전트 결과 검증 완료: 완료
- Gate 5 Sprint 종료 및 사용자 승인: 보고 대기

## 구현 에이전트 결과 초안

### 구현 요약

- Common에 `video_policy` API를 추가하여 RTSP 고정 URL, 기본 영상 format, 지원 해상도, 지원 codec 검증을 제공했다.
- `command_type()`와 `validate_command()`에서 `Command` variant 타입을 explicit branch로 처리하고, 새 payload 타입이 추가되면 compile-time에 누락을 감지하도록 보강했다.
- Client 접속 수 정책은 초기 단일 active Client로 결정하고 ADR로 기록했다.
- 최대 해상도 정책은 기본 1080p, 최대 4K 지원으로 결정하고 ADR로 기록했다.
- README에 RTSP URL 및 영상 정책 요약을 반영했다.

### 변경 파일

- `code/Common/include/camera/common/video_policy.h`
- `code/Common/src/video_policy.cpp`
- `tests/unit/common_video_policy_test.cpp`
- `code/Common/src/command.cpp`
- `CMakeLists.txt`
- `docs/adr/ADR-001-client-connection-policy.md`
- `docs/adr/ADR-002-video-resolution-policy.md`
- `README.md`

### 구현 에이전트 검증 결과

- 통과: `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`
- 통과: `cmake --build build`
- 통과: `ctest --test-dir build --output-on-failure`
  - 결과: 13개 테스트 통과, 실패 0개
- 통과: `make test`
  - 결과: 13개 테스트 통과, 실패 0개
- 통과: `git diff --check`

### 남은 이슈

- 실제 RTSP Server/Client streaming 구현은 Sprint 3 범위 밖이며 PB-008, PB-010에서 처리해야 한다.
- Latency 500ms/200ms/100ms 기준 검증은 정책만 확인했으며 PB-025에서 별도 측정 및 인수 기준을 구현해야 한다.
- 다중 Client 접속은 초기 범위에서 제외했으므로 필요 시 후속 product backlog로 추가해야 한다.

## 검토 결과 요약

- Blocking finding: 없음
- Non-blocking finding: 없음
- 검토 에이전트 최종 권고: 완료

## Scrum Master 재검증 결과

- `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`: 통과
- `cmake --build build`: 통과
- `ctest --test-dir build --output-on-failure`: 통과, 13/13 passed
- `make test`: 통과, 13/13 passed
- `git diff --check`: 통과

## 인수 테스트 결과

- PB-022 명령 타입 확장 안전성 보강: 통과
- PB-023 RTSP 고정 URL 규칙: 통과
- PB-024 Video Format 및 Codec 정책: 통과
- PB-028 Client 접속 수 정책 결정: 통과
- PB-030 최대 해상도 목표 결정: 통과

## Sprint 종료 보고서

- 완료된 백로그 항목: PB-022, PB-023, PB-024, PB-028, PB-030
- 미완료 백로그 항목: 없음
- 재개방된 백로그 항목: 없음
- 수정된 Product Backlog 항목: PB-022, PB-023, PB-024, PB-028, PB-030 상태 완료 표시
- 수정된 요구사항 항목: Client 접속 수 정책과 최대 해상도 정책을 결정 완료 항목으로 이동
- 구현 에이전트 결과: 완료
- 검토 에이전트 결과: 완료 권고
- 남은 리스크: 실제 RTSP streaming, latency 검증, 오류 감지 및 자동 재접속은 후속 Sprint에서 구현 필요
- 다음 Sprint 후보: PB-006 Client 접속 처리, PB-007 명령 처리, PB-008 RTSP/H.264 스트리밍 Endpoint, PB-025 Latency 요구사항 검증 기준

## 리스크

- 영상 정책은 구현 기준을 제공하지만 실제 streaming 성능이나 latency를 보장하지 않는다.
- Client 접속 수 정책은 초기 구현 범위를 제한하므로, 다중 Client가 필요하면 별도 backlog로 추적해야 한다.
