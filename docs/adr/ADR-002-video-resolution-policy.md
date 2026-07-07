# ADR-002 영상 해상도 정책

## 상태

승인

## 맥락

요구사항에는 기본 format `1920x1080, 30FPS, H.264`와 지원 해상도 `1280x720`, `1920x1080`, `3840x2160`이 정의되어 있다. 추가 이슈로 최대 해상도 목표를 1080p로 제한할지, 4K까지 고려할지 결정이 필요하다.

Latency 요구사항은 최소 500ms 이하, 권장 200ms 이하, 실시간 제어 100ms 이하로 제시되어 있으나 실제 성능 검증은 RTSP 구현, codec 처리, 장치 성능, 네트워크 조건에 의존한다.

## 결정

기본 영상 format은 `1920x1080, 30FPS, H.264`로 고정한다.

지원 해상도는 `1280x720`, `1920x1080`, `3840x2160`으로 정의하고, 최대 목표는 4K 지원으로 결정한다. 단, latency 검증과 성능 tuning은 별도 backlog에서 다룬다.

지원 codec은 `H.264`와 `MJPEG`로 정의한다. 초기 streaming 구현은 요구사항의 Server interface 기준에 따라 H.264를 우선 적용하고, MJPEG는 정책상 지원 대상 및 확장 대상으로 유지한다.

## 결과

- PB-024 Video Format 및 Codec 정책은 Common video policy API에서 검증 가능한 상수와 함수로 제공한다.
- PB-008 RTSP/H.264 streaming endpoint는 기본 1080p H.264를 우선 구현한다.
- 4K streaming 성능과 latency 충족 여부는 별도 latency 검증 backlog에서 확인한다.
