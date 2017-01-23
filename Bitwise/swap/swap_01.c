/* swap, function method */

#include <stdio.h>

// x = 1010
// y = 0011
//
// x ^ y 	= 1010 ^ 0011 = 1001
// (x ^ y) ^ y 	= 1001 ^ 0011 = 1010
// (x ^ y) ^ x 	= 1001 ^ 1010 = 0011

// XOR swap function
void swap(int *x, int *y)
{
	if ( x != y ){
		*x ^= *y;
		*y ^= *x;
		*x ^= *y;
	}
}


// It can be done more easily, without checking if the addresses are equal.
void swap_2 (int *x, int *y)
{
	*x ^= *y ^ (*y = *x);
}

int main()
{
	int a = 5;
	int b = 10;

	printf("a: %d, b: %d\n", a, b);
	swap(&a, &b);
	printf("a: %d, b: %d\n", a, b);
	swap_2(&a, &b);
	printf("a: %d, b: %d\n", a, b);
}
