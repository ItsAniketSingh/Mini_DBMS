#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "executor.h"

int getColumnIndex(char* columnName) {

    if(strcmp(columnName, "id") == 0) {
        return 0;
    }

    if(strcmp(columnName, "name") == 0) {
        return 1;
    }

    if(strcmp(columnName, "age") == 0) {
        return 2;
    }

    return -1;
}



void executeSelect(SelectStatement stmt) {

    FILE* fp = fopen("students.txt", "r");

    if(fp == NULL) {

        printf("Could not open table file.\n");
        return;
    }

    char line[256];

    int selectColumn = -1;

    if(strcmp(stmt.column, "*") != 0) {

        selectColumn = getColumnIndex(stmt.column);

        if(selectColumn == -1) {

            printf("Unknown column: %s\n", stmt.column);
            fclose(fp);
            return;
        }
    }

    int whereColumn = -1;

    if(stmt.hasWhere) {

        whereColumn = getColumnIndex(stmt.whereColumn);

        if(whereColumn == -1) {

            printf("Unknown WHERE column: %s\n",
                   stmt.whereColumn);

            fclose(fp);
            return;
        }
    }

    while(fgets(line, sizeof(line), fp)) {

        line[strcspn(line, "\n")] = '\0';

        char temp[256];

        strcpy(temp, line);

        char* columns[10];

        int columnCount = 0;

        char* token = strtok(temp, ",");

        while(token != NULL) {

            columns[columnCount++] = token;

            token = strtok(NULL, ",");
        }

        // WHERE FILTER
        if(stmt.hasWhere) {

            if(strcmp(columns[whereColumn],
                      stmt.whereValue) != 0) {

                continue;
            }
        }

        // SELECT *
        if(strcmp(stmt.column, "*") == 0) {

            printf("%s\n", line);
        }

        // SELECT specific column
        else {

            printf("%s\n", columns[selectColumn]);
        }
    }

    fclose(fp);
}