#include <stdio.h>
#include <music.h>
#include <string.h>
#include <stdlib.h>

typedef struct music
{
    char *name;
    char *artist;
    char *comment;
} Music;

Music *music_create(char *name, char *artist, char *comment)
{
    Music *music = malloc(sizeof(Music));
    if (music == NULL) return NULL;

    music->name = NULL;
    music->artist = NULL;
    music->comment = NULL;

    if (music_set_name(music, name) || music_set_artist(music, artist) || music_set_comment(music, comment))
    {
        music_free(music);
        return NULL;
    }

    return music;
}

void music_free(Music *music)
{
    if (music == NULL) return;
    
    free(music->name);
    free(music->artist);
    free(music->comment);
    free(music);

    return;
}

// funções de set
int music_set_name(Music *music, char *name)
{
    if(music == NULL) return 1;
    
    if (music->name != NULL) {
        free(music->name);
    }
    music->name = strdup(name); 
    if(!music->name) return 1;

    return 0;
}

int music_set_artist(Music *music, char *artist)
{
    if(music == NULL) return 1;

    if (music->artist != NULL) {
        free(music->artist);
    }
    music->artist = strdup(artist);
    if(!music->artist) return 1;
    
    return 0;
}

int music_set_comment(Music *music, char *comment)
{
    if(music == NULL) return 1;

    if (music->comment != NULL) {
        free(music->comment);
    }
    music->comment = strdup(comment);
    if(!music->comment) return 1;
    
    return 0;
}

// funções de get
char *music_get_name(Music *music)
{
    if(music == NULL) return NULL;
    return music->name;
}

char *music_get_artist(Music *music)
{
    if(music == NULL) return NULL;
    return music->artist;
}

char *music_get_comment(Music *music)
{
    if(music == NULL) return NULL;
    return music->comment;
}

/*
    @return int (1|2|-1|1)
*/
// Ordem alfabética
int music_compare_order(Music *music1, Music *music2)
{
    // Código de erro para argumentos incorretos 
    if ((music1 == NULL) || (music2 == NULL)) return INCORRECT_PARAMS_ERROR;

    if ((music1->name == NULL) || (music2->name ==NULL)) return NULL_NAMES_ERROR;
    
    if (strcmp(music1->name, music2->name) < 0)
    {
        return DATA1_BEFORE; // music1 vem antes
    }
    else if (strcmp(music1->name, music2->name) > 0)
    {
        return DATA2_BEFORE; // music1 vem depois
    }

    return DATA_EQUAL; // music1 é igual
}

int music_compare_order_by_name(Music *music1, char *name)
{
    // Código de erro para argumentos incorretos
    if (music1 == NULL) return INCORRECT_PARAMS_ERROR ;

    if ((music1->name == NULL) || name == NULL)  return NULL_NAMES_ERROR;

    if (strcmp(music1->name, name) < 0)
    {
        return DATA1_BEFORE; // music1 vem antes
    }
    else if (strcmp(music1->name, name) > 0)
    {
        return DATA2_BEFORE; // music1 vem depois
    }

    return DATA_EQUAL; // music1 é igual
}