/* Using bitwise operator to do a multiply function */

#include <stdio.h>

int add(int a, int b)
{
	if (b)
		return add(a^b, (a&b)<<1 );
	else
		return a;
}

// this method need a static variable or global variable, it is a weak point in security.
int multiply_2(int a, int b)
{
	// static variable
	static int sum = 0;

	if (b == 0)
		return sum;

	sum = add(sum, a);

	return  multiply_2(a, b-1);
}


int main()
{
	printf("%d\n", multiply_2(8, 11) );
}
