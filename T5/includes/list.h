#ifndef _LIST_H
#define _LIST_H

#include <data.h>

typedef struct List
{
    struct Element *start;
    int elements;

}List;

typedef struct Element
{
    struct Element *next;
    Data *data;

}Element;


#endif
