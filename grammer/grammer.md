# Gramática

```
Program          → Statement*
Statement        → VariableDeclaration
VariableDecl     → "let" Identifier "=" Expression ";"
Expression       → Term (("+" | "-") Term)*
Term             → Factor (("*" | "/") Factor)*
Factor           → Number | Identifier | "(" Expression ")"
```