#ifndef _GRAPH_H
#define _GRAPH_H

#include <poplist.h>

typedef enum
{
    WHITE,
    GREY,
    BLACK
} TypeColor;

typedef struct Edge Edge;
typedef struct Vertex Vertex;
typedef struct Graph Graph;

Graph *graph_create(int pop_size);
void graph_update_edges(Graph *graph, int src, int dest, int weight);
void graph_update(Graph *graph, PopList *list);
void free_graph(Graph *graph);
int export_graph(Graph *graph, PopList *poplist);
int calculate_similarity(void *p1, void *p2);
int graph_get_vertex_qnt(Graph *graph);
int graph_get_edge_weight(Graph *graph, int src, int dest);

#endif
