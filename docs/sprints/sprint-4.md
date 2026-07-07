# 스프린트 4 백로그

## 상태

완료

## 스프린트 목표

Server가 단일 active Client 접속 상태를 추적하고, 연결된 Client의 제어 명령을 처리할 수 있는 Server core를 구축한다.

## 선택 기준

Sprint 4는 Sprint 3에서 확정된 단일 Client 정책과 영상 정책을 바탕으로 실제 RTSP streaming 구현 전에 필요한 Server 세션/명령 처리 기반을 우선 선택한다.

선택 순서:

1. Server 접속 흐름을 unblock하는 P1 Server 항목
2. Frame rate 및 resolution 제어 흐름을 unblock하는 P1 Server 항목
3. 실제 socket, RTSP, UI와 분리해 테스트 가능한 core부터 구현

## 선택된 스프린트 백로그 항목

### PB-006 Client 접속 처리

- 우선순위: P1
- 모듈: Server
- 구현 에이전트 인수인계: 단일 active Client 정책에 따라 connect/disconnect 요청을 처리하고 접속 상태를 추적하는 Server core를 구현한다.
- 필수 테스트: connect, duplicate connect, 다른 Client 접속 거부, disconnect 흐름을 검증한다.

### PB-007 명령 처리

- 우선순위: P1
- 모듈: Server
- 구현 에이전트 인수인계: 연결된 Client의 frame rate 및 resolution 명령을 처리하고 성공 응답 또는 구조화된 오류 응답을 반환한다.
- 필수 테스트: 유효한 명령 처리, 유효하지 않은 명령 거부, 연결되지 않은 Client 명령 거부를 검증한다.

## 구현 에이전트 인수인계

```text
스프린트: 4
백로그 항목 ID: PB-006, PB-007
담당 에이전트: 구현 에이전트
대상 모듈: Server, Tests, Build, Docs
범위:
- Server core session/controller API
- 단일 active Client 접속 상태 추적
- connect/disconnect 처리
- frame rate 명령 처리
- resolution 명령 처리
- 성공/오류 응답 모델
- 통합 테스트 또는 Server core 테스트
범위 제외:
- 실제 TCP/REST/socket networking 구현
- 실제 RTSP/H.264 streaming endpoint 구현
- Qt UI 구현
- Client UI 연결
필수 보고 항목:
- 구현 요약
- 변경 파일
- 테스트 명령
- 테스트 결과
- 차단 이슈
```

## 검토 에이전트 인수인계

```text
스프린트: 4
백로그 항목 ID: PB-006, PB-007
담당 에이전트: 검토 에이전트
리뷰 범위: Server core API, session state, command handling, tests, CMake integration
필수 통합 테스트:
- CMake configure
- CMake build
- CTest
- make test
- git diff --check
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

## 리스크

- Sprint 4는 네트워크 transport를 구현하지 않으므로 실제 Client-Server 통신은 후속 Sprint에서 연결해야 한다.
- 단일 active Client 정책을 기준으로 구현하므로 다중 Client 요구가 생기면 별도 backlog와 설계 변경이 필요하다.

## 구현 결과

- `camera::server::SessionController`를 추가해 단일 active Client 접속 상태, active client id, 현재 frame rate, 현재 resolution을 조회할 수 있게 했다.
- connect 요청은 active Client가 없으면 성공하고, 같은 Client의 중복 connect는 idempotent success로 처리한다.
- 다른 Client가 이미 연결된 상태의 connect, 연결되지 않은 Client 또는 active Client가 아닌 Client의 제어 명령은 `ConnectionFailure` 구조화 오류로 거부한다.
- frame rate 및 resolution 명령은 `camera::common::validate_command()` 결과를 기준으로 검증하고, 유효한 명령만 Server 설정 상태에 반영한다.
- 실제 socket, REST, RTSP, Qt UI 연동은 Sprint 4 범위에서 제외했다.

## 변경 파일

- `code/Server/include/camera/server/session_controller.h`
- `code/Server/src/session_controller.cpp`
- `tests/integration/server_session_controller_test.cpp`
- `code/Server/src/main.cpp`
- `CMakeLists.txt`
- `README.md`
- `docs/sprints/sprint-4.md`

## 구현 에이전트 검증 결과

- 통과: `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`
- 통과: `cmake --build build`
- 통과: `ctest --test-dir build --output-on-failure`
  - 결과: 21개 테스트 통과, 실패 0개
- 통과: `make test`
  - 결과: 21개 테스트 통과, 실패 0개
- 통과: `git diff --check`

## Scrum Master 추가 조치

- 검토 에이전트의 non-blocking finding을 반영하여 active Client가 아닌 Client의 disconnect가 active session을 해제하지 않는지 회귀 테스트를 추가했다.
- 추가 테스트 후 `make test` 결과는 22/22 통과이다.

## 검토 결과 요약

- Blocking finding: 없음
- Non-blocking finding: 2건
  - Server command validation과 video policy의 허용 범위 경계가 불명확하다.
  - inactive Client disconnect 회귀 테스트가 부족하다.
- 조치:
  - inactive Client disconnect 회귀 테스트는 Sprint 4 안에서 추가 완료했다.
  - Server command validation과 video policy 정합성은 PB-031로 신규 등록했다.
- 검토 에이전트 최종 권고: 완료
- 재검토 결과: 추가 회귀 테스트는 충분하며 Sprint 4 완료 권고 유지

## Scrum Master 재검증 결과

- `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`: 통과
- `cmake --build build`: 통과
- `ctest --test-dir build --output-on-failure`: 통과, 21/21 passed
- `make test`: 통과, 22/22 passed
- `git diff --check`: 통과

## 인수 테스트 결과

- PB-006 Client 접속 처리: 통과
- PB-007 명령 처리: 통과

## Sprint 종료 보고서

- 완료된 백로그 항목: PB-006, PB-007
- 미완료 백로그 항목: 없음
- 재개방된 백로그 항목: 없음
- 수정된 Product Backlog 항목: PB-006, PB-007 상태 완료 표시
- 신규 Product Backlog 항목: PB-031 Server 명령 정책과 영상 정책 정합성 정리
- 구현 에이전트 결과: 완료
- 검토 에이전트 결과: 완료 권고
- 남은 리스크: 실제 socket/REST transport, RTSP/H.264 streaming, Client UI 연동은 후속 Sprint에서 구현 필요
- 다음 Sprint 후보: PB-031 Server 명령 정책과 영상 정책 정합성 정리, PB-008 RTSP/H.264 스트리밍 Endpoint, PB-025 Latency 요구사항 검증 기준
