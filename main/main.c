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
    AST_NUMBER,
    AST_BINARY_OPERATION,

} ASTNodeType;


typedef struct  ASTNode {

    ASTNodeType type;
    char value[MAX_TOKEN_LEN];
    struct ASTNode *left;
    struct ASTNode *right;

} ASTNode;


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
    printf("%s", node->type == AST_VARIABLE_DECL ? "VariableDeclaration" : node->type == AST_IDENTIFIER ? "Identifier" : node->type == AST_NUMBER ? "Number" : "Unknow");
    
    if(strlen(node->value) > 0) {
        printf(": %s", node->value);
    }

    printf("\n");
    printAST(node->left, depth + 1);
    printAST(node->right, depth + 1);

}


//lexer 

int isKeyWord(const char *str) {
    return strcmp(str, "let") == 0;
}

void Debug(FILE *f){

    int ch;
    while ((ch = fgetc(f)) != EOF) {
        printf("[Debug] Byte lido: %d (%c)\n", ch, ch);
    }    

}

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

    // printf("[Debug]: Char lido é %c (%d)\n", c, c);

    if(isalpha(c) || c == '_') {

        token.text[i++] = c;
        while ((c = fgetc(fp)) != EOF && (isalnum(c) || c == '_')) {
            token.text[i++] = c;
        }
        token.text[i] = '\0';
        ungetc(c, fp);

        if( isKeyWord(token.text) ) {
            token.type = TOKEN_LET;
        } else {
            token.type = TOKEN_IDENTIFIER;
        }

        // if(strcmp(token.text, "let") == 0) {
        //     token.type = TOKEN_LET;
        // } else {
        //     token.type = TOKEN_IDENTIFIER;
        // }

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

    token.type = TOKEN_UNKNOW;
    token.text[0] = c;
    token.text[1] = '\0';
    return token;

}


// Parser

Token currentToken;
FILE *fp;

void advance() {

    currentToken = getNextToken(fp);

}


void expect(TokenType type) {

    if( currentToken.type != type ){

        printf("Erro de sintaxe: esperado token %d mas veio %d (%s)\n", type, currentToken.type, currentToken.text);
        exit(1);

    }
    advance();

}

//Parse ex: let x = 10;

ASTNode *parseVariableDeclaration() {

    expect(TOKEN_LET);

    if(currentToken.type != TOKEN_IDENTIFIER) {
        printf("Erro: esperado identificador após 'let'\n");
        exit(1);
    }

    ASTNode *idNode = createNode(AST_IDENTIFIER, currentToken.text);
    advance();

    expect(TOKEN_ASSIGN);

    if(currentToken.type != TOKEN_NUMBER) {
        printf("Erro: esperado número após '='\n");
        exit(1);
    }

    ASTNode *numNode = createNode(AST_NUMBER, currentToken.text);
    advance();

    expect(TOKEN_SEMICOLON);
    
    ASTNode *varDecl = createNode(AST_VARIABLE_DECL, "");
    varDecl->left = idNode;
    varDecl->right = numNode;

    return varDecl;

}


ASTNode *parseFactor() {

    if(currentToken.type == TOKEN_NUMBER) {
        ASTNode *numNode = createNode(AST_NUMBER, currentToken.text);
        advance();
        return numNode;
    }

    if(currentToken.type == TOKEN_IDENTIFIER) {
        ASTNode *idNode = createNode(AST_IDENTIFIER, currentToken.text);
        advance();
        return idNode;
    }

    if(strcmp(currentToken.text, "(") == 0) {
        advance();
        ASTNode *expr = parseExpression();
        if(strcmp(currentToken.text, ")") != 0){
            printf("Erro: esperado )\n");
            exit(1);
        }
        advance();
        return expr;
    }

    printf("Erro: factor inválido (%s)\n ", currentToken.text);
    exit(1);

}

ASTNode *parseTerm() {

    ASTNode *node = parseFactor();

    while ((strcmp(currentToken.text, "*") == 0 || strcmp(currentToken.text, "/") == 0)) {

        char operation[2];
        strcpy(operation, currentToken.text);
        advance();

        ASTNode *right = parseFactor();
        ASTNode *operationNode = createNode(AST_BINARY_OPERATION, operation);
        operationNode->left = node;
        operationNode->right = right;
        node = operationNode;

    }

    return node;

}

ASTNode *parseExpression() {

    ASTNode *node = parseTerm();

    while (strcmp(currentToken.text, "+") == 0 || strcmp(currentToken.text, "-") == 0){

        char operation[2];
        strcpy(operation, currentToken.text);
        advance();

        ASTNode *right = parseTerm();
        ASTNode *operationNode = createNode(AST_BINARY_OPERATION, operation);
        operationNode->left = node;
        operationNode->right = right;
        node = operationNode;

    }

    return node;
    

}


// Main da aplicação

int main() {


    fp = fopen("input.ts", "r");
    if(!fp){

        printf("Erro ao abrir o arquivo!\n");
        Debug(fp);
        return 1;

    }

    rewind(fp);

    advance();
    ASTNode *tree = parseVariableDeclaration();

    printf("===== AST =====\n");
    
    printAST(tree, 0);
    
    fclose(fp);

    // system("pause");
    printf("Pressione Enter para sair...\n");
    getchar();

    return 0;

}







