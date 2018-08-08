#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000


/* The structure of stack. */
typedef struct stack stack_t;

struct stack {
        int top;
        int stack_array[MAX_SIZE];
};

stack_t * create_stack(void)
{
        stack_t * s = malloc( sizeof(*s) );
        s->top = -1;
        return s;
}

int is_empty(stack_t * s)
{
        return (s->top == -1);
}

int is_full(stack_t * s)
{
        return (s->top == MAX_SIZE - 1);
}

int stack_size(stack_t * s)
{
        return (s->top + 1);
}

int stack_top(stack_t * s)
{
        return (s->stack_array[s->top]);
}

/* The return value is 0 if this operation is successful, otherwise, the return value is -1. */
int stack_push(stack_t * s, int value)
{
        if ( is_full(s) ) {
                return -1;
        } else {
                /* The value of top is -1 when the stack is empty.
                 * The first element will be pushed to the zero index of the stack.
                 */
                s->top ++;
                s->stack_array[s->top] = value;
                return 0;
        }
}

int stack_pop(stack_t * s)
{
        if ( is_empty(s) ){
                return -1;
        } else {
                /* 1. Use a tmp variable to store the value of the top element.
                 * 2. Clear this element and the top value is subtracted 1.
                 * 3. Return.
                 */
                int tmp = s->stack_array[s->top];
                s->stack_array[s->top] = 0;
                s->top --;
                return tmp;
        }
}

int main()
{
        int i;

        stack_t * s_0 = create_stack();

        for (i = 0; i < 10; i++){
                stack_push(s_0, i * 10);
        }

        for (i = 0; i < 3; i++){
                printf("pop: %d\n", stack_pop(s_0));
        }

        return 0;
}
