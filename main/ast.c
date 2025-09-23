#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

#define _CRT_SECURE_NO_WARNINGS


// Funções, metodos auxiliares para AST
ASTNode *createNode(ASTNodeType type, const char *value) {

    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));

    node->type = type;
    strcpy(node->value, value ? value : "");
    node->left = NULL;
    node->right = NULL;
    return node;

}

void printAST(ASTNode *node, int depth) {

    if(!node) return;

    for(int i = 0; i < depth; i++) printf("   ");

    switch (node->type) {
        case AST_VARIABLE_DECL: printf("variable_declaration"); break;
        case AST_IDENTIFIER: printf("Identifier"); break;
        case AST_NUMBER: printf("Number"); break;
        case AST_BINARY_OPERATION: printf("Binary_Operation"); break;
        case AST_CALL_EXPRESSION: printf("Call_expression"); break;
        default: printf("Uknow"); break;
    }
    
    if(strlen(node->value) > 0) {
        printf(": %s", node->value);
    }

    printf("\n");
    printAST(node->left, depth + 1);
    printAST(node->right, depth + 1);

}
