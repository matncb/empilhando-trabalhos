#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <list.h>
#include <ui.h>

void free_split_strings(char **strings, int count)
{
    for (int i = 0; i < count; i++)
    {
        free(strings[i]);
    }
    free(strings);
    
    return;
}

void ui_remove(List *list, char *name)
{
    if (list_remove_by_name(list, name))
    {
        printf("Contato %s nao encontrado.\n", name);
        return;
    }

    printf("Contato %s removido.\n", name);
}

void ui_search(List *list, char *name)
{
    Data *data = list_search_by_name(list, name);
    if (!data)
    {
        printf("Contato %s nao encontrado.\n", name);
        return;
    }

    printf("Contato Encontrado: [%s, %s, %s]\n", 
            data_get_name(data), 
            data_get_tel(data), 
            data_get_email(data)
        );
}

void ui_list(List *list)
{
    Data **datas = list_datas(list);

    
    int elements = list_get_elements(list);
    if (elements == 0) 
    {
        printf("Contatos: \n"); 
        if(datas){
            free(datas);
        }
        return;
    }
    
    printf("Contatos:\n");
    for (int i = 0; i < elements; i++)
    {
        printf("- [%s, %s, %s]\n", 
            data_get_name(datas[i]), 
            data_get_tel(datas[i]), 
            data_get_email(datas[i])
        );
    }
    free(datas);
    
    return;
}

void ui_run()
{
    char command[FULL_CMD_LENGTH];

    List *list = list_create();

    if (list == NULL)
        exit(1);

    while (true)
    {
        int command_qnt;

        fgets(command, FULL_CMD_LENGTH, stdin);

        char **strings = string_split(command, " ", &command_qnt);
        if (!strings)
        {
            printf("Sem memória disponível\n");
            list_free(list);
            return;
        }
        
        if (command_qnt == 1)
        {
            strings[0][strcspn(strings[0], END_LINE)] = '\0';
    
            if (!strcmp(strings[0], "listar"))
            {
                ui_list(list);
            }
            else if (!strcmp(strings[0], "sair"))
            {
                free_split_strings(strings, command_qnt);
                list_free(list);
                return ;
            }
            else
            {
                printf("Comando não existente\n");
            }
        }
        else if (command_qnt == 2)
        {
            strings[1][strcspn(strings[1], END_LINE)] = '\0';
            if (!strcmp(strings[0], "remover"))
            {
                ui_remove(list, strings[1]); // name
            }
            else if (!strcmp(strings[0], "buscar"))
            {
                ui_search(list, strings[1]); // name
            }
            else
            {
                printf("Comando não existente\n");
            }
        }
        else if (command_qnt == 4)
        {

            // a string tem um \r e um \n,
            // como eu preciso remover o carriage return e o new line
            // adicionei o char nulo substituindo o \r, assim já removo os dois caracteres indesejados
            strings[3][strcspn(strings[3], END_LINE)] = '\0';

            if (!strcmp(strings[0], "inserir"))
            {
                Data *data = data_create(
                    strings[1], // name
                    strings[2],  // tel
                    strings[3] //  email
                );

                if(!data)
                {
                    printf("Sem memória disponível\n");  
                }
                else
                {
                    list_add(list, data);
                }
            }
            else
            {
                printf("Comando inexistente\n");
            }
        }
        else
        {
            printf("Quantidade incorreta de argumentos\n");
        }

        free_split_strings(strings, command_qnt);
    }
    list_free(list);
}

char **string_split(char *string, char *delimiter, int *count)
{
    int cmd_qnt = 0;
    char **strings = malloc(sizeof(char *) * MAX_CMD);
    if (!strings)
        return NULL;

    char *splited = strtok(string, delimiter);

    while (splited != NULL)
    {

        if (cmd_qnt >= MAX_CMD)
            break;

        strings[cmd_qnt] = malloc(sizeof(char) * MAX_CMD_LENGTH);

        if (!strings[cmd_qnt])
        {
            // implementação feita para remover vazamento de memoria
            for (int i = 0; i < cmd_qnt; i++) {
                free(strings[i]);
            }
            free(strings);
            return NULL;
        }    

        strcpy(strings[cmd_qnt], splited);
        splited = strtok(NULL, delimiter);
        cmd_qnt++;
    }
    *count = cmd_qnt;
    return strings;
}


