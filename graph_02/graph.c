#include <stdio.h>
#include <stdlib.h>

struct node {
	int vertex;
	struct node * next;
};

/* We use int ** to store a two dimensional array which is the adjacent list.
 * Similary, we need struct node** to store an array of Linked lists
 */
struct Graph {
	int num_vertices;
	int * visited;
	struct node ** adjacent_list;
};

struct node * create_node(int v);
struct Graph * create_graph(int);
void add_edge(struct Graph *, int, int);
void print_graph(struct Graph *);
void DFS(struct Graph *, int);

struct node * create_node(int v)
{
	struct node * new_node = malloc( sizeof(struct node) );

	new_node->vertex = v;
	new_node->next = NULL;

	return new_node;
}

struct Graph * create_graph(int vertices)
{
	/* Allocate memory for graph and its elements. */
	struct Graph * graph = malloc( sizeof(struct Graph) );
	graph->adjacent_list = malloc( vertices * sizeof(struct node*) );
	graph->visited = malloc( vertices * sizeof(int) );

	/* Initialize graph's elements. */
	graph->num_vertices = vertices;
	for ( int i = 0; i < vertices; i++) {
		graph->adjacent_list[i] = NULL;
		graph->visited[i] = 0;
	}

	return graph;
}

void add_edge(struct Graph * graph, int src, int dest)
{
	/* Add an edge from src to dest.
	 * A new node is added to the begining of the adjacency list of src.
	 * The node is added at the begining.
	 */
	struct node * new_node = create_node(dest);
	new_node->next = graph->adjacent_list[src];
	graph->adjacent_list[src] = new_node;

	/* Since the graph is undirected, add an edge from dest to src also. */
	new_node = create_node(src);
	new_node->next = graph->adjacent_list[dest];
	graph->adjacent_list[dest] = new_node;
}

void print_graph(struct Graph * graph)
{
	struct node * tmp = NULL;

	for (int i = 0; i < graph->num_vertices; i++) {
		tmp = graph->adjacent_list[i];
		printf("\nAdjacency list of vertex %d\n", i);

		while (tmp ) {

			printf("%d", tmp->vertex);
			if (tmp->next != NULL)
				printf(" -> ");

			tmp = tmp->next;
		}
		printf("\n");
	}
	printf("\n");
}

void DFS(struct Graph * graph, int vertex)
{
	struct node * adj_list = graph->adjacent_list[vertex];
	struct node * tmp = adj_list;

	graph->visited[vertex] = 1;
	printf("Visited %d \n", vertex);

	while(tmp != NULL) {

		int connected_vertex = tmp->vertex;
		if(graph->visited[connected_vertex] == 0) {
			DFS(graph, connected_vertex);
		}

		tmp = tmp->next;
	}
}

int main()
{
	struct Graph * graph = create_graph(6);

#if 0
	add_edge(graph, 0, 1);
	add_edge(graph, 0, 2);
	add_edge(graph, 0, 5);
	add_edge(graph, 1, 2);
	add_edge(graph, 2, 3);
	add_edge(graph, 2, 4);
	add_edge(graph, 3, 4);
	add_edge(graph, 3, 5);
#endif

	/* The same scenario of textbook, Algorithms 4th, at the page 533. */
	add_edge(graph, 0, 5);
	add_edge(graph, 2, 4);
	add_edge(graph, 2, 3);
	add_edge(graph, 1, 2);
	add_edge(graph, 0, 1);
	add_edge(graph, 3, 4);
	add_edge(graph, 3, 5);
	add_edge(graph, 0, 2);

	print_graph(graph);
	DFS(graph, 0);

	return 0;
}
