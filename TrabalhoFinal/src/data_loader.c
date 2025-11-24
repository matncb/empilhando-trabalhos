#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <data_loader.h>

#define MAX_LINE_LENGTH 256
#define INITIAL_CAPACITY 100

struct DataBank {
    char **names;
    int name_count;
    char **songs;
    char **artists;
    int song_count;
};

char **read_names_from_csv(char *filename, int *count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir arquivo de nomes");
        return NULL;
    }

    char **names = NULL;
    int capacity = INITIAL_CAPACITY;
    int size = 0;
    char line[MAX_LINE_LENGTH];

    names = (char **)malloc(capacity * sizeof(char *));
    if (!names) {
        fclose(file);
        return NULL;
    }

    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        if (len > 0 && line[len - 1] == '\r') {
            line[len - 1] = '\0';
        }

        if (strlen(line) == 0) continue;

        if (size >= capacity) {
            capacity *= 2;
            char **new_names = (char **)realloc(names, capacity * sizeof(char *));
            if (!new_names) {
                for (int i = 0; i < size; i++) {
                    free(names[i]);
                }
                free(names);
                fclose(file);
                return NULL;
            }
            names = new_names;
        }

        names[size] = strdup(line);
        if (!names[size]) {
            for (int i = 0; i < size; i++) {
                free(names[i]);
            }
            free(names);
            fclose(file);
            return NULL;
        }
        size++;
    }

    fclose(file);
    *count = size;
    return names;
}

int read_songs_from_csv(char *filename, char ***songs, char ***artists, int *count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir arquivo de músicas");
        return 1;
    }

    char **song_list = NULL;
    char **artist_list = NULL;
    int capacity = INITIAL_CAPACITY;
    int size = 0;
    char line[MAX_LINE_LENGTH];

    song_list = (char **)malloc(capacity * sizeof(char *));
    artist_list = (char **)malloc(capacity * sizeof(char *));
    if (!song_list || !artist_list) {
        if (song_list) free(song_list);
        if (artist_list) free(artist_list);
        fclose(file);
        return 1;
    }

    int first_line = 1;
    while (fgets(line, sizeof(line), file)) {
        if (first_line) {
            first_line = 0;
            continue;
        }
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        if (len > 0 && line[len - 1] == '\r') {
            line[len - 1] = '\0';
        }

        if (strlen(line) == 0) continue;

        char *comma = strchr(line, ',');
        if (!comma) {
            continue;
        }

        if (size >= capacity) {
            capacity *= 2;
            char **new_songs = (char **)realloc(song_list, capacity * sizeof(char *));
            char **new_artists = (char **)realloc(artist_list, capacity * sizeof(char *));
            if (!new_songs || !new_artists) {
                // Se realloc falhou, libera os novos ponteiros se existirem
                // e os antigos ainda são válidos
                if (new_songs && new_songs != song_list) free(new_songs);
                if (new_artists && new_artists != artist_list) free(new_artists);
                // Libera memória já alocada
                for (int i = 0; i < size; i++) {
                    free(song_list[i]);
                    free(artist_list[i]);
                }
                free(song_list);
                free(artist_list);
                fclose(file);
                return 1;
            }
            // Atualiza os ponteiros para os novos blocos de memória
            song_list = new_songs;
            artist_list = new_artists;
            song_list = new_songs;
            artist_list = new_artists;
        }

        *comma = '\0';
        char *song_name = line;
        char *artist_name = comma + 1;

        while (*song_name == ' ') song_name++;
        while (*artist_name == ' ') artist_name++;

        song_list[size] = strdup(song_name);
        artist_list[size] = strdup(artist_name);

        if (!song_list[size] || !artist_list[size]) {
            if (song_list[size]) free(song_list[size]);
            if (artist_list[size]) free(artist_list[size]);
            for (int i = 0; i < size; i++) {
                free(song_list[i]);
                free(artist_list[i]);
            }
            free(song_list);
            free(artist_list);
            fclose(file);
            return 1;
        }
        size++;
    }

    fclose(file);
    *songs = song_list;
    *artists = artist_list;
    *count = size;
    return 0;
}

DataBank *data_load_from_csv(char *names_file, char *songs_file) {
    DataBank *bank = (DataBank *)malloc(sizeof(DataBank));
    if (!bank) return NULL;

    bank->names = NULL;
    bank->songs = NULL;
    bank->artists = NULL;
    bank->name_count = 0;
    bank->song_count = 0;

    bank->names = read_names_from_csv(names_file, &bank->name_count);
    if (!bank->names || bank->name_count == 0) {
        printf("Aviso: Nenhum nome carregado do arquivo %s\n", names_file);
        if (bank->names) {
            for (int i = 0; i < bank->name_count; i++) {
                free(bank->names[i]);
            }
            free(bank->names);
        }
        free(bank);
        return NULL;
    }

    if (read_songs_from_csv(songs_file, &bank->songs, &bank->artists, &bank->song_count) != 0) {
        printf("Aviso: Nenhuma música carregada do arquivo %s\n", songs_file);
        for (int i = 0; i < bank->name_count; i++) {
            free(bank->names[i]);
        }
        free(bank->names);
        free(bank);
        return NULL;
    }

    if (bank->song_count == 0) {
        printf("Aviso: Nenhuma música carregada do arquivo %s\n", songs_file);
        for (int i = 0; i < bank->name_count; i++) {
            free(bank->names[i]);
        }
        free(bank->names);
        free(bank);
        return NULL;
    }

    printf("Dados carregados: %d nomes, %d músicas\n", bank->name_count, bank->song_count);
    return bank;
}

void data_bank_free(DataBank *bank) {
    if (!bank) return;

    if (bank->names) {
        for (int i = 0; i < bank->name_count; i++) {
            free(bank->names[i]);
        }
        free(bank->names);
    }

    if (bank->songs) {
        for (int i = 0; i < bank->song_count; i++) {
            free(bank->songs[i]);
        }
        free(bank->songs);
    }

    if (bank->artists) {
        for (int i = 0; i < bank->song_count; i++) {
            free(bank->artists[i]);
        }
        free(bank->artists);
    }

    free(bank);
}

char *data_get_random_name(DataBank *bank) {
    if (!bank || !bank->names || bank->name_count == 0) return NULL;
    int index = rand() % bank->name_count;
    return bank->names[index];
}

char *data_get_random_song(DataBank *bank) {
    if (!bank || !bank->songs || bank->song_count == 0) return NULL;
    int index = rand() % bank->song_count;
    return bank->songs[index];
}

char *data_get_random_artist(DataBank *bank) {
    if (!bank || !bank->artists || bank->song_count == 0) return NULL;
    int index = rand() % bank->song_count;
    return bank->artists[index];
}

void data_get_random_song_pair(DataBank *bank, char **song, char **artist) {
    if (!bank || !bank->songs || !bank->artists || bank->song_count == 0) {
        *song = NULL;
        *artist = NULL;
        return;
    }
    int index = rand() % bank->song_count;
    *song = bank->songs[index];
    *artist = bank->artists[index];
}



