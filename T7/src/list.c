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

} Element;

typedef struct List
{
    struct Element *start;
    struct Element *end;
    int elements;

} List;

void element_free(Element *aux)
{
    if (aux == NULL)
        return;
    data_free(aux->data);
    free(aux);
    return;
}

List *list_create()
{
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL)
        return NULL;

    list->elements = 0;
    list->start = NULL;
    list->end = NULL;

    return list;
}

void list_free(List *list)
{
    if (!list)
        return;

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
    if (!list)
        return -1;
    return list->elements;
}

Data **list_datas(List *list)
{
    if (!list)
        return NULL;
    if (list->elements == 0)
        return NULL;

    Data **array = (Data **)malloc(sizeof(Data *) * list->elements);
    if (!array)
        return NULL;

    Element *aux = list->start;
    int i = 0;

    do
    {
        array[i] = aux->data;
        aux = aux->next;
        i++;

    } while (aux);

    return array;
}

int list_remove_by_name(List *list, char *name)
{
    if (list == NULL || name == NULL)
        return 1;
    if (list->elements == 0)
        return 1;

    Element *aux = list->start;

    int compare = DATA1_BEFORE;

    while ((compare == DATA1_BEFORE) && (aux != NULL))
    {
        compare = data_compare_order_by_name(aux->data, name);

        if (compare == DATA_EQUAL)
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
    int compare = DATA1_BEFORE;

    while ((compare == DATA1_BEFORE) && (aux != NULL))
    {
        compare = data_compare_order_by_name(aux->data, name);

        if (compare == DATA_EQUAL)
        {
            return aux->data;
        }
        aux = aux->next;
    }

    return NULL;
}

int list_add_end(List *list, Data *data)
{
    if (!list) return 1;

    Element *new_element = (Element *)malloc(sizeof(Element));
    if (new_element == NULL) return 1;

    new_element->data = data;
    new_element->prev = list->end;
    new_element->next = NULL;

    if (list->end) (list->end)->next = new_element;
    if (!new_element->prev) list->start = new_element;

    list->end = new_element;
    list->elements++;

    return 0;
}

int list_add_before(List *list, Element *element, Data *data)
{
    if (!element) return 1;
    Element *new_element = (Element *)malloc(sizeof(Element));
    if (new_element == NULL) return 1;

    new_element->data = data;
    new_element->prev = element->prev;
    new_element->next = element;

    if (element->prev)
    {
        element->prev->next = new_element;
    }
    else
    {
        list->start = new_element;
    }

    element->prev = new_element;

    list->elements++;

    return 0;
}

int list_add(List *list, Data *data)
{
    if (list == NULL) return 1;

    Element *aux = list->start;
    int compare = DATA1_BEFORE;

    while ((compare == DATA1_BEFORE) && aux != NULL)
    {
        compare = data_compare_order(aux->data, data);

        if (compare == DATA_EQUAL)
        {
            // já existe um contato com esse nome
            return 2;
        }
        else if (compare == DATA2_BEFORE)
        {
            break;
        }

        aux = aux->next;
    }

    if (aux == NULL) return list_add_end(list,data);

    return list_add_before(list,aux,data);
}
