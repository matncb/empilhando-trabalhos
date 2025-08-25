#include <stdio.h>
#include <stdlib.h>
#include <person.h>

int main()
{
    // Cria buffer e recebe n para alocacao dinamica via CLI
    char buff[20];
    
    printf("How many people register? ");
    fgets(buff, 20, stdin);
    printf("\n");
    int n = atoi(buff);
    
    Person **people = people_create(n);
    for (int i = 0; i < n; i++)
    {
        people[i] = person_create();
        person_ask_info(people[i]);
    }

    // Limpa a memória após a execução
    for (int i = 0; i < n; i++)
    {
        person_print_info(people[i]);
    }
        
    person_free_all(people, n);
    return 0;
}