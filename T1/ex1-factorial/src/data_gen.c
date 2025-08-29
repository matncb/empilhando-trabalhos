#include <stdio.h>
#include <stdlib.h>
#include <data_gen.h>
#include <factorial.h>

// Gera dados usados nos gráficos
void data_generate()
{
    FILE *fp = fopen("data.csv", "w"); // arquivo a ser salvo
    if(fp == NULL) // Verifica se deu certo
    {
        printf("Error opening file!\n");
        exit(1);
    }

    double *times;

    fprintf(fp, "n recursive_time iterative_time\n"); // Constroi colunas da tabela

    // Laço de 0 até N_MAX (definido no header)
    for(int i = 0; i <= N_MAX; i++) 
    {
        times = compair_factorial_n(i);

        // Escreve no arquivo e mostra no terminal
        fprintf(fp, "%d %.15f %.15f\n",  i, times[0], times[1]);
        printf("N: %d Recursive: %.15f Iterative: %.15f\n", i, times[0], times[1]);
        
        free(times); // Livbera a memória depois de usar 
    }

    fclose(fp); // Fecha arquivo
    

    return ;
}