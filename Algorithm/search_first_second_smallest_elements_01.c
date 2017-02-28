/*
 * This is a little bit faster function for computing the first and the second elements at the same time.
 * It employs a recursive  method to implement divide-and-conquer technique.
 *
 * Number of comparisons is about 1.5n-2, where n is the number of elements. The fastest algorithm use n+log(n)
 * comparisons only, while the conventional one requires 2n-3 comparisons.
 */

#include  <stdio.h>
#include  <stdlib.h>
#include  <time.h>
#include  <limits.h>

#define   MAX_SIZE     100

// declaration
void  f_and_s(int [], int, int, int *, int *);
void  first_second(int x[], int n, int *first, int *second);

/* This function accepts the input array x[] and the start and end bounds, then returns the smallest and
 * the second smallest elements in this range by using  divide-and-conquer method.
 *
 * @x: integer array
 * @n: arrary length
 * @first: pointer to a integer for saving first element
 * @second: pointer to a integer for saving second element
 */
void first_second(int x[], int n, int *first, int *second)
{
	f_and_s(x, 0, n-1, first, second);
}


/*
 * @x: integer array
 * @start: the start index of array
 * @end: the end index of array
 * @first: pointer to a integer for saving first element
 * @second: pointer to a integer for saving second element
 */
void f_and_s(int x[], int start, int end, int *f, int *s)
{
	int  mid;
	int  F1, F2;             /* returned smallest items  */
	int  S1, S2;             /* returned second smallest */

	// If range empty, return INT_MAX.
	if (start > end){
		*f = *s = INT_MAX;

	// If exactly one element, return INT_MAX.
	}else if (start == end){
		*f = x[start], *s = INT_MAX;

	}else {
		// cut from middle
		mid = (start + end) / 2;

		f_and_s(x, start, mid, &F1, &S1);
		f_and_s(x, mid+1, end, &F2, &S2);

		// pick 1st and 2nd items.
		if (F1 < F2)
			*f = F1, *s = (S1 < F2) ? S1 : F2;
		else
			*f = F2, *s = (S2 < F1) ? S2 : F1;
	}
}


int main(int argc, char *argv[])
{
	int i;
	int x[MAX_SIZE];
	int n;
	int first, second;

	printf("Recursive method to find first and second elements of array\n");

	n = atoi(argv[1]);

	// randomly gerneate data
	srand((unsigned) clock());
	for (i = 0; i < n; i++) {

		x[i] = rand() % 100;

		if (i % 10 == 0)
			printf("\n");

		printf("%4d, ", x[i]);
	}
	printf("\n");

	first_second(x, n, &first, &second);
	printf("The Smallest Element: %4d\n", first);
	printf("The Second Smallest Element: %4d\n", second);

	return 0;
}
