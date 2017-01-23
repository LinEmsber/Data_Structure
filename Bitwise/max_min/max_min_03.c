/* max */

#include <stdio.h>
#include <stdint.h>

// If a > 0 return 1, if a < 0 return 0.
int sign(int32_t a)
{
        return 1 ^ ((a >> 31) & 0x1);
}


// max(5, 11)
//  = 5 * sign (-6) + 11 * (1 ^ sign(-6) )
//  = 5 * 0 + 11 * (1^0)
//  = 0 + 11
int max(int32_t a, int32_t b)
{
        return a * sign(a - b) + b * ( 1 ^ sign(a - b) );
}

// min(5, 11)
//  = 5 * (1 ^ sign(-6) ) + 11 * sign(-6)
//  = 5 * (1^0) + 11 * 0
//  = 5 + 0
int min(int32_t a, int32_t b)
{
        return a * ( 1 ^ sign(a - b) ) + b * sign(a - b);
}

int main()
{
	printf("max(5, 11) is %d\n", max(5, 11) );
	printf("max(-8, -110) is %d\n", max(-8, -110) );
	printf("max(-5, 1551) is %d\n", max(-5, 1551) );
	
	printf("min(5, 11) is %d\n", min(5, 11) );
	printf("min(-8, -110) is %d\n", min(-8, -110) );
	printf("min(-5, 1551) is %d\n", min(-5, 1551) );
}
