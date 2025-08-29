#include <stdlib.h>

#include <stdio.h>
#include <time.h> // Usado para calcular o tempo de execução
#include <factorial.h>


// Define a função recursiva
unsigned int factorial_recursive(unsigned int n)
{
    if (n ==0) return 1;
    return n* factorial_recursive(n-1);
}

// Define a função iterativa
unsigned int factorial_iterative(unsigned int n)
{
    if (n == 0) return 1;

    unsigned int a = 1;
    for (unsigned int i = 1; i <= n; i++)
    {
        a*=i;
    }

    return a;
}

// Calcula o tempo pela função recursivo
double calculate_recursive_time(unsigned int n)
{
    clock_t starttime, endtime;

    
    starttime = clock();
    for (unsigned int i = 0; i < RECURSIVE_REPEATS; i++)
    {
        factorial_recursive(n);
    }
    endtime = clock();
    
    return (double)((int)(endtime - starttime)) / (RECURSIVE_REPEATS * CLOCKS_PER_SEC);
}

// Calcula o tempo pela função iterativa
double calculate_iterative_time(unsigned int n)
{
    clock_t starttime, endtime;

    starttime = clock();
    
    for (unsigned int i = 0; i < ITERATIVE_REPEATS; i++)
    {
        factorial_iterative(n);
    }
    
    endtime = clock();
    return (double)((int)(endtime - starttime))  / (ITERATIVE_REPEATS * CLOCKS_PER_SEC);

}

// Função que retorna ponteiro com vetor de cada tempo de execução (recursivo e iterativo)
double *compair_factorial_n(unsigned int n)
{
    double *times = (double*) malloc(sizeof(double)*2);

    if (times == NULL)
    {
        printf("Error while allocating memory.");
        exit(1);
    }
    
    times[0] = calculate_recursive_time(n);
    times[1] = calculate_iterative_time(n);

    return times;
}