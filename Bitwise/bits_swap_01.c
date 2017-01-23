/* Swap spicific bits of integer */

// This MACRO only for printing 8 bits.

#include <stdio.h>

// print integer in binary
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


void bits_swap(int * n, int bit_pos_1, int bit_pos_2)
{
	unsigned int b1, b2, tmp;

	// get bits a and b
	b1 = (*n >> bit_pos_1) & 1;
	b2 = (*n >> bit_pos_2) & 1;

	// xor a and b to get result c
	tmp = b1 ^ b2;

	// put result c in original bit positions
	tmp = (tmp << bit_pos_1) | (tmp << bit_pos_2);

	// xor bits a and b with c to get b and a
	*n ^= (int)tmp;
}

void bits_swap_2( int *x, int p1, int p2, unsigned int n)
{
	// Move all bits of first set to rightmost side
	unsigned int set1 =  (*x >> p1) & ((1U << n) - 1);
	unsigned int set2 =  (*x >> p2) & ((1U << n) - 1);

	// XOR the two sets
	unsigned int xor = (set1 ^ set2);

	// Put the xor bits back to their original positions
	xor = (xor << p1) | (xor << p2);

	// XOR the 'xor' with the original number so that the two sets are swapped
	*x ^= xor;
}

int main()
{
	int a = 0b11101011;
	int b = 0b10111011;

	printf("before bits_swap(&a, 2, 6): "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(a));
	bits_swap(&a, 2, 6);
	printf("after  bits_swap(&a, 2, 6): "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(a));

	printf("before bits_swap_2(&b, 2, 5, 2): "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(b));
	bits_swap_2(&b, 2, 5, 2);
	printf("after  bits_swap_2(&b, 2, 5, 2): "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(b));

	return 0;
}
