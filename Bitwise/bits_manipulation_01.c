/* bitwise manipulation */

// SET_BIT(), CLEAR_BIT(), TOGGLE_BIT(), TEST_BIT()

#include <stdio.h>

// print integer in binary for 8-bits
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c\n"

// convert binary number to char
#define BYTE_TO_BINARY(byte)  		\
	(byte & 0x80 ? '1' : '0'), 	\
	(byte & 0x40 ? '1' : '0'), 	\
	(byte & 0x20 ? '1' : '0'), 	\
	(byte & 0x10 ? '1' : '0'), 	\
	(byte & 0x08 ? '1' : '0'), 	\
	(byte & 0x04 ? '1' : '0'), 	\
	(byte & 0x02 ? '1' : '0'), 	\
	(byte & 0x01 ? '1' : '0')


#define SET_BIT(x, y)           (x |= (y) )
#define CLEAR_BIT(x, y)         (x &= ~(y) )
#define TOGGLE_BIT(x, y)        (x ^= (y) )
#define TEST_BIT(x, y)          (x &= (y) )

int main()
{
        int a = 0b00000000;             // original
        int b = 0b01010101;             // set bits
        int c = 0b01010000;             // clear bits
        int d = 0b00001111;             // toggle bits
        int e = 0b00001111;             // test bits

        printf("\n");
        printf("a: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(a));
        printf("b: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(b));
        printf("c: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(c));
        printf("d: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(d));
        printf("e: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(e));
        printf("\n");

        printf("before SET_BIT(a, b), a: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(a));
        SET_BIT(a, b);
        printf("after  SET_BIT(a, b), a: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(a));
        printf("\n");

        printf("before CLEAR_BIT(a, c), a: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(a));
        CLEAR_BIT(a, c);
        printf("after  CLEAR_BIT(a, c), a: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(a));
        printf("\n");

        printf("before TOGGLE_BIT(a, d), a: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(a));
        TOGGLE_BIT(a, d);
        printf("after  TOGGLE_BIT(a, d), a: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(a));
        printf("\n");

        printf("before TEST_BIT(a, e), a: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(a));
        TEST_BIT(a, e);
        printf("after  TEST_BIT(a, e), a: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(a));
        printf("\n");

        return 0;
}
