#ifndef _PLAYLIST_H
#define _PLAYLIST_H

#include <music.h>

typedef struct PlayList PlayList;
typedef struct Element Element;

PlayList *playlist_create();
Music **playlist_songs(PlayList *playlist);
int playlist_remove_by_name(PlayList *playlist, char *name);
int playlist_remove_by_name_and_artist(PlayList *playlist, char *name, char *artist);
Music *playlist_search_by_name(PlayList *playlist, char *name);
void playlist_free(PlayList *playlist);
int playlist_get_elements(PlayList *playlist);
int playlist_add(PlayList *playlist, Music *Music);
int playlist_add_end(PlayList *playlist, Music *music);
int playlist_add_before(PlayList *playlist, Element *element, Music *music);

#endif
