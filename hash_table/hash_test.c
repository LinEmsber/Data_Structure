/* test the hash table */

// gcc -Wall -g hash_test.c hash.c && valgrind --tool=memcheck --leak-check=yes ./a.out 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hash.h"

int * rn_arr_gen( int len , int start, int end)
{
        int i;
        int * ret_arr = NULL;
        int range = start - end;

        // memroy allocation
        ret_arr = (int *) malloc( len * sizeof(int) );
        memset(ret_arr, 0, len + 1);

        // rand seed use time
        srand( (unsigned) time(NULL) );

        // generate arr
        for ( i = 0; i < len; i++ ){
                *(ret_arr + i) = (rand() % range) + 1;
        }

        return ret_arr;
}

void print_arr(int *arr, int len)
{
        int i;

        for ( i = 0; i < len; i++){
                printf("%d ", *(arr + i) );
        }
        printf("\n");
}


int main(int argc, char *argv[])
{
        int i;
        int number_of_nodes;

        int * arr;
        hash_table_t * ht;
        hash_node_t * hn;

        // generate a random number arr
        number_of_nodes = atoi(argv[1]);
        arr = rn_arr_gen( number_of_nodes, 10, 100 );
        print_arr( arr, number_of_nodes );

        // create a hash table
        ht = hash_create( number_of_nodes * 2);

        // push nodes into hash table
        // void hash_set_node(hash_table_t * hash_table, int key, void * data)
        for (i = 0; i < number_of_nodes; i++){
                hash_set_node(ht, arr[i], NULL);
        }

        // obtain node from hash table
        // hash_node_t * hash_get_node(hash_table_t * hash_table, int key)
        for (i = 0; i < number_of_nodes; i++){
                hn = hash_get_node(ht, arr[i]);
                printf("key of node: %d\n", hn->key);
        }

        // free
        // void hash_destroy(hash_table_t * hash_table);
        hash_destroy(ht);
        free(arr);
}
