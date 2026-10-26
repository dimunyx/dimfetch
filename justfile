version := "0.5.0"
build_dir := "build"

default: build

configure version=version:
    cmake -S . -B {{build_dir}} -DCMAKE_BUILD_TYPE=Release -DDIMFETCH_VERSION={{version}}

build version=version: (configure version)
    cmake --build {{build_dir}} --parallel

run version=version: (build version)
    ./{{build_dir}}/dimfetch

clean:
    cmake -E rm -rf {{build_dir}}

reconfigure version=version:
    cmake -E rm -rf {{build_dir}}
    just configure {{version}}
