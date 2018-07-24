/* A union-find algorithm of the disjoint set data structure.
 * The implementation of is_cycle() to check whether an undirected graph contains cycle or not.
 * Reference: https://www.geeksforgeeks.org/union-find/
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Edge {
	int src, dest;
};

struct Graph {
	int num_vertex, num_edge;
	struct Edge * edge;
};

/* Creates a graph with num_vertex vertices and num_edge edges. */
struct Graph * create_graph(int num_vertex, int num_edge)
{
	struct Graph * graph = (struct Graph *) malloc( sizeof(struct Graph) );
	graph->num_vertex = num_vertex;
	graph->num_edge = num_edge;

	graph->edge = (struct Edge *) malloc( graph->num_edge * sizeof(struct Edge) );

	return graph;
}

/* The function to find the subset of an element. */
int find_subset(int parent[], int i)
{
	if (parent[i] == -1)
		return i;
	return find_subset(parent, parent[i]);
}

/* The function to do union of two subsets. */
void union_edges(int parent[], int x, int y)
{
	int x_set = find_subset(parent, x);
	int y_set = find_subset(parent, y);
	parent[x_set] = y_set;
}

/* The function to check whether a given graph contains cycle or not. */
int is_cycle(struct Graph * graph)
{
	int * parent = (int *) malloc( graph->num_vertex * sizeof(int) );
	memset(parent, -1, sizeof(int) * graph->num_vertex);

	/* Iterate through all edges of graph, find subset of both vertices of every edge.
	 * If both subsets are same, then there is cycle in graph.
	 */
	for(int i = 0; i < graph->num_edge; ++i) {

		int x = find_subset(parent, graph->edge[i].src);
		int y = find_subset(parent, graph->edge[i].dest);

		if (x == y)
			return 1;

		union_edges(parent, x, y);
	}

	return 0;
}

int main()
{
#if 0
	/* Let us create the following graph
	   0
	   |  \
	   |    \
	   1-----2 */
	int num_vertex = 3, num_edge = 3;
	struct Graph * graph_object = create_graph(num_vertex, num_edge);

	/* Add edge 0-1. */
	graph_object->edge[0].src = 0;
	graph_object->edge[0].dest = 1;

	/* add edge 1-2. */
	graph_object->edge[1].src = 1;
	graph_object->edge[1].dest = 2;

	/* add edge 0-2. */
	graph_object->edge[2].src = 0;
	graph_object->edge[2].dest = 2;
#endif

	int num_vertex = 5, num_edge = 4;
	struct Graph * graph_object = create_graph(num_vertex, num_edge);

	graph_object->edge[0].src = 0;
	graph_object->edge[0].dest = 1;

	graph_object->edge[1].src = 0;
	graph_object->edge[1].dest = 2;

	graph_object->edge[2].src = 1;
	graph_object->edge[2].dest = 3;

	graph_object->edge[3].src = 1;
	graph_object->edge[3].dest = 4;

	if (is_cycle(graph_object))
		printf("The graph contains cycle.\n");
	else
		printf("The graph does not contain cycle.\n");

	return 0;
}
