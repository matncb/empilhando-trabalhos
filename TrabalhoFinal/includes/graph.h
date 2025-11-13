#ifndef _GRAPH_H
#define _GRAPH_H

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

#endif
