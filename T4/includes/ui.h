#ifndef _UI_H
#define _UI_H

#define MAX_CMD_LENGTH 20
#define MAX_CMD 5
#define FULL_CMD_LENGTH MAX_CMD_LENGTH*MAX_CMD+MAX_CMD

#ifdef WIN32
#define END_LINE "\r\n"
#endif

#ifdef __linux__
#define END_LINE "\n"
#endif

void ui_run();

char **string_split(char *string, char *delimiter, int* count);

int ui_add_document(Queue *queue, Document document);

int ui_print(Queue *queue);

int ui_list(Queue *queue);

void ui_print_document(Document document);

void free_split_strings(char **strings, int count);

int ui_list_off(Queue *queue);

#endif