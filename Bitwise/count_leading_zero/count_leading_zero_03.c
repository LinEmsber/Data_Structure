/* count leading zero of unsigned integer */

#include <stdio.h>
#include <stdint.h>

// iteration version
int clz_03(uint32_t x)
{
	int n = 32, c = 16;

	do {
		// shift c bis
		uint32_t y = x >> c;

		if (y) {
			 n -= c;
			 x = y;
		}

		// c over 2
		c >>= 1;

	// c over 2 until c becomes zero
	} while (c);

	// check the most significant bit 
	return (n - x);
}


int main()
{
	printf("clz_naive(1) is %d\n", clz_03(1) );
	printf("clz_naive(2) is %d\n", clz_03(2) );
	printf("clz_naive(4) is %d\n", clz_03(4) );
	printf("clz_naive(8) is %d\n", clz_03(8) );
	printf("clz_naive(16) is %d\n", clz_03(16) );
}
