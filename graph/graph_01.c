#include<stdio.h>
#include<stdlib.h>

struct edge{
	int vertexIndex;
	struct edge * edgePtr;
}edge;

struct vertex{
	int vertexKey;
	struct edge * edgePtr;
}vertex;

struct vertex graph[10];
int vertexCount = 0;

void insert_vertex(int vertexKey)
{
	graph[vertexCount].vertexKey=vertexKey;
	graph[vertexCount].edgePtr=NULL;
	vertexCount++;
}

void insert_edge(int vertex1, int vertex2)
{
	struct edge *e,*e1,*e2;
	e = graph[vertex1].edgePtr;

	while(e && e->edgePtr) {
		e=e->edgePtr;
	}

	e1 = (struct edge *) malloc( sizeof(*e1) );
	e1->vertexIndex = vertex2;
	e1->edgePtr = NULL;

	if(e)
		e->edgePtr = e1;
	else
		graph[vertex1].edgePtr = e1;

	e=graph[vertex2].edgePtr;

	while(e && e->edgePtr) {
		e = e->edgePtr;
	}

	e2 = (struct edge *)malloc( sizeof(*e2) );
	e2->vertexIndex = vertex1;
	e2->edgePtr = NULL;

	if(e)
		e->edgePtr = e2;
	else
		graph[vertex2].edgePtr = e2;
}

void print_graph()
{
	int i;
	struct edge *e;
	for( i = 0; i < vertexCount; i++ )
	{
		printf("%d(%d)", i, graph[i].vertexKey);
		e = graph[i].edgePtr;
		while(e) {
			printf("->%d", e->vertexIndex);
			e = e->edgePtr;
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
