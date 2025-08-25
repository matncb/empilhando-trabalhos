#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <person.h>

// Aloca uma array de n Person* ponteiros
Person **people_create(int n)
{
    Person **people = (Person **) malloc(n * sizeof(Person*));

    // Verifica se a alocação falhou.
    if (people == NULL)
    {
        printf("Memory allocation error.\n");
        exit(1);
    }
    
    return people;
}

// Aloca memória para cada struct "Person" 
Person *person_create()
{
    Person *p = (Person *) malloc(sizeof(Person));

    if (p == NULL)
    {
        printf("Memory allocation error.\n");
        exit(1);
    }
    
    return p;
}


// Faz prompt dos dados requeridos via CLI e os armazenam na struct
void person_ask_info(Person* p)
{
    printf("Enter with name: ");
    fgets(p->name, sizeof(p->name), stdin);

    printf("Enter with age: ");
    // Ler dados em um buffer temporário, converte com atoi e armazena
    // Alternativa para strtol, apesar de menos seguro
    char buff[20];
    fgets(buff, 20, stdin);
    p->age = atoi(buff);

    printf("Enter with address: ");
    fgets(p->address, sizeof(p->address), stdin);

    printf("\n");

    return;
}

// Retorna os dados
void person_print_info(Person* p)
{
    printf("\n----------------------------\n");
    printf("Name: %s", p->name);
    printf("Age: %d\n", p->age);
    printf("Address: %s", p->address);
    printf("----------------------------\n");

    return;
}

// Limpa cada ponteiro e a array de ponteiros
void person_free_all(Person **people, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(people[i]);
    }

    free(people);

    return ;
}