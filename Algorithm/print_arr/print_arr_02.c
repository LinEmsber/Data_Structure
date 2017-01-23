/* Using rand() to generate a random integer number array */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
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
        // In order to determine the end of array, add one more byte and set it as INT_MAX.
        ret_arr = (int *) malloc( (len + 1) * sizeof(int) );
        memset(ret_arr, 0, len + 1);

        // rand seed use time
        srand( (unsigned) time(NULL) );

        // generate array
        for ( i = 0; i < len; i++ ){
                *(ret_arr + i) = (rand() % range) + 1;
        }
        // set the last byte as INT_MAX
        *(ret_arr + len) = INT_MAX;

        return ret_arr;
}

/* print the array
 *
 * @arr: the target array
 */
void print_arr_INT_MAX(int * arr)
{
        int * ptr = arr;

        while( *ptr != INT_MAX ){
                printf("%d ",  *(ptr++) );
        }

        printf("\n");
}

int main( int argc, char *argv[] )
{
        int * arr = rn_arr_gen( atoi(argv[1]), 10, 100 );

        print_arr_INT_MAX( arr );

        return 0;
}
