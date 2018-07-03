/* The implementation of graph and related operations. */

#include <stdio.h>
#include "graph.h"

graph_t * create_graph(int _num_edges, int _num_vertices)
{
	graph_t * g = malloc ( sizeof(*g) );

	g->num_edges = _num_edges;
	g->num_vertices = _num_vertices;
	setup_vertices(g);

	return g;
}

void setup_vertices(graph_t * _g)
{
	_g->vertex_set = (vertex_t *) malloc( sizeof(_g->num_vertices * sizeof(vertex_t)) );

	for ( int i = 0; i < _g->num_vertices; i++){
		_g->vertex_set[i].label = 0;
		_g->vertex_set[i].is_visited = 0;
		_g->vertex_set[i].num_neighbors = 0;
		_g->vertex_set[i].neighbors = (vertex_t **) malloc (sizeof(vertex_t));
	}
}

void connect_vertices(graph_t * _g)
{
	vertex_t * v_1, * v_2;

	for ( int i = 0; i < _g->num_edges; i++ ){
		v_1 = &(_g->vertex_set[i]);
		v_2 = &( _g->vertex_set[ (i+1) % (_g->num_vertices) ] );
		setup_edge(_g, v_1, v_2);
	}
}

void setup_edge(graph_t * _g, vertex_t * _v_1, vertex_t * _v_2)
{
	_v_1->num_neighbors ++;
	_v_2->num_neighbors ++;

	_v_1->neighbors = (vertex_t **) realloc (_v_1->neighbors, _v_1->num_neighbors * sizeof(vertex_t *) );
	_v_2->neighbors = (vertex_t **) realloc (_v_2->neighbors, _v_2->num_neighbors * sizeof(vertex_t *) );

	_v_1->neighbors[_v_1->num_neighbors - 1] = _v_2;
	_v_2->neighbors[_v_2->num_neighbors - 1] = _v_1;
}

