# 스프린트 5 백로그

## 상태

완료

## 스프린트 목표

신규 Server 요구사항에 따라 기존 C++/Ubuntu/CMake Server 구현과 Windows/Java/Gradle/Spring Boot/MediaMTX Server 요구사항의 관계를 확정한다.

## 선택 기준

Sprint 5는 Server 구현 기술 스택이 바뀌는 요구사항을 받은 직후의 첫 Sprint이므로, 구현보다 아키텍처 결정을 우선한다.

선택 순서:

1. 이후 Server Sprint 전체를 결정하는 P0 Architecture 항목
2. D 드라이브 기반 Windows 작업 환경을 고려한 Server repository 및 산출물 위치 정리
3. PB-033 Java/Gradle Server 프로젝트 골격 검증 전 의존성 제거

## 선택된 스프린트 백로그 항목

### PB-032 Server 기술 스택 전환 의사결정

- 우선순위: P0
- 모듈: Architecture
- 구현 에이전트 인수인계: 기존 C++ Server core를 유지, 폐기, 또는 Java Server로 이관할지 결정하고 ADR로 기록한다.
- 필수 인수 기준:
  - 기존 C++ Server core의 향후 위치와 용도가 결정되어야 한다.
  - 신규 Server 구현 언어와 build tool이 명확해야 한다.
  - Windows D 드라이브 작업 환경 기준의 repository 위치와 산출물 위치가 문서화되어야 한다.

## 구현 에이전트 인수인계

```text
스프린트: 5
백로그 항목 ID: PB-032
담당 에이전트: 구현 에이전트
대상 모듈: Architecture Docs, Requirements, Product Backlog, Project Summary
범위:
- Server 기술 스택 전환 ADR 작성
- 기존 C++ Server core의 향후 용도 결정
- 신규 Windows/Java/Gradle/Spring Boot/MediaMTX Server 방향 결정
- D 드라이브 작업 경로와 WSL/Codex 현재 작업 경로 관계 문서화
- 다음 Sprint 후보 정리
범위 제외:
- Java/Gradle 프로젝트 생성
- D 드라이브 파일 생성 또는 이동
- Spring Boot API 구현
- MediaMTX 실행 또는 설치
필수 보고 항목:
- 결정 요약
- 변경 파일
- 문서 검증 결과
- 차단 이슈
```

## 검토 에이전트 인수인계

```text
스프린트: 5
백로그 항목 ID: PB-032
담당 에이전트: 검토 에이전트
리뷰 범위: ADR, requirements, product backlog, project summary, sprint report
필수 통합 테스트:
- git diff --check
- make test
필수 인수 테스트:
- PB-032 인수 기준 확인
필수 보고 항목:
- 문서 리뷰 발견사항
- 테스트 명령과 결과
- 인수 테스트 결과
- 완료 또는 재개방 권고
```

## 스크럼 마스터 검증 Gate

- Gate 1 Product Backlog Ready: 완료
- Gate 2 Sprint Backlog Selected: 완료
- Gate 3 구현 에이전트 결과 검증 완료: 완료
- Gate 4 검토 에이전트 결과 검증 완료: 완료
- Gate 5 Sprint 종료 및 사용자 승인: 보고 대기

## 구현 결과 초안

변경 파일:

- `docs/adr/ADR-003-server-technology-stack-transition.md`
- `docs/requirements.md`
- `docs/product-backlog.md`
- `docs/project-summary.md`
- `docs/sprints/sprint-5.md`
- `README.md`

결정 요약:

- 제품 Server production path는 Java, Gradle, Spring Boot, MediaMTX, Web UI 기준으로 진행한다.
- 기존 C++/CMake `camera_server_core`는 즉시 삭제하지 않고 Sprint 4까지 검증한 단일 active Client 세션과 명령 처리 도메인 프로토타입 및 참조 구현으로 보존한다.
- C++ Client/Common 작업은 별도 Client 및 공통 개념 검증 자산으로 유지한다.
- Server production path의 언어와 build tool은 Java/Gradle로 고정한다.
- 현재 Codex workspace는 `/home/sungsu/workspace/KOSTA_260707`이다.
- Windows Server 실제 작업 위치는 WSL 기준 `/mnt/d/WindowServer_20260707/untitled`, Windows 표기 기준 `D:\WindowServer_20260707\untitled`이다.
- Gradle build 산출물은 `/mnt/d/WindowServer_20260707/untitled/build` 아래에 생성한다.
- Spring Boot 실행 산출물은 `/mnt/d/WindowServer_20260707/untitled/build/libs` 아래에 생성한다.
- JUnit 결과는 `/mnt/d/WindowServer_20260707/untitled/build/test-results/test`와 `/mnt/d/WindowServer_20260707/untitled/build/reports/tests/test`를 사용한다.
- MediaMTX 설정은 `/mnt/d/WindowServer_20260707/untitled/config/mediamtx.yml`을 사용한다.
- D 드라이브의 Java/Gradle/Spring Boot 작업 디렉터리는 Sprint 5에서 생성하지 않은 기존 외부 작업물로 확인했으며, PB-033에서 제품 Server 골격으로 검증 및 정리한다.

다음 Sprint 우선 후보:

- PB-033 Java/Gradle Server 프로젝트 골격 검증 및 정리
- PB-037 Java Server OpenCV/JUnit 개발환경 검증
- PB-031 Server 명령 정책과 영상 정책 정합성 정리

검증 결과:

- `git diff --check`: 통과
- `make test`: 통과, 22/22 passed

남은 이슈:

- PB-033에서 D 드라이브의 기존 Java/Gradle Server 프로젝트 골격을 검증 및 정리해야 한다.
- PB-037에서 Windows/Java/Gradle/OpenCV/JUnit 개발환경 검증 절차를 확정해야 한다.
- PB-031에서 기존 C++ command validation과 video policy 정합성 기술부채를 정리해야 한다.
- PB-029 얼굴 인식 처리 위치 결정은 여전히 대기 상태이다.

## 검토 결과 및 재작업

검토 에이전트 1차 결과:

- Blocking finding: 2건
  - D 드라이브 repository 위치가 후보로만 기록되어 있고 Java/Gradle 산출물 위치가 부족하다.
  - `/mnt/d/WindowServer_20260707/untitled` 아래에 이미 Java/Gradle/Spring Boot/MediaMTX 작업물이 존재하므로 Sprint 5 범위 밖 생성 여부를 정리해야 한다.
- Non-blocking finding: Server 기술 스택 결정 자체는 문서 간 일관적이다.

Scrum Master 재작업:

- 실제 Server repository를 `/mnt/d/WindowServer_20260707/untitled`로 확정했다.
- Windows 표기를 `D:\WindowServer_20260707\untitled`로 확정했다.
- Gradle build, Spring Boot 실행 산출물, JUnit 결과, MediaMTX 설정 위치를 문서화했다.
- D 드라이브의 기존 Java/Gradle/Spring Boot 작업물은 Sprint 5에서 생성 또는 수정하지 않은 외부 작업물로 기록했다.
- PB-033의 성격을 신규 생성에서 기존 Java/Gradle Server 프로젝트 골격 검증 및 정리로 조정했다.

검토 에이전트 재검토 결과:

- Blocking finding: 없음
- Non-blocking finding: 없음
- 이전 blocking finding 2건은 닫힘
- PB-032 인수 기준 충족
- Sprint 5 완료 권고

## Scrum Master 재검증 결과

- `git diff --check`: 통과
- `make test`: 통과, 22/22 passed

## 인수 테스트 결과

- PB-032 기존 C++ Server core 유지/폐기/이관 결정: 통과
- PB-032 Windows D 드라이브 실제 repository 위치 문서화: 통과
- PB-032 Java/Gradle 산출물 위치 문서화: 통과
- PB-032 다음 Sprint Server 구현 언어 및 build tool 결정: 통과
- Sprint 5 범위 밖 D 드라이브 생성 여부 정리: 통과

## Sprint 종료 보고서

- 완료된 백로그 항목: PB-032
- 미완료 백로그 항목: 없음
- 재개방된 백로그 항목: 없음
- 수정된 Product Backlog 항목: PB-032 상태 완료 표시, PB-033 명칭과 인수 기준 조정
- 신규 ADR: `docs/adr/ADR-003-server-technology-stack-transition.md`
- 구현 에이전트 결과: 완료
- 검토 에이전트 결과: 재검토 후 완료 권고
- 남은 리스크: PB-033에서 D 드라이브 Java/Gradle project를 실제로 build/test 검증해야 함
- 다음 Sprint 후보: PB-033 Java/Gradle Server 프로젝트 골격 검증 및 정리, PB-037 Java Server OpenCV/JUnit 개발환경 검증, PB-031 Server 명령 정책과 영상 정책 정합성 정리

## 리스크

- 현재 Codex workspace는 `/home/sungsu/workspace/KOSTA_260707`이다.
- Windows D 드라이브는 WSL에서 `/mnt/d`로 확인되었으며, 실제 Server 작업 디렉터리는 `/mnt/d/WindowServer_20260707/untitled`이다.
- D 드라이브 작업 디렉터리는 Sprint 5에서 생성하지 않았으며, PB-033에서 검증 및 정리한다.
