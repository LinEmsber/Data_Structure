/* The implementation of insertion sort */

#include <stdio.h>

int * insertion_sort(int *arr, int len)
{
	int i, j;
	int tmp;

	for ( i = 1; i < len; i++ ){
		tmp = arr[i];
		j = i-1;

		while ( (j>=0) && (tmp < arr[j]) ){
			arr[j+1] = arr[j];
			j = j - 1;
		}

		arr[j+1] = tmp;
	}

	return arr;
}

int main()
{
	int i;
	int a[] = {10, 2, 4, 5, 22, 898, 84, 12, 103, 331, 56};
	int length_a = sizeof(a) / sizeof(int);

	// before sorting
	printf("original a[]: ");
	for (i=0; i<length_a; i++){
		printf("%d  ", a[i]);
	}
	printf("\n");


	// insertion sort
	insertion_sort(a, length_a);

	// after sorting
	printf("original a[]: ");
	for (i=0; i<length_a; i++){
		printf("%d  ", a[i]);
	}
	printf("\n");

	return 0;
}
