#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <fibonacci.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Número de argumentos errado\n");
        return 1;
    }

    unsigned int n = atoi(argv[1]);

    clock_t starttime, endtime;

    starttime = clock();
    /* funcoes aqui */
    for (size_t i = 0; i < 1000; i++)
    {
        fibonacci_recursivo(n);
    }
    endtime = clock();
    double ms1 = (int)(endtime - starttime) / CLOCKS_PER_SEC;

    starttime = clock();
    /* funcoes aqui */
    for (size_t i = 0; i < 1000; i++)
    {
        fibonacci_iterativo(n);
    }
    
    endtime = clock();

    double ms2 = (int)(endtime - starttime) / CLOCKS_PER_SEC;

    printf("%.lf e %.lf\n", ms2, ms1);

    return 0;
}