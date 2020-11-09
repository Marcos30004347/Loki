#ifndef SCOPE_H
#define SCOPE_H

#include "AST.hpp"
#include <vector>

namespace GLSL {

class Scope {
    std::vector<AST*> variables;
    std::vector<AST*> structs;
    std::vector<AST*> buffers;
    std::vector<AST*> functions;

public:
    Scope* parent;
    Scope();

    void addStructDefinition(AST*); 
    void addFunctionDefinition(AST*); 
    void addBufferDefinition(AST*); 
    void addVariableDefinition(AST*); 

    AST* getStructDefinition(const char* identifier); 
    AST* getFunctionDefinition(const char* identifier); 
    AST* getBufferDefinition(const char* identifier); 
    AST* getVariableDefinition(const char* identifier); 
};

}

#endif
