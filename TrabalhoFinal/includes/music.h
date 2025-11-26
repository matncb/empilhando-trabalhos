#ifndef _MUSIC_H
#define _MUSIC_H

typedef struct music Music;

enum MusicComparisonReturn {
    MUSIC1_BEFORE = -1,
    MUSIC_EQUAL = 0,
    MUSIC2_BEFORE = 1,
    MUSIC_INCORRECT_PARAMS_ERROR = 2,
    MUSIC_NULL_NAMES_ERROR = 3
};
char *music_get_name(Music *music);
Music *music_create(char *name, char *artist, char *comment);
void music_free(Music *music);
int music_set_name(Music *music, char *name);
int music_set_artist(Music *music, char *artist);
int music_set_comment(Music *music, char *comment);
char *music_get_artist(Music *music);
char *music_get_comment(Music *music);
int music_compare_order(Music *music1, Music *music2);
int music_compare_order_by_name(Music *music1, char *name);
#endif 