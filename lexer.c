#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"

TokenType checkKeyword(char* word) {

    if(strcmp(word, "SELECT") == 0) {
        return TOKEN_SELECT;
    }
    if(strcmp(word, "FROM") == 0) {
        return TOKEN_FROM;
    }
    if (strcmp(word, "WHERE") == 0)
    {
        return TOKEN_WHERE;
    }
    

    return TOKEN_IDENTIFIER;
}

int tokenize(char* input, Token tokens[]) {

    int i = 0;
    int tokenCount = 0;

    while(input[i] != '\0') {

        if(isspace(input[i])) {
            i++;
            continue;
        }
        // WORDS
        if(isalpha(input[i])) {

            char buffer[64];
            int j = 0;

            while(isalpha(input[i])) {
                buffer[j] = input[i];
                j++;
                i++;
            }

            buffer[j] = '\0';
            Token token;
            token.type = checkKeyword(buffer);
            strcpy(token.value, buffer);
            tokens[tokenCount++] = token;
        }

        else if(input[i] == '='){
            Token token;
            token.type = TOKEN_EQUALS;
            strcpy(token.value, "=");
            tokens[tokenCount++] = token;
            i++;
        }
        // *
        else if(input[i] == '*') {
            Token token;
            token.type = TOKEN_STAR;
            strcpy(token.value, "*");
            tokens[tokenCount++] = token;
            i++;
        }
        // ;
        else if(input[i] == ';') {
            Token token;
            token.type = TOKEN_SEMICOLON;
            strcpy(token.value, ";");
            tokens[tokenCount++] = token;
            i++;
        }
        else {

            printf("Unexpected character: %c\n", input[i]);

            i++;
        }
    }

    return tokenCount;
}