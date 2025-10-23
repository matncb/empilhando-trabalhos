#ifndef _DATA_H
#define _DATA_H

typedef struct data Data;

enum CodeCompairissonReturn {
    DATA1_BEFORE = -1,
    DATA_EQUAL = 0,
    DATA2_BEFORE = 1,
    INCORRECT_PARAMS_ERROR = 2,
    NULL_NAMES_ERROR = 3
};

Data *data_create(int code, char *name, float price);
void data_free(Data *data);
int data_set_code(Data *data, int code);
int data_set_name(Data *data, char *name);
int data_set_price(Data *data, float price);
int data_get_code(Data *data);
char *data_get_name(Data *data);
float data_get_price(Data *data);
int data_compare_order(Data *data1, Data *data2);
int data_compare_order_by_code(Data *data1, int code);

#endif 