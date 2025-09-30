#ifndef _LIST_H
#define _LIST_H

#include <task.h>

typedef struct List List;
typedef struct Element Element;

List *list_create();
void element_free(Element *aux);
int list_add_end(List *list, Task *task);
int list_add_start(List *list, Task *task);
int list_remove_end(List *list);
int list_remove_start(List *list);
Task **list_tasks(List *list);
Task *list_start_element(List *list);
Task *list_end_element(List *list);
int list_remove_by_name(List *list, char *name);
void list_free(List *list);
int list_get_elements(List *list);
Task *list_start_element(List *list);

#endif
