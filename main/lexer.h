#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#define MAX_TOKEN_LEN 100

typedef enum {

    TOKEN_LET,
    TOKEN_IDENTIFIER,
    TOKEN_DOT,
    TOKEN_NUMBER,
    TOKEN_ASSIGN,      // =
    TOKEN_SEMICOLON,   // ;
    TOKEN_PLUS,        // +
    TOKEN_MINUS,       // -
    TOKEN_STAR,        // *
    TOKEN_SLASH,       // /
    TOKEN_LEFT_PARENT,      // (
    TOKEN_RIGHT_PARENT,
    TOKEN_UNKNOW,
    TOKEN_EOF

} TokenType;


typedef struct  {

    TokenType type;
    char text[MAX_TOKEN_LEN];

} Token;

Token getNextToken(FILE *fp);

#endif;