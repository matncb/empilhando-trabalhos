#include <stdio.h>
#include <stdlib.h>
#include <person.h>

int main()
{
    // Ao inves de ler a quantidade de pessoas do usuário, define uma constante
    Person people[PEOPLE_QNT];

    for (int i = 0; i < 3; i++)
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

    for (int i = 0; i < 3; i++)
    {
        person_print_info(people[i]);
    }
    return 0;
}