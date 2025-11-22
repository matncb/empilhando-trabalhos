#ifndef _DATA_LOADER_H
#define _DATA_LOADER_H

typedef struct {
    char **names;
    int name_count;
    char **songs;
    char **artists;
    int song_count;
} DataBank;

DataBank *data_load_from_csv(const char *names_file, const char *songs_file);
void data_bank_free(DataBank *bank);
char *data_get_random_name(DataBank *bank);
char *data_get_random_song(DataBank *bank);
char *data_get_random_artist(DataBank *bank);

#endif

