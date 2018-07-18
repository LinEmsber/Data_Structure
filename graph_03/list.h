#ifndef LIST_H
#define LIST_H

typedef struct node node_t;
typedef struct list list_t;

struct node{
        void * data;
        struct node * next;
        struct node * prev;
};

struct list{
        int length;
        struct node * head;
        struct node * tail;
};

#endif
