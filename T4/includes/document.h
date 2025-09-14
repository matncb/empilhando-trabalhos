#ifndef _DOCUMENT_H
#define _DOCUMENT_H

#define QUEUE_SIZE 100
#define NAME_LENGTH 100
#define COLOR_LENGTH 100
#define FORMAT_LENGTH 100

typedef struct
{
    char *name;
    int pages;
    char *color;
    char *format;
    
} Document;

#endif
