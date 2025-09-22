# Conteudo para aprendizado dos fundamentos de C

Em C, strcmp() é utilizada para comparar duas strings e retornar um valor inteiro indicando se são iguais, ou qual a sua ordem alfabética. Já strcpy() serve para copiar o conteúdo de uma string para outra, alocando os caracteres da string de origem para a string de destino. 
strcmp() 
Função: Compara duas strings.
Propósito: Determinar se uma string é igual, menor ou maior que a outra.
Retorno:
0 se as duas strings forem idênticas.
Um valor negativo se a primeira string for lexicograficamente menor que a segunda.
Um valor positivo se a primeira string for lexicograficamente maior que a segunda.
Exemplo:

```C

    #include <string.h>
    #include <stdio.h>

    int main() {
        char s1[] = "abc";
        char s2[] = "abc";
        char s3[] = "abd";

        int result1 = strcmp(s1, s2); // result1 será 0
        int result2 = strcmp(s1, s3); // result2 será negativo

        printf("Resultado de strcmp(s1, s2): %d\n", result1);
        printf("Resultado de strcmp(s1, s3): %d\n", result2);

        return 0;
    }
```
strcpy()
Função: Copia uma string.
Propósito: Transferir o conteúdo de uma string (a de origem) para outra (a de destino). 
Funcionamento: A função copia cada caractere da string de origem para a string de destino, até encontrar o caractere nulo (\0). A string de destino deve ter espaço suficiente para acomodar a string original. 
Exemplo:

```C

    #include <string.h>
    #include <stdio.h>

    int main() {
        char origem[] = "Ola Mundo";
        char destino[20]; // O destino precisa ser grande o suficiente

        strcpy(destino, origem);

        printf("String de origem: %s\n", origem);
        printf("String de destino: %s\n", destino);

        return 0;
    }
```