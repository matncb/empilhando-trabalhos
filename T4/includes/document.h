#ifndef _DOCUMENT_H
#define _DOCUMENT_H

#define NAME_LENGTH 100
#define COLOR_LENGTH 100
#define FORMAT_LENGTH 100

typedef struct
{
    char name[NAME_LENGTH];
    int pages;
    char color[COLOR_LENGTH];
    char format[FORMAT_LENGTH];
    
} Document;

#endif
