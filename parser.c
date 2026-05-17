#include <stdio.h>
#include <string.h>

#include "parser.h"

void syntaxError() {

    printf("Syntax Error!\n");
}

void parse(Token tokens[], int tokenCount) {

    int current = 0;

    SelectStatement stmt;

    // SELECT
    if(tokens[current].type != TOKEN_SELECT) {

        syntaxError();
        return;
    }

    current++;

    // COLUMN
    if(tokens[current].type == TOKEN_IDENTIFIER ||
       tokens[current].type == TOKEN_STAR) {

        strcpy(stmt.column, tokens[current].value);
    }
    else {

        syntaxError();
        return;
    }

    current++;

    // FROM
    if(tokens[current].type != TOKEN_FROM) {

        syntaxError();
        return;
    }

    current++;

    // TABLE NAME
    if(tokens[current].type != TOKEN_IDENTIFIER) {

        syntaxError();
        return;
    }

    strcpy(stmt.table, tokens[current].value);

    current++;

    // ;
    if(tokens[current].type != TOKEN_SEMICOLON) {

        syntaxError();
        return;
    }

    printf("Parsed SELECT Statement\n");
    printf("Column: %s\n", stmt.column);
    printf("Table : %s\n", stmt.table);
}