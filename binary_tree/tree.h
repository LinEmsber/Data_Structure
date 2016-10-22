/* tree.h */


#include <stdio.h>
#include <stdlib.h>


// ======== typedef ========
typedef struct node node_t;
typedef struct tree tree_t;


// ======== structure ========
struct tree
{
        struct node *root;
        int count;
};

struct node
{
        int value;
        void *data;
        struct node *left;
        struct node *right;
	struct node *parent;
};
