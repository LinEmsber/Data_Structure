/* combination, C(n, r), n choose r */

#include <stdio.h>

// n choose r
int combination( int n, int r )
{
	int i;
	int numerator = 1;
	int denominator = 1;

        if ( ( n - r ) < (n / 2) ){
                r = n - r;
        }

	// numerator
	for( i = n; i > (n - r); i--)
		numerator = numerator * i;
        // printf("numerator: %d\n", numerator);

        // denominator
	for(i = 1; i <= r; i++)
		denominator = denominator * i;
        // printf("denominator: %d\n", denominator);

	return numerator / denominator;
}

int main()
{
        int n, r;

        printf("n: ");
        scanf("%d", &n);

        printf("r: ");
        scanf("%d", &r);

        printf("conbination(%d, %d): %d\n", n, r, combination(n, r) );
}
