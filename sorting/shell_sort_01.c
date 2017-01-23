/* shell sort */

#include <stdio.h>

// If len = 10
//
// outer loop:     for (gap = len / 2; gap > 0; gap = gap / 2)
//
//         1st:	gap = 11/2 = 5
//         2nd:	gap = 5/2 = 2
//
//         middle loop:    for (i = gap; i < len; i++)
//
//                 1st:    for(i = 5; i < 10; i++)
//                                 i = 5
//                                 i = 6
//                                 i = 7
//                                 i = 8
//                                 i = 9
//
//                 2nd:    for(i = 2; i < 10; i++)
//                                 i = 2
//                                 i = 3
//                                 i = 4
//                                 i = 5
//                                 i = 6
//                                 i = 7
//                                 i = 8
//                                 i = 9
//
//                 inner loop:     for ( j = i - gap; j >= 0; j = j - gap )
//
//                         1st:    for ( j = 5 - 5; j >= 0; j = 0 - 5 )
//                                         j = 5 - 5 = 0
//                                         j = 6 - 5 = 1
//                                         j = 7 - 5 = 2
//                                         j = 8 - 5 = 3
//                                         j = 9 - 5 = 4
//
//                         2nd:    for ( j = 2 - 2; j >= 0; j = j - gap )
//                                         j = 2 - 2 = 0
//                                         j = 3 - 2 = 1
//                                         j = 4 - 2 = 2 - 2 = 0
//                                         j = 5 - 2 = 3 - 2 = 1
//                                         j = 6 - 2 = 4 - 2 = 2 - 2 = 0
//                                         j = 7 - 2 = 5 - 2 = 3 - 2 = 1
//                                         j = 8 - 2 = 6 - 2 = 4 - 2 = 2 - 2 = 0
//                                         j = 9 - 2 = 7 - 2 = 5 - 2 = 3 - 2 = 1


#define XOR_SWAP_2(a, b)	( ( (a) == (b) ) || ( ( (a) ^= (b) ), ( (b) ^= (a) ), ( (a) ^= (b) ) ) )

void shell_sort(int *arr, int len)
{
	int i, j;
	int gap;

	for (gap = len / 2; gap > 0; gap = gap / 2){

		for (i = gap; i < len; i++){

			// for ( j = i - gap; j >= 0; j = j - gap ){
			// 	if (arr[j] <= arr[ j + gap ]){
			// 		XOR_SWAP_2( arr[j], arr[ j + gap ] );
			// 	}else{
			// 		break;
			// 	}
			// }
			for (j = i - gap; j >= 0 && arr[j] > arr[ j + gap ]; j = j - gap){

				XOR_SWAP_2( arr[j], arr[ j + gap ] );
			}

		}
	}
}

int main()
{

	int i;
	int a[] = {10, 2, 4, 5, 22, 898, 84, 12, 103, 331, 56};
	int length_a = sizeof(a) / sizeof(int);

	// before sort
	printf("original a[]: ");
	for (i = 0; i < length_a; i++){
		printf("%d  ", a[i]);
	}
	printf("\n");

	// start sort
	shell_sort(a, length_a);

	// after sort
	printf("after sort a[]:");
	for (i = 0; i < length_a; i++){
		printf("%d  ", a[i]);
	}
	printf("\n");
}
