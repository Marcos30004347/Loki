#ifndef SCOPE_H
#define SCOPE_H

#include "AST.hpp"
#include <vector>

namespace HLSL {

class Scope {
    std::vector<AST*> variables;
    std::vector<AST*> structs;
    std::vector<AST*> buffers;
    std::vector<AST*> functions;
    std::vector<AST*> types;

public:
    Scope* parent;
    Scope();

    void addStructDefinition(AST*); 
    void addFunctionDefinition(AST*); 
    void addBufferDefinition(AST*); 
    void addVariableDefinition(AST*);
    void addTypeDeclaration(AST*); 

    AST* getTypeDefinition(char* identifier); 
    AST* getStructDefinition(char* identifier); 
    AST* getFunctionDefinition(char* identifier); 
    AST* getBufferDefinition(char* identifier); 
    AST* getVariableDefinition(char* identifier); 
};

}

#endif
