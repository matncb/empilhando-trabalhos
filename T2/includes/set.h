#ifndef _SET_H 
#define _SET_H

typedef struct
{
    int* data;
    int length;
}Set;

void set_print(Set* set);


#endif
