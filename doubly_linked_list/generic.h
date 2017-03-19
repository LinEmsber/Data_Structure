/* Generic functions
 * File: generic.c
 * Author: Lin Emsber
 * Create Date: 2017, Mar, 19
 */

// TODO: add BUILD_BUG_ON_ZERO(), BUILD_BUG_ON_NULL()

/* A safty way to free memroy */
void _safe_free(void **pp)
{
	if (pp != NULL && *pp != NULL){
		free(*pp);
		*pp = NULL;
	}
}

#define SAFE_FREE(p) _safe_free( (void**) &p )
