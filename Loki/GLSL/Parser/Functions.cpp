#include "Functions.hpp"
#include "Expressions.hpp"
#include <stdio.h>
#include <cstdlib>
#include <cctype>

namespace GLSL {

Modifier parseModifier(Parser* parser) {
    Modifier modifier = Modifier::MODIFIER_NONE;
    switch (parser->currentToken()->type) {
    case Token::TOKEN_IN:
        modifier = Modifier::MODIFIER_IN;
        parser->readToken(Token::TOKEN_IN);
        break;
    case Token::TOKEN_INOUT:
        modifier = Modifier::MODIFIER_INOUT;
        parser->readToken(Token::TOKEN_INOUT);
        break;
    case Token::TOKEN_OUT:
        modifier = Modifier::MODIFIER_OUT;
        parser->readToken(Token::TOKEN_OUT);
        break;
    case Token::TOKEN_UNIFORM:
        modifier = Modifier::MODIFIER_UNIFORM;
        parser->readToken(Token::TOKEN_UNIFORM);
        break;
    default:
        break;
    }
    return modifier;
}

FunctionArgument* parseArgument(Parser* parser) {
    FunctionArgument* argument = new FunctionArgument();
    argument->argument_modifier = parseModifier(parser);
    argument->argument_type = parseType(parser);
    argument->argument_name = parser->currentToken()->value;
    parser->readToken(Token::TOKEN_IDENTIFIER);


    if(parser->currentToken()->type == Token::TOKEN_EQUAL) {
        parser->readToken(Token::TOKEN_EQUAL);
        argument->argument_initializer = parseExpression(parser);
    }

    return argument;
}

ASTFunctionDeclaration::ASTFunctionDeclaration() : AST{NodeType::AST_FUNCTION_DECLARATION} {}

ASTFunctionDeclaration* parseFunctionDeclaration(Parser* parser) {
    ASTFunctionDeclaration* func_decl = new ASTFunctionDeclaration();

    func_decl->built_in = false;
    func_decl->func_decl_return_type = parseType(parser);
    func_decl->func_decl_name = parser->currentToken()->value;

    parser->readToken(Token::TOKEN_IDENTIFIER);
    parser->readToken(Token::TOKEN_OPEN_PARENTESIS);

    if(parser->currentToken()->type != Token::TOKEN_CLOSE_PARENTESIS) {
        func_decl->func_decl_arguments.push_back(parseArgument(parser));
        while(parser->currentToken()->type == Token::TOKEN_COMMA) {
            parser->readToken(Token::TOKEN_COMMA);
            func_decl->func_decl_arguments.push_back(parseArgument(parser));
        }
    }

    parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);

    if(parser->currentToken()->type == Token::TOKEN_TWO_POINTS) {
        parser->readToken(Token::TOKEN_TWO_POINTS);
    }

    func_decl->func_decl_body = parseBlock(parser);
    
    // add func decl to scope
    parser->scope->addFunctionDefinition(func_decl);
    
    return func_decl;
}

}