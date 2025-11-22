#include <stdio.h>
#include <person.h>
#include <string.h>
#include <stdlib.h>
#include <playlist.h>

typedef struct person
{
    char *name;
    char *tel;
    char *email;

    struct PlayList *playlist;
} Person;

Person *person_create(char *name, char *tel, char *email)
{
    Person *person = malloc(sizeof(Person));
    if (person == NULL)
        return NULL;

    person->name = NULL;
    person->tel = NULL;
    person->email = NULL;

    if (person_set_name(person, name) || person_set_tel(person, tel) || person_set_email(person, email))
    {
        person_free(person);
        return NULL;
    }

    return person;
}

void person_free(Person *person)
{
    if (person == NULL)
        return;

    free(person->name);
    free(person->tel);
    free(person->email);
    free(person);

    return;
}

// funções de set
int person_set_name(Person *person, char *name)
{
    if (person == NULL || name == NULL)
        return 1;

    if (person->name != NULL)
    {
        free(person->name);
    }
    person->name = strdup(name);
    if (!person->name)
        return 1;

    return 0;
}

int person_set_tel(Person *person, char *tel)
{
    if (person == NULL || tel == NULL)
        return 1;

    if (person->tel != NULL)
    {
        free(person->tel);
    }
    person->tel = strdup(tel);
    if (!person->tel)
        return 1;

    return 0;
}

int person_set_email(Person *person, char *email)
{
    if (person == NULL || email == NULL)
        return 1;

    if (person->email != NULL)
    {
        free(person->email);
    }
    person->email = strdup(email);
    if (!person->email)
        return 1;

    return 0;
}

int person_set_playlist(Person *person, void *playlist)
{
    if(!person || !playlist)
        return 1;

    person->playlist = playlist;
    return 0;
}

// funções de get
char *person_get_name(Person *person)
{
    if (person == NULL)
        return NULL;
    return person->name;
}

char *person_get_tel(Person *person)
{
    if (person == NULL)
        return NULL;
    return person->tel;
}

char *person_get_email(Person *person)
{
    if (person == NULL)
        return NULL;
    return person->email;
}

void *person_get_playlist(Person *person)
{
    if (person == NULL)
        return NULL;
    return person->playlist;
}

/*
    @return int (1|2|-1|1)
*/
// Ordem alfabética
int person_compare_order(Person *person1, Person *person2)
{
    // Código de erro para argumentos incorretos
    if ((person1 == NULL) || (person2 == NULL))
        return INCORRECT_PARAMS_ERROR;

    if ((person1->name == NULL) || (person2->name == NULL))
        return NULL_NAMES_ERROR;

    if (strcmp(person1->name, person2->name) < 0)
    {
        return PERSON1_BEFORE; // person1 vem antes
    }
    else if (strcmp(person1->name, person2->name) > 0)
    {
        return PERSON2_BEFORE; // person1 vem depois
    }

    return PERSON_EQUAL; // person1 é igual
}

int person_compare_order_by_name(Person *person1, char *name)
{
    // Código de erro para argumentos incorretos
    if (person1 == NULL)
        return INCORRECT_PARAMS_ERROR;

    if ((person1->name == NULL) || name == NULL)
        return NULL_NAMES_ERROR;

    if (strcmp(person1->name, name) < 0)
    {
        return PERSON1_BEFORE; // person1 vem antes
    }
    else if (strcmp(person1->name, name) > 0)
    {
        return PERSON2_BEFORE; // person1 vem depois
    }

    return PERSON_EQUAL; // person1 é igual
}




