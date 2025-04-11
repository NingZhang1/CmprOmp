# Compiler selection
CC ?= gcc

# Compiler flags
CFLAGS = -O2 -fopenmp

# Target executable
TARGET = test

# Source files
SRCS = test.cpp

# Default rule
all: $(TARGET)

# Build rule
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -pthread -o $@ $< -lpthread -ldl

# Clean rule
clean:
	rm -f $(TARGET)

# Usage instructions
help:
    @echo "Usage:"
	@echo "  make          - Build the program using the default compiler (gcc)"
	@echo "  make CC=icc   - Build the program using Intel compiler"
	@echo "  make CC=clang - Build the program using Clang compiler"
	@echo "  make clean    - Remove the built executable"