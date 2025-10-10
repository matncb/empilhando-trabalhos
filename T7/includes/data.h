#ifndef _DATA_H
#define _DATA_H

typedef struct data Data;

char *data_get_name(Data *data);
Data *data_create(char *name, char *tel, char *email);
void data_free(Data *data);
void data_set_name(Data *data, char *name);
void data_set_tel(Data *data, char *tel);
void data_set_email(Data *data, char *email);
char *data_get_tel(Data *data);
char *data_get_email(Data *data);

#endif 