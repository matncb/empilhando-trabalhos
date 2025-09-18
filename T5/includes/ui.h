#ifndef _UI_H
#define _UI_H

#define MAX_CMD_LENGTH 20
#define MAX_CMD 5
#define FULL_CMD_LENGTH MAX_CMD_LENGTH*MAX_CMD+MAX_CMD

#define FORCE_RUN_CODES // Input/Saída completamente louca do run codes

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



#endif