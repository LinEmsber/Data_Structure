/* using bitwise to do MACRO of max and min */


#include <stdio.h>

#define MIN(x, y) 	y ^ ( ( x ^ y ) & -( x < y ) )
#define MAX(x, y) 	x ^ ( ( x ^ y ) & -( x < y ) )


int main()
{
	printf("MIN(5, 9): %d\n", MIN(5,9) );
	printf("MAX(5, 9): %d\n", MAX(5,9) );

	printf("MIN(13,4): %d\n", MIN(13,4) );
	printf("MAX(13,4): %d\n", MAX(13,4) );
}
