#ifndef MEM_POOL_H
#define MEM_POOL_H

#include <stdio.h>
#include <stdint.h>

/* typedef */
typedef char * mem_pool_handle;

typedef struct _mem_pool_block mem_pool_block_t;
typedef struct _mem_pool mem_pool_t;

/* structure */
struct _mem_pool_block {
	char * start;
	uint32_t block_size;

	struct _mem_pool_block * next;
	uint8_t is_block_start;
};

struct _mem_pool {
	uint32_t block_size;
	uint32_t block_count;

	char * start;
	char * end;

	struct _mem_pool_block * free_blocks_head;
	struct _mem_pool_block * free_blocks_tail;

	struct _mem_pool * next;
};


/* function */
mem_pool_handle mem_pool_create_pool(uint32_t block_size);
void mem_pool_destroy_pool(mem_pool_handle pool);

char * mem_pool_alloc(mem_pool_handle handle);
int mem_pool_free(mem_pool_handle handle, char * pointer);

void mem_pool_print_info(mem_pool_handle pool);


#endif
