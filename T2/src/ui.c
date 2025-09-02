#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <set.h>
#include <ui.h>

void ui_union(Set* setA, Set* setB)
{
    Set* result = set_union(setA, setB);
    if (!result) {
        printf("Erro na criação da união dos conjuntos.\n");
        return;
    }
    set_print(result);
    set_destroy(result);
    return;
}

void ui_intersect(Set* setA, Set* setB)
{
    Set* result = set_intersect(setA, setB);
    if (!result) {
        printf("Erro na criação da intersecao dos conjuntos.\n");
        return;
    }
    set_print(result);
    set_destroy(result);
    return;
}

void ui_difference(Set* setA, Set* setB)
{
    Set* result = set_difference(setA, setB);
    if (!result) {
        printf("Erro na criação da diferenca dos conjuntos.\n");
        return;
    }
    set_print(result);
    set_destroy(result);
    return;
}

void ui_has_element(Set* set, int x)
{
    printf("%s\n", set_has(set, x) ? "Sim" : "Nao" );
    return;
}

Set* ui_set_init()
{
    char setString[INPT_MAX_LENGTH];
    fgets(setString, INPT_MAX_LENGTH, stdin);
    int *array = string_split_int(setString, " ");

    Set *set = set_create(array, 5);

    if (!set)
    {
        printf("O conjunto não pode ser criado!\n");
        exit(1);
    }
    return set;
}


int *string_split_int(char *string, char *delimiter)
{
    int numbers_qnt = 0;
    int *numbers = malloc(sizeof(int)* SET_MAX_LENGTH);

    char *splited = strtok(string, delimiter);

    while (splited != NULL) {
        numbers[numbers_qnt] = atoi(splited);
        splited = strtok(NULL, delimiter);
        numbers_qnt++;
    }
    return numbers;
}

void ui_run()
{
    Set *setA = ui_set_init();
    Set *setB = ui_set_init();
    
    bool loop = true;
    char command[INPT_CMD_MAX_LENGTH];
    while (loop)
    {
        fgets(command, INPT_CMD_MAX_LENGTH, stdin);
        int *cmd = string_split_int(command, " ");

        switch (cmd[0])
        {
            case -1:
                loop = false;
                break;
                
            case 1:
                ui_union(setA, setB);
                break;

            case 2:
                ui_intersect(setA, setB);
                break;

            case 3:
                ui_difference(setA, setB);
                break;
                
            case 4:
                int x = cmd[1];
                ui_has_element(setA, x);
                break;
        }
        
        free(cmd);
    }
    
    return ;
}