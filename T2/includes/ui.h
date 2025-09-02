#ifndef _UI_H
#define _UI_H

#define INPT_CMD_MAX_LENGTH 20 // QUANTIDADE MAXIMA DE CARACTERES PARA INSERIR NO INPUT
#define INPT_MAX_LENGTH 100 // QUANTIDADE MAXIMA DE CARACTERES PARA INSERIR NO INPUT
#define SET_MAX_LENGTH INPT_MAX_LENGTH

void ui_union(Set* setA, Set* setB);
void ui_intersect(Set* setA, Set* setB);
void ui_difference(Set* setA, Set* setB);
void ui_has_element(Set* set, int x);
Set* ui_set_init();
int *string_split_int(char *string, char *delimiter, int* count);

void ui_command_not_exists();
void ui_wrong_cmd_syntax();

void ui_run();

#endif