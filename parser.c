
#include <stdio.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"

// void error()
// {
//     printf("Syntax Error\n");
// }
int parseCreateTable(Token tokens[], int count, CreateTableNode *node)
{

    int idx = 0;
    if (tokens[idx].type != TOKEN_CREATE)
    {
        // error();
        printf("Create token missing..");
        return 0;
    }
    idx++;

    if (tokens[idx].type != TOKEN_TABLE)
    {
        // error();
        printf("Table token missing");
        return 0;
    }
    idx++;

    if (tokens[idx].type != TOKEN_IDENTIFIER)
    {
        // error();
        printf("Identifier Token missing..");
        return 0;
    }
    else
    {
        strcpy(node->tableName, tokens[idx].value);
    }

    idx++;

    // Left Parenthesis
    if (tokens[idx].type != TOKEN_LPAREN)
    {
        // error();
        printf("L parenthesis missing..");
        return 0;
    }
    idx++;

    node->columnCount = 0;

    while (tokens[idx].type != TOKEN_RPAREN)
    {
        if (tokens[idx].type != TOKEN_IDENTIFIER)
        {
            // error();
            printf("identifier missing in parenthesis");
            return 0;
        }

        strcpy(node->columns[node->columnCount].columnName, tokens[idx].value);

        idx++;

        if (tokens[idx].type != TOKEN_INT && tokens[idx].type != TOKEN_VARCHAR)
        {
            // error();
            printf("Data type missing");
            return 0;
        }

        if (tokens[idx].type == TOKEN_INT)
        {
            node->columns[node->columnCount].type = TYPE_INT;
        }
        else
        {
            node->columns[node->columnCount].type = TYPE_VARCHAR;
        }

        node->columnCount++;

        idx++;

        if (tokens[idx].type == TOKEN_COMMA)
        {
            idx++;
        }
        else if (tokens[idx].type != TOKEN_RPAREN)
        {
            // error();
            printf("R Parenthesis  missing");
            return 0;
        }
    }

    // Right Parenthesis
    if (tokens[idx].type != TOKEN_RPAREN)
    {
        // error();
        printf("Parenthesis missing");
        return 0;
    }
    idx++;
    if (tokens[idx].type != TOKEN_SEMICOLON)
    {
        // error();
        printf("Semicolon missing");
        return 0;
    }
    return 1;
}

int parseInsert(Token tokens[], int count, InsertNode *node)
{
    int idx = 0;

    if (tokens[idx].type != TOKEN_INSERT)
    {
        printf("Insert statement missing\n");
        return 0;
    }
    idx++;

    if (tokens[idx].type != TOKEN_INTO)
    {
        printf("Into statement missing\n");
        return 0;
    }
    idx++;

    if (tokens[idx].type != TOKEN_IDENTIFIER)
    {
        printf("Table name missing\n");
        return 0;
    }

    strcpy(node->tableName, tokens[idx].value);
    idx++;

    if (tokens[idx].type != TOKEN_VALUES)
    {
        printf("Values missing\n");
        return 0;
    }
    idx++;

    if (tokens[idx].type != TOKEN_LPAREN)
    {
        printf("Left parenthesis missing\n");
        return 0;
    }
    idx++;

    node->valueCount = 0;

    while (tokens[idx].type != TOKEN_RPAREN)
    {
        if (tokens[idx].type != TOKEN_NUMBER &&
            tokens[idx].type != TOKEN_IDENTIFIER)
        {
            printf("Value expected\n");
            return 0;
        }

        strcpy(
            node->values[node->valueCount],
            tokens[idx].value);

        node->valueCount++;

        idx++;

        if (tokens[idx].type == TOKEN_COMMA)
        {
            idx++;
        }
        else if (tokens[idx].type != TOKEN_RPAREN)
        {
            printf("Comma expected\n");
            return 0;
        }
    }

    if (tokens[idx].type != TOKEN_RPAREN)
    {
        printf("Right parenthesis missing\n");
        return 0;
    }
    idx++;

    if (tokens[idx].type != TOKEN_SEMICOLON)
    {
        printf("Semicolon missing\n");
        return 0;
    }

    return 1;
}

int parseSelect(Token tokens[], int count, SelectNode *node)
{
    int idx = 0;

    if (tokens[idx].type != TOKEN_SELECT)
    {
        printf("SELECT missing\n");
        return 0;
    }
    idx++;

    node->columnCount = 0;
    node->selectAll = 0;
    node->hasWhere = 0;

    if (tokens[idx].type == TOKEN_STAR)
    {
        node->selectAll = 1;
        idx++;
    }
    else if (tokens[idx].type == TOKEN_IDENTIFIER)
    {
        while (tokens[idx].type != TOKEN_FROM)
        {
            if (tokens[idx].type != TOKEN_IDENTIFIER)
            {
                printf("Column name expected\n");
                return 0;
            }

            strcpy(node->columns[node->columnCount], tokens[idx].value);

            node->columnCount++;

            idx++;

            if (tokens[idx].type == TOKEN_COMMA)
            {
                idx++;
            }
            else if (tokens[idx].type != TOKEN_FROM)
            {
                printf("Comma expected\n");
                return 0;
            }
        }
    }
    else
    {
        printf("Column list or * expected\n");
        return 0;
    }

    if (tokens[idx].type != TOKEN_FROM)
    {
        printf("FROM missing\n");
        return 0;
    }
    idx++;

    if (tokens[idx].type != TOKEN_IDENTIFIER)
    {
        printf("Table name missing\n");
        return 0;
    }

    strcpy(node->tableName, tokens[idx].value);
    idx++;

    if (tokens[idx].type == TOKEN_WHERE)
    {
        node->hasWhere = 1;
        idx++;

        if (tokens[idx].type != TOKEN_IDENTIFIER)
        {
            printf("WHERE column missing\n");
            return 0;
        }
        strcpy(node->whereColumn, tokens[idx].value);
        idx++;

        if (tokens[idx].type != TOKEN_EQUAL)
        {
            printf("= missing !!");
            return 0;
        }
        idx++;

        if (tokens[idx].type != TOKEN_IDENTIFIER &&
            tokens[idx].type != TOKEN_NUMBER)
        {
            printf("WHERE value missing\n");
            return 0;
        }

        strcpy(node->whereValue, tokens[idx].value);
        idx++;
    }

    if (tokens[idx].type != TOKEN_SEMICOLON)
    {
        printf("Semicolon missing\n");
        return 0;
    }

    return 1;
}
