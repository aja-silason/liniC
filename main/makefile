# Nome do executável
TARGET = main

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c11

# Arquivos fonte
SRCS = main.c parser.c lexer.c ast.c eval.c

# Objetos compilados
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(TARGET)

# Linkagem
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilação de cada .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rodar o programa já com input.ts
run: $(TARGET)
	./$(TARGET) input.ts

# Limpeza
clean:
	rm -f $(OBJS) $(TARGET)
