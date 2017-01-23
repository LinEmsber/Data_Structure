/* A effective method to determine the sign of integer */

// This method can expand to any bit, 8 bit , 64 bit, 128 bit

#include <stdio.h>
#include <stdint.h>

// If a > 0 return 1.
// If a < 0 return 0.

// function method
int sign(int32_t a)
{
        return 1 ^ ((a >> 31) & 0x1);
}

// MACRO method
#define SIGN(a) 1 ^ ((a >> 31) & 0x1)


int main()
{
        printf("sign(-100) is %d\n", sign(-100) );
        printf("sign(100) is %d\n", sign(100) );

        printf("SIGN(-100) is %d\n", SIGN(-100) );
        printf("SIGN(100) is %d\n", SIGN(100) );
}
