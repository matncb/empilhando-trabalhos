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

void print_separator() {
    printf("\n========================================\n");
}

void print_graph_info(Graph *graph) {
    if (!graph) return;
    
    print_separator();
    printf("MATRIZ DE ADJACÊNCIA DO GRAFO\n");
    print_separator();
    
    int n = graph_get_vertex_qnt(graph);
    int max = n < 10 ? n : 10;
    
    for (int i = 0; i < max; i++) {
        for (int j = 0; j < max; j++) {
            printf("%3d ", graph_get_edge_weight(graph, i, j));
        }
        printf("\n");
    }
}

void print_queue_info(Queue *queue) {
    if (!queue) return;
    
    print_separator();
    printf("FILA DE RECOMENDAÇÕES (Queue)\n");
    print_separator();
    printf("Elementos na fila: %d\n", queue_get_elements(queue));
    
    Music **musics = queue_get_musics(queue);
    if (musics) {
        for (int i = 0; i < queue_get_elements(queue); i++) {
            printf("  [%d] %s - %s\n", i+1, 
                   music_get_name(musics[i]), 
                   music_get_artist(musics[i]));
        }
        free(musics);
    }
}

void print_tree_info(Tree *tree) {
    if (!tree) return;
    
    print_separator();
    printf("ÁRVORE DE PESSOAS (Tree) - Ordenada por tamanho de playlist\n");
    print_separator();
    printf("Total de elementos: %d\n", tree_get_elements(tree));
    
    Person **people = tree_list(tree, PATH_INORDER);
    if (people) {
        printf("\nPessoas ordenadas (inorder):\n");
        for (int i = 0; i < tree_get_elements(tree); i++) {
            PlayList *pl = (PlayList *)person_get_playlist(people[i]);
            int size = pl ? playlist_get_elements(pl) : 0;
            printf("  - %s: %d músicas\n", 
                   person_get_name(people[i]), size);
        }
        free(people);
    }
}

void print_poplist_info(PopList *poplist) {
    if (!poplist) return;
    
    print_separator();
    printf("LISTA DE PESSOAS (PopList)\n");
    print_separator();
    printf("Total de pessoas: %d\n\n", poplist_get_elements(poplist));
    
    Person **people = poplist_people(poplist);
    if (people) {
        for (int i = 0; i < poplist_get_elements(poplist); i++) {
            PlayList *pl = (PlayList *)person_get_playlist(people[i]);
            int size = pl ? playlist_get_elements(pl) : 0;
            printf("  [%d] %s (%s) - %d músicas\n", 
                   i+1,
                   person_get_name(people[i]),
                   person_get_email(people[i]),
                   size);
        }
        free(people);
    }
}

Queue *generate_recommendations(Graph *graph, PopList *poplist, int person_idx) {
    if (!graph || !poplist) return NULL;
    
    Queue *queue = queue_create();
    if (!queue) return NULL;
    
    Person **people = poplist_people(poplist);
    if (!people) {
        queue_free(queue);
        return NULL;
    }
    
    int n = poplist_get_elements(poplist);
    int vertex_qnt = graph_get_vertex_qnt(graph);
    if (person_idx < 0 || person_idx >= n || person_idx >= vertex_qnt) {
        free(people);
        queue_free(queue);
        return NULL;
    }
    
    // Encontra pessoas com maior similaridade
    int max_similarity = 0;
    int best_match = -1;
    
    for (int i = 0; i < n && i < vertex_qnt; i++) {
        int weight = graph_get_edge_weight(graph, person_idx, i);
        if (i != person_idx && weight > max_similarity) {
            max_similarity = weight;
            best_match = i;
        }
    }
    
    if (best_match >= 0 && max_similarity > 0) {
        // Adiciona músicas da pessoa similar à fila de recomendações
        PlayList *pl = (PlayList *)person_get_playlist(people[best_match]);
        if (pl) {
            Music **songs = playlist_songs(pl);
            if (songs) {
                int size = playlist_get_elements(pl);
                for (int i = 0; i < size && i < 5; i++) {
                    // Cria uma cópia da música para a recomendação
                    Music *rec = music_create(
                        music_get_name(songs[i]),
                        music_get_artist(songs[i]),
                        "Recomendação baseada em similaridade"
                    );
                    if (rec) {
                        queue_add(queue, rec);
                    }
                }
                free(songs);
            }
        }
    }
    
    free(people);
    return queue;
}

int main()
{
    srand(time(NULL));
    
    int vertex_qnt = 100;
    int musics_per_person = 5 + (rand() % 6); // Entre 5 e 10 músicas
    
    printf("=== SISTEMA DE RECOMENDAÇÃO MUSICAL ===\n");
    printf("Carregando dados dos arquivos CSV...\n");
    
    // Carrega dados dos arquivos CSV
    DataBank *data_bank = data_load_from_csv("data/names.csv", "data/songs.csv");
    if (!data_bank) {
        printf("Erro ao carregar dados dos arquivos CSV!\n");
        printf("Certifique-se de que os arquivos data/names.csv e data/songs.csv existem.\n");
        return 1;
    }
    
    printf("Criando %d pessoas com playlists...\n\n", vertex_qnt);

    // Cria o grafo
    Graph *graph = graph_create(vertex_qnt);
    if (!graph) {
        printf("Erro ao criar grafo!\n");
        data_bank_free(data_bank);
        return 1;
    }

    // Cria a lista de pessoas
    PopList *poplist = poplist_create();
    if (!poplist) {
        printf("Erro ao criar lista de pessoas!\n");
        free_graph(graph);
        data_bank_free(data_bank);
        return 1;
    }

    // Cria a árvore para organizar pessoas
    Tree *tree = tree_create();
    if (!tree) {
        printf("Erro ao criar árvore!\n");
        poplist_free(poplist);
        free_graph(graph);
        data_bank_free(data_bank);
        return 1;
    }

    // Cria pessoas e suas playlists
    for (int i = 0; i < vertex_qnt; i++)
    {
        char name[100], tel[20], email[100];
        char *random_name = data_get_random_name(data_bank);
        if (!random_name) {
            printf("Erro: não há nomes disponíveis!\n");
            continue;
        }
        
        // Garante nome único adicionando índice se necessário
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

        // Adiciona músicas aleatórias à playlist
        int musics_to_add = musics_per_person + (rand() % 3);
        for (int j = 0; j < musics_to_add; j++)
        {
            char *random_song = data_get_random_song(data_bank);
            char *random_artist = data_get_random_artist(data_bank);
            
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
        
        // Tenta adicionar à poplist, se falhar (duplicata), tenta novamente com nome diferente
        int add_result = poplist_add(poplist, person);
        if (add_result == 2) {
            // Nome duplicado, cria novo nome único
            snprintf(name, sizeof(name), "%s_%d_%d", random_name, i, rand() % 10000);
            person_set_name(person, name);
            snprintf(email, sizeof(email), "%s_%d_%d@email.com", random_name, i, rand() % 10000);
            person_set_email(person, email);
            add_result = poplist_add(poplist, person);
        }
        
        if (add_result == 0) {
            tree_add(tree, person);
        } else {
            // Se ainda falhar, libera a pessoa
            playlist_free(playlist);
            person_free(person);
        }
    }

    // Atualiza o grafo com as similaridades
    printf("Calculando similaridades entre pessoas...\n");
    graph_update(graph, poplist);

    // Exibe informações
    print_poplist_info(poplist);
    print_tree_info(tree);
    print_graph_info(graph);

    // Gera recomendações para a primeira pessoa usando Queue
    printf("\nGerando recomendações para %s usando Queue...\n", 
           person_get_name(poplist_people(poplist)[0]));
    
    Queue *recommendations = generate_recommendations(graph, poplist, 0);
    if (recommendations) {
        print_queue_info(recommendations);
        queue_free(recommendations);
    }

    // Exporta o grafo
    export_graph(graph, poplist);

    // Limpeza - primeiro libera a árvore (sem liberar pessoas)
    tree_free(tree);
    // Depois libera a poplist (que libera as pessoas)
    poplist_free(poplist);
    // Por fim, libera o grafo
    free_graph(graph);
    // Libera o banco de dados
    data_bank_free(data_bank);

    printf("\n=== Programa finalizado com sucesso! ===\n");
    return 0;
}
