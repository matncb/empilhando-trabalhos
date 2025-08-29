#include <stdio.h>
#include <stdlib.h>

#include <factorial.h>
#include <data_gen.h>

int main(int argc, char *argv[])
{
    // Verificar número de argumentos
    if (argc != 2)
    {
        printf("./main <n>\n");
        return 1;
    }

    unsigned int n = atoi(argv[1]);

    // Executa comparação de tempo
    double *times = compair_factorial_n(n);
    printf("Recursive execusion time: %.15lf s \nIterative execution time: %.15lf s \n", times[0], times[1]);

    // Gerar arquivo com dados
    // Deixar comentado para não gerar arquivo novamente
    data_generate();

    // Desaloca memória usada
    free(times);

    return 0;
}