#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd -- "${SCRIPT_DIR}/.." && pwd)"

# CI-only packaging for act local runs.
: "${BUILD_DIR:=build}"

log()
{
    echo "[$(date -u +%H:%M:%S)] $*"
}

run_build()
{
    log "Running build script..."
    "${REPO_ROOT}/scripts/linux_build.sh"
}

run_install()
{
    log "Running install script..."
    "${REPO_ROOT}/scripts/linux_install.sh"
}

package_for_act()
{
    if [[ "${ACT:-}" != "true" ]]; then
        return
    fi

    log "ACT=true detected, packaging install -> tar.gz"

    if [[ ! -d "${REPO_ROOT}/${BUILD_DIR}/install" ]]; then
        echo "ERROR: install dir missing: ${REPO_ROOT}/${BUILD_DIR}/install"
        exit 1
    fi

    tar -czf andromeda-ubuntu-release.tar.gz \
        -C "${REPO_ROOT}/${BUILD_DIR}" \
        install

    ls -lah andromeda-ubuntu-release.tar.gz
}

main()
{
    # Ensure submodules are initialized and updated
    if [[ -d "${REPO_ROOT}/.git" ]]; then
        log "Updating git submodules..."
        git -C "${REPO_ROOT}" submodule sync --recursive
        git -C "${REPO_ROOT}" submodule update --init --recursive
    fi

    run_build
    run_install
    package_for_act

    log "Done"
}

main "$@"