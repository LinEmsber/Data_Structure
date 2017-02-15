/* roundup and rounddown */

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char u8;
typedef char s8;

#define __round_mask(x, y)      ( ( __typeof__(x) )((y) - 1) )
#define round_up(x, y)          ( ( ((x)-1) | __round_mask(x, y) ) + 1 )
#define round_down(x, y)        ( (x) & ~__round_mask(x, y) )

int main()
{
        u8 a = 0b01100101;
        u8 b = 0b00001000;
        s8 c = 0b11100101;
        s8 d = 0b11111000;

        printf("a: %d\n", a);
        printf("b: %d\n", b);

        printf("round_up(a, b): %d\n", round_up(a, b));
        printf("round_down(a, b): %d\n", round_down(a, b));

        printf("c: %d\n", c);
        printf("d: %d\n", d);

        printf("round_up(c, d): %d\n", round_up(c, d));
        printf("round_down(c, d): %d\n", round_down(c, d));

        return 0;
}
