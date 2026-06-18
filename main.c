#include <stdio.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"
#include "executor.h"

int main()
{
    char input[256];
    Token tokens[100];

    while (1)
    {
        printf("MiniDB >> ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0)
        {
            break;
        }
        int count = tokenization(input, tokens);

        // for (int i = 0; i < count; i++)
        // {
        //     printf("%d -> %s\n",
        //            tokens[i].type,
        //            tokens[i].value);
        // }

        if (tokens[0].type == TOKEN_CREATE)
        {
            CreateTableNode node;
            if(parseCreateTable(tokens, count, &node)){
                executeCreateTable(&node);
            }
        }
        else if(tokens[0].type == TOKEN_INSERT){
            InsertNode node;
            if(parseInsert(tokens, count, &node)){
                executeInsert(&node);
            }
        }
        else if(tokens[0].type == TOKEN_SELECT){
            SelectNode node;
            if(parseSelect(tokens, count, &node)){
                executeSelect(&node);
            }
        }else{
            printf("Invalid Statement\n");
        }
        
    }

    return 0;
}
