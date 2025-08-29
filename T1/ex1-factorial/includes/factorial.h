#ifndef _FACTORIAL_H
#define _FACTORIAL_H

// Os tempos são diferentes porque é o recursivo demora muito mais
// Assim, é necessário rodar mais vezes o iterativo pra ter um resultado que não seja pequeno de mais para ser medido

#define RECURSIVE_REPEATS 1000000
#define ITERATIVE_REPEATS 100000000

unsigned int factorial_iterative(unsigned int n);

unsigned int factorial_recursive(unsigned int n);

double calculate_recursive_time(unsigned int n);

double calculate_iterative_time(unsigned int n);

double *compair_factorial_n(unsigned int n);

#endif