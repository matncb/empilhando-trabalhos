#ifndef _UI_H
#define _UI_H

#define MAX_CMD_LENGTH 20
#define MAX_CMD 5
#define FULL_CMD_LENGTH MAX_CMD_LENGTH*MAX_CMD+MAX_CMD

#define FORCE_RUN_CODES // Input/Output completamente loucos do run codes

#ifndef FORCE_RUN_CODES

#ifdef WIN32
#define END_LINE "\r\n"
#endif

#ifdef __linux__
#define END_LINE "\n"
#endif

#else
#define END_LINE "\r\n"
#endif

void free_split_strings(char **strings, int count);
void ui_remove(Tree *tree, int code);
void ui_search(Tree *tree, int code);
void ui_tree(Tree *tree, PathType path);
void ui_run();
char **string_split(char *string, char *delimiter, int *count);

#endif