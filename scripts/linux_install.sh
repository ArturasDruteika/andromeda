#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd -- "${SCRIPT_DIR}/.." && pwd)"

COMPILER="clang"

CONFIGURE_PRESET=""
BUILD_PRESET=""
BUILD_DIR=""
INSTALL_DIR=""

log()
{
    echo "[$(date -u +%H:%M:%S)] $*"
}

usage()
{
    cat <<EOF
Usage: $(basename "$0") [options]

Options:
    --compiler <clang|gcc>     Compiler preset to use (default: clang)
    -h, --help                 Show this help message

Examples:
    $(basename "$0")
    $(basename "$0") --compiler clang
    $(basename "$0") --compiler gcc
EOF
}

parse_args()
{
    while [[ $# -gt 0 ]]; do
        case "$1" in
            --compiler)
                [[ $# -ge 2 ]] || {
                    echo "Error: --compiler requires a value." >&2
                    usage >&2
                    exit 1
                }

                COMPILER="$2"
                shift 2
                ;;

            --compiler=*)
                COMPILER="${1#*=}"
                shift
                ;;

            -h|--help)
                usage
                exit 0
                ;;

            --)
                shift
                break
                ;;

            *)
                echo "Error: Unknown argument '$1'." >&2
                usage >&2
                exit 1
                ;;
        esac
    done

    case "${COMPILER}" in
        clang|gcc)
            ;;
        *)
            echo "Error: Invalid compiler '${COMPILER}'. Expected 'clang' or 'gcc'." >&2
            usage >&2
            exit 1
            ;;
    esac
}

select_preset()
{
    case "${COMPILER}" in
        clang)
            CONFIGURE_PRESET="release-linux-clang"
            BUILD_PRESET="build-release-linux-clang"
            BUILD_DIR="${REPO_ROOT}/build/linux_clang_release"
            INSTALL_DIR="${REPO_ROOT}/build/linux_clang_install"
            ;;

        gcc)
            CONFIGURE_PRESET="release-linux-gcc"
            BUILD_PRESET="build-release-linux-gcc"
            BUILD_DIR="${REPO_ROOT}/build/linux_gcc_release"
            INSTALL_DIR="${REPO_ROOT}/build/linux_gcc_install"
            ;;
    esac
}

check_dependencies()
{
    local dependencies=(cmake)

    case "${COMPILER}" in
        clang)
            dependencies+=(clang clang++ ninja)
            ;;

        gcc)
            dependencies+=(gcc g++ make)
            ;;
    esac

    for dependency in "${dependencies[@]}"; do
        if ! command -v "${dependency}" >/dev/null 2>&1; then
            echo "Error: Required program '${dependency}' was not found." >&2
            exit 1
        fi
    done

    if [[ ! -f "${REPO_ROOT}/CMakePresets.json" ]]; then
        echo "Error: CMakePresets.json was not found in '${REPO_ROOT}'." >&2
        exit 1
    fi
}

configure()
{
    log "Configuring with preset '${CONFIGURE_PRESET}'..."
    log "Build directory: ${BUILD_DIR}"
    log "Install directory: ${INSTALL_DIR}"

    (
        cd "${REPO_ROOT}"
        cmake --preset "${CONFIGURE_PRESET}"
    )

    log "Configuration complete."
}

build()
{
    log "Building with preset '${BUILD_PRESET}'..."

    (
        cd "${REPO_ROOT}"
        cmake --build --preset "${BUILD_PRESET}" --parallel
    )

    log "Build complete."
}

install()
{
    log "Installing runtime to ${INSTALL_DIR}..."

    # Remove files left by previous installations.
    rm -rf "${INSTALL_DIR}"

    # Install only the runtime component.
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

main()
{
    parse_args "$@"
    select_preset
    check_dependencies

    log "Starting Linux installation..."
    log "Repository root: ${REPO_ROOT}"
    log "Compiler: ${COMPILER}"
    log "Configure preset: ${CONFIGURE_PRESET}"
    log "Build preset: ${BUILD_PRESET}"

    configure
    build
    install
    show_install

    log "Linux installation finished successfully."
}

main "$@"