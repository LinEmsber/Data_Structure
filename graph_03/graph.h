/* The header of graph. */

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

/* typedef */
typedef struct vertex vertex_t;
typedef struct graph graph_t;

/* structure */
struct vertex{
	char label;
	char is_visited;
	int num_adjacent;
	struct vertex ** adjacent_list;
};

struct graph{
	int num_edges;
	int num_vertices;
	struct vertex * vertex_set;
};


/* function declaration */
graph_t * create_graph(int _num_edges, int _num_vertices);
void setup_vertices(graph_t * _g);
void connect_vertices(graph_t * _g);
void setup_edge(graph_t * _g, vertex_t * _v_1, vertex_t * _v_2);
void print_graph(graph_t * _g);

#endif
