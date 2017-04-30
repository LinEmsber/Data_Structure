#ifndef MEM_POOL_H
#define MEM_POOL_H

#include <stdio.h>
#include <stdint.h>

/* typedef */
typedef uint8_t * mem_pool_handle;

typedef struct _mem_pool_block mem_pool_block_t;
typedef struct _mem_pool mem_pool_t;

/* structure */
struct _mem_pool_block {
	uint8_t * start;
	uint32_t block_size;

	struct _mem_pool_block * next;
	uint8_t is_block_start;
};

struct _mem_pool {
	uint32_t block_size;
	uint32_t block_count;

	uint8_t * start;
	uint8_t * end;

	struct _mem_pool_block * free_blocks_head;
	struct _mem_pool_block * free_blocks_tail;

	struct _mem_pool * next;
};


/* function */
mem_pool_handle mem_pool_create_pool(size_t _block_size, size_t _block_count);
void mem_pool_destroy_pool(mem_pool_handle pool);

uint8_t * mem_pool_alloc(mem_pool_handle handle);
int mem_pool_free(mem_pool_handle handle, uint8_t * pointer);

void mem_pool_print_info(mem_pool_handle pool);


#endif
