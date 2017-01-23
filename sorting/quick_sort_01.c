/* KnR C 2nd, p.87 , quick sort */

#include <stdio.h>

void swap(int v[], int i, int j)
{
	int tmp;
	tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}


void quick_sort( int v[], int left, int right)
{
	int i, last;

	// if the index of left element is equal or larger than the index of right element.
	if (left >= right)
		return;

	// swap the most left element with the middle element
	swap(v, left, (left + right) / 2);
	// assign the last index as the most left index (the middle index)
	last = left;

	for (i = left + 1; i <= right; i++){

		if (v[i] < v[left]){
			// last = last + 1;
			// swap(v, last, i);
			swap(v, ++last, i);
		}
	}

	swap(v, left, last);

	// quick sort the left side array
	quick_sort(v, left, last-1);
	// quick sort the right side array
	quick_sort(v, last+1, right);

}

int main()
{

	int i;
	int a[] = {10, 2, 4, 5, 22, 898, 84, 12, 103, 331, 56};
	int length_a = sizeof(a) / sizeof(int);

	// original
	printf("original a[]: ");
	for (i = 0; i < length_a; i++){
		printf("%d  ", a[i]);
	}
	printf("\n");

	// start sort
	quick_sort(a, 0, length_a-1);

	// after sort
	printf("after sort a[]:");
	for (i = 0; i < length_a; i++){
		printf("%d  ", a[i]);
	}
	printf("\n");

	return 0;
}
