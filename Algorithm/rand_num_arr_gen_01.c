/* Using rand() to generate a random integer number array */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* generate a random number array in a specific range
 *
 * @len: the length of array
 * @start: the start number of array
 * @end: the end number of array
 */
int * rn_arr_gen( int len , int start, int end)
{
        int i;
        int * ret_arr = NULL;
        int range = start - end;

        // memroy allocation
        ret_arr = (int *) malloc( len * sizeof(int) );
        memset(ret_arr, 0, len + 1);

        // rand seed use time
        srand( (unsigned) time(NULL) );

        // generate arr
        for ( i = 0; i < len; i++ ){
                *(ret_arr + i) = (rand() % range) + 1;
        }

        return ret_arr;
}

/* a safe free function
 */
void _safe_free(void **pp)
{
	if (pp != NULL && *pp != NULL){
		free(*pp);
		*pp = NULL;
	}
}
#define safe_free(p) _safe_free( (void**) &p )

/* print the array with specific lenght
 *
 * @arr: the target array
 * @len: the length of array
 */
void print_arr(int *arr, int len)
{
        int i;

        for ( i = 0; i < len; i++){
                printf("%d ", *(arr + i) );
        }
        printf("\n");
}

int main( int argc, char *argv[] )
{
        int * arr = rn_arr_gen( atoi(argv[1]), 10, 100 );

        print_arr( arr, atoi(argv[1]) );

        safe_free(arr);

        return 0;
}
