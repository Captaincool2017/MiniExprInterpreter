# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Build and source directories
SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/interpreter

# Find all .cpp files in src/, including subdirectories
SRC := $(shell find $(SRC_DIR) -name '*.cpp')
OBJ := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC))

# Tests source
TEST_SRC = tests/test_evaluator.cpp
TEST_TARGET = $(BUILD_DIR)/test_evaluator

# Default target
all: $(TARGET)

# Link final executable
$(TARGET): $(OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each source file to an object file
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build and run tests
test: $(TEST_TARGET)
	@echo "Running tests..."
	./$(TEST_TARGET)

# Remove main.o from OBJ when linking tests
OBJ_NO_MAIN := $(filter-out $(BUILD_DIR)/src/runtime/main.o, $(OBJ))

$(TEST_TARGET): $(OBJ_NO_MAIN) $(BUILD_DIR)/tests/test_evaluator.o
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^


# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
