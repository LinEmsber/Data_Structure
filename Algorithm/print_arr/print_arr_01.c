/* Using rand() to generate a random integer number array */

// > gcc -Wall print_arr_01.c
// > ./a.out 10

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

/* print the array with specific lenght
 *
 * @arr: the target array
 * @len: the length of array
 */
void print_arr_1(int *arr, int len)
{
        int i;

        for ( i = 0; i < len; i++){
                printf("%d ", *(arr + i) );
        }
        printf("\n");
}

void print_arr_2(int *arr, int len)
{
        int * ptr = arr;

        while( ptr != (arr + len) ){
                printf("%d ",  *(ptr++) );
        }

        printf("\n");
}

int main( int argc, char *argv[] )
{
        int * arr = rn_arr_gen( atoi(argv[1]), 10, 100 );

        print_arr_1( arr, atoi(argv[1]) );
        print_arr_2( arr, atoi(argv[1]) );

        return 0;
}
