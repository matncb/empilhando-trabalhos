#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <tree.h>
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

void ui_remove(Tree *tree, int code)
{
    if (tree_remove(tree, code))
    {
        printf("Produto %d nao encontrado.\n", code);
        return;
    }

    printf("Produto %d removido.\n", code);
}

void ui_search(Tree *tree, int code)
{
    Data *data = tree_search_by_code_pure(tree, code);
    if (!data)
    {
        printf("Produto %d nao encontrado.\n", code);
        return;
    }

    printf("Produto Encontrado: [%d, %s, %.2f]\n", 
            data_get_code(data), 
            data_get_name(data), 
            data_get_price(data)
        );
}

void ui_tree(Tree *tree, PathType path)
{
    int elements = tree_get_elements(tree);

    if (elements == 0) 
    {
        printf("A lista de Produtos esta vazia.\n"); 
        return;
    }

    Data **datas = tree_list(tree, path);
    printf("Produtos ");

    for (int i = 0; i < elements; i++)
    {
        printf("- [%d, %s, %.2f]\n", 
            data_get_code(datas[i]), 
            data_get_name(datas[i]), 
            data_get_price(datas[i])
        );
    }
    free(datas);
    
    return;
}

void ui_run()
{
    char command[FULL_CMD_LENGTH];

    Tree *tree = tree_create();

    if (tree == NULL)
        exit(1);

    while (true)
    {
        int command_qnt;

        fgets(command, FULL_CMD_LENGTH, stdin);

        char **strings = string_split(command, " ", &command_qnt);
        if (!strings)
        {
            printf("Sem memória disponível\n");
            tree_free(tree);
            return;
        }
        
        if (command_qnt == 1)
        {
            strings[0][strcspn(strings[0], END_LINE)] = '\0';
    
            if (!strcmp(strings[0], "preordem"))
            {
                ui_tree(tree, PATH_PREORDER);
            }
            else if (!strcmp(strings[0], "inordem"))
            {
                ui_tree(tree, PATH_INORDER);
            }
            else if (!strcmp(strings[0], "posordem"))
            {
                ui_tree(tree, PATH_POSORDER);
            }
            else if (!strcmp(strings[0], "sair"))
            {
                free_split_strings(strings, command_qnt);
                tree_free(tree);
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
                ui_remove(tree, atoi(strings[1])); // code
            }
            else if (!strcmp(strings[0], "buscar"))
            {
                ui_search(tree, atoi(strings[1])); // code
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
                    atoi(strings[1]), // code
                    strings[2],  // name
                    atof(strings[3]) //  price
                );

                if(!data)
                {
                    printf("Sem memória disponível\n");  
                }
                else
                {
                    if(tree_add(tree, data) == 1){
                        printf("Produto %s ja existe.\n", data_get_name(data));
                        data_free(data);
                    }
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
    tree_free(tree);
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


