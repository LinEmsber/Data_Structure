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
	int v;
	for (v = 0; v < graph->num_vertices; v++) {
		struct node * tmp = graph->adjacent_list[v];
		printf("\nAdjacency list of vertex %d\n", v);
		while (tmp) {
			printf("%d -> ", tmp->vertex);
			tmp = tmp->next;
		}
		printf("\n");
	}
	printf("\n");
}

int main()
{
        struct Graph * graph = create_graph(6);
	add_edge(graph, 0, 1);
	add_edge(graph, 0, 2);
	add_edge(graph, 1, 2);
	add_edge(graph, 1, 4);
	add_edge(graph, 2, 3);
	add_edge(graph, 2, 5);
	add_edge(graph, 4, 3);
	add_edge(graph, 4, 5);

	print_graph(graph);

	return 0;
}
