#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd -- "${SCRIPT_DIR}/.." && pwd)"

submodules_log()
{
    echo "[$(date -u +%H:%M:%S)] $*"
}

init_submodules()
{
    if [[ ! -d "${REPO_ROOT}/.git" ]]; then
        submodules_log "Git repository not detected. Skipping submodule initialization."
        return
    fi

    if ! command -v git >/dev/null 2>&1; then
        echo "Error: Required program 'git' was not found." >&2
        exit 1
    fi

    submodules_log "Synchronizing git submodules..."
    git -C "${REPO_ROOT}" submodule sync --recursive

    submodules_log "Initializing and updating git submodules..."
    git -C "${REPO_ROOT}" submodule update --init --recursive

    submodules_log "Git submodules initialized successfully."
}

if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
    init_submodules
fi