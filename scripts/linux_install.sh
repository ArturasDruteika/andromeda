#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd -- "${SCRIPT_DIR}/.." && pwd)"

BUILD_DIR="${REPO_ROOT}/build/release"
INSTALL_DIR="${REPO_ROOT}/build/install"

COMPILER="clang"
GENERATOR="ninja"

log()
{
    echo "[$(date -u +%H:%M:%S)] $*"
}

usage()
{
    cat <<EOF
Usage: $(basename "$0") [options]

Options:
    --compiler <clang|gcc>     Compiler to use (default: clang)
    --generator <ninja|make>   Build system to use (default: ninja)
    -h, --help                 Show this help message

Examples:
    $(basename "$0")
    $(basename "$0") --compiler gcc
    $(basename "$0") --generator make
    $(basename "$0") --compiler gcc --generator make
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

            --generator)
                [[ $# -ge 2 ]] || {
                    echo "Error: --generator requires a value." >&2
                    usage >&2
                    exit 1
                }
                GENERATOR="$2"
                shift 2
                ;;

            --generator=*)
                GENERATOR="${1#*=}"
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

    case "${GENERATOR}" in
        ninja|make)
            ;;
        *)
            echo "Error: Invalid generator '${GENERATOR}'. Expected 'ninja' or 'make'." >&2
            usage >&2
            exit 1
            ;;
    esac
}

select_toolchain()
{
    case "${COMPILER}" in
        clang)
            C_COMPILER="clang"
            CXX_COMPILER="clang++"
            ;;
        gcc)
            C_COMPILER="gcc"
            CXX_COMPILER="g++"
            ;;
    esac

    case "${GENERATOR}" in
        ninja)
            CMAKE_GENERATOR="Ninja"
            ;;
        make)
            CMAKE_GENERATOR="Unix Makefiles"
            ;;
    esac
}

check_dependencies()
{
    local dependencies=(
        cmake
        "${C_COMPILER}"
        "${CXX_COMPILER}"
    )

    case "${GENERATOR}" in
        ninja)
            dependencies+=(ninja)
            ;;
        make)
            dependencies+=(make)
            ;;
    esac

    for dependency in "${dependencies[@]}"; do
        if ! command -v "${dependency}" >/dev/null 2>&1; then
            echo "Error: Required program '${dependency}' was not found." >&2
            exit 1
        fi
    done
}

configure()
{
    log "Configuring Release build..."
    log "Build directory: ${BUILD_DIR}"
    log "Install directory: ${INSTALL_DIR}"
    log "Generator: ${CMAKE_GENERATOR}"
    log "C compiler: ${C_COMPILER}"
    log "C++ compiler: ${CXX_COMPILER}"

    cmake \
        -S "${REPO_ROOT}" \
        -B "${BUILD_DIR}" \
        -G "${CMAKE_GENERATOR}" \
        -DCMAKE_C_COMPILER="${C_COMPILER}" \
        -DCMAKE_CXX_COMPILER="${CXX_COMPILER}" \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR}"

    log "Configuration complete."
}

build()
{
    log "Building Release..."

    cmake --build "${BUILD_DIR}" --parallel

    log "Build complete."
}

install()
{
    log "Installing to ${INSTALL_DIR}..."

    cmake --install "${BUILD_DIR}"

    log "Installation complete."
}

show_install()
{
    log "Installed files:"

    if command -v tree >/dev/null 2>&1; then
        tree "${INSTALL_DIR}"
    else
        find "${INSTALL_DIR}" -type f -print
    fi
}

main()
{
    parse_args "$@"
    select_toolchain
    check_dependencies

    log "Starting Linux install..."
    log "Repository root: ${REPO_ROOT}"

    configure
    build
    install
    show_install

    log "Linux install finished successfully."
}

main "$@"