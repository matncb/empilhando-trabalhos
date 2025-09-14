#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <queue.h>
#include <ui.h>
#include <string.h>


int ui_add_document(Queue *queue, Document document)
{
    return queue_add(queue, document);
}


int ui_print(Queue *queue)
{
    int res;
    Document document;
    
    res = queue_remove(queue, &document);
    if (!res) ui_print_document(document);
    return res;
}

void ui_print_document(Document document)
{
    printf("%s (%d paginas, %s, %s)", document.name, 
        document.pages, 
        document.color, 
        document.format);

    return;
}

void ui_list_off(Queue *queue)
{
    while (!ui_print(queue)){
        if (!queue_is_empty(queue)) printf(", ");
    }
}

int ui_list(Queue *queue)
{
    Queue *new_queue = (Queue *) malloc(sizeof(Queue));
    if (!new_queue) return 1;

    *new_queue = *queue;
    printf("Fila: [");
    ui_list_off(new_queue);
    printf("]\n");

    free(new_queue);
    return 0;
}


void ui_run()
{
    char command[FULL_CMD_LENGTH];

    Queue *queue = queue_create();

    if (queue == NULL) exit(1);

    while (true)
    {
        int command_qnt;

        fgets(command, FULL_CMD_LENGTH, stdin);

        char**strings = string_split(command, " ", &command_qnt);

        if(command_qnt == 1){
            if(strcmp(command, "print\n") == 0){
                if(queue_is_empty(queue)){
                    printf("Fila de impressao vazia.\n");
                }else{
                    printf("Imprimindo: ");
                    ui_print(queue);
                    printf("\n");
                }
            }else if(strcmp(command, "list\n") == 0){
                ui_list(queue);
            }else if(strcmp(command, "off\n") == 0){
                printf("Fila final: [");
                ui_list_off(queue);
                printf("]\n");
                break;
            }    
        }else if(command_qnt == 5){
            strings[4][strlen(strings[4])-1] = '\0';
            if(strcmp(strings[0], "add") == 0){
                Document document = {
                    strings[1], // name
                    atoi(strings[2]), // pages
                    strings[3], //color
                    strings[4] // format
                };
                queue_add(queue, document);
            }
        }
        
        
    }

    free(queue);

}

char **string_split(char *string, char *delimiter, int* count)
{
    int cmd_qnt = 0;
    char **strings = malloc(sizeof(char*)* MAX_CMD);

    char *splited = strtok(string, delimiter);

    while (splited != NULL) {
        
        if( cmd_qnt >= MAX_CMD ) break;

        strings[cmd_qnt] = malloc(sizeof(char)*MAX_CMD_LENGTH);
        strcpy(strings[cmd_qnt], splited);
        splited = strtok(NULL, delimiter);
        cmd_qnt++;
    }
    *count = cmd_qnt;
    return strings;
}