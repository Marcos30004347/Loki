#include "Scope.hpp"
#include <malloc.h>
#include <string.h>

Scope* initScope(Scope* parent) {
    Scope* scope = (Scope*)malloc(sizeof(Scope));
    scope->parent = parent;
    scope->functions_definitions_count = 0;
    scope->variables_definitions_count = 0;
    scope->structs_definitions_count = 0;

    scope->functions_definitions = nullptr;
    scope->variables_definitions = nullptr;
    scope->structs_definitions = nullptr;
    return scope;
}

void addStructToScope(Scope* scope, AST* struct_def) {
    scope->structs_definitions_count += 1;
    AST** list = (AST**)realloc(
        scope->structs_definitions,
        scope->structs_definitions_count * sizeof(AST*)
    );
    free(scope->structs_definitions);
    scope->structs_definitions = list;
    scope->structs_definitions[scope->structs_definitions_count - 1] = struct_def;
}

AST* getStructFromScope(Scope* scope, char* struct_identifier) {
    Scope* current = scope;
    while(current) {
        for(int i=0; i<current->structs_definitions_count; i++) {
            if(strcmp(current->structs_definitions[i]->struct_identifier->identifier, struct_identifier) == 0) {
                return current->structs_definitions[i];
            }
        }
        current = current->parent;
    }

    return nullptr;
}

void addFunctionToScope(Scope* scope, AST* function_def) {
    scope->functions_definitions_count += 1;
    AST** list = (AST**)realloc(
        scope->functions_definitions,
        scope->functions_definitions_count * sizeof(AST*)
    );

    free(scope->functions_definitions);
    scope->functions_definitions = list;

    scope->functions_definitions[scope->functions_definitions_count - 1] = function_def;
}
AST* getFunctionFromScope(Scope* scope, char* function_identifier) {
    Scope* current = scope;
        while(current) {
        for(int i=0; i<current->functions_definitions_count; i++) {
            if(strcmp(current->functions_definitions[i]->func_dec_identifier->identifier, function_identifier) == 0) {
                return current->functions_definitions[i];
            }
        }
        scope = scope->parent;
    }
    return nullptr;
}

void addVariableToScope(Scope* scope, AST* variable_def) {

    scope->variables_definitions_count += 1;
    AST** list = (AST**)realloc(
        scope->variables_definitions,
        scope->variables_definitions_count * sizeof(AST*)
    );

    free(scope->variables_definitions);
    scope->variables_definitions = list;

    scope->variables_definitions[scope->variables_definitions_count - 1] = variable_def;
}

AST* getVariableFromScope(Scope* scope, char* variable_identifier) {
    Scope* current = scope;
    while(current) {
        for(int i=0; i<current->variables_definitions_count; i++) {
            if(strcmp(current->variables_definitions[i]->var_def_identifier->identifier, variable_identifier) == 0) {
                return current->variables_definitions[i];
            }
        }

        current = current->parent;
    }
    return nullptr;
}
