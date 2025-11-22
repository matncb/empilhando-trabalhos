#ifndef _POPLIST_H
#define _POPLIST_H

#include <person.h>

typedef struct PopList PopList;
typedef struct Element Element;

PopList *poplist_create();
Person **poplist_people(PopList *poplist);
int poplist_remove_by_name(PopList *poplist, char *name);
Person *poplist_search_by_name(PopList *poplist, char *name);
void poplist_free(PopList *poplist);
int poplist_get_elements(PopList *poplist);
int poplist_add(PopList *poplist, Person *Person);

#endif
