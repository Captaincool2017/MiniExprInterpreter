CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
BUILD_DIR = build

SRC := $(wildcard main.cpp src/*.cpp)
OBJ := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC))
TARGET := $(BUILD_DIR)/interpreter

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
