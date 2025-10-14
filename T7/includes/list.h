#ifndef _LIST_H
#define _LIST_H

#include <data.h>

typedef struct List List;
typedef struct Element Element;

List *list_create();
void element_free(Element *aux);
Data **list_datas(List *list);
int list_remove_by_name(List *list, char *name);
Data *list_search_by_name(List *list, char *name);
void list_free(List *list);
int list_get_elements(List *list);
int list_add(List *list, Data *data);

#endif
