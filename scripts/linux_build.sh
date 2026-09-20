#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"

# shellcheck source=linux_generate.sh
source "${SCRIPT_DIR}/linux_generate.sh"

build()
{
    log "Building with preset '${BUILD_PRESET}'..."

    (
        cd "${REPO_ROOT}"
        cmake --build --preset "${BUILD_PRESET}" --parallel
    )

    log "Build complete."
}

build_main()
{
    parse_args "$@"
    select_preset
    check_generate_dependencies

    log "Starting Linux build..."
    log "Repository root: ${REPO_ROOT}"
    log "Compiler: ${COMPILER}"
    log "Configuration: ${CONFIG}"
    log "Configure preset: ${CONFIGURE_PRESET}"
    log "Build preset: ${BUILD_PRESET}"

    generate
    build

    log "Linux build finished successfully."
}

if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
    build_main "$@"
fi