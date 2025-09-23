#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eval.h"

#define _CRT_SECURE_NO_WARNINGS

#define MAX_VARS 100

typedef struct {

    char name[MAX_TOKEN_LEN];
    int value;

} Variable;


static Variable variables[MAX_VARS];
static int varCount = 0;

void setVariable(const char *name, int value){

    for(int i = 0; i < varCount; i++) {
        if(strcmp(variables[i].name, name) == 0) {
            variables[i].value = value;
            return;
        }
    }

    strcpy(variables[varCount].name, name);
    variables[varCount].value = value;
    varCount++;
}

int getVariable(const char *name){

    for(int i = 0; i < varCount; i++) {

        if(strcmp(variables[i].name, name) == 0) {

            return variables[i].value;

        }

    }
    printf("Erro: variavel '%s' não definida!\n", name);
    exit(1);

}


int eval(ASTNode *node) {

    if(!node) return 0;

    switch (node->type) {
        case AST_NUMBER:
            return atoi(node->value);
            // break;

        case AST_IDENTIFIER:
            return getVariable(node->value);
            // break;

        case AST_BINARY_OPERATION: {
            int left = eval(node->left);
            int right = eval(node->right);
            if(strcmp(node->value, "+") == 0) return left + right;
            if(strcmp(node->value, "-") == 0) return left - right;
            if(strcmp(node->value, "*") == 0) return left * right;
            if(strcmp(node->value, "/") == 0) return left / right;
            break;
        }

        case AST_VARIABLE_DECL: {
            int value = eval(node->right);
            setVariable(node->left->value, value);
            return value;
        }

        case AST_CALL_EXPRESSION: {
            if(strcmp(node->value, "console.log") == 0) {
                int result = eval(node->left);
                printf("%d\n", result);
                return result;
            }
            break;
        }
    }
    
    return 0;

}




