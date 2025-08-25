#ifndef _PERSON_H
#define _PERSON_H

#define PEOPLE_QNT 3 // Caso específico para 3 pessoas

typedef struct _Person {
    char name[50];
    int age;
    char address[50];

} Person;


void person_print_info(Person p);
#endif