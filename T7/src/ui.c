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
        printf("Tarefa %s nao encontrada.\n", name);
        return;
    }

    printf("Tarefa %s removida.\n", name);
}

void ui_execute_next(List *list)
{
    if (list_get_elements(list) == 0)
    {
        printf("A lista de tarefas esta vazia.\n");
        return;
    }
    
    Task *task = list_start_element(list);
    printf("Tarefa Concluida: %s, %s, %imin\n",
        task_get_name(task), 
        task_get_description(task), 
        task_get_duration(task)
    );

    list_remove_start(list);
    return;
}

void ui_execute_last(List *list)
{
    if (list_get_elements(list) == 0)
    {
        printf("A lista de tarefas esta vazia.\n");
        return;
    }
    
    Task *task = list_end_element(list);
    printf("Tarefa Concluida: %s, %s, %imin\n",
        task_get_name(task), 
        task_get_description(task), 
        task_get_duration(task)
    );

    list_remove_end(list);
    return;
}


void ui_list(List *list)
{
    Task **tasks = list_tasks(list);

    
    int elements = list_get_elements(list);
    if (elements == 0) 
    {
        printf("Lista de Tarefas: \n"); 
        if(tasks){
            free(tasks);
        }
        return;
    }
    
    printf("Lista de Tarefas: ");
    for (int i = 0; i < elements; i++)
    {
        printf("[%s, %s, %imin]", 
            task_get_name(tasks[i]), 
            task_get_description(tasks[i]), 
            task_get_duration(tasks[i])
        );
        if(i != elements-1) printf(" -> ");
    }
    printf("\n");
    free(tasks);
    
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
            if (!strcmp(strings[0], "executar_proxima"))
            {
                ui_execute_next(list);
            }
            else if (!strcmp(strings[0], "executar_ultima"))
            {
                ui_execute_last(list);
            }
            else if (!strcmp(strings[0], "listar"))
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

            if (!strcmp(strings[0], "adicionar"))
            {
                Task *task = task_create(
                    strings[1], // name
                    strings[2],  // description
                    atoi(strings[3]) //  duration
                );

                if(!task)
                {
                    printf("Sem memória disponível\n");  
                }
                else
                {
                    list_add_end(list, task);
                }
            }
            else
            if (!strcmp(strings[0], "adicionar_prioritario"))
            {
                Task *task = task_create(
                    strings[1], // name
                    strings[2],  // description
                    atoi(strings[3]) //  duration
                );

                if(!task) 
                {
                    printf("Sem memória disponível\n");
                }
                else
                {
                    list_add_start(list, task);
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


