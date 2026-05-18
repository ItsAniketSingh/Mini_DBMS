#include <stdio.h>
#include <string.h>

#include "parser.h"

void syntaxError() {

    printf("Syntax Error!\n");
}

void parse(Token tokens[], int tokenCount) {

    int current = 0;

    SelectStatement stmt;

    stmt.hasWhere = 0;

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

    // TABLE
    if(tokens[current].type != TOKEN_IDENTIFIER) {

        syntaxError();
        return;
    }

    strcpy(stmt.table, tokens[current].value);

    current++;

    // OPTIONAL WHERE
    if(current < tokenCount &&
       tokens[current].type == TOKEN_WHERE) {

        stmt.hasWhere = 1;

        current++;

        // COLUMN NAME
        if(tokens[current].type != TOKEN_IDENTIFIER) {

            syntaxError();
            return;
        }

        strcpy(stmt.whereColumn, tokens[current].value);

        current++;

        // =
        if(tokens[current].type != TOKEN_EQUALS) {

            syntaxError();
            return;
        }

        current++;

        // NUMBER
        if(tokens[current].type != TOKEN_NUMBER) {

            syntaxError();
            return;
        }

        strcpy(stmt.whereValue, tokens[current].value);

        current++;
    }

    printf("Parsed SELECT Statement\n");

    printf("Column : %s\n", stmt.column);

    printf("Table  : %s\n", stmt.table);

    if(stmt.hasWhere) {

        printf("WHERE  : %s = %s\n",
               stmt.whereColumn,
               stmt.whereValue);
    }
}