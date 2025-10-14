#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <list.h>
#include <data.h>

typedef struct Element
{
    struct Element *next;
    struct Element *prev;

    Data *data;

}Element;

typedef struct List
{
    struct Element *start;
    struct Element *end;
    int elements;

}List;

void element_free(Element *aux)
{
    if(aux == NULL) return; 
    data_free(aux->data);
    free(aux);
    return;
}

List *list_create()
{
    List *list = (List *) malloc(sizeof(List));
    if (list == NULL) return NULL;

    list->elements = 0;
    list->start = NULL;
    list->end = NULL;

    return list;
}

void list_free(List *list)
{
    if (!list) return;

    if (list->elements == 0)
    {
        free(list);
        return;
        }
        
        Element *aux = list->start;
        Element *aux_free;
        while (aux->next)
    {
        aux_free = aux;
        aux = aux->next;
        
        element_free(aux_free);
    }

    element_free(aux);
    free(list);
}

int list_get_elements(List *list)
{
    if (!list) return -1;
    return list->elements;
}

Data **list_datas(List *list)
{
    if (!list) return NULL;
    if (list->elements == 0) return NULL;

    Data **array = (Data **) malloc(sizeof(Data*)*list->elements);
    if (!array) return NULL;
    
    Element *aux = list->start;
    int i = 0;
    
    do{
        array[i] = aux->data;
        aux = aux->next;
        i++;

    }while (aux);

    return array;
}

int list_remove_by_name(List *list, char *name)
{
    if (list == NULL || name == NULL) return 1;
    if (list->elements == 0) return 1;
    
    Element *aux = list->start;

    while (aux)
    {
        if (strcmp(data_get_name(aux->data), name) == 0)
        {
            if (aux->prev)
            {
                (aux->prev)->next = aux->next;
            }
            else
            {
                list->start = aux->next;
            }

            if (aux->next) 
            {
                (aux->next)->prev = aux->prev;
            }
            else
            {
                list->end = aux->prev;
            }

            element_free(aux);
            list->elements--;
            return 0;
        }
        aux = aux->next;
    }
    return 1;
}

Data *list_search_by_name(List *list, char *name)
{
    if (list == NULL || name == NULL)
        return NULL;
    if (list->elements == 0)
        return NULL;

    Element *aux = list->start;

    while (aux)
    {
        if (strcmp(data_get_name(aux->data), name) == 0)
        {
            if (aux->prev)
            {
                (aux->prev)->next = aux->next;
            }
            else
            {
                list->start = aux->next;
            }

            if (aux->next)
            {
                (aux->next)->prev = aux->prev;
            }
            else
            {
                list->end = aux->prev;
            }

            element_free(aux);
            list->elements--;
            return 0;
        }
        aux = aux->next;
    }
    return aux->data;
}

int list_add(List *list, Data *data)
{

}


