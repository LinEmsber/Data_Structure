#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


int main()
{
	graph_t * graph_object = create_graph(8, 8);
	connect_vertices(graph_object);

	print_graph(graph_object);

	for (int i = 0; i < graph_object->num_vertices; i++)
		for (int j = i + 1; j < graph_object->num_vertices; j++)
			DFS(graph_object, graph_object.vertex_set[i], graph_object.vertex_set[j])

	return 0;
}
