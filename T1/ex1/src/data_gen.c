#include <stdio.h>
#include <stdlib.h>
#include <data_gen.h>
#include <fibonacci.h>

void data_generate()
{
    FILE *fp = fopen("data.csv", "w");
    if(fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    double *times = NULL;

    fprintf(fp, "n recursive_time iterative_time\n",  i, times[0], times[1]);
    for(int i = 0; i <= N_MAX; i++)
    {
        times = compair_fibonacci_n(i);
        fprintf(fp, "%d %.15f %.15f\n",  i, times[0], times[1]);
        printf("N: %d Recursive: %.15f Iterative: %.15f\n", i, times[0], times[1]);
    }
    fclose(fp);

    return ;
}