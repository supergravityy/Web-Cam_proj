# 스프린트 2 백로그

## 상태

완료

## 스프린트 목표

Client와 Server 기능 구현의 기반이 되는 Common 명령 모델, 구조화된 오류 모델, 의존성 manifest, 설정 검증 실패 정책을 구축한다.

## 선택 기준

Sprint 2는 Sprint 1에서 완료된 빌드/테스트 기반 위에서 다음 기능 개발을 unblock하는 항목을 우선 선택한다.

선택 순서:

1. Client-Server 제어 흐름의 기반이 되는 P1 Common 항목
2. 재현 가능한 의존성 설정을 위한 P1 Tooling 항목
3. Sprint 1 검토에서 도출된 P2 기술부채 항목

## 선택된 스프린트 백로그 항목

### PB-004 명령 모델 정의

- 우선순위: P1
- 모듈: Common
- 구현 에이전트 인수인계: connect, disconnect, frame rate, resolution 명령 모델과 검증 로직을 구현한다.
- 필수 단위 테스트: 유효한 명령과 유효하지 않은 명령을 검증한다.

### PB-005 구조화된 오류 모델

- 우선순위: P1
- 모듈: Common
- 구현 에이전트 인수인계: connection, streaming, command, unsupported setting 실패를 표현하는 오류 모델과 사용자 표시 문구 변환을 구현한다.
- 필수 단위 테스트: 오류 코드와 사용자 표시 문구 변환을 검증한다.

### PB-018 vcpkg Manifest

- 우선순위: P1
- 모듈: Tooling
- 구현 에이전트 인수인계: `vcpkg.json`에 OpenCV, Qt, GTest 의존성을 선언하고 CMake의 vcpkg toolchain 사용 방법을 문서화한다.
- 필수 검증: 기존 system package 환경에서도 CMake build/test가 유지되어야 한다.

### PB-021 설정 검증 실패 코드 정책

- 우선순위: P2
- 모듈: Tooling
- 구현 에이전트 인수인계: setup verification script가 필수 항목 누락 시 non-zero exit code를 반환하고, 필수/선택 항목을 구분하도록 개선한다.
- 필수 검증: 현재 환경에서 script가 성공 종료해야 하며 누락 항목 보고 형식이 명확해야 한다.

## 구현 에이전트 인수인계

```text
스프린트: 2
백로그 항목 ID: PB-004, PB-005, PB-018, PB-021
담당 에이전트: 구현 에이전트
대상 모듈: Common, Tooling, Tests, Docs
범위:
- Common command model
- Common error model
- Unit tests
- vcpkg manifest
- setup verification exit code policy
범위 제외:
- 실제 Client-Server networking 구현
- 실제 RTSP/H.264 streaming 구현
- Qt UI 구현
필수 보고 항목:
- 구현 요약
- 변경 파일
- 단위 테스트 명령
- 단위 테스트 결과
- 설정 검증 결과
- 차단 이슈
```

## 검토 에이전트 인수인계

```text
스프린트: 2
백로그 항목 ID: PB-004, PB-005, PB-018, PB-021
담당 에이전트: 검토 에이전트
리뷰 범위: Common API, command validation, error conversion, tests, vcpkg manifest, setup verification policy
필수 통합 테스트:
- CMake configure
- CMake build
- CTest
- make test
- setup verification script
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

## 구현 결과 요약

- PB-004: Common 명령 모델에 connect, disconnect, frame rate, resolution 명령과 검증 API를 추가했다.
- PB-005: Common 오류 코드와 사용자 표시용 text 변환 API를 추가했다.
- PB-018: `vcpkg.json`에 GTest, OpenCV, Qt 의존성을 선언하고 README에 vcpkg toolchain 사용 예를 추가했다.
- PB-021: 환경 검증 스크립트가 필수/선택 항목을 구분하고 필수 항목 누락 시 non-zero exit code를 반환하도록 변경했다.

## 검토 결과 요약

- Blocking finding: 없음
- Non-blocking finding: 없음
- 참고 리스크: `command_type()`는 현재 variant의 마지막 타입을 `SetResolution`으로 처리하므로, 향후 명령 타입 추가 시 분기 보강이 필요하다.
- 조치: 참고 리스크를 PB-022 명령 타입 확장 안전성 보강으로 제품 백로그에 등록했다.
- 검토 에이전트 최종 권고: 완료

## 통합 테스트 결과

- `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`: 통과
- `cmake --build build`: 통과
- `ctest --test-dir build --output-on-failure`: 통과, 8/8 passed
- `make test`: 통과, 8/8 passed
- `bash .codex/skills/setup-development-environment/scripts/check_environment.sh`: 통과
- `/tmp`에서 setup verification script 실행 시 필수 프로젝트 파일 누락으로 exit code 1 반환 확인
- `git diff --check`: 통과

## 인수 테스트 결과

- PB-004 명령 모델 정의: 통과
- PB-005 구조화된 오류 모델: 통과
- PB-018 vcpkg Manifest: 통과
- PB-021 설정 검증 실패 코드 정책: 통과

## Sprint 종료 보고서

- 완료된 백로그 항목: PB-004, PB-005, PB-018, PB-021
- 미완료 백로그 항목: 없음
- 재개방된 백로그 항목: 없음
- 수정된 Product Backlog 항목: PB-004, PB-005, PB-018, PB-021 상태 완료 표시
- 신규 Product Backlog 항목: PB-022 명령 타입 확장 안전성 보강
- 구현 에이전트 결과: 완료
- 검토 에이전트 결과: 완료 권고
- 남은 리스크: 향후 명령 타입 추가 시 `command_type()` 분기 안정성 보강 필요
- 다음 Sprint 후보: PB-006 Client 접속 처리, PB-007 명령 처리, PB-013 사용자 오류 표시, PB-022 명령 타입 확장 안전성 보강

## 리스크

- Sprint 2 기준 blocking risk는 없다.
- 명령 타입 확장 안정성은 PB-022로 추적한다.
