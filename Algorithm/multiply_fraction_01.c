/* Multiplies an integer by a fraction, while avoiding unnecessary overflow or loss of precision. */

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char u8;
typedef char s8;


#define mult_frac(x, numer, denom)(                     \
{                                                       \
        typeof(x) quot = (x) / (denom);                 \
        typeof(x) rem  = (x) % (denom);                 \
        (quot * (numer)) + ((rem * (numer)) / (denom)); \
}                                                       \
)

int main()
{
        u8 a = 14;
        u8 b = 5;
        u8 c = 4;

        printf("a: %d\n", a);
        printf("b: %d\n", b);
        printf("c: %d\n", c);

        // a * (b/c)
        printf("mult_frac(a, b, c): %d\n", mult_frac(a, b, c));

        return 0;
}
