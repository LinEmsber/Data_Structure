/* using bitwise to do function of max and min */

// In the function min() or max(), we use condition, ( x < y ), to determine the maximum or minimum.
//
// If x < y happen, then -( x < y ) return -1. Since C program using two's complement, -1 is represented
// 1111,1111 in binary, then:
//		( x ^ y ) & -( x < y )
//	=	( x ^ y ) & 1111,1111
//	=	( x ^ y )
//
// If x < y didnt happen, then -( x < y ) return 0, then:
//		( x ^ y ) & -( x < y )
//	=	( x ^ y ) & 0
//	=	0
//
// On the other hand, we use XOR swap concept to jump back to number x or y.
// If ( x ^ y ) != 0, then y ^ ( ( x ^ y ) ) = x or x ^ ( ( x ^ y ) ) = y.
// If ( x ^ y ) == 0, then y ^ 0 = y or x ^ 0 = x.

#include <stdio.h>

int min(int x, int y)
{
	// printf("min(x, y) = y ^ ( ( x ^ y ) & -( x < y ) );\n");
	// printf("( x ^ y ): %d\n", (x ^ y));
	// printf("-( x < y ): %d\n", -( x < y ));
	// printf("( ( x ^ y ) & -( x < y ) ): %d\n", ( ( x ^ y ) & -( x < y ) ));
	// printf("y ^ ( ( x ^ y ) & -( x < y ) ): %d\n", y ^ ( ( x ^ y ) & -( x < y ) ));
	return y ^ ( ( x ^ y ) & -( x < y ) );
}

int max(int x, int y)
{
	// printf("max(x, y) = x ^ ( ( x ^ y ) & -( x < y ) );\n");
	// printf("( x ^ y ): %d\n", (x ^ y));
	// printf("-( x < y ): %d\n", -( x < y ));
	// printf("( ( x ^ y ) & -( x < y ) ): %d\n", ( ( x ^ y ) & -( x < y ) ));
	// printf("x ^ ( ( x ^ y ) & -( x < y ) ): %d\n", x ^ ( ( x ^ y ) & -( x < y ) ));
	return x ^ ( ( x ^ y ) & -( x < y ) );
}


int main()
{
	printf("min(5, 9): %d\n", min(5,9) );
	printf("max(5, 9): %d\n\n", max(5,9) );

	printf("min(13,4): %d\n", min(13,4) );
	printf("max(13,4): %d\n\n", max(13,4) );
}
