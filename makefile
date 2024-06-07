BITS ?= 64

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

CC = g++
CFLAGS = -MMD -ggdb -O3 -std=c++20 -I./include -DDEBUG 
LDFLAGS = -lfmt -lprotobuf

# Recursively find all .cc files
SRC = $(shell find $(SRC_DIR) -name '*.cc')

# Object files (flattened structure)
OBJ = $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SRC))

# Dependency files
DEPS = $(OBJ:.o=.d)

# Binary executable
TARGET = rabia

.PHONY: all clean directories

all: directories $(BIN_DIR)/$(TARGET)

directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)
	@find $(SRC_DIR) -type d -exec mkdir -p $(OBJ_DIR)/{} \;

$(BIN_DIR)/$(TARGET): $(OBJ)
	@echo "[LD] $^ --> $@"
	@$(CC) $(OBJ) $(LDFLAGS) -o $@

# Pattern rule for compiling .cc to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(dir $@)
	@echo "[CXX] $< --> $@"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up..."
	@rm -rf $(BIN_DIR) $(OBJ_DIR)

-include $(DEPS)