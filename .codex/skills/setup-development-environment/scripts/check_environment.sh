#!/usr/bin/env bash
set -u

check_command() {
    local name="$1"
    if command -v "$name" >/dev/null 2>&1; then
        printf '[OK] %-18s %s\n' "$name" "$(command -v "$name")"
    else
        printf '[MISS] %-16s not found\n' "$name"
    fi
}

check_pkg_config() {
    local name="$1"
    if command -v pkg-config >/dev/null 2>&1 && pkg-config --exists "$name"; then
        printf '[OK] pkg-config %-7s %s\n' "$name" "$(pkg-config --modversion "$name" 2>/dev/null)"
    else
        printf '[MISS] pkg-config %-5s not found\n' "$name"
    fi
}

echo '== Host tools =='
check_command g++
check_command gcc
check_command make
check_command cmake
check_command gdb
check_command pkg-config
check_command git
check_command curl
check_command docker
check_command code

echo
echo '== Libraries =='
check_pkg_config opencv4
check_pkg_config Qt6Core
check_pkg_config Qt6Widgets

echo
echo '== vcpkg =='
if [ -n "${VCPKG_ROOT:-}" ] && [ -x "$VCPKG_ROOT/vcpkg" ]; then
    printf '[OK] VCPKG_ROOT       %s\n' "$VCPKG_ROOT"
elif [ -x "packages/vcpkg/vcpkg" ]; then
    printf '[OK] project vcpkg    packages/vcpkg/vcpkg\n'
else
    printf '[MISS] vcpkg          not found in VCPKG_ROOT or packages/vcpkg\n'
fi

echo
echo '== Project files =='
for file in docs/requirements.md Makefile CMakeLists.txt .vscode/c_cpp_properties.json .vscode/tasks.json .vscode/launch.json; do
    if [ -e "$file" ]; then
        printf '[OK] %-24s present\n' "$file"
    else
        printf '[MISS] %-22s missing\n' "$file"
    fi
done
