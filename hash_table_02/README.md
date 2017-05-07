# Hash Table

## Introduction
The implementation of the hash table.

## Strucuture
```c
/* strucuture */
struct hash_element {
	struct hash_element * next;
	void * data;
	char * key;
};

struct hash_table {
	unsigned int capacity;
	unsigned int element_number;
	struct hash_element ** table;
};


struct hash_element_iter {
	struct hash_table * hash_table;
	unsigned int index;
	struct hash_element * element;
};
```

## Function
```c
/* function */

unsigned int hash_table_calc_hash(char* str);

hash_table_t * hash_table_create(unsigned int _capacity);
void * hash_table_put(hash_table_t * _ht, char * _key, void * _data);
void * hash_table_get(hash_table_t * _ht, char * _key);
void * hash_table_remove(hash_table_t * _ht, char * _key);

void hash_table_list_keys(hash_table_t * _ht, char ** _key_array, size_t _len);
void hash_table_list_datas(hash_table_t * _ht, void ** _data_array, size_t _len);

hash_elem_t * hash_table_iterate(hash_elem_iter_t * _iterator);
char * hash_table_iterate_keys(hash_elem_iter_t * iterator);
void * hash_table_iterate_datas(hash_elem_iter_t * iterator);

void hash_table_clear(hash_table_t * _ht, int _free_data);
void hash_table_destroy(hash_table_t * _ht);
```


## References
- [phsym/hashtable.c](https://gist.github.com/phsym/4605704)
- [Hash Functions](http://www.cse.yorku.ca/~oz/hash.html)
