/* Using bitwise operator to do a multiply function */

#include <stdio.h>

int add(int a, int b)
{
	if (b)
		return add(a^b, (a&b)<<1 );
	else
		return a;
}


int multiply_3(int a, int b)
{
	// printf("a: %d, b: %d\t", a, b);
	// printf("b << 31 >> 31: %d\t", b << 31 >> 31);
	// printf("a & ( b << 31 >> 31) ): %d\n", a & ( b << 31 >> 31) );
	if (!a)
		return 0;

	return multiply_3( a << 1, b >> 1 ) + ( a & ( b << 31 >> 31) );
}


// Sum of the corresponding number a, when the corresponding number is odd number.
// 6 * 2 = 12		18 / 2  = 9 (O)
// 6 * 2^2 = 24		18 / 2^2 = 4 (X)
// 6 * 2^3 = 48		18 / 2^3 = 2 (X)
// 6 * 2^4 = 96		18 / 2^4 = 1 (O)
//
// so,
// 6 * 18 = 12 + 96 = 108


int main()
{
	printf("%d\n", multiply_3(6, 18) );
}
