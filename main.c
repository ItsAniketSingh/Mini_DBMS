#include <stdio.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"

void printTokens(Token tokens[], int count) {

    for(int i = 0; i < count; i++) {

        printf("%d -> %s\n",
               tokens[i].type,
               tokens[i].value);
    }
}

int main() {

    char input[1024];

    while(1) {

        printf("mini_sql > ");
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';

        if(strcmp(input, ".exit") == 0) {

            printf("Bye!\n");

            break;
        }

        Token tokens[100];

        int tokenCount = tokenize(input, tokens);

        // printTokens(tokens, tokenCount);

        parse(tokens, tokenCount);

        printf("\n");
    }

    return 0;
}