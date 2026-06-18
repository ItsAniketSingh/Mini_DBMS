#include <ctype.h>
#include <string.h>

#include "lexer.h"


TokenType checkToken(char *str)
{
    if (strcmp(str, "select") == 0)
        return TOKEN_SELECT;

    if (strcmp(str, "from") == 0)
        return TOKEN_FROM;

    if (strcmp(str, "where") == 0)
        return TOKEN_WHERE;

    if (strcmp(str, "insert") == 0)
        return TOKEN_INSERT;

    if (strcmp(str, "create") == 0)
        return TOKEN_CREATE;

    if (strcmp(str, "table") == 0)
        return TOKEN_TABLE;

    if (strcmp(str, "into") == 0)
        return TOKEN_INTO;

    if (strcmp(str, "values") == 0)
        return TOKEN_VALUES;

    if(strcmp(str, "int") == 0){
        return TOKEN_INT;
    }
    if (strcmp(str,"varchar") == 0)
    {
        return TOKEN_VARCHAR;
    }
    
    return TOKEN_IDENTIFIER;
}

int tokenization(char *input, Token tokens[])
{
    int i = 0;
    int count = 0;

    while (input[i] != '\0')
    {
        if (isspace(input[i]))
        {
            i++;
            continue;
        }

        if (isalpha(input[i]) || input[i] == '_')
        {
            char buffer[64];
            int j = 0;

            while (isalnum(input[i]) || input[i] == '_')
            {
                buffer[j++] = tolower(input[i]);
                i++;
            }

            buffer[j] = '\0';

            tokens[count].type = checkToken(buffer);
            strcpy(tokens[count].value, buffer);

            count++;
            continue;
        }

        if (isdigit(input[i]))
        {
            char buffer[64];
            int j = 0;

            while (isdigit(input[i]))
            {
                buffer[j++] = input[i];
                i++;
            }

            buffer[j] = '\0';

            tokens[count].type = TOKEN_NUMBER;
            strcpy(tokens[count].value, buffer);

            count++;
            continue;
        }

        if (input[i] == '*')
        {
            tokens[count].type = TOKEN_STAR;
            strcpy(tokens[count].value, "*");
            count++;
            i++;
            continue;
        }

        if (input[i] == '(')
        {
            tokens[count].type = TOKEN_LPAREN;
            strcpy(tokens[count].value, "(");
            count++;
            i++;
            continue;
        }

        if (input[i] == ')')
        {
            tokens[count].type = TOKEN_RPAREN;
            strcpy(tokens[count].value, ")");
            count++;
            i++;
            continue;
        }

        if (input[i] == ',')
        {
            tokens[count].type = TOKEN_COMMA;
            strcpy(tokens[count].value, ",");
            count++;
            i++;
            continue;
        }
        if(input[i] == '='){
            tokens[count].type = TOKEN_EQUAL;
            strcpy(tokens[count].value, "=");
            count++;
            i++;
            continue;
        }
        
        if (input[i] == ';')
        {
            tokens[count].type = TOKEN_SEMICOLON;
            strcpy(tokens[count].value, ";");
            count++;
            i++;
            continue;
        }

        i++;
    }

    tokens[count].type = TOKEN_EOF;
    strcpy(tokens[count].value, "EOF");
    count++;

    return count;
}

