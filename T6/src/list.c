#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <list.h>
#include <task.h>

typedef struct Element
{
    struct Element *next;
    struct Element *prev;

    Task *task;

}Element;

typedef struct List
{
    struct Element *start;
    struct Element *end;
    int elements;

}List;

void element_free(Element *aux)
{
    if(!aux) return; 
    task_free(aux->task);
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

int list_add_end(List *list, Task *task)  
{
    if (!list) return 1;
    Element *new_element = (Element *) malloc(sizeof(Element));
    if (new_element == NULL) return 1;
    
    new_element->task = task;
    new_element->prev = list->end;
    new_element->next = NULL;

    if (list->end) (list->end)->next = new_element;
    if (!new_element->prev) list->start = new_element;

    list->end = new_element;
    list->elements++;

    return 0;
}

int list_add_start(List *list, Task *task)
{
    if (!list) return 1;
    Element *new_element = (Element *)malloc(sizeof(Element));
    if (new_element == NULL) return 1;

    new_element->task = task;
    new_element->prev = NULL;
    new_element->next = list->start;

    if (list->start) (list->start)->prev = new_element;
    if (!new_element->next) (list->end) = new_element;

    list->start = new_element;
    list->elements++;

    return 0;
}

int list_remove_end(List *list)
{
    if (!list) return 1;
    if(list->elements == 0) return 1;

    Element *aux = list->end;
    if ((list->end)->prev)
    {
        ((list->end)->prev)->next = NULL;
    }
    else
    {
        list->start = (list->end)->next;
    }

    list->end = (list->end)->prev;
    element_free(aux);

    list->elements--;
    return 0;
}

int list_remove_start(List *list)
{
    if (!list) return 1;
    if (list->elements == 0) return 1;

    Element *aux = list->start;
    if ((list->start)->next)
    {
        ((list->start)->next)->prev = NULL;
    }
    else
    {
        list->end = (list->start)->prev;
    }
    list->start = (list->start)->next;
    element_free(aux);

    list->elements--;
    return 0;
}

Task *list_start_element(List *list)
{
    if (!list) return NULL;
    if (list->start == NULL) return NULL;
    return (list->start)->task;
}

Task *list_end_element(List *list)
{
    if (!list) return NULL;
    if (list->end == NULL)
        return NULL;
    return (list->end)->task;
}

int list_get_elements(List *list)
{
    if (!list) return -1;
    return list->elements;
}

Task **list_tasks(List *list)
{
    if (!list) return NULL;
    if (list->elements == 0) return NULL;

    Task **array = (Task **) malloc(sizeof(Task*)*list->elements);
    if (!array) return NULL;
    
    Element *aux = list->start;
    int i = 0;
    
    do{
        array[i] = aux->task;
        aux = aux->next;
        i++;

    }while (aux);

    return array;
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

int list_remove_by_name(List *list, char *name)
{
    if (list == NULL || name == NULL) return 1;
    if (list->elements == 0) return 1;
    
    Element *aux = list->start;

    while (aux)
    {
        if (strcmp(task_get_name(aux->task), name) == 0)
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


