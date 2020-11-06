
#include "Utils.hpp"

#include <string.h>
#include <stdlib.h>
#include <cstdio>


void parserReadToken(Parser* parser, Token::TokenType type) {
    if(parser->current_token->token_type == type) {
        parser->previous_token = parser->current_token;
        parser->current_token = lexerGetNextToken(parser->lexer);
    } else {
        printf("\033[31mUnexpected token \033[0m '%s', \033[31mExpecting \033[0m'%i'\033[31m!\033[0m\n", parser->current_token->value, type);
        exit(-1);
    }
}


void addStatement(AST* statements, AST* item) {
    statements->statements_list_count += 1;
    
    statements->statements_list = (AST**)realloc(
        statements->statements_list,
        statements->statements_list_count * sizeof(AST*)
    );
    
    statements->statements_list[ statements->statements_list_count - 1] = item;
}

void addDeclaration(AST* declarations, AST* declaration) {
    declarations->declarations_list_count += 1;
    
    declarations->declarations_list = (AST**)realloc(
        declarations->declarations_list,
        declarations->declarations_list_count * sizeof(AST*)
    );
    
    declarations->declarations_list[ declarations->declarations_list_count - 1] = declaration;
}


void addFuncCallArgument(AST* func_call, AST* argument) {
    func_call->func_call_arguments_count += 1;
    
    func_call->func_call_arguments = (AST**)realloc(
        func_call->func_call_arguments,
        func_call->func_call_arguments_count * sizeof(AST*)
    );
    
    func_call->func_call_arguments[ func_call->func_call_arguments_count - 1] = argument;
}

void addFuncDecArgument(AST* func_dec, AST* argument) {
    func_dec->func_dec_arguments_count += 1;
    
    func_dec->func_dec_arguments = (AST**)realloc(
        func_dec->func_dec_arguments,
        func_dec->func_dec_arguments_count * sizeof(AST*)
    );
    
    func_dec->func_dec_arguments[func_dec->func_dec_arguments_count - 1] = argument;
}



void addVariableDefinitions(AST* variables, AST* variable) {
    variables->vars_declarations_count += 1;
    
    variables->vars_declarations = (AST**)realloc(
        variables->vars_declarations,
        variables->vars_declarations_count * sizeof(AST*)
    );

    variables->vars_declarations[variables->vars_declarations_count - 1] = variable;

}


void addSwitchCase(AST* swtch, AST* cs) {
    swtch->switch_cases_count += 1;
    swtch->switch_cases = (AST**)realloc(
        swtch->switch_cases,
        swtch->switch_cases_count * sizeof(AST*)
    );
    swtch->switch_cases[swtch->switch_cases_count - 1] = cs;
}

char* copyString(const char* str) {
    if(!str) {
        char* copy = (char*)malloc(sizeof(char));
        copy[0] = '\0';
        return copy;
    }

    unsigned int size = strlen(str);
    char* copy = (char*)malloc(sizeof(char) * size);

    strcpy(copy, str);
    return copy;
}


char* getIdentifierString(AST* node) {
    return copyString(node->identifier);
}

char* append(char* a, const char* b) {
    char* fallback = new char[1];
    fallback[0] = '\0';
    return strcat(a ? a : fallback, b);
}

Type getTypeFromString(const char* type_id) {
    if(strcmp(type_id, "void") == 0) return Type::TYPE_VOID;
    if(strcmp(type_id, "int") == 0) return Type::TYPE_INT;
    if(strcmp(type_id, "uint") == 0) return Type::TYPE_UINT;
    if(strcmp(type_id, "float") == 0) return Type::TYPE_FLOAT;
    if(strcmp(type_id, "bool") == 0) return Type::TYPE_BOOL;
    if(strcmp(type_id, "vec2") == 0) return Type::TYPE_VEC2;
    if(strcmp(type_id, "vec3") == 0) return Type::TYPE_VEC3;
    if(strcmp(type_id, "vec4") == 0) return Type::TYPE_VEC4;
    if(strcmp(type_id, "mat2") == 0) return Type::TYPE_MAT2;
    if(strcmp(type_id, "mat2x2") == 0) return Type::TYPE_MAT2X2;
    if(strcmp(type_id, "mat2x3") == 0) return Type::TYPE_MAT2X3;
    if(strcmp(type_id, "mat2x4") == 0) return Type::TYPE_MAT2X4;
    if(strcmp(type_id, "mat3") == 0) return Type::TYPE_MAT3;
    if(strcmp(type_id, "mat3x2") == 0) return Type::TYPE_MAT3X2;
    if(strcmp(type_id, "mat3x3") == 0) return Type::TYPE_MAT3X3;
    if(strcmp(type_id, "mat3x4") == 0) return Type::TYPE_MAT3X4;
    if(strcmp(type_id, "mat4") == 0) return Type::TYPE_MAT4;
    if(strcmp(type_id, "mat4x2") == 0) return Type::TYPE_MAT4X2;
    if(strcmp(type_id, "mat4x3") == 0) return Type::TYPE_MAT4X3;
    if(strcmp(type_id, "mat4x4") == 0) return Type::TYPE_MAT4X4;
    return Type::TYPE_STRUCT; // Never reached
}

