#ifndef _QUEUE_H
#define _QUEUE_H

#include <music.h>
#include <stdbool.h>

#define QUEUE_SIZE 100

typedef struct Queue Queue;

Queue *queue_create();

int queue_add(Queue *queue, Music *music);
int queue_remove(Queue *queue, Music **music);
bool queue_is_empty(Queue *queue);
bool queue_is_full(Queue *queue);
Music **queue_get_musics(Queue *queue);

int queue_get_bottom(Queue *queue);
int queue_get_elements(Queue *queue);
int queue_get_top(Queue *queue);
void queue_free(Queue *queue);

#endif

