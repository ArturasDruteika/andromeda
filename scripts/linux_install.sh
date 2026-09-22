#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"

# shellcheck source=linux_build.sh
source "${SCRIPT_DIR}/linux_build.sh"

install()
{
    log "Installing runtime packages to ${INSTALL_DIR}..."

    # Remove the previous complete installation so stale files from
    # old examples/builds cannot survive.
    rm -rf "${INSTALL_DIR}"

    cmake --install "${BUILD_DIR}" \
        --component runtime

    if [[ ! -d "${INSTALL_DIR}" ]]; then
        echo "Error: Install directory was not created: ${INSTALL_DIR}" >&2
        exit 1
    fi

    # Verify that the expected example packages were installed.
    local examples=(
        "solar_system_simulation"
        "sphere_cubes"
    )

    local example

    for example in "${examples[@]}"; do
        if [[ ! -d "${INSTALL_DIR}/${example}" ]]; then
            echo "Error: Example was not installed: ${example}" >&2
            exit 1
        fi

        if [[ ! -d "${INSTALL_DIR}/${example}/bin" ]]; then
            echo "Error: Missing bin directory for: ${example}" >&2
            exit 1
        fi

        if [[ ! -d "${INSTALL_DIR}/${example}/lib" ]]; then
            echo "Error: Missing lib directory for: ${example}" >&2
            exit 1
        fi

        if [[ ! -d "${INSTALL_DIR}/${example}/res" ]]; then
            echo "Error: Missing res directory for: ${example}" >&2
            exit 1
        fi
    done

    log "Installation complete."
}

show_install()
{
    log "Installed files:"

    if command -v tree >/dev/null 2>&1; then
        tree "${INSTALL_DIR}"
    else
        find "${INSTALL_DIR}" -print
    fi
}

install_main()
{
    parse_args "$@"

    if [[ "${CONFIG}" != "release" ]]; then
        echo "Error: Installation is only supported for the release configuration." >&2
        exit 1
    fi

    select_preset
    check_generate_dependencies

    log "Starting Linux installation..."
    log "Repository root: ${REPO_ROOT}"
    log "Compiler: ${COMPILER}"
    log "Configuration: ${CONFIG}"
    log "Configure preset: ${CONFIGURE_PRESET}"
    log "Build preset: ${BUILD_PRESET}"
    log "Install directory: ${INSTALL_DIR}"

    generate
    build
    install
    show_install

    log "Linux installation finished successfully."
}

if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
    install_main "$@"
fi