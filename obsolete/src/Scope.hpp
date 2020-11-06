#ifndef SCOPE
#define SCOPE

#include "AST.hpp"

struct Scope {
    Scope* parent;
    AST** structs_definitions;
    unsigned int structs_definitions_count;
    AST** functions_definitions;
    unsigned int functions_definitions_count;
    AST** variables_definitions;
    unsigned int variables_definitions_count;
};

Scope* initScope(Scope* parent);

void addStructToScope(Scope* scope, AST* struct_def);
AST* getStructFromScope(Scope* scope, char* struct_identifier);

void addFunctionToScope(Scope* scope, AST* function_def);
AST* getFunctionFromScope(Scope* scope, char* function_identifier);

void addVariableToScope(Scope* scope, AST* variable_def);
AST* getVariableFromScope(Scope* scope, char* variable_identifier);

#endif