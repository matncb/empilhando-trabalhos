#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <list.h>

List *list_create()
{
    List *list = (List *) malloc(sizeof(List));
    if (!list) return NULL;

    list->elements = 0;
    list->start = NULL;

    return list;
}

int list_append(List *list, Data *data)  
{
    Element *new_element = (Element *) malloc(sizeof(Element));
    if (!new_element) return NULL;
    new_element->data = data;

    new_element->next = NULL;

    if (!list)
    {
        list->start = new_element;
    }
    else
    {
        Element *aux = list->start;
        while (aux->next)
        {
            aux = aux->next;
        }

        aux->next = new_element;
    }

    list->elements++;
    return 0;
}

int list_remove(List *list, Element *element)
{
    Element *aux = list->start;
    while (aux->next)
    {
        aux = aux->next;
    }

}