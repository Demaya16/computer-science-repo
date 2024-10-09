# Define the compiler and the flags
CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic

# Define the target executable
TARGET=growing_arrays

# Define the source and object files
SRC=growing_arrays.c test_growing_arrays.c
OBJ=$(SRC:.c=.o)

# Default target
all: $(TARGET)

# Linking the object files to create the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compiling the source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

