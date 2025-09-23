#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"

#define _CRT_SECURE_NO_WARNINGS

// Main da aplicação

FILE *fp;

int main() {


    fp = fopen("input.ts", "r");

    if(!fp){

        printf("Erro ao abrir o arquivo!\n");
        return 1;

    }

    printf("===== AST =====\n");
    
    parseProgram();
    
    fclose(fp);

    printf("Pressione Enter para sair...\n");
    getchar();

    return 0;

}
