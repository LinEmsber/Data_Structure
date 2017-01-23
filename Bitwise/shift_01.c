/* An shift example */

#include<stdio.h>

int main()
{


	// 0000 0000 0011 1100   = 60
	// << 1
	// -------------------
	// 0000 0000 0111 1000   = 120

	int a = 60;

	printf("\nNumber is left Shifted By 1 Bit : %d",a << 1);
	printf("\nNumber is left Shifted By 2 Bits : %d",a << 2);
	printf("\nNumber is left Shifted By 3 Bits : %d",a << 3);

	printf("\nNumber is right Shifted By 1 Bit : %d",a >> 1);
	printf("\nNumber is right Shifted By 2 Bits : %d",a >> 2);
	printf("\nNumber is right Shifted By 3 Bits : %d",a >> 3);

	return(0);
}
