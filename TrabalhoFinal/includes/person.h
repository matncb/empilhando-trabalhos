#ifndef _PERSON_H
#define _PERSON_H

typedef struct person Person;

enum NameCompairissonReturn
{
    PERSON1_BEFORE = -1,
    PERSON_EQUAL = 0,
    PERSON2_BEFORE = 1,
    INCORRECT_PARAMS_ERROR = 2,
    NULL_NAMES_ERROR = 3
};

char *person_get_name(Person *person);
Person *person_create(char *name, char *tel, char *email);
void person_free(Person *person);
int person_set_name(Person *person, char *name);
int person_set_tel(Person *person, char *tel);
int person_set_email(Person *person, char *email);
char *person_get_tel(Person *person);
char *person_get_email(Person *person);
int person_compare_order(Person *person1, Person *person2);
int person_compare_order_by_name(Person *person1, char *name);

#endif