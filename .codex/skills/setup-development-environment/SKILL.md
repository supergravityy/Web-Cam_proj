---
name: setup-development-environment
description: docs/requirements.md를 기준으로 이 저장소의 C++ 개발환경을 설치, 설정, 복구, 검증할 때 사용하는 스킬이다. Ubuntu/WSL2, VS Code, CMake, g++, gdb, vcpkg, Docker, OpenCV, Qt, Google Test 설정을 다룬다.
---

# 개발환경 설정 스킬

## 목적

이 스킬은 `docs/requirements.md`에서 요구하는 카메라 관제 Client-Server C++ 프로젝트 개발환경을 준비하기 위해 사용한다.

이 스킬이 다루는 범위:

- Ubuntu 또는 WSL2 host 설정
- C++ compiler, CMake, make, gdb, pkg-config
- VS Code extension 및 workspace 설정
- vcpkg 기반 dependency: OpenCV, Qt, Google Test
- Docker 기반 개발환경
- 환경 검증 및 설정 보고

## 필요한 context

파일을 변경하거나 설치를 수행하기 전에 다음을 읽는다.

- `docs/requirements.md`
- `README.md`
- `Makefile`
- 존재하는 경우 `.vscode/` 파일

구체적인 설치 명령과 검증 단계는 `references/ubuntu-wsl2-cpp-setup.md`를 읽는다.

## 작업 흐름

1. 현재 저장소 상태를 확인한다.
2. `docs/requirements.md`와 비교한다.
3. 가능한 경우 `bash .codex/skills/setup-development-environment/scripts/check_environment.sh`를 실행한다.
4. 누락된 tool, 누락된 dependency, VS Code 설정 불일치를 식별한다.
5. package 설치 명령을 실행하기 전에는 sudo, network, Docker 권한이 필요할 수 있으므로 사용자 승인을 요청한다.
6. 필요한 최소 설정 변경만 적용한다.
7. 명령 점검, 가능한 경우 CMake configure/build, VS Code 설정 검토로 검증한다.
8. 설치한 것, 설정한 것, 검증하지 못한 것, 필요한 다음 수동 작업을 보고한다.

## 설정 정책

- 전역 변경보다 프로젝트 로컬 설정을 우선한다.
- 사용자가 명시적으로 요청하지 않으면 shell startup file을 수정하지 않는다.
- vcpkg가 전역 설치되어 있다고 가정하지 않는다. `$VCPKG_ROOT`와 `packages/vcpkg`를 모두 지원한다.
- 사용자가 native Ubuntu/WSL2 설정을 선택하면 Docker를 필수로 요구하지 않는다.
- 사용자가 Docker 또는 system package를 선택하면 vcpkg를 필수로 요구하지 않는다.
- 빌드 산출물은 `build`에 둔다.
- 프로젝트 로컬 tool을 설치할 때 외부 package는 `packages` 아래에 둔다.
- `.vscode`, `Makefile`, CMake 파일의 사용자 변경은 보존한다.

## 기대 출력

Setup Agent로 동작할 때는 다음을 포함한 간결한 보고서를 작성한다.

- `감지됨`: OS, compiler, CMake, gdb, Docker, vcpkg, VS Code CLI
- `설치 또는 설정됨`: 완료한 작업
- `변경된 프로젝트 파일`: 변경한 path
- `검증됨`: 통과한 명령
- `주의 필요`: 누락된 tool, 승인 필요 명령, 수동 GUI 단계
