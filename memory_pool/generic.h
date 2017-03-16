/* Generic functions
 * File: generic.h
 * Author: Lin Emsber
 * Create Date: 2017, Mar, 14
 */

#include <stdio.h>
#include <stdlib.h>
#include "mem_pool.h"


#ifndef GENERIC_H
#define GENERIC_H


#define SAFE_FREE(p) _safe_free( (void**) &p )

/* A safty way to free memroy */
void _safe_free(void **pp);

/* print structure mem_pool_t for debug */
void print_mem_pool( mem_pool_t * mp );

/* print structure mem_block_t for debug */
void print_mem_block( mem_block_t * mb );


/* align byte boundary */
uint32_t size_align(uint32_t size);

/* decide mp_entry size */
uint32_t size_check(uint32_t size);

#endif
