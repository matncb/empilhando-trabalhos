#ifndef _TASK_H
#define _TASK_H

typedef struct Task Task;

char *task_get_name(Task *task);
Task *task_create(char *name, char *description, int duration);
void task_free(Task *task);
void task_set_name(Task *task, char *name);
void task_set_description(Task *task, char *description);
void task_set_duration(Task *task, int duration);
char *task_get_name(Task *task);
char *task_get_description(Task *task);
int task_get_duration(Task *task);

#endif 