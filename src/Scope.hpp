#include "AST.hpp"

#ifndef SCOPE_H
#define SCOPE_H

struct Scope {
    AST** functions_def;
    unsigned int functions_def_count;

    AST** variables_def;
    unsigned int variables_def_count;
};

Scope* initScope();

AST* scopeAddFunctionDefinition(Scope* scope, AST* node);
AST* scopeGetFunctionDefinition(Scope* scope, const char* fname);

AST* scopeAddVariableDefinition(Scope* scope, AST* node);
AST* scopeGetVariableDefinition(Scope* scope, const char* vname);

#endif
