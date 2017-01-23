/* count leading zero of unsigned integer */

#include <stdio.h>
#include <stdint.h>

// byte-shift version
int clz_02(uint32_t x)
{
	if (x == 0)
		return 32;

	int n = 1;

	// if x >> 16 == 0, then n = n + 16 and x = x << 16
	if ((x >> 16) == 0) { n += 16; x <<= 16; }
	if ((x >> 24) == 0) { n += 8; x <<= 8; }
	if ((x >> 28) == 0) { n += 4; x <<= 4; }
	if ((x >> 30) == 0) { n += 2; x <<= 2; }
	// check the most significant bit 
	n = n - (x >> 31);
	return n;
}

int main()
{
	printf("clz_naive(1) is %d\n", clz_02(1) );
	printf("clz_naive(2) is %d\n", clz_02(2) );
	printf("clz_naive(4) is %d\n", clz_02(4) );
	printf("clz_naive(8) is %d\n", clz_02(8) );
	printf("clz_naive(16) is %d\n", clz_02(16) );
}
