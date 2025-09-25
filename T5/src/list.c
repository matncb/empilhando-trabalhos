#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <list.h>
#include <music.h>

typedef struct List
{
    struct Element *start;
    int elements;

}List;

typedef struct Element
{
    struct Element *next;
    
    Music *music;

}Element;

List *list_create()
{
    List *list = (List *) malloc(sizeof(List));
    if (list == NULL) return NULL;

    list->elements = 0;
    list->start = NULL;

    return list;
}

int list_append(List *list, Music *music)  
{
    Element *new_element = (Element *) malloc(sizeof(Element));
    if (new_element == NULL) return 1;
    
    new_element->music = music;

    new_element->next = NULL;

    if (!list->start)
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

int list_remove(List *list)
{
    if(list->elements == 0) return 1;

    Element *aux = list->start;
    list->start = aux->next;
    music_free(aux->music);
    free(aux);

    list->elements--;
    return 0;
}

Music *list_start_element(List *list)
{
    if (list->start == NULL) return NULL;
    return (list->start)->music;
}

int list_get_elements(List *list)
{
    return list->elements;
}

Music **list_songs(List *list)
{
    if (list->elements == 0) return NULL;

    Music **array = (Music **) malloc(sizeof(Music*)*list->elements);
    if (!array) return NULL;
    
    Element *aux = list->start;
    int i = 0;
    
    do{
        array[i] = aux->music;
        aux = aux->next;
        i++;

    }while (aux);

    return array;
}

void list_free(List *list)
{
    Element *aux = list->start;
    Element *aux_free;
    while (aux->next)
    {
        aux_free = aux;
        aux = aux->next;

        music_free(aux_free->music);
        free(aux_free);
    }

    music_free(aux->music);
    free(aux);
    free(list);
}

int list_remove_by_name(List *list, char *name)
{
    if (list->elements == 0) return 1;
    
    Element *aux = list->start;
    Element *aux_free;

    if (strcmp(music_get_name(aux->music), name) == 0)
    {
        if (aux->next)
        {
            list->start = aux->next;
        }
        else
        {
            list->start = NULL;
        }
        music_free(aux->music);
        free(aux);
        list->elements--;

        return 0;
    }

    while (aux->next)
    {
        if (strcmp(music_get_name((aux->next)->music), name) == 0)
        {
            aux_free = aux->next;
            aux->next = (aux->next)->next;
            music_free(aux_free->music);
            free(aux_free);
            list->elements--;
            return 0;
        }
    }

       
    return 1;
}


