#ifndef _LIST_H
#define _LIST_H

#include <music.h>

typedef struct List List;

List *list_create();
int list_append(List *list, Music *music);
int list_remove(List *list);
Music **list_songs(List *list);
int list_remove_by_name(List *list, char *name);
void list_free(List *list);
int list_get_elements(List *list);
Music *list_start_element(List *list);

#endif
