/* Using bitwise operator to do a addition and subtraction function */

#include <stdio.h>

/*
If a and b are 2^n, then a + b = a ^ b, and a & b = 0.

add(4, 8):
4 -> 0100
8 -> 1000
4 ^ 8 = 1100
4 & 8 = 0000
(4 & 8) << 1 = 0000

add(5, 9):
5 -> 0101
9 -> 1001
5 ^ 9 = 1100 = 12
(5 & 9) << 1 = 0001 << 1 = 0010 = 2

1100 ^ 0010 = 1110
12 + 2 = 14

*/

// TODO: MACRO do recursively call functions
#define add_MACRO(a, b) (b) ? add_MACRO( (a) ^ (b), ( (a) & (b) ) << 1 ) : a

int add_1(int a, int b)
{
	if (b){
		return add_1( a ^ b, ( a & b ) << 1 );
	}else{
		return a;
	}
}


int add_2(int x,int y)
{
	int a, b;
	do{
		a = x & y;
		b = x ^ y;
		x = a << 1;
		y = b;
	}while(a);

	return b;
}

int add_3(int a, int b)
{
        if (b == 0)
                return a;

        // add, but not carry
        int sum = a ^ b;
        // carry, but not add
        int carry = (a & b) << 1;

        return add_3(sum, carry);
}

int negate(int x)
{
	return add_1(~x,1);
}

int sub_1(int x,int y)
{
	return add_1(x,negate(y));
}

int sub_2(int x,int y){
	return add_1(x, add_1(~y, 1));
}


int main()
{
	printf("add_1(4, 8): %d\n", add_1(4, 8) );
	printf("add_1(-10, -100): %d\n", add_1(-10, -100) );

	printf("sub_1(4, 8): %d\n", sub_1(4, 8) );
	printf("sub_1(-10, -100): %d\n", sub_1(-10, -100) );

	printf("add_2(4, 8): %d\n", add_2(4, 8) );
	printf("add_2(-10, -100): %d\n", add_2(-10, -100) );

	printf("sub_2(4, 8): %d\n", sub_2(4, 8) );
	printf("sub_2(-10, -100): %d\n", sub_2(-10, -100) );

        printf("add_3(4, 8): %d\n", add_3(4, 8) );

        return 0;
}
