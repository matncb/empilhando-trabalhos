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
        printf("Musica %s nao encontrada.\n", name);
        return;
    }

    printf("Musica %s removida.\n", name);
}

void ui_play(List *list)
{
    if (list_get_elements(list) == 0)
    {
        printf("Nao ha musicas na playlist.\n");
        return;
    }
    
    Music *music = list_start_element(list);
    printf("Tocando: %s, %s, %is\n",
        music_get_name(music), 
        music_get_artist(music), 
        music_get_duration(music)
    );

    list_remove(list);
    return;
}

void ui_list(List *list)
{
    Music **musics = list_songs(list);
    
    int elements = list_get_elements(list);
    if (elements == 0) 
    {
        printf("Playlist: []\n");
        return;
    }
    
    printf("Playlist: ");
    for (int i = 0; i < elements; i++)
    {
        printf("[%s, %s, %is]", 
            music_get_name(musics[i]), 
            music_get_artist(musics[i]), 
            music_get_duration(musics[i])
        );
        if(i != elements-1) printf(" -> ");
    }
    printf("\n");
    
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
            return;
        }
        
        if (command_qnt == 1)
        {
            strings[0][strcspn(strings[0], END_LINE)] = '\0';
            if (!strcmp(strings[0], "play"))
            {
                ui_play(list);
            }
            else if (!strcmp(strings[0], "list"))
            {
                ui_list(list);
            }
            else if (!strcmp(strings[0], "remove"))
            {
                ui_remove(list, strings[1]);
            }
            else if (!strcmp(strings[0], "off"))
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
            if (!strcmp(strings[0], "remove"))
            {
                ui_remove(list, strings[1]);
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

            if (!strcmp(strings[0], "add"))
            {
                Music *music = music_create(
                    strings[1], // name
                    strings[2],  // artist
                    atoi(strings[3]) //  duration
                );

                if(!music) {
                    printf("Sem memória disponível\n");
                    return;
                }

                list_append(list, music);
            }
        }
        else
        {
            printf("Comando não existente\n");
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
            return NULL;

        strcpy(strings[cmd_qnt], splited);
        splited = strtok(NULL, delimiter);
        cmd_qnt++;
    }
    *count = cmd_qnt;
    return strings;
}


