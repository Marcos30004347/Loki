#include "Scope.hpp"
#include "Lib/String.hpp"

#include "Struct.hpp"
#include "Variables.hpp"
#include "Functions.hpp"
#include "Buffer.hpp"
#include <stdio.h>
namespace HLSL {

Scope::Scope() {
    this->parent = nullptr;
    this->variables =  std::vector<AST*>();
    this->structs = std::vector<AST*>();
    this->buffers = std::vector<AST*>();
    this->functions = std::vector<AST*>();
}

void Scope::addBufferDefinition(AST* buff) {
    this->buffers.push_back(buff);
}

void Scope::addStructDefinition(AST* st) {
    this->structs.push_back(st);
}

void Scope::addFunctionDefinition(AST* fn) {
    this->functions.push_back(fn);
}

void Scope::addVariableDefinition(AST* var) {
    this->variables.push_back(var);
}

AST* Scope::getStructDefinition(const char* identifier) {
    for(int i = 0; i < this->structs.size(); i++) {
        if(strcmp(identifier, static_cast<ASTStruct*>(this->structs[i])->struct_identifier) == 0) return this->structs[i];
    }

    if(this->parent) return this->getStructDefinition(identifier);
    
    return nullptr;
}

AST* Scope::getFunctionDefinition(const char* identifier) {
    for(int i = 0; i < this->functions.size(); i++) {
        if(strcmp(identifier, static_cast<ASTFunctionDeclaration*>(this->functions[i])->func_decl_name) == 0) return this->functions[i];
    }
    
    if(this->parent) return this->getFunctionDefinition(identifier);
    
    return nullptr;
}

AST* Scope::getBufferDefinition(const char* identifier) {
    for(int i = 0; i < this->buffers.size(); i++) {
        if(strcmp(identifier, static_cast<ASTBuffer*>(this->buffers[i])->buffer_name) == 0) return this->buffers[i];
    }
    
    if(this->parent) return this->getBufferDefinition(identifier);
    
    return nullptr;
}

AST* Scope::getVariableDefinition(const char* identifier) {
    for(int i = 0; i < this->variables.size(); i++) {
        if(strcmp(identifier, static_cast<ASTVarDecl*>(this->variables[i])->var_decl_name) == 0) return this->variables[i];
    }
    
    for(int i = 0; i < this->buffers.size(); i++) {
        for(int j = 0; j < static_cast<ASTBuffer*>(this->buffers[i])->buffer_fields.size(); j++) {
            if(strcmp(identifier, static_cast<ASTVarDecl*>(static_cast<ASTBuffer*>(this->buffers[i])->buffer_fields[j])->var_decl_name) == 0)
                return static_cast<ASTVarDecl*>(static_cast<ASTBuffer*>(this->buffers[i])->buffer_fields[j]);
        }
    }


    if(this->parent) return this->getVariableDefinition(identifier);
    
    return nullptr;
}

}