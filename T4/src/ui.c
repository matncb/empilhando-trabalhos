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
    printf("%s (%d %s, %s, %s)", 
        document.name, 
        document.pages,
        document.pages > 1 ? "paginas" : "pagina",
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

    // a função queue_get_documents retorna uma cópia dos documentos de queue 
    // sem de fato alterar o próprio queue, visto que 
    // só temos o método de remove para receber os elementos da fila
    
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

            // utilizamos substring ao inves de strcmp() 
            // pois havia uma diferença entre linux e windows usando \r\n e apenas o \n
            if(strstr(command, "print"))
            {
                ui_print(queue);
            }
            else if(strstr(command, "list"))
            {
                ui_list(queue);
            }
            else if(strstr(command, "off")){
                ui_list_off(queue); // Formatação de saída diferente
                free_split_strings(strings, command_qnt);
                break;
            }    
        }
        else if(command_qnt == 5){

            // a string tem um \r e um \n, 
            // como eu preciso remover o carriage return e o new line
            // adicionei o char nulo substituindo o \r, assim já removo os dois caracteres indesejados
            strings[4][strlen(strings[4])-2] = '\0';


            if(strstr(strings[0], "add")){
                Document document;

                // fizemos uma cópia dos ponteiros de string, 
                // pois ao longo do fluxo de impressão de documento pode ocorrer liberação de memória
                // e apagar as strings dos documentos de forma indevida
                strcpy(document.name, strings[1]); // name
                document.pages = atoi(strings[2]); // pages
                strcpy(document.color, strings[3]); // color
                strcpy(document.format, strings[4]); // format
                
                queue_add(queue, document);
            }
        }else{
            printf("Comando não existente\n");
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

        if (!strings[cmd_qnt]) return NULL;

        strcpy(strings[cmd_qnt], splited);
        splited = strtok(NULL, delimiter);
        cmd_qnt++;
    }
    *count = cmd_qnt;
    return strings;
}