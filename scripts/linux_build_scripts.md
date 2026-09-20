# Linux Build Scripts

The Linux scripts are split into separate stages so that each script has a single responsibility while reusing the previous stage.

## Script hierarchy

```text
linux_git_submodules_init.sh
    │
    │  Initializes and updates Git submodules recursively
    ▼
linux_generate.sh
    │
    │  Initialize Submodules + Configure / Generate
    ▼
linux_build.sh
    │
    │  Initialize Submodules + Generate + Build
    ▼
linux_install.sh
    │
    │  Initialize Submodules + Generate + Build + Install
    ▼
Release installation


linux_setup.sh
    │
    │  Installs system/build dependencies
    ▼
linux_ci.sh
    │
    ├── Setup
    ├── Clang Debug
    ├── Clang Release
    ├── GCC Debug
    └── GCC Release
```

## Scripts

### `linux_git_submodules_init.sh`

Initializes and updates all Git submodules recursively.

It performs the equivalent of:

```bash
git submodule sync --recursive
git submodule update --init --recursive
```

This includes nested submodules inside other submodules.

It is automatically used by:

```text
linux_generate.sh
    ↓
linux_build.sh
    ↓
linux_install.sh
```

It can also be executed directly:

```bash
./scripts/linux_git_submodules_init.sh
```

---

### `linux_setup.sh`

Installs the Linux packages required to configure and build the project.

It is primarily used by:

```text
linux_ci.sh
```

It can also be executed directly:

```bash
./scripts/linux_setup.sh
```

---

### `linux_generate.sh`

Initializes Git submodules and configures/generates the CMake build system using `CMakePresets.json`.

Conceptually:

```text
linux_git_submodules_init.sh
            ↓
         Generate
```

Examples:

```bash
# Clang Release
./scripts/linux_generate.sh

# Clang Debug
./scripts/linux_generate.sh --config debug

# GCC Release
./scripts/linux_generate.sh --compiler gcc

# GCC Debug
./scripts/linux_generate.sh --compiler gcc --config debug
```

---

### `linux_build.sh`

Sources `linux_generate.sh` and adds the build stage.

Conceptually:

```text
linux_git_submodules_init.sh
            ↓
         Generate
            ↓
          Build
```

Therefore:

```bash
./scripts/linux_build.sh
```

performs:

```text
Initialize Submodules → Generate → Build
```

Examples:

```bash
# Clang Release
./scripts/linux_build.sh

# Clang Debug
./scripts/linux_build.sh --config debug

# GCC Release
./scripts/linux_build.sh --compiler gcc

# GCC Debug
./scripts/linux_build.sh --compiler gcc --config debug
```

---

### `linux_install.sh`

Sources `linux_build.sh` and adds the installation stage.

Conceptually:

```text
linux_git_submodules_init.sh
            ↓
         Generate
            ↓
          Build
            ↓
         Install
```

Therefore:

```bash
./scripts/linux_install.sh
```

performs:

```text
Initialize Submodules → Generate → Build → Install
```

Installation is intended for Release builds.

Examples:

```bash
# Clang Release
./scripts/linux_install.sh

# GCC Release
./scripts/linux_install.sh --compiler gcc
```

The resulting installations are:

```text
build/
├── linux_clang_install/
│   ├── bin/
│   └── lib/
│
└── linux_gcc_install/
    ├── bin/
    └── lib/
```

---

### `linux_ci.sh`

Runs the complete Linux CI pipeline.

It first uses `linux_setup.sh` to install the required Linux build dependencies.

Each build then goes through `linux_generate.sh`, which automatically initializes and updates Git submodules before CMake generation.

```text
linux_ci.sh
│
├── Linux Setup
│   └── Install system/build dependencies
│
├── Clang Debug
│   └── Submodules → Generate → Build
│
├── Clang Release
│   └── Submodules → Generate → Build → Install
│
├── GCC Debug
│   └── Submodules → Generate → Build
│
└── GCC Release
    └── Submodules → Generate → Build → Install
```

Run locally with:

```bash
./scripts/linux_ci.sh
```

When running through `act` with `ACT=true`, the Release installations are also packaged as `.tar.gz` archives.

## CMake presets

The scripts do not define compiler flags, generators, or CMake build directories themselves.

Those configurations are defined by:

```text
CMakePresets.json
```

The Linux configurations are:

| Compiler | Configuration | Configure Preset | Build Preset |
|---|---|---|---|
| Clang | Debug | `debug-linux-clang` | `build-debug-linux-clang` |
| Clang | Release | `release-linux-clang` | `build-release-linux-clang` |
| GCC | Debug | `debug-linux-gcc` | `build-debug-linux-gcc` |
| GCC | Release | `release-linux-gcc` | `build-release-linux-gcc` |

## Typical usage

Initialize/update Git submodules only:

```bash
./scripts/linux_git_submodules_init.sh
```

For development:

```bash
./scripts/linux_build.sh --config debug
```

For a Release installation:

```bash
./scripts/linux_install.sh
```

For GCC:

```bash
./scripts/linux_install.sh --compiler gcc
```

To validate all supported Linux configurations:

```bash
./scripts/linux_ci.sh
```

## Summary

```text
linux_git_submodules_init.sh = Initialize/update Git submodules
linux_setup.sh               = Install Linux system dependencies
linux_generate.sh            = Submodules + Generate
linux_build.sh               = Submodules + Generate + Build
linux_install.sh             = Submodules + Generate + Build + Install
linux_ci.sh                  = Setup + all Linux Debug/Release builds
```

The dependency chain is:

```text
linux_git_submodules_init.sh
            ↓
linux_generate.sh
            ↓
linux_build.sh
            ↓
linux_install.sh

linux_setup.sh ───────────────┐
                             ▼
                        linux_ci.sh
                             │
                             └── invokes build/install pipelines
```