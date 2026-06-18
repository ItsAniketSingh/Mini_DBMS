#ifndef LEXER_H
#define LEXER_H

typedef enum
{
    TOKEN_SELECT,
    TOKEN_FROM,
    TOKEN_WHERE,
    TOKEN_INSERT,
    TOKEN_INTO,

    TOKEN_CREATE,
    TOKEN_TABLE,

    TOKEN_STAR,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,
    TOKEN_EQUAL,


    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_VALUES,

    TOKEN_INT,
    TOKEN_VARCHAR,

    TOKEN_LPAREN,
    TOKEN_RPAREN,
    
    TOKEN_EOF
} TokenType;

typedef struct
{
    TokenType type;
    char value[64];
} Token;

int tokenization(char *input, Token token[]);

#endif
