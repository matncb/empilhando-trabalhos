#include <fibonacci.h>

unsigned int fibonnaci_recursivo(unsigned int n)
{
    if (n <= 1) return n;
    return fibonnaci_recursivo(n-1) + fibonacci_recursivo(n-2);
}

unsigned int fibonnaci_iterativo(unsigned int n)
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
