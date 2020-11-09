#include "Variables.hpp"
#include "Expression.hpp"

namespace GLSL {

ASTVariableDeclaration::ASTVariableDeclaration(): AST { AST_VARIABLE_DECLARATION } {}

ASTVariableDeclaration* parseVariableDeclaration(Parser* parser) {
    ASTVariableDeclaration* var_decl = new ASTVariableDeclaration();
    
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
    var_decl->type = parseDeclarationBaseType(parser);
    
    // Parse Variable Name
    var_decl->name = parser->currentToken()->value;

    parser->readToken(Token::TOKEN_IDENTIFIER);

    if (parser->currentToken()->type == Token::TOKEN_OPEN_SQUARE_BRACKETS) {
        var_decl->is_array = true;
        parser->readToken(Token::TOKEN_OPEN_SQUARE_BRACKETS);
        if(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
            var_decl->array_size = parseExpression(parser);
        } else {
            var_decl->array_size = nullptr;
        }
        parser->readToken(Token::TOKEN_CLOSE_SQUARE_BRACKETS);
    }
    
    if (parser->currentToken()->type == Token::TOKEN_EQUAL) {
        parser->readToken(Token::TOKEN_EQUAL);
        var_decl->default_value = parseExpression(parser);
    }

    parser->readToken(Token::TOKEN_SEMICOLON);

    parser->scope->addVariableDefinition(var_decl);
    return var_decl;
}

}