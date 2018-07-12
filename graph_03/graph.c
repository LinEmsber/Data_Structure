/* The implementation of graph and related operations. */

#include <stdio.h>
#include "graph.h"

graph_t * create_graph(int _num_edges, int _num_vertices)
{
	graph_t * g = malloc ( sizeof(graph_t) );
	g->num_edges = _num_edges;
	g->num_vertices = _num_vertices;
	setup_vertices(g);

	return g;
}

void setup_vertices(graph_t * _g)
{
	_g->vertex_set = (vertex_t *) malloc( sizeof(_g->num_vertices * sizeof(vertex_t)) );

	for ( int i = 0; i < _g->num_vertices; i++){
		_g->vertex_set[i].label = 'A' + i;
		_g->vertex_set[i].is_visited = 0;
		_g->vertex_set[i].num_adjacent = 0;
		_g->vertex_set[i].adjacent_list = (vertex_t **) malloc (sizeof(vertex_t *));
		/* It is must initialize this pointer to avoid the error happens on function realloc(). */
		_g->vertex_set[i].adjacent_list = NULL;
	}
}

void connect_vertices(graph_t * _g)
{
	vertex_t * v_1, * v_2;

	for ( int i = 0; i < _g->num_edges; i++ ){
		// printf("%d", i);
		v_1 = &(_g->vertex_set[i]);
		v_2 = &( _g->vertex_set[ (i+1) % (_g->num_vertices) ] );
		// v_2 = &( _g->vertex_set[i+1]);
		setup_edge(_g, v_1, v_2);
	}
}

void setup_edge(graph_t * _g, vertex_t * _v_1, vertex_t * _v_2)
{
	_v_1->num_adjacent ++;
	_v_2->num_adjacent ++;

	_v_1->adjacent_list = (vertex_t **) realloc (_v_1->adjacent_list, _v_1->num_adjacent * sizeof(vertex_t *) );
	_v_2->adjacent_list = (vertex_t **) realloc (_v_2->adjacent_list, _v_2->num_adjacent * sizeof(vertex_t *) );

	_v_1->adjacent_list[_v_1->num_adjacent - 1] = _v_2;
	_v_2->adjacent_list[_v_2->num_adjacent - 1] = _v_1;
}

void print_graph(graph_t * _g)
{
	int i, j;
	vertex_t * current;
	printf("\nThis graph has %d Vertices and %d Edges\n", _g->num_vertices, _g->num_edges);

	/* print the vertex set. */
	for(i = 0; i < _g->num_vertices; ++i) {

		current = &(_g->vertex_set[i]);
		printf("%c: ", current->label);

		for(j = 0; j < current->num_adjacent - 1; ++j)
			printf("%c, ", current->adjacent_list[j]->label);

		if(current->adjacent_list > 0)
			printf("%c\n", current->adjacent_list[j]->label);
		else
			printf("\n");
	}
}

int is_adjacent(vertex_t * _v_1, vertex_t * _v_2)
{
	for(int i = 0; i < _v_1->num_adjacent; i++)
		if(	_v_1->adjacent_list[i] == _v_2)
			return 1;
	return 0;
}

void clear_visited(graph_t * g)
{
	int i;
	for(i = 0; i < g->num_vertices; i++)
		g->vertex_set[i].is_visited = 0;
}

int DFS_recursive_helper(graph_t * g, vertex_t * current, vertex_t * dst)
{
	current->is_visited = 1;

	if(current == dst)
		return 1;

	for(int i = 0; i < current->num_adjacent; i++)
		if( !(current->adjacent_list[i]->is_visited) )
			if( DFS_recursive_helper(g, current->adjacent_list[i], dst) )
				return 1;
	return 0;
}

int DFS_recursive(graph_t * g, vertex_t * src, vertex_t * dst)
{
	clear_visited(g);
	return DFS_recursive_helper(g, src, dst);
}

int DFS(graph_t * g, vertex_t * src, vertex_t * dst)
{

}
