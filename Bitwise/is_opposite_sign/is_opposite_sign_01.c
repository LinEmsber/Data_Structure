/* Detect if two integers have opposite signs */

#include <stdio.h>
#include <stdbool.h>

// If x and y have opposite signs, return ture.
bool is_opposite(int x, int y)
{
	return ((x ^ y) < 0 );
}

int main()
{
	printf("is_opposite(-100, 100): %d\n", is_opposite(-100, 100) );
	printf("is_opposite(50, 100): %d\n", is_opposite(50, 100) );

}
