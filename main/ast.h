#ifndef AST_H
#define AST_H

#define MAX_TOKEN_LEN 100

typedef enum {

    AST_VARIABLE_DECL,
    AST_IDENTIFIER,
    AST_NUMBER,
    AST_BINARY_OPERATION,
    AST_CALL_EXPRESSION,

} ASTNodeType;


typedef struct  ASTNode {

    ASTNodeType type;
    char value[MAX_TOKEN_LEN];
    struct ASTNode *left;
    struct ASTNode *right;

} ASTNode;

// Funções, metodos auxiliares para AST
ASTNode *createNode(ASTNodeType type, const char *value);

void printAST(ASTNode *node, int depth);

#endif;