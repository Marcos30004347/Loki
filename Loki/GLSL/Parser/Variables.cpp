#include "Variables.hpp"
#include "Expressions.hpp"
#include <stdio.h>
#include <stdlib.h>

namespace GLSL {

ASTVarDecl::ASTVarDecl(): AST { AST_VARIABLE_DECLARATION } {}


bool isVariableDeclaration(Parser* parser) {
    if(parser->currentToken()->type == Token::Type::TOKEN_OPEN_SQUARE_BRACKETS) {
        return false;
    }

    unsigned int index = parser->getTokenIndex();
    // Parse Layout Qualifiers
    parseLayoutQualifier(parser);

    // Parse Interpolation Qualifiers
    InterpolationQualifier q = parseInterpolationQualifier(parser);
    while(q != InterpolationQualifier::INTERPQUA_NONE) {
        InterpolationQualifier q = parseInterpolationQualifier(parser);
    }

    // Parse Storage Qualifiers
    parseStorageQualifier(parser);
    
    // Parse Precision Qualifier
    parsePrecisionQualifier(parser);
    parseType(parser);
    printf("==================  %s\n", parser->currentToken()->value);
    if(parser->currentToken()->type != Token::Type::TOKEN_IDENTIFIER) {
        parser->setTokenIndex(index);
        return false;
    }
    printf("==================  %s\n", parser->currentToken()->value);

    parser->readToken(Token::Type::TOKEN_IDENTIFIER);

    bool result = true;
    if(
        parser->currentToken()->type == Token::TOKEN_OPEN_PARENTESIS
    ) result = false;

    parser->setTokenIndex(index);
    return result;
}



ASTVarDecl* parseVarDecl(Parser* parser) {
    ASTVarDecl* var_decl = new ASTVarDecl();
    // Parse Layout Qualifiers
    var_decl->layout = parseLayoutQualifier(parser);

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
    var_decl->var_decl_type = parseType(parser);
    
    while(parser->currentToken()->type == Token::Type::TOKEN_OPEN_SQUARE_BRACKETS) {
        parser->readToken(Token::Type::TOKEN_OPEN_SQUARE_BRACKETS);
        var_decl->var_decl_dim_lenghts.push_back(parseExpression(parser));
        parser->readToken(Token::Type::TOKEN_CLOSE_SQUARE_BRACKETS);
    }
    

    // Parse Variable Name
    var_decl->name = parser->currentToken()->value;
    printf("Parsing Variable %s\n", parser->currentToken()->value);
    parser->readToken(Token::TOKEN_IDENTIFIER);


    printf("Parsing Variable %s\n", parser->currentToken()->value);

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