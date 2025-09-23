#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

// Token atual (global)
static Token currentToken;
extern FILE *fp;  // reusar o mesmo fp global

// Prototypes
static void advance();
static ASTNode *parseStatement();
static ASTNode *parseExpression();
static ASTNode *parseTerm();
static ASTNode *parseFactor();
static ASTNode *parseVariableDeclaration();
static ASTNode *parseConsoleLog();
// void parseProgram(FILE *fp);

// Avança para próximo token
static void advance() {
    currentToken = getNextToken(fp);
}

// =========================
//   Programa
// =========================
void parseProgram() {
    // ASTNode *root = NULL;

    while (currentToken.type != TOKEN_EOF) {
        ASTNode *stmt = parseStatement();
        if (!stmt) break;

        // imprime e avalia
        printAST(stmt, 0);
        eval(stmt);

        if(currentToken.type == TOKEN_EOF) break;
    }



    // return root;
}


// void parseProgram() {

//     while (currentToken.type != TOKEN_EOF){
        
//         ASTNode *tree = NULL;
        
//         if(strcmp(currentToken.text, "let") == 0) {
//             tree = parseVariableDeclaration();
//         } else if(strcmp(currentToken.text, "console") == 0) {
//             tree = parseConsoleLog();
//         } else {
//             printf("Erro: instrucao desconhecida '%s'\n", currentToken.text);
//             return;
//         }

//         printAST(tree, 0);
//         eval(tree);
        
//         if(currentToken.type == TOKEN_EOF) break;

//     }

// }


// =========================
//   Statement
// =========================
static ASTNode *parseStatement() {
    if (strcmp(currentToken.text, "let") == 0) {
        return parseVariableDeclaration();
    } else if (strcmp(currentToken.text, "console") == 0) {
        return parseConsoleLog();
    } else {
        printf("Erro: instrução desconhecida '%s'\n", currentToken.text);
        return NULL;
    }
}

// =========================
//   Expressões
// =========================
static ASTNode *parseFactor() {
    if (currentToken.type == TOKEN_NUMBER) {
        ASTNode *numNode = createNode(AST_NUMBER, currentToken.text);
        advance();
        return numNode;
    }

    if (currentToken.type == TOKEN_IDENTIFIER) {
        ASTNode *idNode = createNode(AST_IDENTIFIER, currentToken.text);
        advance();
        return idNode;
    }

    if (currentToken.type == TOKEN_LEFT_PARENT) {
        advance();
        ASTNode *expr = parseExpression();
        if (currentToken.type != TOKEN_RIGHT_PARENT) {
            printf("Erro: esperado ')'\n");
            exit(1);
        }
        advance();
        return expr;
    }

    printf("Erro: fator inválido (%s)\n", currentToken.text);
    exit(1);
}

static ASTNode *parseTerm() {
    ASTNode *node = parseFactor();

    while (currentToken.type == TOKEN_STAR || currentToken.type == TOKEN_SLASH) {
        char op[2];
        strcpy(op, currentToken.text);
        advance();

        ASTNode *right = parseFactor();
        ASTNode *opNode = createNode(AST_BINARY_OPERATION, op);
        opNode->left = node;
        opNode->right = right;
        node = opNode;
    }

    return node;
}

static ASTNode *parseExpression() {
    ASTNode *node = parseTerm();

    while (currentToken.type == TOKEN_PLUS || currentToken.type == TOKEN_MINUS) {
        char op[2];
        strcpy(op, currentToken.text);
        advance();

        ASTNode *right = parseTerm();
        ASTNode *opNode = createNode(AST_BINARY_OPERATION, op);
        opNode->left = node;
        opNode->right = right;
        node = opNode;
    }

    return node;
}

// =========================
//   Declarações
// =========================
static ASTNode *parseVariableDeclaration() {
    // let
    advance();

    if (currentToken.type != TOKEN_IDENTIFIER) {
        printf("Erro: esperado identificador após 'let'\n");
        exit(1);
    }

    ASTNode *idNode = createNode(AST_IDENTIFIER, currentToken.text);
    advance();

    if (currentToken.type != TOKEN_ASSIGN) {
        printf("Erro: esperado '='\n");
        exit(1);
    }
    advance();

    ASTNode *expr = parseExpression();

    if (currentToken.type != TOKEN_SEMICOLON) {
        printf("Erro: esperado ';'\n");
        exit(1);
    }
    advance();

    ASTNode *decl = createNode(AST_VARIABLE_DECL, "");
    decl->left = idNode;
    decl->right = expr;
    return decl;
}

static ASTNode *parseConsoleLog() {
    // console.log(expr);
    advance(); // console
    if (currentToken.type != TOKEN_DOT) {
        printf("Erro: esperado '.' após 'console'\n");
        exit(1);
    }
    advance();

    if (strcmp(currentToken.text, "log") != 0) {
        printf("Erro: esperado 'log' após 'console.'\n");
        exit(1);
    }
    advance();

    if (currentToken.type != TOKEN_LEFT_PARENT) {
        printf("Erro: esperado '('\n");
        exit(1);
    }
    advance();

    ASTNode *expr = parseExpression();

    if (currentToken.type != TOKEN_RIGHT_PARENT) {
        printf("Erro: esperado ')'\n");
        exit(1);
    }
    advance();

    if (currentToken.type != TOKEN_SEMICOLON) {
        printf("Erro: esperado ';'\n");
        exit(1);
    }
    advance();

    ASTNode *call = createNode(AST_CALL_EXPRESSION, "console.log");
    call->left = expr;
    return call;
}
