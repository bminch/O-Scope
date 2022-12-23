#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*STATE_HANDLER_T)(void);

extern STATE_HANDLER_T parser_state, parser_last_state, parser_task;

typedef void (*PARSER_HANDLER_T)(char *args);

typedef struct {
    char *command;
    PARSER_HANDLER_T handler;
} DISPATCH_ENTRY_T;

void init_parser(void);

#endif

