---
name: setup-development-environment
description: Use this skill when installing, configuring, repairing, or verifying the C++ development environment for this repository based on docs/requirements.md. Covers Ubuntu/WSL2, VS Code, CMake, g++, gdb, vcpkg, Docker, OpenCV, Qt, and Google Test setup.
---

# Setup Development Environment

## Purpose

Use this skill to prepare the development environment required by `docs/requirements.md` for the camera control Client-Server C++ project.

The skill covers:

- Ubuntu or WSL2 host setup
- C++ compiler, CMake, make, gdb, pkg-config
- VS Code extensions and workspace settings
- vcpkg-based dependencies: OpenCV, Qt, Google Test
- Docker-based development environment
- Environment verification and setup reporting

## Required Context

Before changing files or installing anything, read:

- `docs/requirements.md`
- `README.md`
- `Makefile`
- `.vscode/` files, if present

For concrete install commands and verification steps, read `references/ubuntu-wsl2-cpp-setup.md`.

## Workflow

1. Inspect the current repository state.
2. Compare it with `docs/requirements.md`.
3. Run `bash .codex/skills/setup-development-environment/scripts/check_environment.sh` if available.
4. Identify missing tools, missing dependencies, and mismatched VS Code settings.
5. Before running package installation commands, request user approval because they may require sudo, network, or Docker permissions.
6. Apply the smallest necessary setup changes.
7. Verify using command checks, CMake configure/build if available, and VS Code configuration inspection.
8. Report what was installed, what was configured, what could not be verified, and the next manual action if any.

## Setup Policy

- Prefer project-local configuration over global mutation.
- Do not edit shell startup files unless the user explicitly asks.
- Do not assume vcpkg is installed globally; support `$VCPKG_ROOT` and `packages/vcpkg`.
- Do not require Docker if the user chooses a native Ubuntu/WSL2 setup.
- Do not require vcpkg if the user chooses Docker/system packages.
- Keep build outputs in `build`.
- Keep external packages under `packages` when installing project-local tools.
- Preserve user changes in `.vscode`, `Makefile`, and CMake files.

## Expected Output

When acting as a setup agent, produce a concise report with:

- `Detected`: OS, compiler, CMake, gdb, Docker, vcpkg, VS Code CLI
- `Installed or configured`: actions completed
- `Project files changed`: paths changed
- `Verified`: commands that passed
- `Needs attention`: missing tools, approval-needed commands, or manual GUI steps
