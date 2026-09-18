# Linux Build Scripts

The Linux scripts are split into separate stages so that each script has a single responsibility while reusing the previous stage.

## Script hierarchy

```text
linux_setup.sh
    │
    │  Installs system/build dependencies
    │
    └──────────────────────────────┐
                                   ▼
linux_generate.sh             linux_ci.sh
    │                              │
    │  Configure / Generate        │  CI orchestration
    ▼                              │
linux_build.sh                     ├── setup
    │                              ├── Clang Debug
    │  Generate + Build            ├── Clang Release
    ▼                              ├── GCC Debug
linux_install.sh                   └── GCC Release
    │
    │  Generate + Build + Install
    ▼
Release installation
```

## Scripts

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

Configures and generates the CMake build system using `CMakePresets.json`.

This is the lowest-level build script.

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
linux_generate.sh
        ↓
      build
```

Therefore:

```bash
./scripts/linux_build.sh
```

performs:

```text
Generate → Build
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
linux_generate.sh
        ↓
linux_build.sh
        ↓
     install
```

Therefore:

```bash
./scripts/linux_install.sh
```

performs:

```text
Generate → Build → Install
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

It uses `linux_setup.sh` to install build dependencies and then validates every Linux compiler/configuration combination defined by the project.

```text
linux_ci.sh
│
├── Setup Linux dependencies
│
├── Clang Debug
│   └── Generate → Build
│
├── Clang Release
│   └── Generate → Build → Install
│
├── GCC Debug
│   └── Generate → Build
│
└── GCC Release
    └── Generate → Build → Install
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

For development:

```bash
./scripts/linux_build.sh --config debug
```

For a clean Release installation:

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
linux_generate.sh = Generate
linux_build.sh    = Generate + Build
linux_install.sh  = Generate + Build + Install
linux_ci.sh       = Setup + all Linux Debug/Release builds
linux_setup.sh    = System dependencies
```