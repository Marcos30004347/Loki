#include <malloc.h>
#include <string.h>

#include "Scope.hpp"

Scope* initScope() {
    Scope* s = (Scope*)calloc(1, sizeof(Scope));
    s->functions_def = nullptr;
    s->functions_def_count = 0;

    s->variables_def = nullptr;
    s->variables_def_count = 0;

    return s;
}

AST* scopeAddFunctionDefinition(Scope* scope, AST* node) {
  
    if(scope->functions_def == nullptr) {
        scope->functions_def_count = 1;
        scope->functions_def = (AST**)calloc(1, sizeof(AST*));
    } else {
        scope->functions_def = (AST**)realloc(scope->functions_def, sizeof(AST*) * scope->functions_def_count + 1);
        scope->functions_def_count += 1;
    }

    scope->functions_def[scope->functions_def_count - 1] = node;
    return node;
}

AST* scopeGetFunctionDefinition(Scope* scope, const char* fname) {
    // for(int i=0; i<scope->functions_def_count; i++) {
    //     if(strcmp(scope->functions_def[i]->func_def_name, fname) == 0) {
    //         return scope->functions_def[i];
    //     }
    // }

    return nullptr;
}

AST* scopeAddVariableDefinition(Scope* scope, AST* node) {
    if(scope->variables_def == nullptr) {
        scope->variables_def = (AST**)calloc(1, sizeof(AST*));
        scope->variables_def[0] = node;
        scope->variables_def_count = 1;
        return node;
    }

    scope->variables_def = (AST**)realloc(
        scope->variables_def,
        scope->variables_def_count * sizeof(AST*)
    );

    scope->variables_def_count += 1;
    scope->variables_def[scope->variables_def_count - 1] = node;

    return node;
}

AST* scopeGetVariableDefinition(Scope* scope, const char* vname) {
    // for(int i=0; i<scope->variables_def_count; i++) {
    //     if(strcmp(scope->variables_def[i]->var_def_name, vname) == 0) {
    //         return scope->variables_def[i];
    //     }
    // }

    return nullptr;
}

