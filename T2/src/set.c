#include <stdio.h>
#include <stdlib.h>

#include <set.h>

Set* set_create(int length)
{
    Set* set = (Set*) malloc(sizeof(Set));
    set->length = length;
}

void set_fill(Set* set)
{
    if (set->length == 0)
    {
        set->data = NULL;
    }
    return;
}

void set_print(Set* set)
{
    
    return ;
}