# Jake

**Jake** is a simple, JSON-based build tool inspired by `make`, written in C++. Instead of a `Makefile`, Jake uses a `jakefile.json` to define variables and build targets. The goal is the explicitness and simplicity.

---

## Features

* JSON-based build configuration (`jakefile.json`)
* User-defined build targets
* Variable expansion with support for **nested variables**
* Targets executed via shell commands
* Silent commands using `@` (similar to Make)
* Dynamic CLI flags (can appear anywhere in the command)
* `Ctrl + C` (SIGINT) handling with automatic cleanup
* Portable and dependency-light (only `nlohmann/json`)

---

## Requirements

- C++17-compatible compiler (e.g. `g++`, `clang++`)
- POSIX-compatible shell environment
- [nlohmann/json](https://github.com/nlohmann/json)

---

## `jakefile.json` Format

### Variables

Variables are defined once and can reference each other.

```json
"variables": {
  "CXX": "g++",
  "CXXFLAGS": "-std=c++17 -I./src/headers",
  "TARGET": "main",
  "OBJDIR": "objs",
  "OBJS": "${OBJDIR}/main.o ${OBJDIR}/parse_variables.o"
}
```

Nested variables are fully resolved.

---

### Processes (Targets)

Each target is a list of shell commands.

```json
"processes": {
  "build": [
    "@mkdir -p ${OBJDIR}",
    "${CXX} ${CXXFLAGS} -c src/main.cpp -o ${OBJDIR}/main.o",
    "${CXX} ${CXXFLAGS} -c src/headers/parse_variables.cpp -o ${OBJDIR}/parse_variables.o",
    "${CXX} -o ${TARGET} ${OBJS}"
  ],

  "clean": [
    "rm -rf ${OBJDIR} ${TARGET}"
  ]
}
```

#### Notes

* Commands starting with `@` are executed silently.
* There are **no implicit targets** — all targets are user-defined.

---

## Usage

### Basic

```bash
jake build
jake clean
```

If no target is provided, Jake will exit with an error and list available targets.

---

### Flags (can be anywhere)

Flags can appear **before or after** the target.

```bash
jake -v build
jake build -n
jake -n -v build
```

#### Supported Flags

| Flag              | Description                           |
| ----------------- | ------------------------------------- |
| `-h`, `--help`    | Show help and exit                    |
| `-n`, `--dry-run` | Print commands without executing them |
| `-v`, `--verbose` | Print additional debug information    |

---

## Ctrl + C (SIGINT)

If the user interrupts Jake with **Ctrl + C**:

* The current build is aborted
* A cleanup command is executed automatically
* Cleanup uses `OBJDIR` and `TARGET` from `jakefile.json` when available

This prevents half-built artifacts from being left behind.

---

## Building

### Installation

```
git clone https://github.com/nothingburguer/jake.git
cd jake
sudo make install
```

### Uninstallation

On the repo cloned folder, just run `sudo make uninstall`

---
