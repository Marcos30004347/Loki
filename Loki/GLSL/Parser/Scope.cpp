#include "Scope.hpp"
#include "Lib/String.hpp"

#include "Struct.hpp"
#include "Variables.hpp"
#include "Functions.hpp"
#include "Buffer.hpp"

namespace GLSL {

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

    return nullptr;
}

AST* Scope::getFunctionDefinition(const char* identifier) {

    return nullptr;
}

AST* Scope::getBufferDefinition(const char* identifier) {

    return nullptr;
}

AST* Scope::getVariableDefinition(const char* identifier) {

    return nullptr;
}

}