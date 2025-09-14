#ifndef _QUEUE_H
#define _QUEUE_H

#include <document.h>

typedef struct
{
    int bottom, top, elements; //bottom é o índice do primeiro elemento e top é o último mais 1 (proximo)
    Document documents[QUEUE_SIZE];
} Queue;


Queue *queue_create();

int queue_add(Queue *queue, Document document);
int queue_remove(Queue *queue, Document *document);
bool queue_is_empty(Queue *queue);
bool queue_is_full(Queue *queue);

#endif
