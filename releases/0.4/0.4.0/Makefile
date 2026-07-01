CXX ?= g++
CXXFLAGS = -Wall -Wextra -std=c++26 -Wno-ignored-attributes
MAKEFLAGS += --jobs=$(shell nproc)
DIST_DIR = dist
TARGET = $(DIST_DIR)/dimfetch
SRC = $(wildcard src/*.cpp src/modules/*.cpp)
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
