/* increment and decrement signed and less than zero integer */

// If integer x < 0, then x >> 31 = -1.
// 
// Decimal	        Two's complement
// 127                  0111 1111
// 64                   0100 0000
// 1                    0000 0001
// 0                    0000 0000
// −1                   1111 1111
// −64                  1100 0000
// −127                 1000 0001
// −128                 1000 0000

#include <stdio.h>


#define increment_1(x)  ( (x) -= ( (x) >> 31 ) )
#define decrement_1(x)  ( (x) += ( (x) >> 31 ) )

void increment_2 (int *x)
{
        if (*x < 0)
                ++ *x;
}

void decrement_2 (int *x)
{
        if (*x < 0)
                -- *x;
}

int main()
{
        int a = -100;
        int *pa = &a;

        printf("original a: %d\n", a);

        increment_1(a);
        printf("increment_1(a): %d\n", a);

        decrement_1(a);
        printf("decrement_1(a): %d\n", a);

        increment_2(pa);
        printf("increment_2(a): %d\n", a);

        decrement_2(pa);
        printf("increment_2(a): %d\n", a);

}
