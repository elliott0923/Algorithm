# Variables for compiler and flags
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

# Directories for object and binary files
BIN_DIR = bin
SRC_DIR = src
OBJ_FILES = main_opt.o

# Default target to build the optimized version
all: $(BIN_DIR)/cb

# Target for the optimized version of the binary
$(BIN_DIR)/cb: $(OBJ_FILES) 
	mkdir -p $(BIN_DIR)          # Create bin directory if it doesn't exist
	$(CC) $(OPTFLAGS) $(OBJ_FILES) -o $(BIN_DIR)/cb

# Rule to compile src/main.cpp into main_opt.o
main_opt.o: $(SRC_DIR)/main.cpp 
	$(CC) $(CFLAGS) -I$(SRC_DIR) $(OPTFLAGS) -o $@ $<


# Clean all generated object files and binary
clean:
	rm -rf *.o lib/*.a lib/*.o $(BIN_DIR)/*