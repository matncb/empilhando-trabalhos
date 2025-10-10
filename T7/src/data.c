#include <stdio.h>
#include <data.h>
#include <string.h>
#include <stdlib.h>

typedef struct Data
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

    data_set_name(data, name);
    data_set_tel(data, tel);
    data_set_email(data, email);    
    
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

void data_set_name(Data *data, char *name)
{
    if(data == NULL) return;
    
    if (data->name != NULL) {
        free(data->name);
    }
    data->name = strdup(name); 
}

void data_set_tel(Data *data, char *tel)
{
    if(data == NULL) return;

    if (data->tel != NULL) {
        free(data->tel);
    }
    data->tel = strdup(tel);
}

void data_set_email(Data *data, char *email)
{
    if(data == NULL) return;

    if (data->email != NULL) {
        free(data->email);
    }
    data->email = strdup(email);
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