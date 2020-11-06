#include "Variables.hpp"
#include <stdio.h>
#include <cstdlib>
#include <cctype>

namespace HLSL {

ASTVarDecl::ASTVarDecl(): AST{NodeType::NODE_TYPE_VARIABLE_DECLARATION} {}

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



ASTVarDecl* parseVarDecl(Parser* parser) {
    ASTVarDecl* var_decl = new ASTVarDecl();
    var_decl->annotations = std::vector<Annotation*>(0);
    var_decl->var_decl_pack_offset = nullptr;
    var_decl->var_decl_register = nullptr;
    var_decl->var_decl_semantic = nullptr;
    var_decl->var_decl_default_value = nullptr;

    // Variable Storage Class
    var_decl->var_decl_storage_class = parseStorageClass(parser);

    // Variable Type Modifier
    var_decl->var_decl_type_modifier = parseTypeModifier(parser);

    // Variable type
    var_decl->var_decl_type = parseBaseType(parser);

    // Variable name
    var_decl->var_decl_name = parser->currentToken()->value;
    parser->readToken(Token::Type::TOKEN_IDENTIFIER);

    // Variable array
    if(parser->currentToken()->type == Token::Type::TOKEN_OPEN_SQUARE_BRACKETS) {
        parser->readToken(Token::Type::TOKEN_OPEN_SQUARE_BRACKETS);
        var_decl->var_decl_is_array = true;
        var_decl->var_decl_array_size = atoi(parser->currentToken()->value);
        parser->readToken(Token::Type::TOKEN_INT_LITERAL);
        parser->readToken(Token::Type::TOKEN_CLOSE_SQUARE_BRACKETS);

    } else {
        var_decl->var_decl_is_array = false;
        var_decl->var_decl_array_size = 1;
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
            annotation->annotation_type = parseBaseType(parser);
            annotation->annotation_name = parser->currentToken()->value;
            parser->readToken(Token::Type::TOKEN_IDENTIFIER);
        
            annotation->annotation_value = parseLiteral(parser, var_decl->var_decl_type);
            
            parser->readToken(parser->currentToken()->type);
            
            parser->readToken(Token::Type::TOKEN_SEMICOLON);

            var_decl->annotations.push_back(annotation);

        }
        parser->readToken(Token::Type::TOKEN_LESS);
    }

    if(parser->currentToken()->type == Token::TOKEN_EQUAL) {
        parser->readToken(Token::Type::TOKEN_EQUAL);

        if(var_decl->var_decl_is_array) {
            var_decl->var_decl_default_value = parseLiteralList(
                parser,
                var_decl->var_decl_type,
                var_decl->var_decl_array_size
            );
        } else {
            var_decl->var_decl_default_value = (Literal**)malloc(sizeof(Literal*)*var_decl->var_decl_array_size);
            var_decl->var_decl_default_value[0] = parseLiteral(parser, var_decl->var_decl_type);
        }
    }

    // Variable Semicolon
    parser->readToken(Token::Type::TOKEN_SEMICOLON);

    return var_decl;
}

}
