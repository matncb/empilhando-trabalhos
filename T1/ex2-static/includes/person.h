#ifndef _PERSON_H
#define _PERSON_H


// Define a estrutura a ser utilizada
typedef struct _Person {
    char name[50];
    int age;
    char address[50];

} Person;


void person_print_info(Person p);
#endif