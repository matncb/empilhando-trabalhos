#ifndef _LIST_H
#define _LIST_H

typedef struct List{
    int data;
    struct List *prev;
    struct List *next;
}List;


List *list_alloc();

List *list_append(List *list, int data);

List *list_remove(List *list, int data);

List *list_first(List *list);

List *list_last(List *list);

void list_free(List *list);

int list_get_data(List *list);


#define INT_TO_POINTER(u) (void*)u

#endif