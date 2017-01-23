/* Using bitwise operator to do a multiply function */

#include <stdio.h>

int add(int a, int b)
{
	if (b)
		return add(a^b, (a&b)<<1 );
	else
		return a;
}


int multiply(int a, int b)
{
	int result = 0;

	while ( b != 0){

		if ( b & 1){
			result = result + a;
		}

		a <<= 1;
		b >>= 1;
	}

	return result;
}


int main()
{
	printf("%d\n", multiply(8, 11) );
	
	return 0;
}
