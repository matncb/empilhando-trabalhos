#include <stdio.h>
#include <data.h>
#include <string.h>
#include <stdlib.h>

typedef struct data
{
    int code;
    char *name;
    float price;
} Data;

Data *data_create(int code, char *name, float price)
{
    Data *data = (Data *)malloc(sizeof(Data));
    if (data == NULL) return NULL;
    
    data->name = NULL;

    if (data_set_name(data, name))
    {
        data_free(data);
        return NULL;
    }

    data_set_code(data, code);
    data_set_price(data, price);

    return data;
}

void data_free(Data *data)
{
    if (data == NULL) return;
    
    free(data->name);
    free(data);

    return;
}

// funções de set
int data_set_code(Data *data, int code)
{
    if(data == NULL) return 1;
    data->code = code; 
    return 0;
}

int data_set_name(Data *data, char *name)
{
    if(data == NULL) return 1;

    if (data->name != NULL) {
        free(data->name);
    }
    data->name = strdup(name);
    if(!data->name) return 1;
    
    return 0;
}

int data_set_price(Data *data, float price)
{
    if(data == NULL) return 1;
    data->price = price;
    return 0;
}

// funções de get
int data_get_code(Data *data)
{
    if(data == NULL) return 1;
    return data->code;
}

char *data_get_name(Data *data)
{
    if(data == NULL) return NULL;
    return data->name;
}

float data_get_price(Data *data)
{
    if(data == NULL) return 1;
    
    return data->price;
}

int data_compare_order(Data *data1, Data *data2)
{
    // Código de erro para argumentos incorretos 
    if ((data1 == NULL) || (data2 == NULL)) return INCORRECT_PARAMS_ERROR;
    
    if (data1->code < data2->code)
    {
        return DATA1_BEFORE; // data1 vem antes
    }
    else if (data1->code > data2->code)
    {
        return DATA2_BEFORE; // data1 vem depois
    }

    return DATA_EQUAL; // data1 é igual
}

int data_compare_order_by_code(Data *data1, int code)
{
    // Código de erro para argumentos incorretos
    if (data1 == NULL) return INCORRECT_PARAMS_ERROR;

    if (data1->code < code)
    {
        return DATA1_BEFORE; // data1 vem antes
    }
    else if (data1->code > code)
    {
        return DATA2_BEFORE; // data1 vem depois
    }

    return DATA_EQUAL; // data1 é igual
}