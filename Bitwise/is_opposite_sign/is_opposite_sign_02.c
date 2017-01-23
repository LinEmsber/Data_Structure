/* Detect if two integers have opposite signs */

#include <stdio.h>

// If x and y have opposite signs, return ture.
#define IS_OPPOSITE_SIGN(x, y) ( (x ^ y) < 0 )

int main()
{
	printf("is_opposite(-100, 100): %d\n", IS_OPPOSITE_SIGN(-100, 100) );
	printf("is_opposite(50, 100): %d\n", IS_OPPOSITE_SIGN(50, 100) );

}
