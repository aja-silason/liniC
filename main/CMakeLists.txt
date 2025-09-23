cmake_minimum_required(VERSION 3.15)

# Nome do projeto
project(liniC C)

# Versão do C
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Ativar warnings
# add_compile_options(-Wall -Wextra)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Arquivos fonte
set(SOURCES
    main.c
    parser.c
    lexer.c
    ast.c
    eval.c
)

# Executável final
add_executable(liniC ${SOURCES})


