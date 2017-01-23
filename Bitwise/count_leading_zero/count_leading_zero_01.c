/* count leading zero of unsigned integer */

#include <stdio.h>
#include <stdint.h>

// naive version
int clz_01(uint32_t x)
{
	if ( x == 0 )
		return 32;

	int  n = 0;

	// if x < 0000 0000 0000 0000 1111 1111 1111 1111, then n = n + 16 and x = x << 16
	if ( x <= 0x0000FFFF) { n += 16; x <<= 16;} 
	if ( x <= 0x00FFFFFF) { n += 8; x <<= 8; }
	if ( x <= 0x0FFFFFFF) { n += 4; x <<= 4; }
	if ( x <= 0x3FFFFFFF) { n += 2; x <<= 2; }
	if ( x <= 0x7FFFFFFF) { n += 1; x <<= 1; }

	return n;
}

int main()
{
	printf("clz_01(1) is %d\n", clz_01(1) );
	printf("clz_01(2) is %d\n", clz_01(2) );
	printf("clz_01(4) is %d\n", clz_01(4) );
	printf("clz_01(8) is %d\n", clz_01(8) );
	printf("clz_01(16) is %d\n", clz_01(16) );
}
