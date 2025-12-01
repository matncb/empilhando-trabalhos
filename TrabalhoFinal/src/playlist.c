#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <playlist.h>
#include <music.h>

typedef struct Element
{
    struct Element *next;
    struct Element *prev;

    Music *music;

} Element;

typedef struct PlayList
{
    struct Element *start;
    struct Element *end;
    int elements;

} PlayList;

void playlist_element_free(Element *aux)
{
    if (aux == NULL)
        return;
    music_free(aux->music);
    free(aux);
    return;
}

PlayList *playlist_create()
{
    PlayList *playlist = (PlayList *)malloc(sizeof(PlayList));
    if (playlist == NULL)
        return NULL;

    playlist->elements = 0;
    playlist->start = NULL;
    playlist->end = NULL;

    return playlist;
}

void playlist_free(PlayList *playlist)
{
    if (!playlist)
        return;

    if (playlist->elements == 0 || !playlist->start)
    {
        free(playlist);
        return;
    }

    Element *aux = playlist->start;
    Element *aux_free;
    while (aux->next)
    {
        aux_free = aux;
        aux = aux->next;

        playlist_element_free(aux_free);
    }

    playlist_element_free(aux);
    free(playlist);
}

int playlist_get_elements(PlayList *playlist)
{
    if (!playlist)
        return -1;
    return playlist->elements;
}

Music **playlist_songs(PlayList *playlist)
{
    if (!playlist)
        return NULL;
    if (playlist->elements == 0)
        return NULL;

    Music **array = (Music **)malloc(sizeof(Music *) * playlist->elements);
    if (!array)
        return NULL;

    Element *aux = playlist->start;
    if (!aux)
    {
        free(array);
        return NULL;
    }

    int i = 0;

    do
    {
        array[i] = aux->music;
        aux = aux->next;
        i++;

    } while (aux && i < playlist->elements);

    return array;
}

int playlist_remove_by_name(PlayList *playlist, char *name)
{
    if (playlist == NULL || name == NULL)
        return 1;
    if (playlist->elements == 0)
        return 1;

    Element *aux = playlist->start;

    while (aux != NULL)
    {
        int compare = music_compare_order_by_name(aux->music, name);

        if (compare == MUSIC_EQUAL)
        {
            if (aux->prev)
            {
                (aux->prev)->next = aux->next;
            }
            else
            {
                playlist->start = aux->next;
            }

            if (aux->next)
            {
                (aux->next)->prev = aux->prev;
            }
            else
            {
                playlist->end = aux->prev;
            }

            playlist_element_free(aux);
            playlist->elements--;
            return 0;
        }
        else if (compare == MUSIC2_BEFORE)
        {
            break;
        }
        
        aux = aux->next;
    }
    return 1;
}

int playlist_remove_by_name_and_artist(PlayList *playlist, char *name, char *artist)
{
    if (playlist == NULL || name == NULL || artist == NULL)
        return 1;
    if (playlist->elements == 0)
        return 1;

    Element *aux = playlist->start;

    while (aux != NULL)
    {
        int compare = music_compare_order_by_name(aux->music, name);

        if (compare == MUSIC_EQUAL)
        {
            char *existing_artist = music_get_artist(aux->music);
            
            if (existing_artist != NULL && strcmp(existing_artist, artist) == 0)
            {
                if (aux->prev)
                {
                    (aux->prev)->next = aux->next;
                }
                else
                {
                    playlist->start = aux->next;
                }

                if (aux->next)
                {
                    (aux->next)->prev = aux->prev;
                }
                else
                {
                    playlist->end = aux->prev;
                }

                playlist_element_free(aux);
                playlist->elements--;
                return 0;
            }
        }
        else if (compare == MUSIC2_BEFORE)
        {
            break;
        }
        
        aux = aux->next;
    }
    return 1;
}

Music *playlist_search_by_name(PlayList *playlist, char *name)
{
    if (playlist == NULL || name == NULL)
        return NULL;
    
    if (playlist->elements == 0)
        return NULL;

    Element *aux = playlist->start;
    int compare = MUSIC1_BEFORE;

    while ((compare == MUSIC1_BEFORE) && (aux != NULL))
    {
        compare = music_compare_order_by_name(aux->music, name);

        if (compare == MUSIC_EQUAL)
        {
            return aux->music;
        }
        aux = aux->next;
    }

    return NULL;
}

int playlist_add(PlayList *playlist, Music *music)
{
    if (playlist == NULL) return 1;

    Element *aux = playlist->start;
    Element *insert_position = NULL;
    char *new_artist = music_get_artist(music);

    while (aux != NULL)
    {
        int compare = music_compare_order(aux->music, music);
        
        if (compare == MUSIC_EQUAL)
        {
            char *existing_artist = music_get_artist(aux->music);
            
            if (existing_artist != NULL && new_artist != NULL && 
                strcmp(existing_artist, new_artist) == 0)
            {
                return 2;
            }
            insert_position = aux->next;
        }
        else if (compare == MUSIC2_BEFORE)
        {
            insert_position = aux;
            break;
        }
        else
        {
            insert_position = aux->next;
        }
        
        aux = aux->next;
    }

    if (insert_position == NULL) 
        return playlist_add_end(playlist, music);

    return playlist_add_before(playlist, insert_position, music);
}

int playlist_add_end(PlayList *playlist, Music *music)
{
    if (!playlist)
        return 1;

    Element *new_element = (Element *)malloc(sizeof(Element));
    if (new_element == NULL)
        return 1;

    new_element->music = music;
    new_element->prev = playlist->end;
    new_element->next = NULL;

    if (playlist->end)
        (playlist->end)->next = new_element;
    if (!new_element->prev)
        playlist->start = new_element;

    playlist->end = new_element;
    playlist->elements++;

    return 0;
}

int playlist_add_before(PlayList *playlist, Element *element, Music *music)
{
    if (!element)
        return 1;
    Element *new_element = (Element *)malloc(sizeof(Element));
    if (new_element == NULL)
        return 1;

    new_element->music = music;
    new_element->prev = element->prev;
    new_element->next = element;

    if (element->prev)
    {
        element->prev->next = new_element;
    }
    else
    {
        playlist->start = new_element;
    }

    element->prev = new_element;

    playlist->elements++;

    return 0;
}
