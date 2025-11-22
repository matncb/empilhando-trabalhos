#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ui.h>
#include <person.h>
#include <playlist.h>
#include <music.h>

void free_split_strings(char **strings, int count)
{
    for (int i = 0; i < count; i++)
    {
        free(strings[i]);
    }
    free(strings);
    return;
}

char **string_split(char *string, char *delimiter, int *count)
{
    int cmd_qnt = 0;
    char **strings = malloc(sizeof(char *) * MAX_CMD);
    if (!strings)
        return NULL;

    char *splited = strtok(string, delimiter);

    while (splited != NULL)
    {
        if (cmd_qnt >= MAX_CMD)
            break;

        strings[cmd_qnt] = malloc(sizeof(char) * MAX_CMD_LENGTH);
        if (!strings[cmd_qnt])
        {
            for (int i = 0; i < cmd_qnt; i++)
            {
                free(strings[i]);
            }
            free(strings);
            return NULL;
        }

        strcpy(strings[cmd_qnt], splited);
        splited = strtok(NULL, delimiter);
        cmd_qnt++;
    }
    *count = cmd_qnt;
    return strings;
}

void ui_list_people(PopList *poplist)
{
    if (!poplist)
    {
        printf("Lista de pessoas vazia.\n");
        return;
    }

    Person **people = poplist_people(poplist);
    if (!people)
    {
        printf("Erro ao obter lista de pessoas.\n");
        return;
    }

    int n = poplist_get_elements(poplist);
    printf("Pessoas cadastradas (%d):\n", n);
    for (int i = 0; i < n; i++)
    {
        PlayList *pl = (PlayList *)person_get_playlist(people[i]);
        int size = pl ? playlist_get_elements(pl) : 0;
        printf("  [%d] %s - %d musicas\n", i + 1, person_get_name(people[i]), size);
    }
    free(people);
    return;
}

int ui_find_person_index(PopList *poplist, char *name)
{
    if (!poplist || !name)
        return -1;

    Person **people = poplist_people(poplist);
    if (!people)
        return -1;

    int n = poplist_get_elements(poplist);
    for (int i = 0; i < n; i++)
    {
        if (strcmp(person_get_name(people[i]), name) == 0)
        {
            int idx = i;
            free(people);
            return idx;
        }
    }
    free(people);
    return -1;
}

Queue *ui_generate_recommendations(Graph *graph, PopList *poplist, int person_idx)
{
    if (!graph || !poplist)
        return NULL;

    Queue *queue = queue_create();
    if (!queue)
        return NULL;

    Person **people = poplist_people(poplist);
    if (!people)
    {
        queue_free(queue);
        return NULL;
    }

    int n = poplist_get_elements(poplist);
    int vertex_qnt = graph_get_vertex_qnt(graph);
    if (person_idx < 0 || person_idx >= n || person_idx >= vertex_qnt)
    {
        free(people);
        queue_free(queue);
        return NULL;
    }

    PlayList *person_pl = (PlayList *)person_get_playlist(people[person_idx]);
    Music **person_songs = NULL;
    int person_pl_size = 0;
    if (person_pl)
    {
        person_songs = playlist_songs(person_pl);
        person_pl_size = playlist_get_elements(person_pl);
    }

    int candidates[100];
    int weights[100];
    int candidates_count = 0;
    

    for (int i = 0; i < n && i < vertex_qnt; i++)
    {
        if (i == person_idx)
            continue;

        int similarity = graph_get_edge_weight(graph, person_idx, i);
        if (similarity > 0)
        {
            candidates[candidates_count] = i;
            weights[candidates_count] = similarity;
            
            candidates_count++;
        }
    }

    if (candidates_count == 0)
    {
        if (person_songs)
            free(person_songs);
        free(people);
        queue_free(queue);
        return queue;
    }

    for (int i = 0; i < candidates_count - 1; i++)
    {
        for (int j = 0; j < candidates_count - i - 1; j++)
        {
            if (weights[j] < weights[j + 1])
            {
                int temp_idx = candidates[j];
                int temp_weight = weights[j];
                candidates[j] = candidates[j + 1];
                weights[j] = weights[j + 1];
                candidates[j + 1] = temp_idx;
                weights[j + 1] = temp_weight;
            }
        }
    }

    int top_percentage = 30;
    int top_count = (candidates_count * top_percentage) / 100;
    if (top_count < 1)
        top_count = 1;
    if (top_count > candidates_count)
        top_count = candidates_count;

    int total_weight = 0;
    for (int i = 0; i < top_count; i++)
    {
        total_weight += weights[i];
    }

    int max_recommendations = 5;
    int attempts = 0;
    int max_attempts = top_count * 10;

    while (queue_get_elements(queue) < max_recommendations && attempts < max_attempts)
    {
        attempts++;

        int random_val = rand() % total_weight;
        int selected_idx = -1;
        int cumulative = 0;

        for (int i = 0; i < top_count; i++)
        {
            cumulative += weights[i];
            if (random_val < cumulative)
            {
                selected_idx = candidates[i];
                break;
            }
        }

        if (selected_idx < 0)
            continue;

        PlayList *pl = (PlayList *)person_get_playlist(people[selected_idx]);
        if (!pl)
            continue;

        Music **songs = playlist_songs(pl);
        if (!songs)
            continue;

        int size = playlist_get_elements(pl);
        if (size == 0)
        {
            free(songs);
            continue;
        }

        int song_idx = rand() % size;
        Music *candidate = songs[song_idx];

        bool is_duplicate = false;

        Music **queue_musics = queue_get_musics(queue);
        if (queue_musics)
        {
            int queue_size = queue_get_elements(queue);
            for (int i = 0; i < queue_size; i++)
            {
                if (music_compare_order(queue_musics[i], candidate) == MUSIC_EQUAL)
                {
                    is_duplicate = true;
                    break;
                }
            }
            free(queue_musics);
        }

        if (!is_duplicate && person_songs)
        {
            for (int i = 0; i < person_pl_size; i++)
            {
                if (music_compare_order(person_songs[i], candidate) == MUSIC_EQUAL)
                {
                    is_duplicate = true;
                    break;
                }
            }
        }

        if (!is_duplicate)
        {
            Music *rec = music_create(
                music_get_name(candidate),
                music_get_artist(candidate),
                "Recomendacao baseada em similaridade");

            if (rec)
            {
                queue_add(queue, rec);
            }
        }

        free(songs);
    }

    if (person_songs)
        free(person_songs);
    free(people);
    return queue;
}

void ui_show_recommendations(Graph *graph, PopList *poplist, char *person_name)
{
    if (!graph || !poplist || !person_name)
    {
        printf("Parametros invalidos.\n");
        return;
    }

    int idx = ui_find_person_index(poplist, person_name);
    if (idx < 0)
    {
        printf("Pessoa %s nao encontrada.\n", person_name);
        return;
    }

    Person **people = poplist_people(poplist);
    if (!people)
        return;

    Person *person = people[idx];
    printf("\nRecomendacoes para %s:\n", person_get_name(person));

    Queue *recommendations = ui_generate_recommendations(graph, poplist, idx);
    if (!recommendations || queue_get_elements(recommendations) == 0)
    {
        printf("Nenhuma recomendacao disponivel.\n");
        if (recommendations)
            queue_free(recommendations);
        free(people);
        return;
    }

    Music **musics = queue_get_musics(recommendations);
    if (musics)
    {
        int size = queue_get_elements(recommendations);
        for (int i = 0; i < size; i++)
        {
            printf("  [%d] %s - %s\n", i + 1,
                   music_get_name(musics[i]),
                   music_get_artist(musics[i]));
        }
        free(musics);
    }

    queue_free(recommendations);
    free(people);
    return;
}

void ui_show_graph(Graph *graph, PopList *poplist)
{
    if (!graph || !poplist)
    {
        printf("Grafo ou lista de pessoas invalidos.\n");
        return;
    }

    Person **people = poplist_people(poplist);
    if (!people)
        return;

    int n = poplist_get_elements(poplist);
    int max_show = n < 10 ? n : 10;

    printf("\nMatriz de adjacencia (primeiras %d pessoas):\n", max_show);
    printf("      ");
    for (int j = 0; j < max_show; j++)
    {
        printf("%6.6s ", person_get_name(people[j]));
    }
    printf("\n");

    for (int i = 0; i < max_show; i++)
    {
        printf("%6.6s ", person_get_name(people[i]));
        for (int j = 0; j < max_show; j++)
        {
            int weight = graph_get_edge_weight(graph, i, j);
            printf("%6d ", weight);
        }
        printf("\n");
    }

    free(people);
    return;
}

void ui_show_similar(Graph *graph, PopList *poplist, char *person_name)
{
    if (!graph || !poplist || !person_name)
    {
        printf("Parametros invalidos.\n");
        return;
    }

    int idx = ui_find_person_index(poplist, person_name);
    if (idx < 0)
    {
        printf("Pessoa %s nao encontrada.\n", person_name);
        return;
    }

    Person **people = poplist_people(poplist);
    if (!people)
        return;

    int n = poplist_get_elements(poplist);
    int vertex_qnt = graph_get_vertex_qnt(graph);

    printf("\nPessoas similares a %s:\n", person_name);

    int found = 0;
    for (int i = 0; i < n && i < vertex_qnt; i++)
    {
        if (i != idx)
        {
            int weight = graph_get_edge_weight(graph, idx, i);
            if (weight > 0)
            {
                PlayList *pl = (PlayList *)person_get_playlist(people[i]);
                int size = pl ? playlist_get_elements(pl) : 0;
                printf("  %s - Similaridade: %d (playlist com %d musicas)\n",
                       person_get_name(people[i]), weight, size);
                found++;
            }
        }
    }

    if (found == 0)
    {
        printf("Nenhuma pessoa similar encontrada.\n");
    }

    free(people);
    return;
}

void ui_show_tree(Tree *tree)
{
    if (!tree)
    {
        printf("Arvore invalida.\n");
        return;
    }

    Person **people = tree_list(tree, PATH_INORDER);
    if (!people)
    {
        printf("Arvore vazia.\n");
        return;
    }

    int n = tree_get_elements(tree);
    printf("\nArvore AVL (ordenada por tamanho de playlist):\n");
    printf("Total de elementos: %d\n", n);

    for (int i = 0; i < n; i++)
    {
        PlayList *pl = (PlayList *)person_get_playlist(people[i]);
        int size = pl ? playlist_get_elements(pl) : 0;
        printf("  [%d] %s - %d musicas\n", i + 1, person_get_name(people[i]), size);
    }

    free(people);
    return;
}

void ui_add_person(Graph *graph, PopList *poplist, Tree *tree, char *name, char *tel, char *email)
{
    if (!graph || !poplist || !tree || !name || !tel || !email)
    {
        printf("Parametros invalidos.\n");
        return;
    }

    Person *person = person_create(name, tel, email);
    if (!person)
    {
        printf("Erro ao criar pessoa.\n");
        return;
    }

    PlayList *playlist = playlist_create();
    if (!playlist)
    {
        person_free(person);
        printf("Erro ao criar playlist.\n");
        return;
    }

    person_set_playlist(person, playlist);

    int add_result = poplist_add(poplist, person);
    if (add_result == 2)
    {
        char new_name[100];
        snprintf(new_name, sizeof(new_name), "%s_%d", name, rand() % 10000);
        person_set_name(person, new_name);
        snprintf(new_name, sizeof(new_name), "%s_%d@email.com", name, rand() % 10000);
        person_set_email(person, new_name);
        add_result = poplist_add(poplist, person);
    }

    if (add_result == 0)
    {
        tree_add(tree, person);
        graph_update(graph, poplist);
        printf("Pessoa %s adicionada com sucesso.\n", person_get_name(person));
    }
    else
    {
        playlist_free(playlist);
        person_free(person);
        printf("Erro ao adicionar pessoa.\n");
    }
    return;
}

void ui_remove_person(Graph *graph, PopList *poplist, Tree *tree, char *name)
{
    if (!graph || !poplist || !tree || !name)
    {
        printf("Parametros invalidos.\n");
        return;
    }

    Person *person = poplist_search_by_name(poplist, name);
    if (!person)
    {
        printf("Pessoa %s nao encontrada.\n", name);
        return;
    }

    PlayList *pl = (PlayList *)person_get_playlist(person);
    int playlist_size = pl ? playlist_get_elements(pl) : 0;

    if (poplist_remove_by_name(poplist, name) == 0)
    {
        tree_remove(tree, playlist_size);
        graph_update(graph, poplist);
        printf("Pessoa %s removida com sucesso.\n", name);
    }
    else
    {
        printf("Erro ao remover pessoa.\n");
    }
    return;
}

void ui_add_music(Graph *graph, PopList *poplist, Tree *tree, char *person_name, char *music_name, char *artist)
{
    if (!graph || !poplist || !tree || !person_name || !music_name || !artist)
    {
        printf("Parametros invalidos.\n");
        return;
    }

    Person *person = poplist_search_by_name(poplist, person_name);
    if (!person)
    {
        printf("Pessoa %s nao encontrada.\n", person_name);
        return;
    }

    PlayList *playlist = (PlayList *)person_get_playlist(person);
    if (!playlist)
    {
        printf("Playlist da pessoa %s nao encontrada.\n", person_name);
        return;
    }

    int old_size = playlist_get_elements(playlist);

    Music *music = music_create(music_name, artist, "Adicionada manualmente");
    if (!music)
    {
        printf("Erro ao criar musica.\n");
        return;
    }

    int result = playlist_add(playlist, music);
    if (result == 0)
    {
        int new_size = playlist_get_elements(playlist);
        if (old_size != new_size)
        {
            tree_remove(tree, old_size);
            tree_add(tree, person);
            graph_update(graph, poplist);
        }
        printf("Musica %s adicionada a playlist de %s.\n", music_name, person_name);
    }
    else if (result == 2)
    {
        music_free(music);
        printf("Musica %s ja existe na playlist.\n", music_name);
    }
    else
    {
        music_free(music);
        printf("Erro ao adicionar musica.\n");
    }
    return;
}

void ui_remove_music(Graph *graph, PopList *poplist, Tree *tree, char *person_name, char *music_name)
{
    if (!graph || !poplist || !tree || !person_name || !music_name)
    {
        printf("Parametros invalidos.\n");
        return;
    }

    Person *person = poplist_search_by_name(poplist, person_name);
    if (!person)
    {
        printf("Pessoa %s nao encontrada.\n", person_name);
        return;
    }

    PlayList *playlist = (PlayList *)person_get_playlist(person);
    if (!playlist)
    {
        printf("Playlist da pessoa %s nao encontrada.\n", person_name);
        return;
    }

    int old_size = playlist_get_elements(playlist);

    int result = playlist_remove_by_name(playlist, music_name);
    if (result == 0)
    {
        int new_size = playlist_get_elements(playlist);
        if (old_size != new_size)
        {
            tree_remove(tree, old_size);
            tree_add(tree, person);
            graph_update(graph, poplist);
        }
        printf("Musica %s removida da playlist de %s.\n", music_name, person_name);
    }
    else
    {
        printf("Musica %s nao encontrada na playlist.\n", music_name);
    }
    return;
}

void ui_show_playlist(PopList *poplist, char *person_name)
{
    if (!poplist || !person_name)
    {
        printf("Parametros invalidos.\n");
        return;
    }

    Person *person = poplist_search_by_name(poplist, person_name);
    if (!person)
    {
        printf("Pessoa %s nao encontrada.\n", person_name);
        return;
    }

    PlayList *playlist = (PlayList *)person_get_playlist(person);
    if (!playlist)
    {
        printf("Playlist da pessoa %s nao encontrada.\n", person_name);
        return;
    }

    Music **songs = playlist_songs(playlist);
    if (!songs)
    {
        printf("Playlist de %s vazia.\n", person_name);
        return;
    }

    int size = playlist_get_elements(playlist);
    printf("\nPlaylist de %s (%d musicas):\n", person_name, size);

    for (int i = 0; i < size; i++)
    {
        printf("  [%d] %s - %s\n", i + 1,
               music_get_name(songs[i]),
               music_get_artist(songs[i]));
    }

    free(songs);
    return;
}

void ui_show_help()
{
    printf("Comandos disponiveis:\n");
    printf("  list - Lista todas as pessoas\n");
    printf("  recommend <nome> - Mostra recomendacoes para uma pessoa\n");
    printf("  similar <nome> - Mostra pessoas similares\n");
    printf("  graph - Mostra matriz de adjacencia\n");
    printf("  tree - Mostra arvore AVL\n");
    printf("  add_person <nome> <telefone> <email> - Adiciona nova pessoa\n");
    printf("  remove_person <nome> - Remove uma pessoa\n");
    printf("  add_music <nome_pessoa> <nome_musica> <artista> - Adiciona musica a playlist\n");
    printf("  remove_music <nome_pessoa> <nome_musica> - Remove musica da playlist\n");
    printf("  playlist <nome> - Mostra musicas da playlist de uma pessoa\n");
    printf("  help - Mostra esta lista de comandos\n");
    printf("  off - Encerra o programa\n");
    return;
}

void ui_run(Graph *graph, PopList *poplist, Tree *tree)
{
    char command[FULL_CMD_LENGTH];

    while (true)
    {
        int command_qnt;

        fgets(command, FULL_CMD_LENGTH, stdin);

        char **strings = string_split(command, " ", &command_qnt);
        if (!strings)
        {
            printf("Sem memoria disponivel\n");
            return;
        }

        if (command_qnt == 1)
        {
            strings[0][strcspn(strings[0], END_LINE)] = '\0';
            if (!strcmp(strings[0], "list"))
            {
                ui_list_people(poplist);
            }
            else if (!strcmp(strings[0], "graph"))
            {
                ui_show_graph(graph, poplist);
            }
            else if (!strcmp(strings[0], "tree"))
            {
                ui_show_tree(tree);
            }
            else if (!strcmp(strings[0], "help"))
            {
                ui_show_help();
            }
            else if (!strcmp(strings[0], "off"))
            {
                free_split_strings(strings, command_qnt);
                return;
            }
            else
            {
                printf("Comando nao existente\n");
            }
        }
        else if (command_qnt == 2)
        {
            strings[1][strcspn(strings[1], END_LINE)] = '\0';
            if (!strcmp(strings[0], "recommend"))
            {
                ui_show_recommendations(graph, poplist, strings[1]);
            }
            else if (!strcmp(strings[0], "similar"))
            {
                ui_show_similar(graph, poplist, strings[1]);
            }
            else if (!strcmp(strings[0], "remove_person"))
            {
                ui_remove_person(graph, poplist, tree, strings[1]);
            }
            else if (!strcmp(strings[0], "playlist"))
            {
                ui_show_playlist(poplist, strings[1]);
            }
            else
            {
                printf("Comando nao existente\n");
            }
        }
        else if (command_qnt == 3)
        {
            strings[2][strcspn(strings[2], END_LINE)] = '\0';
            if (!strcmp(strings[0], "remove_music"))
            {
                ui_remove_music(graph, poplist, tree, strings[1], strings[2]);
            }
            else
            {
                printf("Comando nao existente\n");
            }
        }
        else if (command_qnt == 4)
        {
            strings[3][strcspn(strings[3], END_LINE)] = '\0';
            if (!strcmp(strings[0], "add_person"))
            {
                ui_add_person(graph, poplist, tree, strings[1], strings[2], strings[3]);
            }
            else if (!strcmp(strings[0], "add_music"))
            {
                ui_add_music(graph, poplist, tree, strings[1], strings[2], strings[3]);
            }
            else
            {
                printf("Comando nao existente\n");
            }
        }
        else
        {
            printf("Quantidade incorreta de argumentos\n");
        }

        free_split_strings(strings, command_qnt);
        printf("\n");
    }
}

