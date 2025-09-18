#ifndef _LIST_H
#define _LIST_H

#include <data.h>

typedef struct List
{
    struct List *start;
    struct List *end;

    int elements;

}List;

typedef struct Element
{
    struct List *next;
    struct List *prev;

    Data *data;

}Element;


#endif
