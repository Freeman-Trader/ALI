# Compiler
CC = gcc

# Remove Command
RM = rm

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Target executable
TARGET = main

# Source files
SRCS = $(TARGET).cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Library
LIB = -lstdc++

# Default rule
all: $(TARGET)
	make $(TARGET)

# Rule to build and run the executable
$(TARGET):
	$(CC) $(CFLAGS) $(SRCS) -o $(OBJS) $(LIB)
	./$(OBJS)

# Rule to build and run the debug executable
debug:
	$(CC) $(CFLAGS) $(SRCS) -g -o $(OBJS) $(LIB)
	gdb ./$(OBJS)

# Clean rule
clean:
	$(RM) $(OBJS) $(TARGET)