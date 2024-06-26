# Daniel Tsadik
# Tsadik88@gmail.com   

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Iinclude

# Source directories
SRC_DIR = src
INCLUDE_DIR = include

# Find all cpp files in the src directory
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Main file
MAIN = main.cpp

# Output executable
TARGET = main

all: $(TARGET) Test

# Rule to compile the program
$(TARGET): $(OBJECTS) $(MAIN)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Pattern rule to compile .o files from .cpp files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Pattern rule to compile the test files
Test: Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

Test.o: Test.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean rule
.PHONY: clean all
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET) *.o Test