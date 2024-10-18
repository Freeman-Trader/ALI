# Makefile

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Source files
SOURCES = Main.cpp

# Output executable
TARGET = Main

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean target
clean:
	rm -f $(TARGET)
