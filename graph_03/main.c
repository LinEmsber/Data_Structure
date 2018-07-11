#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


int main()
{
	graph_t * graph_object = create_graph(3, 3);
	connect_vertices(graph_object);

	print_graph(graph_object);

	return 0;
}
