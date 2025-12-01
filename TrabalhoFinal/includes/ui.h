#ifndef _UI_H
#define _UI_H

#include <poplist.h>
#include <graph.h>
#include <tree.h>
#include <queue.h>

#define MAX_CMD_LENGTH 200
#define MAX_CMD 5
#define FULL_CMD_LENGTH MAX_CMD_LENGTH*MAX_CMD+MAX_CMD

#define FORCE_RUN_CODES

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

void ui_run(Graph *graph, PopList *poplist, Tree *tree);
char **string_split(char *string, char *delimiter, int *count);
void free_split_strings(char **strings, int count);
void ui_list_people(PopList *poplist);
void ui_show_recommendations(Graph *graph, PopList *poplist, char *person_name);
void ui_show_graph(Graph *graph, PopList *poplist);
void ui_export_graph(Graph *graph, PopList *poplist);
void ui_show_similar(Graph *graph, PopList *poplist, char *person_name);
void ui_show_tree(Tree *tree);
void ui_add_person(Graph *graph, PopList *poplist, Tree *tree, char *name, char *tel, char *email);
void ui_remove_person(Graph *graph, PopList *poplist, Tree *tree, char *name);
void ui_add_music(Graph *graph, PopList *poplist, Tree *tree, char *person_name, char *music_name, char *artist);
void ui_remove_music(Graph *graph, PopList *poplist, Tree *tree, char *person_name, char *music_name, char *artist);
void ui_show_playlist(PopList *poplist, char *person_name);
void ui_show_help(void);

#endif

