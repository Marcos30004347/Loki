#include "Declarations.hpp"
#include "Expressions.hpp"
#include "Block.hpp"
#include <stdio.h>
#include <stdlib.h>

namespace GLSL {

ASTVarDecl::ASTVarDecl(): AST { AST_VARIABLE_DECLARATION } {}
ASTFunctionDeclaration::ASTFunctionDeclaration(): AST{AST_FUNCTION_DECLARATION} {}

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


void parseFunctionArguments(ASTFunctionDeclaration* func_decl, Parser* parser) {
    parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
    if(parser->currentToken()->type != Token::TOKEN_CLOSE_PARENTESIS) {
        func_decl->func_decl_arguments.push_back(parseArgument(parser));
        while(parser->currentToken()->type == Token::TOKEN_COMMA) {
            parser->readToken(Token::TOKEN_COMMA);
            func_decl->func_decl_arguments.push_back(parseArgument(parser));
        }
    }
    parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
}


AST* parseDeclaration(Parser* parser) {
    ASTVarDecl* var_decl = new ASTVarDecl();
    ASTFunctionDeclaration* func_decl = new ASTFunctionDeclaration();

    // Parse Layout Qualifiers
    var_decl->layout = parseLayoutQualifier(parser);
    func_decl->built_in = false;

    // Parse Interpolation Qualifiers
    var_decl->interpolation_qualifiers.push_back(parseInterpolationQualifier(parser));
    while(var_decl->interpolation_qualifiers.back() != InterpolationQualifier::INTERPQUA_NONE) {
        var_decl->interpolation_qualifiers.push_back(parseInterpolationQualifier(parser));
    }

    // Parse Storage Qualifiers
    var_decl->storage_qualifier = parseStorageQualifier(parser);
    
    // Parse Precision Qualifier
    var_decl->precision_qualifier = parsePrecisionQualifier(parser);

    // Parse Variable Type
    ASTType* type = parseType(parser);

    if(parser->currentToken()->type == Token::TOKEN_SEMICOLON) {

        parser->readToken(Token::TOKEN_SEMICOLON);
        delete func_decl;
        delete var_decl;
        return type->type;
    }

    var_decl->var_decl_type = type;
    
    while(parser->currentToken()->type == Token::Type::TOKEN_OPEN_SQUARE_BRACKETS) {
        parser->readToken(Token::Type::TOKEN_OPEN_SQUARE_BRACKETS);
        type->dimensions.push_back(parseExpression(parser));
        parser->readToken(Token::Type::TOKEN_CLOSE_SQUARE_BRACKETS);
    }
    

    // Parse Variable Name
    var_decl->name = parser->currentToken()->value;
    func_decl->func_decl_name = parser->currentToken()->value;
    parser->readToken(Token::TOKEN_IDENTIFIER);

    if(parser->currentToken()->type == Token::TOKEN_OPEN_PARENTESIS) {
        // FUNCTION
        delete var_decl; // delete variable declaration
        parseFunctionArguments(func_decl, parser);

        if(parser->currentToken()->type == Token::TOKEN_TWO_POINTS) {
            parser->readToken(Token::TOKEN_TWO_POINTS);
        }

        if(parser->currentToken()->type == Token::TOKEN_OPEN_CURLY_BRACKETS) {
            func_decl->func_decl_body = parseBlock(parser);
        } else {
            parser->readToken(Token::TOKEN_SEMICOLON);
        }
    
        // add func decl to scope
        parser->scope->addFunctionDefinition(func_decl);
        return func_decl;
    } else {
        delete func_decl;
        if(parser->currentToken()->type == Token::Type::TOKEN_OPEN_SQUARE_BRACKETS && var_decl->var_decl_dim_lenghts.size()) {
            printf("Error: size of array already defined previous to variable name '%s' at line '%i'\n", var_decl->name, parser->currentToken()->line);
        }

        // Variable array
        while(parser->currentToken()->type == Token::Type::TOKEN_OPEN_SQUARE_BRACKETS) {
            parser->readToken(Token::Type::TOKEN_OPEN_SQUARE_BRACKETS);
            var_decl->var_decl_dim_lenghts.push_back(parseExpression(parser));
            parser->readToken(Token::Type::TOKEN_CLOSE_SQUARE_BRACKETS);
            printf("%s\n", parser->currentToken()->value);
        }
        
        printf("Parsing Variable\n");
        if (parser->currentToken()->type == Token::TOKEN_EQUAL) {
            parser->readToken(Token::TOKEN_EQUAL);
            var_decl->default_value = parseExpression(parser);
        }

        parser->readToken(Token::TOKEN_SEMICOLON);
        printf("Parsing Variable\n");

        parser->scope->addVariableDefinition(var_decl);
        return var_decl;
    }
}

}