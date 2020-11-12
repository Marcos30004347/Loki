#include "Scope.hpp"
#include "Lib/String.hpp"

#include "Structs.hpp"
#include "Buffer.hpp"
#include "Declarations.hpp"
#include "Types.hpp"

#include <stdio.h>

namespace GLSL {

Scope::Scope() {
    this->parent = nullptr;
    this->variables =  std::vector<AST*>();
    this->buffers = std::vector<AST*>();
    this->functions = std::vector<AST*>();
    this->types = std::vector<AST*>();
}

void Scope::addBufferDefinition(AST* buff) {
    this->buffers.push_back(buff);
}

void Scope::addTypeDeclaration(AST* buff) {
    this->types.push_back(buff);
}

void Scope::addFunctionDefinition(AST* fn) {
    this->functions.push_back(fn);
}

void Scope::addVariableDefinition(AST* var) {
    this->variables.push_back(var);
}

AST* Scope::getTypeDefinition(char* identifier) {
    for(int i = 0; i < this->types.size(); i++) {
        if(!static_cast<ASTTypeDecl*>(this->types[i])->type_name) {
        }
        if(strcmp(identifier, static_cast<ASTTypeDecl*>(this->types[i])->type_name) == 0) return this->types[i];
    }
    if(this->parent) return this->parent->getTypeDefinition(identifier);
    
    return nullptr;
}

AST* Scope::getFunctionDefinition(char* identifier) {
    for(int i = 0; i < this->functions.size(); i++) {
        // if(strcmp(identifier, static_cast<ASTFunctionDeclaration*>(this->functions[i])->func_decl_name) == 0) return this->functions[i];
    }
    
    if(this->parent) return this->getFunctionDefinition(identifier);
    
    return nullptr;
}

AST* Scope::getBufferDefinition(char* identifier) {
    for(int i = 0; i < this->buffers.size(); i++) {
        if(strcmp(identifier, static_cast<ASTBuffer*>(this->buffers[i])->name) == 0) return this->buffers[i];
    }
    
    if(this->parent) return this->parent->getBufferDefinition(identifier);
    
    return nullptr;
}

AST* Scope::getVariableDefinition(char* identifier) {
    for(int i = 0; i < this->variables.size(); i++) {
        // if(strcmp(identifier, static_cast<ASTVarDecl*>(this->variables[i])->var_decl_name) == 0) return this->variables[i];
    }
    
    for(int i = 0; i < this->buffers.size(); i++) {
        // for(int j = 0; j < static_cast<ASTBuffer*>(this->buffers[i])->buffer_fields.size(); j++) {
            // if(strcmp(identifier, static_cast<ASTVarDecl*>(static_cast<ASTBuffer*>(this->buffers[i])->buffer_fields[j])->var_decl_name) == 0)
            //     return static_cast<ASTVarDecl*>(static_cast<ASTBuffer*>(this->buffers[i])->buffer_fields[j]);
        // }
    }

    if(this->parent) return this->parent->getVariableDefinition(identifier);
    
    return nullptr;
}

}