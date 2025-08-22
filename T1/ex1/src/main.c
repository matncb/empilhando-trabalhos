#include <stdio.h>
#include <stdlib.h>

#include <fibonacci.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Número de argumentos errado\n");
        return 1;
    }

    unsigned int n = atoi(argv[1]);


    double *times = compair_fibonacci_n(n);
    printf("%.15lf : %.15lf\n", times[0], times[1]);
    


    return 0;
}