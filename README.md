# Web-Cam_proj

## 프로젝트 문서

- [요구사항 문서](docs/requirements.md)
- [프로젝트 지침](instruction.md)
- [제품 백로그](docs/product-backlog.md)
- [스프린트 1 백로그](docs/sprints/sprint-1.md)
- [구현 에이전트](agent/developer.md)
- [검토 에이전트](agent/reviewer.md)
- [스크럼 마스터 에이전트](agent/scrum-master.md)
- [셋업 매니저 에이전트](agent/setup-manager.md)
- [개발환경 설정 스킬](.codex/skills/setup-development-environment/SKILL.md)

## C/C++ 작업 공간

디렉터리 구조:

- `code/Inc`: 헤더 파일
- `code/Src`: C/C++ 소스 파일
- `build`: 빌드 산출물
- `packages`: OpenCV 같은 외부 라이브러리

빌드 및 실행:

```bash
make
make run
make clean
```

VS Code 연동:

- `Ctrl+Shift+B`: Makefile 기반 빌드
- `F5`: gdb로 `build/webcam_app` 빌드 및 디버그

외부 라이브러리는 다음과 같은 일반적인 구조로 `packages` 아래에 둘 수 있다.

```text
packages/opencv/include
packages/opencv/lib
packages/opencv/lib/pkgconfig
```

Makefile은 패키지의 `include`, `lib`, `lib64`, `pkgconfig` 디렉터리를 자동으로 탐색한다.
