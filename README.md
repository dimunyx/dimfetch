# dimfetch

A small Linux system information display written in C++.

## Build

Requirements: a C++26 compiler and CMake. Optional system tools enable extra
details: `lspci` (GPU), `edid-decode` (monitor identification), `pacman` or
Portage (package counts), `flatpak`, `wpctl`, `pactl`, `amixer`, and `wmctrl`.
Missing optional tools are reported as unknown or unavailable; they are not
needed to build the program.

```sh
just build
./dist/dimfetch
```

Set a release version at build time with `make VERSION=0.5.0`. Use `make clean`
to remove generated object files and the executable.

## Usage

```text
dimfetch [--help | --version]
```

The output includes distribution, hardware, session, storage, memory, and
other system information. Arch and Gentoo have dedicated logos; other
distributions use a text fallback.
