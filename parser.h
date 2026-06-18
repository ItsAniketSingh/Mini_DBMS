#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"

typedef enum
{
    TYPE_INT,
    TYPE_VARCHAR
} DataType;

typedef struct
{
    char columnName[64];
    DataType type;
} ColumnDef;

typedef struct
{
    char tableName[64];
    int columnCount;
    ColumnDef columns[20];
} CreateTableNode;

typedef struct
{
    char tableName[64];
    int valueCount;
    char values[20][64];
} InsertNode;

typedef struct
{
    char tableName[64];
    int columnCount;
    char columns[20][64];
    int selectAll;

    int hasWhere;

    char whereColumn[64];
    char whereValue[64];
} SelectNode;

int parseCreateTable(Token tokens[], int count, CreateTableNode *node);
int parseInsert(Token tokens[], int count, InsertNode *node);
int parseSelect(Token tokens[], int count, SelectNode *node);

#endif
