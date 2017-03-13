CC ?= gcc
CFLAGS_common ?= -Wall -std=gnu99
CFLAGS_opt  = -O0

SRCS_common = main.c

EXEC = main 


main: $(SRCS_common) mem_pool.c mem_pool.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
	 	-o $@ $(SRCS_common) $@.c

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o 
