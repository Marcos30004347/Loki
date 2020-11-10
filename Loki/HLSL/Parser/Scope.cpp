#include "Scope.hpp"
#include "Lib/String.hpp"

#include "Struct.hpp"
#include "Buffer.hpp"
#include "Variables.hpp"
#include "Functions.hpp"

#include <stdio.h>

namespace HLSL {

Scope::Scope() {
    this->parent = nullptr;
    this->variables =  std::vector<AST*>();
    this->structs = std::vector<AST*>();
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

void Scope::addStructDefinition(AST* st) {
    this->structs.push_back(st);
}

void Scope::addFunctionDefinition(AST* fn) {
    this->functions.push_back(fn);
}

void Scope::addVariableDefinition(AST* var) {
    this->variables.push_back(var);
}

AST* Scope::getStructDefinition(char* identifier) {
    for(int i = 0; i < this->structs.size(); i++) {
        if(strcmp(identifier, static_cast<ASTStruct*>(this->structs[i])->struct_identifier) == 0) return this->structs[i];
    }

    if(this->parent) return this->getStructDefinition(identifier);
    
    return nullptr;
}


AST* Scope::getTypeDefinition(char* identifier) {
    for(int i = 0; i < this->types.size(); i++) {
        if(!static_cast<ASTType*>(this->types[i])->type_name) {
        }
        if(strcmp(identifier, static_cast<ASTType*>(this->types[i])->type_name) == 0) return this->types[i];
    }

    if(this->parent) return this->getTypeDefinition(identifier);
    
    return nullptr;
}

AST* Scope::getFunctionDefinition(char* identifier) {
    for(int i = 0; i < this->functions.size(); i++) {
        if(strcmp(identifier, static_cast<ASTFunctionDeclaration*>(this->functions[i])->func_decl_name) == 0) {
            ASTFunctionDeclaration* decl = static_cast<ASTFunctionDeclaration*>(this->functions[i]);
            // if(decl->func_decl_arguments.size() != arguments.size()) continue;

            // for(int j = 0; j < decl->func_decl_arguments.size(); j++) {
            //     if(decl->func_decl_arguments[j] ->argument_type != arguments[j]) {
            //         decl = nullptr;
            //         break;
            //     }
            // }
            if(decl) return decl;
        }
    }
    
    if(this->parent) return this->getFunctionDefinition(identifier);
    
    return nullptr;
}

AST* Scope::getBufferDefinition(char* identifier) {
    for(int i = 0; i < this->buffers.size(); i++) {
        if(strcmp(identifier, static_cast<ASTBuffer*>(this->buffers[i])->buffer_name) == 0) return this->buffers[i];
    }
    
    if(this->parent) return this->getBufferDefinition(identifier);
    
    return nullptr;
}

AST* Scope::getVariableDefinition(char* identifier) {
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