# target
TARGET = main

# compiler
CC = gcc

# flags
CFLAGS = -Wall -g

# source code
SRCS = tree.c main.c
OBJS = $(SRCS: .c=.o)

# header
DEPS = tree.h

# object
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(CFLAGS_INCLUDE)


$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(CFLAGS_INCLUDE)


# clean
.PHONY: clean
clean:
	$(RM) $(EXEC) *.o $(TARGET)
