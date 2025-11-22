#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <poplist.h>
#include <person.h>

typedef struct Element
{
    struct Element *next;
    struct Element *prev;

    Person *person;

} Element;

typedef struct PopList
{
    struct Element *start;
    struct Element *end;
    int elements;

} PopList;

void poplist_element_free(Element *aux)
{
    if (aux == NULL)
        return;
    person_free(aux->person);
    free(aux);
    return;
}

PopList *poplist_create()
{
    PopList *poplist = (PopList *)malloc(sizeof(PopList));
    if (poplist == NULL)
        return NULL;

    poplist->elements = 0;
    poplist->start = NULL;
    poplist->end = NULL;

    return poplist;
}

void poplist_free(PopList *poplist)
{
    if (!poplist)
        return;

    if (poplist->elements == 0)
    {
        free(poplist);
        return;
    }

    Element *aux = poplist->start;
    Element *aux_free;
    while (aux->next)
    {
        aux_free = aux;
        aux = aux->next;

        poplist_element_free(aux_free);
    }

    poplist_element_free(aux);
    free(poplist);
}

int poplist_get_elements(PopList *poplist)
{
    if (!poplist)
        return -1;
    return poplist->elements;
}

Person **poplist_people(PopList *poplist)
{
    if (!poplist)
        return NULL;
    if (poplist->elements == 0)
        return NULL;

    Person **array = (Person **)malloc(sizeof(Person *) * poplist->elements);
    if (!array)
        return NULL;

    Element *aux = poplist->start;
    int i = 0;

    do
    {
        array[i] = aux->person;
        aux = aux->next;
        i++;

    } while (aux);

    return array;
}

int poplist_remove_by_name(PopList *poplist, char *name)
{
    if (poplist == NULL || name == NULL)
        return 1;
    if (poplist->elements == 0)
        return 1;

    Element *aux = poplist->start;

    int compare = PERSON1_BEFORE;

    while ((compare == PERSON1_BEFORE) && (aux != NULL))
    {
        compare = person_compare_order_by_name(aux->person, name);

        if (compare == PERSON_EQUAL)
        {
            if (aux->prev)
            {
                (aux->prev)->next = aux->next;
            }
            else
            {
                poplist->start = aux->next;
            }

            if (aux->next)
            {
                (aux->next)->prev = aux->prev;
            }
            else
            {
                poplist->end = aux->prev;
            }

            poplist_element_free(aux);
            poplist->elements--;
            return 0;
        }
        aux = aux->next;
    }
    return 1;
}

Person *poplist_search_by_name(PopList *poplist, char *name)
{
    if (poplist == NULL || name == NULL)
        return NULL;
    
    if (poplist->elements == 0)
        return NULL;

    Element *aux = poplist->start;
    int compare = PERSON1_BEFORE;

    while ((compare == PERSON1_BEFORE) && (aux != NULL))
    {
        compare = person_compare_order_by_name(aux->person, name);

        if (compare == PERSON_EQUAL)
        {
            return aux->person;
        }
        aux = aux->next;
    }

    return NULL;
}

int poplist_add_end(PopList *poplist, Person *person)
{
    if (!poplist)
        return 1;

    Element *new_element = (Element *)malloc(sizeof(Element));
    if (new_element == NULL)
        return 1;

    new_element->person = person;
    new_element->prev = poplist->end;
    new_element->next = NULL;

    if (poplist->end)
        (poplist->end)->next = new_element;
    if (!new_element->prev)
        poplist->start = new_element;

    poplist->end = new_element;
    poplist->elements++;

    return 0;
}

int poplist_add_before(PopList *poplist, Element *element, Person *person)
{
    if (!element)
        return 1;
    Element *new_element = (Element *)malloc(sizeof(Element));
    if (new_element == NULL)
        return 1;

    new_element->person = person;
    new_element->prev = element->prev;
    new_element->next = element;

    if (element->prev)
    {
        element->prev->next = new_element;
    }
    else
    {
        poplist->start = new_element;
    }

    element->prev = new_element;

    poplist->elements++;

    return 0;
}

int poplist_add(PopList *poplist, Person *person)
{
    if (poplist == NULL) return 1;

    Element *aux = poplist->start;
    int compare = PERSON1_BEFORE;

    while ((compare == PERSON1_BEFORE) && aux != NULL)
    {
        compare = person_compare_order(aux->person, person);

        if (compare == PERSON_EQUAL)
        {
            // já existe uma música com esse nome
            return 2;
        }
        else if (compare == PERSON2_BEFORE)
        {
            break;
        }

        aux = aux->next;
    }

    if (aux == NULL) return poplist_add_end(poplist,person);

    return poplist_add_before(poplist,aux,person);
}
