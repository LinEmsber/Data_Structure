/* Generic functions
 * File: generic.h
 * Author: Lin Emsber
 * Create Date: 2017, Mar, 14
 */


#ifndef GENERIC_H
#define GENERIC_H



// TODO: add data_alignment()


// ========== free ==========
void _safe_free(void **pp)
{
	if (pp != NULL && *pp != NULL){
		free(*pp);
		*pp = NULL;
	}
}

#define SAFE_FREE(p) _safe_free( (void**) &p )


/* align byte boundary
 */
uint32_t size_align(uint32_t size)
{
	return (size + (MEM_POOL_ALIGN_SIZE - 1)) & ~(MEM_POOL_ALIGN_SIZE - 1);
}

/* decide mp_entry size
 */
uint32_t size_check(uint32_t size)
{
	return size <= 0 ? MEM_POOL_SIZE : size_align(size);
}

#endif
