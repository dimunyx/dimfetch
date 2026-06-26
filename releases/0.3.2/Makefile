CXX ?= g++
CXXFLAGS += -Wall -Wextra -std=c++26
DIST_DIR = dist
TARGET = $(DIST_DIR)/dimfetch
SRC = main.cpp modules/os.cpp modules/pc.cpp modules/monitor.cpp modules/utils.cpp modules/kernel.cpp
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
