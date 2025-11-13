#include <stdio.h>
#include <graph.h>

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
    for(int i=0; i<=vertex_qnt; i++){
        graph->adjMatrix[i] = malloc(vertex_qnt * sizeof(int));
        if (!graph->adjMatrix[i]){
            return NULL;
        }
        for(int j=0; j<=vertex_qnt; j++){
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
    for (int i = 0; i < graph->vertex_qnt; i++){
        free(graph->adjMatrix[i]);
    }

    free(graph->adjMatrix);
    free(graph);

    return;
}

int export_graph(Graph *graph) {
    FILE *file = fopen("graph.csv", "w");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return 1; // Retorna 1 indicando erro
    }

    // Escreve a matriz no arquivo, separando por vírgula
    for (int i = 0; i < graph->vertex_qnt; i++) {
        for (int j = 0; j < graph->vertex_qnt; j++) {
            // Escreve o número
            fprintf(file, "%d", graph->adjMatrix[i][j]);
            
            // Adiciona vírgula, exceto após o último elemento da linha
            if (j < graph->vertex_qnt - 1) {
                fprintf(file, ",");
            }
        }
        // Adiciona uma nova linha ao final de cada linha da matriz
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Grafo exportado com sucesso para 'graph.csv'\n");
    return 0; // Retorna 0 indicando sucesso
}

void graph_update(Graph *graph, Poplist *list)
{
    
}