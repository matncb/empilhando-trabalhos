#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <person.h>

// Função para printar informações de uma pessoa
void person_print_info(Person p)
{
    printf("\n----------------------------\n");
    printf("Name: %s", p.name);
    printf("Age: %d\n", p.age);
    printf("Address: %s", p.address);
    printf("----------------------------\n");

    return;
}
