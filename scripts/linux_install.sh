#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"

# shellcheck source=linux_build.sh
source "${SCRIPT_DIR}/linux_build.sh"

install()
{
    log "Installing runtime to ${INSTALL_DIR}..."

    rm -rf "${INSTALL_DIR}"

    cmake --install "${BUILD_DIR}" \
        --component runtime

    if [[ ! -d "${INSTALL_DIR}" ]]; then
        echo "Error: Install directory was not created: ${INSTALL_DIR}" >&2
        exit 1
    fi

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