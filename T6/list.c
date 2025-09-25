
#include <stdlib.h>
#include "list.h"



List *list_alloc()
{
    List *list = malloc(sizeof(List));
    
    list->next = NULL;
    list->prev = NULL;
    list->data = NULL;

    return list;
}

List *list_append(List *list, int data)
{   
    List *new_list = list_alloc();
    List *last_list;
    
    
    
    if(list){
        last_list = list_last(list);
        last_list->next = new_list;
        new_list->prev = last_list;
    }

    new_list->data = data;
    new_list->next = NULL;
    

    return new_list;
}


List *list_remove(List *list, int data)
{
    List *tmp = list;
    while(tmp){
        if(tmp->data == data){
            list->next = list->next->next;
            list_free(list->next);
        }
        tmp = list->next;
    }   
}


List *list_first(List *list)
{
    List *first = list;
    while(first->prev){
        first = first->prev;
    }
    return first;
}

List *list_last(List *list)
{
    List *last = list;
    while(last->next){
        last = last->next;
    }
    return last;
}


void list_free(List *list)
{
    free(list);
}


