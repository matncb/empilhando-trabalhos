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
    
    if (!res)
    {
        printf("Imprimindo: ");
        ui_print_document(document);
        printf("\n");
    }
    else
    {
        printf("Fila de impressao vazia.\n");
    }

     
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


int ui_list(Queue *queue)
{
    Document *documents = queue_get_documents(queue);
    if (!documents) {
        printf("Sem memória para impressão\n");
        return 1;
    }

    int elements = queue_get_elements(queue);

    printf("Fila: [");
    for (int i=0; i < elements; i++)
    {
        ui_print_document(documents[i]);

        if(i != elements-1) printf(", ");
    
    }
    printf("]\n");

    free(documents);

    return 0;
}

int ui_list_off(Queue *queue)
{
    Document *documents = queue_get_documents(queue);
    if (!documents)
    {
        printf("Sem memória para impressão\n");
        return 1;
    }

    int elements = queue_get_elements(queue);

    printf("Fila final: [");
    for (int i = 0; i < elements; i++)
    {
        ui_print_document(documents[i]);

        if (i != elements - 1)
            printf(", ");
    }
    printf("]\n");

    free(documents);

    return 0;
}

void free_split_strings(char **strings, int count)
{
    for (int i = 0; i < count; i++)
    {
        free(strings[i]);
    }
    free(strings);
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
        if(!strings) {
            printf("Sem memória disponível\n");
            return;
        }

        if(command_qnt == 1){
            if(strcmp(command, "print\n") == 0)
            {
                ui_print(queue);
            }
            else if(strcmp(command, "list\n") == 0)
            {
                ui_list(queue);
            }
            else if(strcmp(command, "off\n") == 0){
                ui_list_off(queue);
                free_split_strings(strings, command_qnt);
                break;
            }    
        }
        else if(command_qnt == 5){
            strings[4][strlen(strings[4])-1] = '\0';
            if(strcmp(strings[0], "add") == 0){
                Document document;
                strcpy(document.name, strings[1]); // name
                document.pages = atoi(strings[2]); // pages
                strcpy(document.color, strings[3]); // color
                strcpy(document.format, strings[4]); // format
                
                queue_add(queue, document);
            }
        }
            
        free_split_strings(strings, command_qnt); 
    }
    free(queue);

}

char **string_split(char *string, char *delimiter, int* count)
{
    int cmd_qnt = 0;
    char **strings = malloc(sizeof(char*)* MAX_CMD);
    if(!strings) return NULL;

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