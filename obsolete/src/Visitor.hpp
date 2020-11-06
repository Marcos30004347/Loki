#ifndef VISITOR
#define VISITOR

#include "Shader.hpp"
#include "AST.hpp"
#include "Scope.hpp"



struct Visitor {
    Scope* global_scope;
    Scope* current_scope;

    // GLES shaders
    Shader* gles_vertex_shader;
    Shader* gles_fragment_shader;
};

Visitor* initVisitor();
void visitDeclarations(Visitor* visitor, AST* node);
void visitFunctionDeclaration(Visitor* visitor, AST* node);
void visitFunctionArgumentsDeclaration(Visitor* visitor, AST* node);
void visitVariableDeclaration(Visitor* visitor, AST* node);



#endif