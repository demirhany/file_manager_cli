# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -Iinclude

# Directories
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
LOG_DIR = logs

# Target executable
TARGET = $(BIN_DIR)/file_manager

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# Default target
all: setup $(TARGET)

# Build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create necessary directories
setup:
	mkdir -p $(BIN_DIR) $(LOG_DIR)

# Clean up generated files
clean:
	rm -rf $(BIN_DIR)/* $(LOG_DIR)/*

# Clean up everything including logs and binary
clean-all: clean
	rm -rf $(BIN_DIR) $(LOG_DIR)

# Phony targets
.PHONY: all setup clean clean-all

