CXX ?= g++
CXXFLAGS = -Wall -Wextra -std=c++26
DIST_DIR = dist
TARGET = $(DIST_DIR)/dimfetch
SRC = src/main.cpp src/modules/os.cpp src/modules/pc.cpp src/modules/monitor.cpp src/modules/utils.cpp src/modules/kernel.cpp
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
