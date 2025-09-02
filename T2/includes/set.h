#ifndef _SET_H 
#define _SET_H

typedef struct
{
    int* data;
    int length;
}Set;

Set* set_create(int* array, int length);

void set_destroy(Set* set);

void set_print(Set* set);

Set* set_union(Set* setA, Set* setB);

Set* set_intersect(Set* setA, Set* setB);

Set* set_difference(Set* setA, Set* setB);

bool set_has(Set* set, int x);

#endif
