#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct {

    char column[64];
    char table[64];

    int hasWhere;

    char whereColumn[64];
    char whereValue[64];

} SelectStatement;

void parse(Token tokens[], int tokenCount);

#endif