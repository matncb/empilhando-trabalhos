#ifndef _MUSIC_H
#define _MUSIC_H

typedef struct Music Music;

char *music_get_name(Music *music);
Music *music_create(char *name, char *artist, int duration);
void music_free(Music *music);
void music_set_name(Music *music, char *name);
void music_set_artist(Music *music, char *artist);
void music_set_duration(Music *music, int duration);
char *music_get_name(Music *music);
char *music_get_artist(Music *music);
int music_get_duration(Music *music);

#endif 