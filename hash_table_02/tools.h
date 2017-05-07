/* tools.h */

#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** string_increament(unsigned int _string_len)
{
	int i, j;
	char ** ptr_ptr_string;
	char string_[8] = "CKDENSD";

	ptr_ptr_string = (char **) malloc ( sizeof(char*) * _string_len );

	for (i = 0; i < _string_len; i++){

		ptr_ptr_string[i] = (char *) malloc ( sizeof(char) * 8 );

		for (j = 0; j < 7; j++){
			string_[j] ++;
			string_[j] = ( (string_[j] - 65) % 26) + 65;
		}

		strcpy(ptr_ptr_string[i], string_);
	}

	return ptr_ptr_string;
}



char ** random_string_generator(size_t _each_string_length, size_t _string_count)
{
	int i, j;
	char ** ptr_ptr_string;
	char string_tmp[_each_string_length];

	ptr_ptr_string = malloc ( sizeof(char *) * _string_count );

	for (i = 0; i < _string_count; i++){

		/* create the memory space for each string */
		ptr_ptr_string[i] = malloc (sizeof(char) * _each_string_length);

		/* generate the random string */
		for(j = 0; j < _each_string_length - 1; j++) {
			string_tmp[j] = (rand() % 26) + 'a';
		}
		string_tmp[_each_string_length - 1] = '\0';

		/* copy the random string to the target string */
		strncpy(ptr_ptr_string[i], string_tmp, _each_string_length);
	}

	return ptr_ptr_string;
}

void free_string(char ** _ptr_ptr_string, size_t _string_count)
{
	int i;

	for (i = 0; i < _string_count; i++){
		free(_ptr_ptr_string[i]);
	}

	free(_ptr_ptr_string);
}

#endif
