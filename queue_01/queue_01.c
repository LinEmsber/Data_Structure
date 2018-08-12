#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct queue queue_t;

struct queue {
	int queue_array[MAX_SIZE];
	int front;
	int rear;
};

queue_t * create_queue(void)
{
	queue_t * q = (queue_t *) malloc( sizeof(queue_t) );
	q->front = -1;
	q->rear = -1;
	return q;
}

int is_full(queue_t * q)
{
	return ( ( (q->rear + 1) ) == q->front );
}

int is_empty(queue_t * q)
{
	return ( (q->rear == -1) && (q->front == -1) );
}

void enqueue(queue_t * q, int data)
{
	if ( is_full(q) ) {
		printf("Full\n");

	} else if ( is_empty(q) ) {
		/* Increases both front and rear. */
		q->front++;
                q->rear++;
		q->queue_array[ (q->rear) ] = data;

	} else {
		/* Increase the value of rear. */
		q->rear = (q->rear + 1);
		q->queue_array[q->rear] = data;
	}
}

int dequeue(queue_t * q)
{
	int data;
	if ( is_empty(q) ) {
		printf("Empty\n");
		return -1;

        /* If the index of front equals rear's, it means the tasks of the queue have been completed. */
	} else if (q->front == q->rear) {
		data = q->queue_array[q->front];
		q->front = -1;
		q->rear = -1;

	} else {
                /* Increase the value of rear. */
		data = q->queue_array[q->front];
		q->front = (q->front + 1);
	}

	return data;
}

int main()
{
        int i;

        queue_t * q_0 = create_queue();

        printf("\nStart to enqueue.\n");
        for (i = 0; i < 3; i++){
                printf("enqueue: %d\n", i * 10);
                enqueue(q_0, i * 10);
        }

        printf("\nStart to dequeue.\n");
        for (i = 0; i < 2; i++){
                printf("dequeue: %d\n", dequeue(q_0));
        }

        printf("\nStart to enqueue.\n");
        for (i = 0; i < 4; i++){
                printf("enqueue: %d\n", i * 10);
                enqueue(q_0, i * 10);
        }

        printf("\nStart to dequeue.\n");
        for (i = 0; i < 6; i++){
                printf("dequeue: %d\n", dequeue(q_0));
        }

	return 0;
}
