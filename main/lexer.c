#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

#define _CRT_SECURE_NO_WARNINGS

Token getNextToken(FILE *fp) {

    Token token;
    int c;
    int i = 0;

    while ((c = fgetc(fp)) != EOF && isspace(c));
    
    if(c == EOF) {
        token.type = TOKEN_EOF;
        strcpy(token.text, "EOF");
        return token;
    }

    if(isalpha(c) || c == '_') {

        token.text[i++] = c;
        while ((c = fgetc(fp)) != EOF && (isalnum(c) || c == '_')) {
            token.text[i++] = c;
        }
        token.text[i] = '\0';
        ungetc(c, fp);

        if(strcmp(token.text, "let") == 0) {
            token.type = TOKEN_LET;
        } else {
            token.type = TOKEN_IDENTIFIER;
        }

        return token;

    }

    if(isdigit(c)) {
        token.text[i++] = c;
        while ((c = fgetc(fp)) != EOF && isdigit(c)){
            token.text[i++] = c;
        }

        token.text[i] = '\0';
        ungetc(c, fp);
        token.type = TOKEN_NUMBER;
        return token;
        
    }

    if(c == '=') {
        token.type = TOKEN_ASSIGN;
        strcpy(token.text, "=");
        return token;
    }

    if( c == ';' ){
        token.type = TOKEN_SEMICOLON;
        strcpy(token.text, ";");
        return token;
    }

    if(c == '+') {
        token.type = TOKEN_PLUS;
        strcpy(token.text, "+");
        return token;
    }

    if(c == '-') {
        token.type = TOKEN_MINUS;
        strcpy(token.text, "-");
        return token;
    }

    if(c == '*') {
        token.type = TOKEN_STAR;
        strcpy(token.text, "*");
        return token;
    }

    if(c == '/') {
        token.type = TOKEN_SLASH;
        strcpy(token.text, "/");
        return token;
    }

    if(c == '(') {
        token.type = TOKEN_LEFT_PARENT;
        strcpy(token.text, "(");
        return token;
    }

    if(c == ')') {
        token.type = TOKEN_RIGHT_PARENT;
        strcpy(token.text, ")");
        return token;
    }

    if(c == '.'){
        token.type = TOKEN_DOT;
        strcpy(token.text, ".");
        return token;
    }

    token.type = TOKEN_UNKNOW;
    token.text[0] = c;
    token.text[1] = '\0';
    
    return token;

}

