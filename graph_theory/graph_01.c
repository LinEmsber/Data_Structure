#include<stdio.h>
#include<stdlib.h>

struct Edge{
	int vertexIndex;
	struct Edge * edge_ptr;
}edge;

struct vertex{
	int vertex_key;
	struct Edge * edge_ptr;
}vertex;

struct vertex graph[10];
int vertexCount = 0;

void insert_vertex(int vertex_key)
{
	graph[vertexCount].vertex_key = vertex_key;
	graph[vertexCount].edge_ptr = NULL;
	vertexCount++;
}

void insert_edge(int vertex1, int vertex2)
{
	struct Edge *e, *e1, *e2;
	e = graph[vertex1].edge_ptr;

	while(e && e->edge_ptr) {
		e = e->edge_ptr;
	}

	e1 = (struct Edge *) malloc( sizeof(*e1) );
	e1->vertexIndex = vertex2;
	e1->edge_ptr = NULL;

	if(e){
		e->edge_ptr = e1;
	} else {
		graph[vertex1].edge_ptr = e1;
	}

	e = graph[vertex2].edge_ptr;

	while(e && e->edge_ptr) {
		e = e->edge_ptr;
	}

	e2 = (struct Edge *) malloc( sizeof(*e2) );
	e2->vertexIndex = vertex1;
	e2->edge_ptr = NULL;

	if(e){
		e->edge_ptr = e2;
	} else {
		graph[vertex2].edge_ptr = e2;
	}
}

void print_graph()
{
	int i;
	struct Edge * e;

	for( i = 0; i < vertexCount; i++ ) {
		printf("%d(%d)", i, graph[i].vertex_key);
		e = graph[i].edge_ptr;

		while(e) {
			printf("->%d", e->vertexIndex);
			e = e->edge_ptr;
		}

		printf("\n");
	}
}

main()
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

	print_graph();

	return 0;
}
