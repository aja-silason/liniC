#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 100

//Definir os tokens

typedef enum {

    TOKEN_LET,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_ASSIGN,
    TOKEN_SEMICOLON,
    TOKEN_UNKNOW,
    TOKEN_EOF

} TokenType;

typedef struct  {

    TokenType type;
    char text[MAX_TOKEN_LEN];

} Token;


// Estrutura de AST
typedef enum {

    AST_VARIABLE_DECL,
    AST_IDENTIFIER,
    AST_NUMBER

} ASTNodeType;


typedef struct  ASTNode {

    ASTNodeType type;
    char value[MAX_TOKEN_LEN];
    struct ASTNode *left;
    struct ASTNode *right;

} ASTNode;


// Funções, metodos auxiliares para AST
ASTNode *createNote(ASTNodeType type, const char *value) {

    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));

    node->type = type;
    strcpy(node->left, value ? value : "");
    node->left = NULL;
    node->right = NULL;
    return node;

}

void printAST(ASTNode *node, int depth) {

    if(!node) return;

    for(int i = 0; i < depth; i++) printf("   ");
    printf("%s", node->type == AST_VARIABLE_DECL ? "VariableDeclaration" : node->type == AST_IDENTIFIER ? "Identifier" : node->type == AST_NUMBER ? "Number" : "Unknow");
    
    if(strlen(node->value) > 0) {
        printf(": %s", node->value);
    }

    printf("\n");
    printAST(node->left, depth + 1);
    printAST(node->right, depth + 1);

}


//lexer 



