# 스프린트 1 백로그

## 상태

계획됨

## 스프린트 목표

Client-Server 기능 개발을 시작하기 전에 필요한 CMake 기반 프로젝트 골격과 개발 작업 흐름을 구축한다.

## 선택 기준

Sprint 1은 `docs/product-backlog.md`의 준비된 제품 백로그 항목 중 우선순위가 가장 높은 항목에서 선택한다.

선택 순서:

1. P0 기반 작업
2. build, test, IntelliSense, 환경 검증을 unblock하는 작업
3. 인수 기준이 명확하고 첫 스프린트에서 수행 가능한 크기의 작업

## 선택된 스프린트 백로그 항목

### PB-001 CMake 프로젝트 구조

- 우선순위: P0
- 모듈: Build
- 구현 에이전트 인수인계: root CMake project, target, build output rule, `compile_commands.json`을 만든다.
- 필수 단위 테스트: CTest가 test target을 발견할 수 있어야 한다.

### PB-002 디렉터리 구조 전환

- 우선순위: P0
- 모듈: Repository
- 구현 에이전트 인수인계: `code/Client`, `code/Server`, `code/Common`, `tests` 구조를 생성하거나 전환한다.
- 필수 단위 테스트: source migration이 동작을 변경하지 않는다면 해당 없음.

### PB-003 VS Code 빌드 및 디버그 연동

- 우선순위: P0
- 모듈: Tooling
- 구현 에이전트 인수인계: Client와 Server용 IntelliSense, CMake build task, gdb launch config를 연결한다.
- 필수 단위 테스트: 해당 없음. build/debug configuration 점검으로 검증한다.

### PB-015 Google Test 기반 구성

- 우선순위: P0
- 모듈: Tests
- 구현 에이전트 인수인계: Google Test target과 기본 Common unit test 1개를 추가한다.
- 필수 단위 테스트: `ctest --test-dir build --output-on-failure`

### PB-020 설정 검증

- 우선순위: P0
- 모듈: Tooling
- 구현 에이전트 인수인계: 필수 tool과 dependency에 맞게 setup verification을 유지한다.
- 필수 단위 테스트: 해당 없음. setup verification script를 실행한다.

## 구현 에이전트 인수인계

```text
스프린트: 1
백로그 항목 ID: PB-001, PB-002, PB-003, PB-015, PB-020
담당 에이전트: 구현 에이전트
대상 모듈: Build, Repository, Tooling, Tests
범위: build/test/debug 기반 구축만 수행
범위 제외: Client UI, Server streaming, command protocol 구현
필수 보고 항목:
- 구현 요약
- 변경 파일
- 단위 테스트 명령
- 단위 테스트 결과
- 설정 검증 결과
- 차단 이슈
```

## 리뷰어 인수인계

```text
스프린트: 1
백로그 항목 ID: PB-001, PB-002, PB-003, PB-015, PB-020
담당 에이전트: 검토 에이전트
리뷰 범위: build structure, source layout, VS Code integration, Google Test wiring, setup verification
필수 통합 테스트:
- CMake로 project configure
- 모든 target build
- CTest 실행
필수 인수 테스트:
- 선택된 각 backlog item의 인수 기준 확인
필수 보고 항목:
- 코드 리뷰 발견사항
- 통합 테스트 명령과 결과
- 인수 테스트 명령과 결과
- 완료 또는 재개방 권고
```

## 스크럼 마스터 검증 Gate

- Gate 1 Product Backlog Ready: 대기
- Gate 2 Sprint Backlog Selected: 완료
- Gate 3 구현 에이전트 결과 검증 완료: 대기
- Gate 4 검토 에이전트 결과 검증 완료: 대기

## 리스크

- 현재 저장소에는 아직 Client, Server, Common, tests source file이 없을 수 있다.
- PB-001과 PB-015가 구현되기 전까지 build verification이 blocked 상태로 남을 수 있다.
