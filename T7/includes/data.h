#ifndef _DATA_H
#define _DATA_H

typedef struct data Data;

enum NameCompairissonReturn {
    DATA1_BEFORE = -1,
    DATA_EQUAL = 0,
    DATA2_BEFORE = 1,
    INCORRECT_PARAMS_ERROR = 2,
    NULL_NAMES_ERROR = 3
};
char *data_get_name(Data *data);
Data *data_create(char *name, char *tel, char *email);
void data_free(Data *data);
void data_set_name(Data *data, char *name);
void data_set_tel(Data *data, char *tel);
void data_set_email(Data *data, char *email);
char *data_get_tel(Data *data);
char *data_get_email(Data *data);
int data_compare_order(Data *data1, Data *data2);
int data_compare_order_by_name(Data *data1, char *name);

#endif 