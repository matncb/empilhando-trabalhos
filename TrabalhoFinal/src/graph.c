#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <poplist.h>
#include <person.h>
#include <playlist.h>
#include <music.h>

typedef struct Graph{
    int vertex_qnt;
    int **adjMatrix;
}Graph;


Graph *graph_create(int vertex_qnt)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));

    if (!graph){
        return NULL;
    }
    
    graph->vertex_qnt = vertex_qnt;
    graph->adjMatrix = (int**)malloc(vertex_qnt * sizeof(int*));
    if (!graph->adjMatrix){
        return NULL;
    }
    for(int i=0; i<vertex_qnt; i++){
        graph->adjMatrix[i] = malloc(vertex_qnt * sizeof(int));
        if (!graph->adjMatrix[i]){
            return NULL;
        }
        for(int j=0; j<vertex_qnt; j++){
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

void graph_update_edges(Graph *graph, int src, int dest, int weight)
{
    graph->adjMatrix[src][dest] = weight;
    graph->adjMatrix[dest][src] = weight;
    return;
}

void free_graph(Graph *graph)
{
    if (!graph) return;
    
    if (graph->adjMatrix) {
        for (int i = 0; i < graph->vertex_qnt; i++){
            if (graph->adjMatrix[i]) {
                free(graph->adjMatrix[i]);
            }
        }
        free(graph->adjMatrix);
    }

    free(graph);

    return;
}

int export_graph(Graph *graph, PopList *poplist) {
    FILE *file = fopen("graph.csv", "w");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return 1; // Retorna 1 indicando erro
    }

    if (!graph || !poplist) {
        fclose(file);
        return 1;
    }

    // Obtém lista de pessoas
    Person **people = poplist_people(poplist);
    int n_people = poplist_get_elements(poplist);
    int vertex_qnt = graph_get_vertex_qnt(graph);
    
    // Escreve cabeçalho: primeira linha com nomes
    fprintf(file, ","); // Célula vazia no canto superior esquerdo
    for (int j = 0; j < vertex_qnt; j++) {
        if (j < n_people && people[j]) {
            char *name = person_get_name(people[j]);
            if (name) {
                fprintf(file, "%s", name);
            } else {
                fprintf(file, "Pessoa_%d", j);
            }
        } else {
            fprintf(file, "Pessoa_%d", j);
        }
        // Adiciona vírgula, exceto após o último elemento
        if (j < vertex_qnt - 1) {
            fprintf(file, ",");
        }
    }
    fprintf(file, "\n");

    // Escreve a matriz com nomes na primeira coluna
    for (int i = 0; i < vertex_qnt; i++) {
        // Primeira coluna: nome da pessoa
        if (i < n_people && people[i]) {
            char *name = person_get_name(people[i]);
            if (name) {
                fprintf(file, "%s", name);
            } else {
                fprintf(file, "Pessoa_%d", i);
            }
        } else {
            fprintf(file, "Pessoa_%d", i);
        }
        fprintf(file, ",");
        
        // Resto da linha: valores da matriz
        for (int j = 0; j < vertex_qnt; j++) {
            fprintf(file, "%d", graph_get_edge_weight(graph, i, j));
            
            // Adiciona vírgula, exceto após o último elemento da linha
            if (j < vertex_qnt - 1) {
                fprintf(file, ",");
            }
        }
        // Adiciona uma nova linha ao final de cada linha da matriz
        fprintf(file, "\n");
    }

    if (people) {
        free(people);
    }

    fclose(file);
    printf("Grafo exportado com sucesso para 'graph.csv'\n");
    return 0; // Retorna 0 indicando sucesso
}

void graph_update(Graph *graph, PopList *list)
{
    if (!graph || !list) return;
    
    int n = poplist_get_elements(list);
    if (n <= 0) return;
    
    Person **people = poplist_people(list);
    if (!people) return;
    
    // Calcula similaridade baseada em músicas em comum
    for (int i = 0; i < n && i < graph->vertex_qnt; i++) {
        for (int j = i + 1; j < n && j < graph->vertex_qnt; j++) {
            int similarity = calculate_similarity(people[i], people[j]);
            graph_update_edges(graph, i, j, similarity);
        }
    }
    
    free(people);
}

int calculate_similarity(void *p1, void *p2)
{
    if (!p1 || !p2) return 0;
    
    Person *person1 = (Person *)p1;
    Person *person2 = (Person *)p2;
    
    PlayList *pl1 = (PlayList *)person_get_playlist(person1);
    PlayList *pl2 = (PlayList *)person_get_playlist(person2);
    
    if (!pl1 || !pl2) return 0;
    
    int count = 0;
    Music **songs1 = playlist_songs(pl1);
    Music **songs2 = playlist_songs(pl2);
    
    if (!songs1 || !songs2) {
        if (songs1) free(songs1);
        if (songs2) free(songs2);
        return 0;
    }
    
    int n1 = playlist_get_elements(pl1);
    int n2 = playlist_get_elements(pl2);
    
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (music_compare_order(songs1[i], songs2[j]) == MUSIC_EQUAL) {
                count++;
            }
        }
    }
    
    free(songs1);
    free(songs2);
    
    return count;
}

int graph_get_vertex_qnt(Graph *graph)
{
    if (!graph) return 0;
    return graph->vertex_qnt;
}

int graph_get_edge_weight(Graph *graph, int src, int dest)
{
    if (!graph || !graph->adjMatrix) return 0;
    if (src < 0 || src >= graph->vertex_qnt || dest < 0 || dest >= graph->vertex_qnt) return 0;
    return graph->adjMatrix[src][dest];
}