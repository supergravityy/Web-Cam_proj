# 프로젝트 지침

## 1. 목적

이 문서는 카메라 관제 시스템 프로젝트 전체에 적용되는 규칙, 원칙, 템플릿, 프로세스, 목표 디렉터리 구조를 정의한다.

모든 개발 작업은 다음 문서와 일치해야 한다.

- `docs/requirements.md`
- `docs/product-backlog.md`
- `agent/` 역할 지침
- 이 `instruction.md`

## 2. 제품 요약

제품은 Client-Server 구조의 카메라 관제 시스템이다.

- Client는 Server로부터 RTSP/H.264 영상 스트림을 수신한다.
- Client는 Server로 제어 명령을 송신한다.
- Server는 영상 스트리밍을 제공하고 카메라 제어 명령을 처리한다.
- Client UI는 Qt로 구현한다.
- 비전 및 영상 처리는 OpenCV와 FFmpeg 관련 라이브러리를 사용한다.
- 단위 테스트는 Google Test를 사용한다.

## 3. 스크럼 프로세스

이 프로젝트의 개발 프로세스는 스크럼이다.

### 3.1 Scrum 산출물

- 제품 백로그(Product Backlog): `docs/product-backlog.md`
- 스프린트 백로그(Sprint Backlog): 스프린트마다 `docs/sprints/sprint-N.md`에 작성
- 인수인계 기록(Handoff 기록): 스프린트 문서 또는 에이전트 보고서에 작성
- 증분(Increment): 완료 기준(Definition of Done)을 만족하는 동작 코드

### 3.2 Scrum 역할

- 제품 책임자(Product Owner): 요구사항과 백로그 우선순위를 소유한다.
- 스크럼 마스터(Scrum Master): 요구사항부터 검증된 스프린트 증분까지 스크럼 흐름을 소유한다.
- 구현 에이전트: 할당된 스프린트 백로그 항목을 구현하고 단위 테스트 결과를 보고한다.
- 검토 에이전트: 소스 변경을 리뷰하고 통합 테스트 및 인수 테스트 결과를 보고한다.
- 셋업 매니저 에이전트(Setup Manager Agent): 개발환경 설치, 설정, 검증을 소유한다.

### 3.3 Scrum 이벤트

- 스프린트 계획(Sprint Planning): 스프린트에서 수행할 제품 백로그 항목을 선택한다.
- 구현 에이전트 인수인계: 스크럼 마스터가 선택된 스프린트 백로그 항목을 구현 에이전트에게 전달한다.
- 구현 에이전트 검증: 스크럼 마스터가 구현 범위와 단위 테스트 증거를 검증한다.
- 검토 에이전트 인수인계: 스크럼 마스터가 소스 변경과 단위 테스트 증거를 검토 에이전트에게 전달한다.
- 검토 에이전트 검증: 스크럼 마스터가 리뷰, 통합 테스트, 인수 테스트 증거를 검증한다.
- 데일리 스크럼(Daily Scrum): 진행 상황, blocker, 다음 작업을 점검한다.
- 스프린트 리뷰(Sprint Review): 완료된 증분을 시연한다.
- 스프린트 회고(Sprint Retrospective): 프로세스 개선점을 식별한다.
- 백로그 정제(Backlog Refinement): 백로그 항목을 분할, 명확화, 추정, 재우선순위화한다.

### 3.4 스프린트 규칙

- 각 스프린트에는 명확한 스프린트 목표가 있어야 한다.
- 백로그 항목은 인수 기준(Acceptance Criteria)이 명확할 때만 스프린트에 들어갈 수 있다.
- 스크럼 마스터는 제품 백로그에서 우선순위, 의존성 순서, 준비 상태, 스프린트 용량을 기준으로 스프린트 백로그 항목을 선택한다.
- 구현 에이전트는 구현 결과와 단위 테스트 증거를 스크럼 마스터에게 보고해야 한다.
- 검토 에이전트는 코드 리뷰 결과, 통합 테스트 결과, 인수 테스트 결과를 스크럼 마스터에게 보고해야 한다.
- 구현 에이전트와 검토 에이전트는 스크럼 마스터의 명시적 인수인계가 있을 때만 작업한다.
- 구현, 단위 테스트, 검토, 통합 테스트, 인수 테스트는 사람 개입 없이 agent들이 수행한다.
- 각 스프린트 종료 시 스크럼 마스터는 결과 보고서를 작성하고 사용자에게 다음 스프린트 진행 허락을 요청한다.
- 문제가 발생하면 Product Backlog를 수정 및 재작성한 뒤 스프린트 선택부터 반복한다.
- 모든 Product Backlog 항목이 구현될 때까지 스프린트 반복을 계속한다.
- 작업은 완료 기준(Definition of Done)을 만족해야만 완료된다.
- Blocker는 스크럼 마스터가 문서화해야 한다.
- 기술 부채는 명시적인 백로그 항목으로 기록해야 한다.

## 4. 목표 디렉터리 구조

현재 저장소에는 `code/Inc`와 `code/Src`가 있다. 목표 구조는 다음 형태로 발전시킨다.

```text
.
├── agent/
│   ├── developer.md
│   ├── reviewer.md
│   ├── scrum-master.md
│   └── setup-manager.md
├── build/
│   └── .gitkeep
├── code/
│   ├── Client/
│   │   ├── Inc/
│   │   └── Src/
│   ├── Server/
│   │   ├── Inc/
│   │   └── Src/
│   ├── Common/
│   │   ├── Inc/
│   │   └── Src/
│   ├── Inc/
│   └── Src/
├── docs/
│   ├── product-backlog.md
│   ├── requirements.md
│   └── sprints/
│       └── sprint-1.md
├── packages/
│   ├── .gitkeep
│   └── vcpkg/
├── tests/
│   ├── unit/
│   └── integration/
├── .vscode/
├── CMakeLists.txt
├── CMakePresets.json
├── Dockerfile
├── Makefile
├── README.md
├── instruction.md
└── vcpkg.json
```

### 4.1 디렉터리 규칙

- `agent/`: 저장소 에이전트 역할 정의만 둔다.
- `.codex/skills/`: 재사용 가능한 스킬 절차와 설정 참고 문서만 둔다.
- `build/`: 생성된 빌드 산출물만 둔다.
- `packages/`: 외부 패키지 매니저 또는 로컬 vendor 라이브러리를 둔다.
- `code/Common`: 공통 명령 모델, 프로토콜 정의, 유틸리티를 둔다.
- `code/Client`: Qt UI, Client 네트워킹, 스트림 표시, 명령 송신 코드를 둔다.
- `code/Server`: RTSP/H.264 스트리밍, Client 세션 처리, 명령 처리 코드를 둔다.
- `tests/unit`: Common 및 독립 로직에 대한 빠른 단위 테스트를 둔다.
- `tests/integration`: Client-Server 흐름과 스트리밍 통합 테스트를 둔다.
- `docs/`: 요구사항, 백로그, 스프린트 문서, 아키텍처 노트, 의사결정 기록을 둔다.

## 5. 아키텍처 원칙

- Client, Server, Common 모듈은 분리한다.
- 공유 명령 타입과 프로토콜 모델은 Common에 둔다.
- UI 코드는 Server와 Common에 넣지 않는다.
- 카메라/스트리밍 구현 세부사항은 Client UI 위젯에서 분리한다.
- 전역 상태보다 명시적 인터페이스를 선호한다.
- 네트워크, 스트림, 장치 작업은 모두 실패 가능성이 있다고 가정한다.
- Server는 Client에 구조화된 오류를 반환한다.
- Client UI는 사용자에게 오류를 명확하게 표시한다.

## 6. 개발환경 규칙

- OS: Ubuntu 또는 WSL2
- IDE: VS Code
- 언어: C++17 이상. 단, 백로그 결정으로 변경할 수 있다.
- 빌드 도구: CMake
- 컴파일러: g++
- 디버거: gdb
- 패키지/배포: vcpkg 또는 Docker
- 비전 라이브러리: OpenCV
- UI 프레임워크: Qt6
- 테스트 프레임워크: Google Test

개발환경 설치와 검증은 `agent/setup-manager.md`를 사용한다.
백로그 선택, 인수인계 조율, 최종 스크럼 검증은 `agent/scrum-master.md`를 사용한다.
구현과 단위 테스트 보고는 구현 에이전트 정의서인 `agent/developer.md`를 사용한다.
코드 리뷰, 통합 테스트, 인수 테스트 보고는 검토 에이전트 정의서인 `agent/reviewer.md`를 사용한다.

## 7. 빌드 규칙

- CMake를 프로젝트 빌드의 기준으로 삼는다.
- Makefile은 CMake 명령을 감싸는 wrapper로 둘 수 있다.
- 빌드 산출물은 `build` 아래에만 생성한다.
- CMake는 IntelliSense를 위해 `compile_commands.json`을 내보내야 한다.
- CMake target 이름은 명확하게 지정한다.
  - `camera_client`
  - `camera_server`
  - `camera_common`
  - `camera_tests`
- Debug 빌드는 디버그 심벌을 포함해야 한다.
- Release 빌드 산출물과 Debug 빌드 산출물을 같은 빌드 트리에 섞지 않는다.

## 8. 의존성 규칙

- Ubuntu/WSL2에서 빠르게 개발할 때는 system package를 우선 사용한다.
- 재현 가능한 의존성 설정에는 vcpkg manifest mode를 우선 사용한다.
- 깨끗한 재현 빌드에는 Docker를 우선 사용한다.
- 명시적으로 필요하지 않으면 생성된 package contents를 commit하지 않는다.
- `packages/vcpkg`는 로컬 도구 checkout이며 Git에서 무시되어야 한다.

## 9. 코딩 규칙

- C++17 기능은 보수적으로 사용한다.
- 헤더는 `Inc` 디렉터리에, 구현은 `Src` 디렉터리에 둔다.
- socket, camera handle, stream, file 같은 자원에는 RAII를 선호한다.
- 소유권이 있는 raw pointer는 피한다.
- 명령 검증 로직은 명령 정의 근처에 둔다.
- public API는 작게 유지하고 명확한 이름으로 문서화한다.
- 주석은 자명하지 않은 동작에만 추가한다.

## 10. 오류 처리 규칙

- Client는 다음 상황에서 명확한 오류 메시지를 표시해야 한다.
  - Server 접속 실패
  - Stream 수신 실패
  - Command 처리 실패
  - 지원하지 않는 frame rate
  - 지원하지 않는 resolution
- Server는 구조화된 실패 응답을 반환해야 한다.
- 로그는 connection, streaming, command, device 오류를 구분해야 한다.
- OpenCV, FFmpeg, socket, Qt API의 실패 반환값을 무시하지 않는다.

## 11. 테스트 규칙

- Common 명령 모델과 검증 로직에는 단위 테스트가 필요하다.
- Client-Server 명령 흐름에는 통합 테스트가 필요하다.
- 실제 카메라 하드웨어가 준비되기 전에는 mock RTSP/H.264 source로 스트리밍 테스트를 수행할 수 있다.
- 모든 백로그 항목은 인수 기준을 포함해야 한다.
- 버그 수정에는 가능한 경우 regression test를 포함한다.
- 구현 에이전트는 리뷰로 넘기기 전에 단위 테스트를 실행하고 보고한다.
- 검토 에이전트는 Scrum Master가 작업을 닫기 전에 통합 테스트와 인수 테스트를 실행하고 보고한다.

## 12. 문서화 규칙

- 요구사항은 `docs/requirements.md`에 둔다.
- 제품 백로그는 `docs/product-backlog.md`에 둔다.
- 스프린트 계획은 `docs/sprints/`에 둔다.
- 스프린트 문서는 선택된 백로그 항목, 구현 에이전트 인수인계, 구현 에이전트 검증, 검토 에이전트 인수인계, 검토 에이전트 검증을 기록해야 한다.
- 필요한 경우 아키텍처 결정은 `docs/adr/ADR-NNN-title.md` 형식을 사용한다.
- README는 간결하게 유지하고 상세 문서로 연결한다.

## 13. 준비 기준(Definition of Ready)

제품 백로그 항목은 다음 조건을 만족할 때 준비된 것으로 본다.

- 사용자 가치가 명확하다.
- 인수 기준이 작성되어 있다.
- 의존성이 식별되어 있다.
- 대상 모듈이 알려져 있다.
- 테스트 기대사항이 명확하다.
- 한 스프린트 안에 수행할 수 있을 만큼 작거나 명시적으로 분할되어 있다.

## 14. 완료 기준(Definition of Done)

백로그 항목은 다음 조건을 만족할 때 완료된다.

- 코드가 올바른 모듈에 구현되어 있다.
- 빌드가 통과한다.
- 구현 에이전트 단위 테스트가 통과했거나 승인된 blocker가 문서화되어 있다.
- 검토 에이전트 통합 테스트가 통과했거나 승인된 blocker가 문서화되어 있다.
- 검토 에이전트 인수 테스트가 통과했거나 승인된 blocker가 문서화되어 있다.
- 인수 기준이 만족된다.
- 오류 처리가 구현되어 있다.
- 동작, 설정, 작업 흐름이 변경된 경우 문서가 업데이트되어 있다.
- 관련 없는 변경이 포함되어 있지 않다.
- Scrum Master가 구현 에이전트와 검토 에이전트 보고서를 검증한다.

## 15. 템플릿

### 15.1 사용자 스토리 템플릿

```text
ID:
제목:
역할:
원하는 것:
목적:
우선순위:
추정치:
모듈:
의존성:
인수 기준:
- 조건:
- 동작:
- 결과:
테스트:
- 단위:
- 통합:
비고:
```

### 15.2 스프린트 계획 템플릿

```text
스프린트:
기간:
스프린트 목표:
선택된 백로그 항목:
- ID:
용량:
리스크:
완료 기준 점검:
데일리 스크럼 기록:
리뷰 기록:
회고 기록:
```

### 15.3 에이전트 보고서 템플릿

```text
에이전트:
작업:
입력:
수행 내용:
변경 파일:
검증:
차단 이슈:
다음 권장 작업:
```

### 15.4 Architecture Decision Record 템플릿

```text
# ADR-NNN: 제목

## 상태

제안 | 승인 | 폐기 | 대체됨

## 배경

## 결정

## 결과
```

### 15.5 구현 에이전트 인수인계 템플릿

```text
스프린트:
백로그 항목 ID:
스프린트 목표:
요구사항 출처:
담당 에이전트:
대상 모듈:
범위:
인수 기준:
필수 단위 테스트:
예상 파일:
제약:
범위 제외:
필수 보고 항목:
- 구현 요약
- 변경 파일
- 단위 테스트 명령
- 단위 테스트 결과
- 차단 이슈
```

### 15.6 검토 에이전트 인수인계 템플릿

```text
스프린트:
백로그 항목 ID:
소스 변경:
구현 에이전트 단위 테스트 증거:
리뷰 범위:
필수 통합 테스트:
필수 인수 테스트:
알려진 리스크:
필수 보고 항목:
- 코드 리뷰 발견사항
- 통합 테스트 명령
- 통합 테스트 결과
- 인수 테스트 명령
- 인수 테스트 결과
- 차단 이슈
```
