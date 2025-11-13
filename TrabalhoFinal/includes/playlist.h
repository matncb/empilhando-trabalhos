#ifndef _PLAYLIST_H
#define _PLAYLIST_H

#include <music.h>

typedef struct PlayList PlayList;
typedef struct Element Element;

PlayList *playlist_create();
void element_free(Element *aux);
Music **playlist_songs(PlayList *playlist);
int playlist_remove_by_name(PlayList *playlist, char *name);
Music *playlist_search_by_name(PlayList *playlist, char *name);
void playlist_free(PlayList *playlist);
int playlist_get_elements(PlayList *playlist);
int playlist_add(PlayList *playlist, Music *Music);

#endif
