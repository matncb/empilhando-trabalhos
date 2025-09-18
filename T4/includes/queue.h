#ifndef _QUEUE_H
#define _QUEUE_H

#include <document.h>

#define QUEUE_SIZE 100

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
Document *queue_get_documents(Queue *queue);

int queue_get_bottom(Queue *queue);
int queue_get_elements(Queue *queue);
int queue_get_top(Queue *queue);

#endif
