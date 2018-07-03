#include<stdio.h>
#include<stdlib.h>

/* Structure of Edge and Vertex. */
struct Edge{
	int Vertex_index;
	struct Edge * next;
};

struct Vertex{
	int vertex_key;
	struct Edge * edge_ptr;
};

struct Vertex graph[10];
int vertex_count = 0;

void insert_vertex(int vertex_key)
{
	graph[vertex_count].vertex_key = vertex_key;
	graph[vertex_count].edge_ptr = NULL;
	vertex_count++;
}

/* Construct the connection between vertex_1 and vertex_2. */
void insert_edge(int vertex_1, int vertex_2)
{
	struct Edge * e_tmp;

	struct Edge * e_1 = (struct Edge *) malloc( sizeof(*e_1) );
	e_1->Vertex_index = vertex_2;
	e_1->next = NULL;

	/* Start from the first edge to find the last edge of vertex. */
	e_tmp = graph[vertex_1].edge_ptr;
	while(e_tmp && e_tmp->next)
		e_tmp = e_tmp->next;

	/* If the e_tmp is NULL means that it is the first edge of this vertex. */
	if(e_tmp){
		e_tmp->next = e_1;
	} else {
		graph[vertex_1].edge_ptr = e_1;
	}

	e_tmp = graph[vertex_2].edge_ptr;

	struct Edge * e_2 = (struct Edge *) malloc( sizeof(*e_2) );
	e_2->Vertex_index = vertex_1;
	e_2->next = NULL;

	while(e_tmp && e_tmp->next)
	e_tmp = e_tmp->next;

	if(e_tmp){
		e_tmp->next = e_2;
	} else {
		graph[vertex_2].edge_ptr = e_2;
	}
}

void print_graph()
{
	int i;
	struct Edge * e_tmp;

	for( i = 0; i < vertex_count; i++ ) {

		printf("%d (%d)", i, graph[i].vertex_key);
		e_tmp = graph[i].edge_ptr;

		while(e_tmp) {
			printf(" -> %d", e_tmp->Vertex_index);
			e_tmp = e_tmp->next;
		}

		printf("\n");
	}
}

int main()
{

	insert_vertex(5);
	insert_vertex(3);
	insert_vertex(4);
	insert_vertex(2);
	insert_vertex(9);

	insert_edge(0, 1);
	insert_edge(0, 2);
	insert_edge(1, 3);
	insert_edge(1, 4);

	printf("vertex count: %d\n\n", vertex_count);

	print_graph();

	return 0;
}
