# ADR-001 Client 접속 수 정책

## 상태

승인

## 맥락

요구사항에는 Client가 Server에 접속하여 영상 스트리밍을 수신하고 제어 명령을 송출하는 흐름이 정의되어 있다. 추가 이슈로 단일 Client만 고려할지, 다중 Client 접속까지 고려할지 결정이 필요하다.

초기 구현은 RTSP 스트리밍, 제어 명령, 오류 처리, 자동 재접속을 순차적으로 구축해야 하므로 Client 세션 수가 늘어나면 Server 상태 관리, stream fan-out, 명령 충돌 처리, 테스트 범위가 크게 증가한다.

## 결정

초기 구현은 단일 active Client 접속만 지원한다.

Server는 동시에 하나의 active Client 세션을 기준으로 접속 상태와 제어 명령을 처리한다. 추가 Client 접속 정책, 다중 Client fan-out, Client별 권한 및 명령 충돌 처리는 후속 product backlog로 분리한다.

## 결과

- PB-006 Client 접속 처리는 단일 active Client 세션을 기준으로 구현한다.
- PB-007 명령 처리는 단일 Client가 송출한 명령을 기준으로 한다.
- PB-008 RTSP streaming endpoint는 단일 active Client 수신 흐름을 우선 검증한다.
- 다중 Client 지원이 필요해지면 별도 backlog를 생성하고 설계, 구현, 통합 테스트 범위를 재산정한다.
