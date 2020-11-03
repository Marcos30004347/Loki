#ifndef PARSER_UTILS
#define PARSER_UTILS

#include "Parser/Parser.hpp"
#include "Translator/GLES2Translator.hpp"

#include <string.h>
#include <stdlib.h>
#include <cstdio>

template <typename T>
bool tokenMatchesTypes(Parser* parser,T t) {
    if(parser->current_token->token_type == t) {
        parser->previous_token = parser->current_token;
        parser->current_token = lexerGetNextToken(parser->lexer);
        return true;
    }
    return false;
}

template<typename T, typename... Args>
bool tokenMatchesTypes(Parser* parser, T t, Args... args) {
    if(parser->current_token->token_type == t) {
        parser->previous_token = parser->current_token;
        parser->current_token = lexerGetNextToken(parser->lexer);
        return true;
    }
    else return tokenMatchesTypes(parser, args...);
}

void addShaderAttribute(Shader* shader, char* attribute_str);
bool isASTStatement(AST* root);
void parserReadToken(Parser* parser, Token::TokenType type);
void addStatement(AST* statements, AST* item);
void addDeclaration(AST* declarations, AST* declaration);
void addFuncCallArgument(AST* func_call, AST* argument);
void addFuncDecArgument(AST* func_dec, AST* argument);
void addVariableDefinitions(AST* variables, AST* variable);
void addSwitchCase(AST* swtch, AST* cs);
char* copyString(const char* str);

#endif
