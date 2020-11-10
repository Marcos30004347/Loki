#include "Variables.hpp"
#include "Struct.hpp"
#include "Expressions.hpp"
#include "Evaluation.hpp"

#include <stdio.h>
#include <cstdlib>
#include <cctype>

namespace HLSL {

ASTVarDecl::ASTVarDecl(): AST{NodeType::AST_VARIABLE_DECLARATION} {}

StorageClass parseStorageClass(Parser* parser) {
    switch(parser->currentToken()->type) {
        case Token::Type::TOKEN_EXTERN:
            parser->readToken(Token::TOKEN_EXTERN);
            return StorageClass::STORAGECLASS_EXTERN;
        case Token::Type::TOKEN_NOINTERPOLATION:
            parser->readToken(Token::TOKEN_NOINTERPOLATION);
            return StorageClass::STORAGECLASS_NOINTERPOLATION;
        case Token::Type::TOKEN_PRECISE:
            parser->readToken(Token::TOKEN_PRECISE);
            return StorageClass::STORAGECLASS_PRECISE;
        case Token::Type::TOKEN_SHARED:
            parser->readToken(Token::TOKEN_SHARED);
            return StorageClass::STORAGECLASS_SHARED;
        case Token::Type::TOKEN_GROUPSHARED:
            parser->readToken(Token::TOKEN_GROUPSHARED);
            return StorageClass::STORAGECLASS_GROUPSHARED;
        case Token::Type::TOKEN_STATIC:
            parser->readToken(Token::TOKEN_STATIC);
            return StorageClass::STORAGECLASS_STATIC;
        case Token::Type::TOKEN_UNIFORM:
            parser->readToken(Token::TOKEN_UNIFORM);
            return StorageClass::STORAGECLASS_UNIFORM;
        case Token::Type::TOKEN_VOLATILE:
            parser->readToken(Token::TOKEN_VOLATILE);
            return StorageClass::STORAGECLASS_VOLATILE;
        case Token::Type::TOKEN_INLINE:
            parser->readToken(Token::TOKEN_INLINE);
            return StorageClass::STORAGECLASS_INLINE;
    }

    return StorageClass::STORAGECLASS_NONE;
}

TypeModifier parseTypeModifier(Parser* parser) {
    switch(parser->currentToken()->type) {
        case Token::Type::TOKEN_CONST:
            parser->readToken(Token::TOKEN_CONST);
            return TypeModifier::TYPEMODIFIER_CONST;
        case Token::Type::TOKEN_ROW_MAJOR:
            parser->readToken(Token::TOKEN_ROW_MAJOR);
            return TypeModifier::TYPEMODIFIER_ROW_MAJOR;
        case Token::Type::TOKEN_COLUMN_MAJORM:
            parser->readToken(Token::TOKEN_COLUMN_MAJORM);
            return TypeModifier::TYPEMODIFIER_COLUMN_MAJOR;
    }

    return TypeModifier::TYPEMODIFIER_NONE;
}



bool isVariableDeclaration(Parser* parser) {
    if(parser->currentToken()->type == Token::Type::TOKEN_OPEN_SQUARE_BRACKETS) {
        return false;
    }

    unsigned int index = parser->getTokenIndex();

    parseStorageClass(parser);
    parseTypeModifier(parser);
    parseType(parser);
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

    var_decl->annotations = std::vector<Annotation*>(0);
    var_decl->var_decl_pack_offset = nullptr;
    var_decl->var_decl_register = nullptr;
    var_decl->var_decl_semantic = nullptr;
    var_decl->var_decl_default_value = nullptr;

    // Variable Storage Class
    var_decl->var_decl_storage_class = parseStorageClass(parser);
    var_decl->var_decl_interpolation_modifier = parseInterpolationModifier(parser);

    // Variable Type Modifier
    var_decl->var_decl_type_modifier = parseTypeModifier(parser);

    // Variable type
    var_decl->var_decl_type = parseType(parser);

    // Variable name
    var_decl->var_decl_name = parser->currentToken()->value;
    parser->readToken(Token::Type::TOKEN_IDENTIFIER);

    // Variable array
    while(parser->currentToken()->type == Token::Type::TOKEN_OPEN_SQUARE_BRACKETS) {
        parser->readToken(Token::Type::TOKEN_OPEN_SQUARE_BRACKETS);
        var_decl->var_decl_dim_lenghts.push_back(parseExpression(parser, true));
        parser->readToken(Token::Type::TOKEN_CLOSE_SQUARE_BRACKETS);

    }

    // Variable PackOffset/Register/Semantic
    while(parser->currentToken()->type == Token::Type::TOKEN_TWO_POINTS) {

        parser->readToken(Token::Type::TOKEN_TWO_POINTS);
        switch (parser->currentToken()->type) {
        case Token::Type::TOKEN_PACKOFFSET:
            var_decl->var_decl_pack_offset = parsePackOffset(parser);
            break;
        case Token::Type::TOKEN_REGISTER:
            var_decl->var_decl_register = parseRegister(parser);
            break;
        default:
            var_decl->var_decl_semantic = parseSemantic(parser);
            break;
        }
    }

    if(parser->currentToken()->type == Token::Type::TOKEN_GREATER) {
        while(parser->currentToken()->type != Token::Type::TOKEN_LESS) {
            parser->readToken(Token::Type::TOKEN_GREATER);
            Annotation* annotation = new Annotation();
            annotation->annotation_type = parseType(parser);
            annotation->annotation_name = parser->currentToken()->value;
            parser->readToken(Token::Type::TOKEN_IDENTIFIER);
        
            annotation->annotation_value = parseLiteral(parser);
            
            parser->readToken(parser->currentToken()->type);
            
            parser->readToken(Token::Type::TOKEN_SEMICOLON);

            var_decl->annotations.push_back(annotation);

        }
        parser->readToken(Token::Type::TOKEN_LESS);
    }

    if(parser->currentToken()->type == Token::TOKEN_EQUAL) {
        parser->readToken(Token::Type::TOKEN_EQUAL);

        var_decl->var_decl_default_value = parseExpression(parser);
    }

    // Variable Semicolon
    parser->readToken(Token::Type::TOKEN_SEMICOLON);

    // Add var decl to scope
    parser->scope->addVariableDefinition(var_decl);

    return var_decl;
}

}
