#ifndef _FIBONACCI_H
#define _FIBONACCI_H

#define RECURSIVE_REPEATS 10000
#define ITERATIVE_REPEATS 1000000

unsigned int fibonacci_iterative(unsigned int n);

unsigned int fibonacci_recursive(unsigned int n);

double calculate_recursive_time(unsigned int n);

double calculate_iterative_time(unsigned int n);

double *compair_fibonacci_n(unsigned int n);

#endif