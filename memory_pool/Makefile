# name of executable
NAME = main

# compiler to use
CC ?= gcc

# compiler flags and options
CFLAGS_common = -Wall -std=gnu99
CFLAGS_opt  = -O0

# source files
SRCS = main.c
SRCS_LIB = mem_pool.c

# run the compilation
$(NAME): $(SRCS_LIB)
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) $(SRCS_LIB) $@.c -o $@

# clean 
.PHONY: clean
clean:
	$(RM) $(EXEC) *.o
