#include <stdio.h>
#include <music.h>
#include <string.h>
#include <stdlib.h>

// funções de set

Music *music_create(char *name, char *artist, int duration)
{
    Music *music = malloc(sizeof(Music));
    if (!music) return NULL;

    music_set_name(music, name);
    music_set_artist(music, artist);
    music_set_duration(music, duration);    
    
    return music;
}

void music_free(Music *music)
{
    free(music->name);
    free(music->artist);
    free(music);
}

void music_set_name(Music *music, char *name)
{
    if (music->name != NULL) {
        free(music->name);
    }
    music->name = strdup(name); 
}

void music_set_artist(Music *music, char *artist)
{
    if (music->artist != NULL) {
        free(music->artist);
    }
    music->artist = strdup(artist);
}

void music_set_duration(Music *music, int duration)
{
    music->duration = duration;
}


// funções de get
char *music_get_name(Music *music)
{
    return music->name;
}

char *music_get_artist(Music *music)
{
    return music->artist;
}

int music_get_duration(Music *music)
{
    return music->duration;
}