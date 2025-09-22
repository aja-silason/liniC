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

    // FILE *f = fopen("codigo.txt", "r");
    // if (!f) {
    //     perror("Erro ao abrir o arquivo");
    //     return 1;
    // }

    int ch;
    while ((ch = fgetc(f)) != EOF) {
        printf("[Debug] Byte lido: %d (%c)\n", ch, ch);
    }
    // fclose(f);
    

}

Token getNextToken(FILE *fp) {

    Token token;
    int c;
    int i = 0;

    while ((c == fgetc(fp)) != EOF && isspace(c));
    
    if(c == EOF) {
        token.type = TOKEN_EOF;
        strcpy(token.text, "EOF");
        return token;
    }

    // printf("[Debug]: Char lido é %c (%d)\n", c, c);

    if(isalpha(c) || c == '_') {

        token.text[i++] = c;
        while ((c == fgetc(fp)) != EOF && (isalnum(c) || c == '_')) {
            token.text[i++] = c;
        }
        token.text[i] = '\0';
        ungetc(c, fp);

        if( isKeyWord(token.text) ) {
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

    ASTNode *idNode = createNote(AST_IDENTIFIER, currentToken.text);
    advance();

    expect(TOKEN_ASSIGN);

    if(currentToken.type != TOKEN_NUMBER) {
        printf("Erro: esperado número após '='\n");
        exit(1);
    }

    ASTNode *numNode = createNote(AST_NUMBER, currentToken.text);
    advance();

    expect(TOKEN_SEMICOLON);
    ASTNode *varDecl = createNote(AST_VARIABLE_DECL, "");
    varDecl->left = idNode;
    varDecl->right = numNode;

    return varDecl;

}




// Main da aplicação

int main() {


    fp = fopen("input.ts", "r");
    if(!fp){

        printf("Erro ao abrir o arquivo!\n");
        return 1;

    }

    Debug(fp);

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







