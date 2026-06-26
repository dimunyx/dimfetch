CXX ?= g++
CXXFLAGS = -Wall -Wextra -std=c++26 -march=native -pipe
DIST_DIR = build
TARGET = $(DIST_DIR)/dimfetch
SRC = src/main.cpp
OBJ = $(SRC:.cpp=.o)

all: build

build: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(DIST_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(DIST_DIR) $(OBJ)

.PHONY: all clean
