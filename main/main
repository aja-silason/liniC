#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 100

#define MAX_VARS 100

//Definir os tokens

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


// Estrutura de AST
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

typedef struct {

    char name[MAX_TOKEN_LEN];
    int value;

} Variable;


Variable variables[MAX_TOKEN_LEN];
int varCount = 0;

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

// Parser
Token currentToken;
FILE *fp;

ASTNode *parseExpression();
ASTNode *parseFactor();
ASTNode *parseTerm();
ASTNode *parseVariableDeclaration();
ASTNode *parseConsoleLog();
void parseProgram();

void advance() {
    currentToken = getNextToken(fp);
}


void expect(TokenType type) {

    if( currentToken.type != type ){

        if(type == TOKEN_EOF && currentToken.type == TOKEN_EOF) return;

        printf("Erro de sintaxe: esperado token %d mas veio %d (%s)\n", type, currentToken.type, currentToken.text);
        exit(1);

    }
    advance();

}

//Parsers
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

    if(currentToken.type == TOKEN_LEFT_PARENT) {
        advance();
        ASTNode *expr = parseExpression();
        if(currentToken.type != TOKEN_RIGHT_PARENT){
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

    while (currentToken.type == TOKEN_STAR || currentToken.type == TOKEN_SLASH) {

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

    while (currentToken.type == TOKEN_PLUS || currentToken.type == TOKEN_MINUS){

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

ASTNode *parseVariableDeclaration() {

    expect(TOKEN_LET);

    if(currentToken.type != TOKEN_IDENTIFIER) {
        printf("Erro: esperado identificador após 'let'\n");
        exit(1);
    }

    ASTNode *idNode = createNode(AST_IDENTIFIER, currentToken.text);
    advance();

    expect(TOKEN_ASSIGN);

    ASTNode *expressionNode = parseExpression();

    expect(TOKEN_SEMICOLON);

    ASTNode *variableDeclaration = createNode(AST_VARIABLE_DECL, "");
    
    variableDeclaration->left = idNode;
    variableDeclaration->right = expressionNode;

    return variableDeclaration;

}

ASTNode *parseConsoleLog(){

    expect(TOKEN_IDENTIFIER);
    expect(TOKEN_DOT);
    expect(TOKEN_IDENTIFIER);

    expect(TOKEN_LEFT_PARENT);
    ASTNode *expression = parseExpression();
    expect(TOKEN_RIGHT_PARENT);
    expect(TOKEN_SEMICOLON);

    ASTNode *call = createNode(AST_CALL_EXPRESSION, "console.log");
    call->left = expression;
    return call;

}

void parseProgram() {

    while (currentToken.type != TOKEN_EOF){
        
        ASTNode *tree = NULL;
        
        if(strcmp(currentToken.text, "let") == 0) {
            tree = parseVariableDeclaration();
        } else if(strcmp(currentToken.text, "console") == 0) {
            tree = parseConsoleLog();
        } else {
            printf("Erro: instrucao desconhecida '%s'\n", currentToken.text);
            return;
        }

        printAST(tree, 0);
        eval(tree);
        
        if(currentToken.type == TOKEN_EOF) break;

    }

}


// Main da aplicação
int main() {


    fp = fopen("input.ts", "r");
    if(!fp){

        printf("Erro ao abrir o arquivo!\n");
        return 1;

    }

    advance();

    printf("===== AST =====\n");
    
    parseProgram();
    
    fclose(fp);

    printf("Pressione Enter para sair...\n");
    getchar();

    return 0;

}
