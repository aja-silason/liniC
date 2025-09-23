#ifndef EVAL_H
#define EVAL_H

#include "ast.h"

void setVariable(const char *name, int value);
int getVariable(const char *name);
int eval(ASTNode *node);

#endif