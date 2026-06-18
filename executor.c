

#include <stdio.h>
#include <string.h>

#include "executor.h"

int executeCreateTable(CreateTableNode *node)
{

    char fileName[128];
    FILE *check = fopen(fileName, "r");

    if (check != NULL)
    {
        fclose(check);
        printf("Table already exists\n");
        return 0;
    }
    fclose(check);
    FILE *fp;

    snprintf(fileName, sizeof(fileName), "%s.meta", node->tableName);

    fp = fopen(fileName, "w");

    if (fp == NULL)
    {
        printf("Could not create table\n");
        return 0;
    }

    fprintf(fp, "%d\n", node->columnCount);
    for (int i = 0; i < node->columnCount; i++)
    {
        fprintf(fp, "%s ", node->columns[i].columnName);
        if (node->columns[i].type == TYPE_INT)
        {
            fprintf(fp, "INT\n");
        }
        else
        {
            fprintf(fp, "VARCHAR\n");
        }
    }
    fclose(fp);

    char dataFileName[128];

    snprintf(dataFileName, sizeof(dataFileName), "%s.data", node->tableName);

    FILE *df = fopen(dataFileName, "w");

    if (df == NULL)
    {
        printf("Could not create data file\n");
        return 0;
    }

    fclose(df);

    return 1;
}

int executeInsert(InsertNode *node)
{
    char fileName[128];

    sprintf(fileName, "%s.data", node->tableName);

    FILE *fp = fopen(fileName, "a");

    if (fp == NULL)
    {
        printf("Could not open table file \n");
        return 0;
    }

    for (int i = 0; i < node->valueCount; i++)
    {
        fprintf(fp, "%s", node->values[i]);
        if (i != node->valueCount - 1)
        {
            fprintf(fp, "|");
        }
    }
    fprintf(fp, "\n");

    fclose(fp);

    printf("1 row inserted\n");
    return 1;
}

int executeSelect(SelectNode *node)
{
    char metaFile[128];
    char dataFile[128];

    sprintf(metaFile, "%s.meta", node->tableName);
    sprintf(dataFile, "%s.data", node->tableName);

    FILE *mf = fopen(metaFile, "r");

    if (mf == NULL)
    {
        printf("Table does not exist\n");
        return 0;
    }

    int columnCount;
    fscanf(mf, "%d", &columnCount);

    char metaColumns[20][64];
    char metaType[64];

    for (int i = 0; i < columnCount; i++)
    {
        fscanf(mf, "%s %s", metaColumns[i], metaType);
    }

    int selectedIndex[20];
    int selectedCount = 0;


    // Head Row
    if (node->selectAll)
    {
        for (int i = 0; i < columnCount; i++)
        {
            selectedIndex[selectedCount++] = i;
            printf("%-15s", metaColumns[i]);
        }
    }
    else
    {
        for (int i = 0; i < node->columnCount; i++)
        {
            int found = 0;

            for (int j = 0; j < columnCount; j++)
            {
                if (strcmp(node->columns[i], metaColumns[j]) == 0)
                {
                    selectedIndex[selectedCount++] = j;
                    printf("%-15s", metaColumns[j]);
                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                printf("Column %s not found\n", node->columns[i]);
                fclose(mf);
                return 0;
            }
        }
    }

    printf("\n");

    for (int i = 0; i < selectedCount; i++)
    {
        printf("---------------");
    }

    printf("\n");

    int whereIndex = -1;

    if (node->hasWhere)
    {
        for (int i = 0; i < columnCount; i++)
        {
            if (strcmp(metaColumns[i], node->whereColumn) == 0)
            {
                whereIndex = i;
                break;
            }
        }

        if (whereIndex == -1)
        {
            printf("WHERE column not found\n");
            fclose(mf);
            return 0;
        }
    }

    fclose(mf);

    FILE *df = fopen(dataFile, "r");

    if (df == NULL)
    {
        printf("Could not open data file\n");
        return 0;
    }

    char line[512];

    while (fgets(line, sizeof(line), df))
    {
        char fields[20][64];
        int fieldCount = 0;

        char *token = strtok(line, "|\n");

        while (token != NULL)
        {
            strcpy(fields[fieldCount], token);
            fieldCount++;

            token = strtok(NULL, "|\n");
        }

        if (node->hasWhere)
        {
            if (strcmp(fields[whereIndex],node->whereValue) != 0)
            {
                continue;
            }
        }

        for (int i = 0; i < selectedCount; i++)
        {
            printf("%-15s",
                   fields[selectedIndex[i]]);
        }

        printf("\n");
    }

    fclose(df);

    return 1;
}
