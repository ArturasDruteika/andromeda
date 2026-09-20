#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd -- "${SCRIPT_DIR}/.." && pwd)"

# shellcheck source=linux_setup.sh
source "${SCRIPT_DIR}/linux_setup.sh"

log()
{
    echo "[$(date -u +%H:%M:%S)] $*"
}

run_builds()
{
    log "Building all Linux configurations..."

    log "Building Clang Debug..."
    "${REPO_ROOT}/scripts/linux_build.sh" \
        --compiler clang \
        --config debug

    log "Building Clang Release..."
    "${REPO_ROOT}/scripts/linux_install.sh" \
        --compiler clang \
        --config release

    log "Building GCC Debug..."
    "${REPO_ROOT}/scripts/linux_build.sh" \
        --compiler gcc \
        --config debug

    log "Building GCC Release..."
    "${REPO_ROOT}/scripts/linux_install.sh" \
        --compiler gcc \
        --config release

    log "All Linux configurations built successfully."
}

package_for_act()
{
    if [[ "${ACT:-}" != "true" ]]; then
        return
    fi

    log "ACT=true detected, packaging Release installations..."

    local clang_install="${REPO_ROOT}/build/linux_clang_install"
    local gcc_install="${REPO_ROOT}/build/linux_gcc_install"

    if [[ ! -d "${clang_install}" ]]; then
        echo "Error: Clang install directory missing: ${clang_install}" >&2
        exit 1
    fi

    if [[ ! -d "${gcc_install}" ]]; then
        echo "Error: GCC install directory missing: ${gcc_install}" >&2
        exit 1
    fi

    tar -czf "${REPO_ROOT}/andromeda-linux-clang-release.tar.gz" \
        -C "${REPO_ROOT}/build" \
        linux_clang_install

    tar -czf "${REPO_ROOT}/andromeda-linux-gcc-release.tar.gz" \
        -C "${REPO_ROOT}/build" \
        linux_gcc_install

    ls -lah \
        "${REPO_ROOT}/andromeda-linux-clang-release.tar.gz" \
        "${REPO_ROOT}/andromeda-linux-gcc-release.tar.gz"
}

main()
{
    log "Starting Linux CI..."
    log "Repository root: ${REPO_ROOT}"

    install_build_deps_linux
    run_builds
    package_for_act

    log "Linux CI finished successfully."
}

main "$@"