/* detect 0 or NULL char '\0' */

// This MACRO can use in alignment.
// If we can ensure that no NULL in the char, we can align or move it directly.


bool detect_null(unsigned int x)
{
	return ( (x - 0x01010101) & ~(x) & 0x80808080 ) != 0;
}


// explanation 1:
//
// One of the most prominent example of detecting zeroes is strlen.
// To improve performance many bytes are examined in parallel.
//
// Since C language use two's complement. The negtive of number n equal (~n)+1, even n is zero.
// Meanwhile, 0x80 equal 128 in decimal, as well as 1000 0000 in binary.
//
// 	-n = (~n) + 1
// 	-n - 1 = (~n)
//
// 	Decimal		Two's complement
// 	--------	--------
// 	127 		0111 1111
// 	64 		0100 0000
// 	1 		0000 0001
// 	0 		0000 0000
// 	−1 		1111 1111
// 	−64 		1100 0000
// 	−127 		1000 0001
// 	−128 		1000 0000
//
// example 1:
//
// If x is 0:
//
// (x - 0x01) & ~(x) & 0x80
//
// calculate in hexadecimal:
// = (0x00 - 0x01) & ~(0x00) & 0x80
// = 0xff & 0xff & 0x80
// = 0xff & 0x80
// = 0x80
// != 0
//
// calcuate in decimal:
// (0000 0000 - 0000 0001) & ~(0000 0000) & ( 1000 0000)
// = (1111 1111) & (1111 1111) & ( 1000 0000)
// = (1111 1111) & (1000 0000)
// = (1000 0000)
//
//
// example 2:
//
// If x is 64 in decimal, and it is 0100 0000 in binary, and 0x40 in hexadecimal.
//
// (x - 0x01) & ~(x) & 0x80
//
// calculate in hexadecimal:
// = (0x40 - 0x01) & ~(0x40) & 0x80
// = 0x3f & 0xbf & 0x80
// = 0x3f & 0x80
// = 0
//
// calcuate in decimal:
//
// (0100 0000 - 1) & ~(0100 0000) & (1000 0000)
// = (0011 0000) & (1011 1111) & (1000 0000)
// = (0011 0000) & (1000 0000)
// = (0000 0000)
//
//
// explanation 2:
//
// The expression x − 0x01010101 sets the highest bit of a byte if a single input byte is within the input set
// { 0x00, 0x81, 0x82, 0x83, ..., 0xFF } because the result will be { 0xFF, 0x80, 0x81, 0x82, ..., 0xFE }
//
// On the other hand, ~x sets the highest bit of a byte if a single input byte is within the input set
// { 0x00, 0x01, 0x02, 0x03, ..., 0x7F } because the result will be { 0xFF, 0xFE, 0xFD, 0xFC, ..., 0x80 }
//
// The only value contained in both input sets is 0x00, exactly what we are looking for.
// That means, only for x = 0 the highest bit is still set after ANDing: (x − 0x01010101) & ~x .
// Please do not be confused by the fact that a result ≠ 0 actually indicates a zero byte.
//
// The resulting value is equal to zero if all (!) of these highest bits are zero.
// If at least one is still set to 1, caused by a zero byte, the comparison != 0 gives "true".
