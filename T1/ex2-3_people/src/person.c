#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <person.h>

/* 
    Recebe a estrutura Person e printa as informações da pessoa.
*/
void person_print_info(Person p)
{
    printf("\n----------------------------\n");
    printf("Name: %s", p.name);
    printf("Age: %d\n", p.age);
    printf("Address: %s", p.address);
    printf("----------------------------\n");

    return;
}
