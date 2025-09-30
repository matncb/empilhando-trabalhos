#include <stdio.h>
#include <task.h>
#include <string.h>
#include <stdlib.h>

typedef struct Task
{
    char *name;
    char *description;
    int duration;
} Task;

Task *task_create(char *name, char *description, int duration)
{
    Task *task = malloc(sizeof(Task));
    if (!task) return NULL;

    task->name = NULL;
    task->description = NULL;

    task_set_name(task, name);
    task_set_description(task, description);
    task_set_duration(task, duration);    
    
    return task;
}

void task_free(Task *task)
{
    if (!task) return;
    
    free(task->name);
    free(task->description);
    free(task);

    return;
}

// funções de set

void task_set_name(Task *task, char *name)
{
    if(!task) return;
    
    if (task->name != NULL) {
        free(task->name);
    }
    task->name = strdup(name); 
}

void task_set_description(Task *task, char *description)
{
    if(!task) return;

    if (task->description != NULL) {
        free(task->description);
    }
    task->description = strdup(description);
}

void task_set_duration(Task *task, int duration)
{
    if(!task) return;

    task->duration = duration;
}


// funções de get
char *task_get_name(Task *task)
{
    if(!task) return NULL;
    return task->name;
}

char *task_get_description(Task *task)
{
    if(!task) return NULL;
    return task->description;
}

int task_get_duration(Task *task)
{
    if(!task) return -1;

    return task->duration;
}