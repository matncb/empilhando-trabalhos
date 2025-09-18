#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <list.h>
#include <data.h>

List *list_create()
{
    List *list = (List *) malloc(sizeof(List));

    if (!list) return NULL;

    list->elements = 0;
    list->start = NULL;
    list->end = NULL;

    return list;
}

int list_add_after(List *list, Data *data, Element *element)
{
    Element *new_element = (Element *) malloc(sizeof(Element));

    new_element->data = data;
 
    if (!new_element) return 1;

    if (!element) // Lista vazia
    {
        new_element->prev = NULL;
        new_element->next = NULL;

        list->start = new_element;
        list->end = new_element;
    }
    else
    {
        Element *aux = element->next;
        element->next = new_element;
        new_element->next = aux;
        new_element->prev = element;

        if (!new_element->next)
        {
            list->end = new_element;
        }
    }

    list->elements++;
    return 0;
}