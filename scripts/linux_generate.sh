#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd -- "${SCRIPT_DIR}/.." && pwd)"

# shellcheck source=submodules_init.sh
source "${SCRIPT_DIR}/linux_git_submodules_init.sh"

COMPILER="clang"
CONFIG="release"

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
    --compiler <clang|gcc>       Compiler to use (default: clang)
    --config <debug|release>     Configuration to use (default: release)
    -h, --help                   Show this help message

Examples:
    $(basename "$0")
    $(basename "$0") --compiler gcc
    $(basename "$0") --config debug
    $(basename "$0") --compiler gcc --config debug
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

            --config)
                [[ $# -ge 2 ]] || {
                    echo "Error: --config requires a value." >&2
                    usage >&2
                    exit 1
                }

                CONFIG="$2"
                shift 2
                ;;

            --config=*)
                CONFIG="${1#*=}"
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

    case "${CONFIG}" in
        debug|release)
            ;;
        *)
            echo "Error: Invalid config '${CONFIG}'. Expected 'debug' or 'release'." >&2
            usage >&2
            exit 1
            ;;
    esac
}

select_preset()
{
    case "${COMPILER}:${CONFIG}" in
        clang:debug)
            CONFIGURE_PRESET="debug-linux-clang"
            BUILD_PRESET="build-debug-linux-clang"
            BUILD_DIR="${REPO_ROOT}/build/linux_clang_debug"
            INSTALL_DIR=""
            ;;

        clang:release)
            CONFIGURE_PRESET="release-linux-clang"
            BUILD_PRESET="build-release-linux-clang"
            BUILD_DIR="${REPO_ROOT}/build/linux_clang_release"
            INSTALL_DIR="${REPO_ROOT}/build/linux_clang_install"
            ;;

        gcc:debug)
            CONFIGURE_PRESET="debug-linux-gcc"
            BUILD_PRESET="build-debug-linux-gcc"
            BUILD_DIR="${REPO_ROOT}/build/linux_gcc_debug"
            INSTALL_DIR=""
            ;;

        gcc:release)
            CONFIGURE_PRESET="release-linux-gcc"
            BUILD_PRESET="build-release-linux-gcc"
            BUILD_DIR="${REPO_ROOT}/build/linux_gcc_release"
            INSTALL_DIR="${REPO_ROOT}/build/linux_gcc_install"
            ;;
    esac
}

check_generate_dependencies()
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

generate()
{
    init_submodules

    log "Generating with preset '${CONFIGURE_PRESET}'..."

    (
        cd "${REPO_ROOT}"
        cmake --preset "${CONFIGURE_PRESET}"
    )

    log "Generation complete."
}

generate_main()
{
    parse_args "$@"
    select_preset
    check_generate_dependencies

    log "Starting Linux generation..."
    log "Repository root: ${REPO_ROOT}"
    log "Compiler: ${COMPILER}"
    log "Configuration: ${CONFIG}"
    log "Configure preset: ${CONFIGURE_PRESET}"

    generate

    log "Linux generation finished successfully."
}

if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
    generate_main "$@"
fi