#include <stdlib.h>

#include <stdio.h>
#include <time.h> // Usado para calcular o tempo de execução
#include <fibonacci.h>


// Define a função recursiva
unsigned int fibonacci_recursive(unsigned int n)
{
    if (n <= 1) return n;
    return fibonacci_recursive(n-1) + fibonacci_recursive(n-2);
}

// Define a função iterativa
unsigned int fibonacci_iterative(unsigned int n)
{
    if (n <= 1) return n;

    unsigned int a = 0, b = 1, c;
    for (unsigned int i = 2; i <= n; i++)
    {
        c  = a + b;
        a = b;
        b = c;
    }

    return c;
}

// Calcula o tempo pela função recursivo
double calculate_recursive_time(unsigned int n)
{
    clock_t starttime, endtime;

    
    starttime = clock();
    for (unsigned int i = 0; i < RECURSIVE_REPEATS; i++)
    {
        fibonacci_recursive(n);
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
        fibonacci_iterative(n);
    }
    
    endtime = clock();
    return (double)((int)(endtime - starttime))  / (ITERATIVE_REPEATS * CLOCKS_PER_SEC);

}

// Função que retorna ponteiro com vetor de cada tempo de execução (recursivo e iterativo)
double *compair_fibonacci_n(unsigned int n)
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