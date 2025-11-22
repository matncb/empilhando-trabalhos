#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <data_loader.h>

#define MAX_LINE_LENGTH 256
#define INITIAL_CAPACITY 100

static char **read_names_from_csv(const char *filename, int *count) {
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
        // Remove newline
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        if (len > 0 && line[len - 1] == '\r') {
            line[len - 1] = '\0';
        }

        // Skip empty lines
        if (strlen(line) == 0) continue;

        // Expand array if needed
        if (size >= capacity) {
            capacity *= 2;
            char **new_names = (char **)realloc(names, capacity * sizeof(char *));
            if (!new_names) {
                // Free already allocated strings
                for (int i = 0; i < size; i++) {
                    free(names[i]);
                }
                free(names);
                fclose(file);
                return NULL;
            }
            names = new_names;
        }

        // Allocate and copy name
        names[size] = strdup(line);
        if (!names[size]) {
            // Free already allocated strings
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

static int read_songs_from_csv(const char *filename, char ***songs, char ***artists, int *count) {
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

    while (fgets(line, sizeof(line), file)) {
        // Remove newline
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        if (len > 0 && line[len - 1] == '\r') {
            line[len - 1] = '\0';
        }

        // Skip empty lines
        if (strlen(line) == 0) continue;

        // Find comma separator
        char *comma = strchr(line, ',');
        if (!comma) {
            // No comma, treat entire line as song name, artist is "Unknown"
            continue; // Skip malformed lines
        }

        // Expand arrays if needed
        if (size >= capacity) {
            capacity *= 2;
            char **new_songs = (char **)realloc(song_list, capacity * sizeof(char *));
            char **new_artists = (char **)realloc(artist_list, capacity * sizeof(char *));
            if (!new_songs || !new_artists) {
                if (new_songs) free(new_songs);
                if (new_artists) free(new_artists);
                // Free already allocated strings
                for (int i = 0; i < size; i++) {
                    free(song_list[i]);
                    free(artist_list[i]);
                }
                free(song_list);
                free(artist_list);
                fclose(file);
                return 1;
            }
            song_list = new_songs;
            artist_list = new_artists;
        }

        // Split line: song,artist
        *comma = '\0';
        char *song_name = line;
        char *artist_name = comma + 1;

        // Trim whitespace
        while (*song_name == ' ') song_name++;
        while (*artist_name == ' ') artist_name++;

        song_list[size] = strdup(song_name);
        artist_list[size] = strdup(artist_name);

        if (!song_list[size] || !artist_list[size]) {
            if (song_list[size]) free(song_list[size]);
            if (artist_list[size]) free(artist_list[size]);
            // Free already allocated strings
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

DataBank *data_load_from_csv(const char *names_file, const char *songs_file) {
    DataBank *bank = (DataBank *)malloc(sizeof(DataBank));
    if (!bank) return NULL;

    bank->names = NULL;
    bank->songs = NULL;
    bank->artists = NULL;
    bank->name_count = 0;
    bank->song_count = 0;

    // Load names
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

    // Load songs
    if (read_songs_from_csv(songs_file, &bank->songs, &bank->artists, &bank->song_count) != 0) {
        printf("Aviso: Nenhuma música carregada do arquivo %s\n", songs_file);
        // Free names
        for (int i = 0; i < bank->name_count; i++) {
            free(bank->names[i]);
        }
        free(bank->names);
        free(bank);
        return NULL;
    }

    if (bank->song_count == 0) {
        printf("Aviso: Nenhuma música carregada do arquivo %s\n", songs_file);
        // Free names
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

