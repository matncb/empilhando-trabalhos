#ifndef _PERSON_H
#define _PERSON_H

typedef struct _Person {
    char name[50];
    int age;
    char address[50];

} Person;


Person **people_create(int n);
Person *person_create();

void person_ask_info(Person* p);
void person_print_info(Person* p);

void person_free_all(Person **people, int n);

#endif