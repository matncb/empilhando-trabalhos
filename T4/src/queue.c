#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <queue.h>
#include <document.h>

Queue *queue_create()
{
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    if (queue == NULL) return NULL;

    queue->top = 0;
    queue->bottom = 0;
    queue->elements = 0;

    return queue;
}

int queue_add(Queue *queue, Document document)
{
 
    if (queue_is_full(queue))
    {
        return 1;
    }
    
    queue->documents[queue->top] = document;

    queue->top = (queue->top == QUEUE_SIZE -1) ? 0 : queue->top + 1;

    queue->elements++;

    return 0;
}

int queue_remove(Queue *queue, Document *document)
{
    if (queue_is_empty(queue))
    {
        return 1;
    }
    
    *document = queue->documents[queue->bottom];

    queue->bottom = (queue->bottom == QUEUE_SIZE - 1) ? 0 : queue->bottom + 1;

    queue->elements--;

    return 0;

}

Document *queue_get_documents(Queue *queue)
{
    Queue *new_queue = (Queue*) malloc(sizeof(Queue));

    if (!new_queue) return NULL;
    *new_queue = *queue;

    Document *documents = (Document*) malloc(sizeof(Document)*queue->elements);
    if (!documents) return NULL;

    for (int i = 0; i<queue->elements; i++)
    {
        queue_remove(new_queue, &documents[i]);
    }

    free(new_queue);

    return documents;

}

int queue_get_elements(Queue *queue)
{
    return queue->elements;
}

bool queue_is_empty(Queue *queue)
{
    return (queue->elements == 0);
}

bool queue_is_full(Queue *queue)
{
    return (queue->elements == QUEUE_SIZE);
}