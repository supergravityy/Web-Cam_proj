#!/usr/bin/env bash
set -u

missing_required=0

check_command() {
    local name="$1"
    local requirement="$2"
    if command -v "$name" >/dev/null 2>&1; then
        printf '[OK]   %-10s command %-18s %s\n' "$requirement" "$name" "$(command -v "$name")"
    else
        printf '[MISS] %-10s command %-18s not found\n' "$requirement" "$name"
        if [ "$requirement" = "required" ]; then
            missing_required=$((missing_required + 1))
        fi
    fi
}

check_pkg_config() {
    local name="$1"
    local requirement="$2"
    if command -v pkg-config >/dev/null 2>&1 && pkg-config --exists "$name"; then
        printf '[OK]   %-10s pkg-config %-12s %s\n' "$requirement" "$name" "$(pkg-config --modversion "$name" 2>/dev/null)"
    else
        printf '[MISS] %-10s pkg-config %-12s not found\n' "$requirement" "$name"
        if [ "$requirement" = "required" ]; then
            missing_required=$((missing_required + 1))
        fi
    fi
}

check_file() {
    local file="$1"
    local requirement="$2"
    if [ -e "$file" ]; then
        printf '[OK]   %-10s file %-24s present\n' "$requirement" "$file"
    else
        printf '[MISS] %-10s file %-24s missing\n' "$requirement" "$file"
        if [ "$requirement" = "required" ]; then
            missing_required=$((missing_required + 1))
        fi
    fi
}

check_dir() {
    local dir="$1"
    local requirement="$2"
    if [ -d "$dir" ]; then
        printf '[OK]   %-10s dir  %-24s present\n' "$requirement" "$dir"
    else
        printf '[MISS] %-10s dir  %-24s missing\n' "$requirement" "$dir"
        if [ "$requirement" = "required" ]; then
            missing_required=$((missing_required + 1))
        fi
    fi
}

echo '== Host tools =='
check_command g++ required
check_command gcc required
check_command make required
check_command cmake required
check_command ctest required
check_command gdb required
check_command pkg-config required
check_command git required
check_command curl required
check_command docker optional
check_command code optional

echo
echo '== Libraries =='
check_pkg_config gtest required
check_pkg_config opencv4 required
check_pkg_config Qt6Core required
check_pkg_config Qt6Widgets required

echo
echo '== vcpkg =='
if [ -n "${VCPKG_ROOT:-}" ] && [ -x "$VCPKG_ROOT/vcpkg" ]; then
    printf '[OK]   optional   VCPKG_ROOT       %s\n' "$VCPKG_ROOT"
elif [ -x "packages/vcpkg/vcpkg" ]; then
    printf '[OK]   optional   project vcpkg    packages/vcpkg/vcpkg\n'
else
    printf '[MISS] optional   vcpkg            not found in VCPKG_ROOT or packages/vcpkg\n'
fi

echo
echo '== Project files =='
check_file docs/requirements.md required
check_file Makefile required
check_file CMakeLists.txt required
check_file CMakePresets.json required
check_file vcpkg.json required
check_file .vscode/c_cpp_properties.json optional
check_file .vscode/tasks.json optional
check_file .vscode/launch.json optional

echo
echo '== Project directories =='
check_dir code/Common required
check_dir code/Client required
check_dir code/Server required
check_dir tests/unit required
check_dir tests/integration optional
check_dir build optional
check_dir packages optional

echo
echo '== CMake outputs =='
if [ -f build/compile_commands.json ]; then
    printf '[OK]   optional   file %-24s present\n' 'build/compile_commands.json'
else
    printf '[MISS] optional   file %-24s missing; run cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug\n' 'build/compile_commands.json'
fi

echo
if [ "$missing_required" -gt 0 ]; then
    printf '[FAIL] required checks missing: %s\n' "$missing_required"
    exit 1
fi

printf '[OK] required checks passed\n'
