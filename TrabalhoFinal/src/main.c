#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <playlist.h>
#include <poplist.h>
#include <graph.h>
#include <music.h>
#include <person.h>
#include <queue.h>
#include <tree.h>
#include <data_loader.h>
#include <ui.h>


int main()
{
    srand(time(NULL));
    
    int vertex_qnt = 100;
    int musics_per_person = 5 + (rand() % 6);
    
    printf("=== SISTEMA DE RECOMENDAÇÃO MUSICAL ===\n");
    printf("Carregando dados dos arquivos CSV...\n");
    DataBank *data_bank = data_load_from_csv("data/names.csv", "data/songs.csv");
    if (!data_bank) {
        printf("Erro ao carregar dados dos arquivos CSV!\n");
        printf("Certifique-se de que os arquivos data/names.csv e data/songs.csv existem.\n");
        return 1;
    }
    
    printf("Criando %d pessoas com playlists...\n\n", vertex_qnt);

    Graph *graph = graph_create(vertex_qnt);
    if (!graph) {
        printf("Erro ao criar grafo!\n");
        data_bank_free(data_bank);
        return 1;
    }

    PopList *poplist = poplist_create();
    if (!poplist) {
        printf("Erro ao criar lista de pessoas!\n");
        free_graph(graph);
        data_bank_free(data_bank);
        return 1;
    }

    Tree *tree = tree_create();
    if (!tree) {
        printf("Erro ao criar árvore!\n");
        poplist_free(poplist);
        free_graph(graph);
        data_bank_free(data_bank);
        return 1;
    }

    for (int i = 0; i < vertex_qnt; i++)
    {
        char name[100], tel[20], email[100];
        char *random_name = data_get_random_name(data_bank);
        if (!random_name) {
            printf("Erro: não há nomes disponíveis!\n");
            continue;
        }
        
        snprintf(name, sizeof(name), "%s_%d", random_name, i);
        snprintf(tel, sizeof(tel), "119%08d", rand() % 100000000);
        snprintf(email, sizeof(email), "%s_%d@email.com", random_name, i);

        Person *person = person_create(name, tel, email);
        if (!person) continue;

        PlayList *playlist = playlist_create();
        if (!playlist) {
            person_free(person);
            continue;
        }

        int musics_to_add = musics_per_person + (rand() % 3);
        for (int j = 0; j < musics_to_add; j++)
        {
            char *random_song = NULL;
            char *random_artist = NULL;
            data_get_random_song_pair(data_bank, &random_song, &random_artist);
            
            if (!random_song || !random_artist) {
                continue;
            }
            
            Music *music = music_create(
                random_song, 
                random_artist, 
                "Música favorita"
            );
            
            if (music) {
                playlist_add(playlist, music);
            }
        }
        
        person_set_playlist(person, playlist);
        
        int add_result = poplist_add(poplist, person);
        if (add_result == 2) {
            snprintf(name, sizeof(name), "%s_%d_%d", random_name, i, rand() % 10000);
            person_set_name(person, name);
            snprintf(email, sizeof(email), "%s_%d_%d@email.com", random_name, i, rand() % 10000);
            person_set_email(person, email);
            add_result = poplist_add(poplist, person);
        }
        
        if (add_result == 0) {
            tree_add(tree, person);
        } else {
            playlist_free(playlist);
            person_free(person);
        }
    }

    printf("Calculando similaridades entre pessoas...\n");
    graph_update(graph, poplist);

    export_graph(graph, poplist);

    printf("\n=== SISTEMA INTERATIVO ===\n");
    ui_show_help();
    printf("\n");

    ui_run(graph, poplist, tree);

    tree_free(tree);
    poplist_free(poplist);
    free_graph(graph);
    data_bank_free(data_bank);

    printf("\n=== Programa finalizado com sucesso! ===\n");
    return 0;
}
