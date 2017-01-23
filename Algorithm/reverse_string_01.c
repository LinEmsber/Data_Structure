/* An example of reverse string function */

#include <stdio.h>
#include <string.h>

#define XORSWAP(a, b)   ((&(a) == &(b)) ? (a) : ((a)^=(b),(b)^=(a),(a)^=(b)))

/* reverse a string
 *
 * @s: the target string
 */
int reverse_string(char *s)
{
	if (!s)
		return 1;

	char * start = s;

	// find the last char position.
	// char * end = s + strlen(s) - 1;
	char * end = s;
	while( end && *end)
		++end;
	--end;
	
	printf("address of str: %p\n", start);
	printf("address of end: %p\n", end);

	// reverse
	while( start < end ){
		XORSWAP( *start, *end );
		start++;
		end--;
	}

	return 0;
}


int main()
{

	char string[] = "This_is_a_string_which we want to modify.";

	printf("original str: %s\n", string);
	reverse_string(string);
	printf("modified str: %s\n", string);

	return 0;
}
