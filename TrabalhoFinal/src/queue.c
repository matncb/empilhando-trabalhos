#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <queue.h>
#include <music.h>

Queue *queue_create()
{
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    if (queue == NULL) return NULL;

    queue->top = 0;
    queue->bottom = 0;
    queue->elements = 0;

    return queue;
}

int queue_add(Queue *queue, Music *music)
{
 
    if (queue_is_full(queue))
    {
        return 1;
    }
    
    queue->musics[queue->top] = music;

    queue->top = (queue->top == QUEUE_SIZE -1) ? 0 : queue->top + 1;

    queue->elements++;

    return 0;
}

int queue_remove(Queue *queue, Music **music)
{
    if (queue_is_empty(queue))
    {
        return 1;
    }
    
    *music = queue->musics[queue->bottom];

    queue->bottom = (queue->bottom == QUEUE_SIZE - 1) ? 0 : queue->bottom + 1;

    queue->elements--;

    return 0;

}

Music **queue_get_musics(Queue *queue)
{
    if (!queue || queue->elements == 0) return NULL;

    Music **musics = (Music**) malloc(sizeof(Music*)*queue->elements);
    if (!musics) return NULL;

    int idx = queue->bottom;
    for (int i = 0; i < queue->elements; i++)
    {
        musics[i] = queue->musics[idx];
        idx = (idx == QUEUE_SIZE - 1) ? 0 : idx + 1;
    }

    return musics;
}

int queue_get_elements(Queue *queue)
{
    if (!queue) return -1;
    return queue->elements;
}

int queue_get_bottom(Queue *queue)
{
    if (!queue) return -1;
    return queue->bottom;
}

int queue_get_top(Queue *queue)
{
    if (!queue) return -1;
    return queue->top;
}

bool queue_is_empty(Queue *queue)
{
    if (!queue) return true;
    return (queue->elements == 0);
}

bool queue_is_full(Queue *queue)
{
    if (!queue) return false;
    return (queue->elements == QUEUE_SIZE);
}

void queue_free(Queue *queue)
{
    if (!queue) return;
    
    Music *music;
    while (!queue_is_empty(queue)) {
        if (queue_remove(queue, &music) == 0) {
            music_free(music);
        }
    }
    
    free(queue);
}

