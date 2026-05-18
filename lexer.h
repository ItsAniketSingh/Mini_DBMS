#ifndef LEXER_H
#define LEXER_H

typedef enum {

    TOKEN_SELECT,
    TOKEN_FROM,
    TOKEN_WHERE,

    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,

    TOKEN_STAR,
    TOKEN_COMMA,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_SEMICOLON,
    TOKEN_EQUALS,

    TOKEN_UNKNOWN,
    TOKEN_EOF

} TokenType;

typedef struct {

    TokenType type;
    char value[64];

} Token;

int tokenize(char* input, Token tokens[]);

#endif