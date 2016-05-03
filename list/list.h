/* A multi-thread safe linked list
 * File: list.h
 * Author: Lin Emsber
 * Create Date: 2016, May, 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// ====================typedef====================
typedef struct list_node_s node_t
typedef struct linked_list_s list_t

typedef void (*free_cb) (void*);


// ====================struct====================

typedef struct _list_entry_s {
    struct _linked_list_s *list;
    struct _list_entry_s *prev;
    struct _list_entry_s *next;
    void *value;
    int tagged;
} list_entry_t;

struct _linked_list_s {
    list_entry_t *head;
    list_entry_t *tail;
    list_entry_t *cur;
    size_t  pos;
    size_t length;
#ifdef THREAD_SAFE
    pthread_mutex_t lock;
#endif
    free_value_callback_t free_value_cb;
    int refcnt;
    list_entry_t *slices;
};

struct _slice_s {
    linked_list_t *list;
    size_t offset;
    size_t length;
};
