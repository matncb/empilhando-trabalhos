#include <stdio.h>
#include <stdlib.h>
#include <person.h>

int main()
{
    char buff[20];
    
    // Supondo o caso mais geral, onde o usuario passa o valor de pessoas a serem cadastradas
    
    /* Input do usuario */
    printf("How many people register (1-100)? ");
    fgets(buff, 20, stdin);
    printf("\n");
    int n = atoi(buff);
    
    if (n > 100)
    {
        printf("n (1-100)");
        exit(1);
    }

    Person people[100]; // Estaticamente, máximo de 100 pessoas

    for (int i = 0; i < n; i++)
    {
        printf("Enter with name: ");
        fgets(people[i].name, sizeof(people[i].name), stdin);

        printf("Enter with age: ");
        char buff[20];
        fgets(buff, 20, stdin);
        people[i].age = atoi(buff);

        printf("Enter with address: ");
        fgets(people[i].address, sizeof(people[i].address), stdin);
     
        printf("\n");
    }

    // Faz laço e itera sobre people
    for (int i = 0; i < n; i++)
    {
        person_print_info(people[i]); // printa informações de cada pessoa
    }
    return 0;
}