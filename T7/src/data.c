#include <stdio.h>
#include <data.h>
#include <string.h>
#include <stdlib.h>

typedef struct data
{
    char *name;
    char *tel;
    char *email;
} Data;

Data *data_create(char *name, char *tel, char *email)
{
    Data *data = malloc(sizeof(Data));
    if (data == NULL) return NULL;

    data->name = NULL;
    data->tel = NULL;
    data->email = NULL;

    if (data_set_name(data, name) || data_set_tel(data, tel) || data_set_email(data, email))
    {
        free(data);
        return NULL;
    }

    return data;
}

void data_free(Data *data)
{
    if (data == NULL) return;
    
    free(data->name);
    free(data->tel);
    free(data->email);
    free(data);

    return;
}

// funções de set
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

int data_set_tel(Data *data, char *tel)
{
    if(data == NULL) return 1;

    if (data->tel != NULL) {
        free(data->tel);
    }
    data->tel = strdup(tel);
    if(!data->tel) return 1;
    
    return 0;
}

int data_set_email(Data *data, char *email)
{
    if(data == NULL) return 1;

    if (data->email != NULL) {
        free(data->email);
    }
    data->email = strdup(email);
    if(!data->email) return 1;
    
    return 0;
}

// funções de get
char *data_get_name(Data *data)
{
    if(data == NULL) return NULL;
    return data->name;
}

char *data_get_tel(Data *data)
{
    if(data == NULL) return NULL;
    return data->tel;
}

char *data_get_email(Data *data)
{
    if(data == NULL) return NULL;
    return data->email;
}

/*
    @return int (1|2|-1|1)
*/
// Ordem alfabética
int data_compare_order(Data *data1, Data *data2)
{
    // Código de erro para argumentos incorretos 
    if ((data1 == NULL) || (data2 == NULL)) return INCORRECT_PARAMS_ERROR;

    if ((data1->name == NULL) || (data2->name ==NULL)) return NULL_NAMES_ERROR;
    
    if (strcmp(data1->name, data2->name) < 0)
    {
        return DATA1_BEFORE; // data1 vem antes
    }
    else if (strcmp(data1->name, data2->name) > 0)
    {
        return DATA2_BEFORE; // data1 vem depois
    }

    return DATA_EQUAL; // data1 é igual
}

int data_compare_order_by_name(Data *data1, char *name)
{
    // Código de erro para argumentos incorretos
    if (data1 == NULL) return INCORRECT_PARAMS_ERROR ;

    if ((data1->name == NULL) || name == NULL)  return NULL_NAMES_ERROR;

    if (strcmp(data1->name, name) < 0)
    {
        return DATA1_BEFORE; // data1 vem antes
    }
    else if (strcmp(data1->name, name) > 0)
    {
        return DATA2_BEFORE; // data1 vem depois
    }

    return DATA_EQUAL; // data1 é igual
}