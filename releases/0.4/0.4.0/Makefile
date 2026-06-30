CXX ?= g++
CXXFLAGS = -Wall -Wextra -std=c++26 -Wno-ignored-attributes
MAKEFLAGS += --jobs=$(shell nproc)
DIST_DIR = dist
TARGET = $(DIST_DIR)/dimfetch
SRC = src/modules/version.cpp src/modules/system-init.cpp src/modules/volume.cpp src/main.cpp src/modules/shell.cpp src/modules/brightness.cpp src/modules/packages.cpp src/modules/battery.cpp src/modules/uptime.cpp src/modules/disk.cpp src/modules/memory.cpp src/modules/gpu.cpp src/modules/cpu.cpp src/modules/wm.cpp src/modules/terminal.cpp src/modules/os.cpp src/modules/pc.cpp src/modules/monitor.cpp src/modules/utils.cpp src/modules/kernel.cpp
OBJ = $(SRC:.cpp=.o)

all: build

build: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(DIST_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -Isrc -c $< -o $@

clean:
	rm -rf $(DIST_DIR) $(OBJ)

.PHONY: all clean build
