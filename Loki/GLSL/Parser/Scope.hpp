#ifndef GLSL_SCOPE_H
#define GLSL_SCOPE_H

#include "AST.hpp"
#include <vector>

namespace GLSL {

class Scope {
    std::vector<AST*> variables;
    std::vector<AST*> buffers;
    std::vector<AST*> functions;
    std::vector<AST*> types;

public:
    Scope* parent;
    Scope();

    void addFunctionDefinition(AST*); 
    void addBufferDefinition(AST*); 
    void addVariableDefinition(AST*);
    void addTypeDeclaration(AST*); 

    AST* getTypeDefinition(char* identifier); 
    AST* getFunctionDefinition(char* identifier); 
    AST* getBufferDefinition(char* identifier); 
    AST* getVariableDefinition(char* identifier); 
};

}

#endif
