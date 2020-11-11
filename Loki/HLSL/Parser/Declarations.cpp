#include "Declarations.hpp"
#include "Struct.hpp"
#include "Expressions.hpp"
#include "Evaluation.hpp"
#include "Block.hpp"

#include <stdio.h>
#include <cstdlib>
#include <cctype>

namespace HLSL {

ASTVarDecl::ASTVarDecl(): AST{NodeType::AST_VARIABLE_DECLARATION} {}
ASTFunctionDeclaration::ASTFunctionDeclaration(): AST{NodeType::AST_FUNCTION_DECLARATION} {}

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

    while(parser->currentToken()->type == Token::TOKEN_TWO_POINTS) {
        parser->readToken(Token::TOKEN_TWO_POINTS);
        InterpolationModifier modifier = parseInterpolationModifier(parser);
        if(modifier == InterpolationModifier::INTERPMOD_NONE) {
            argument->argument_semantic = parseSemantic(parser);
        }
        argument->argument_interpolation_modifier = modifier;
    }

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
    ASTVarDecl* declaration = new ASTVarDecl();
    ASTFunctionDeclaration* func_decl = new ASTFunctionDeclaration();
    func_decl->built_in = false;

    if(parser->currentToken()->type == Token::TOKEN_OPEN_SQUARE_BRACKETS) {
        parser->readToken(Token::TOKEN_OPEN_SQUARE_BRACKETS);
        FuncAttribute* att = new FuncAttribute();
        att->name = parser->currentToken()->value;
        parser->readToken(Token::TOKEN_IDENTIFIER);
        parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
        if(parser->currentToken()->type != Token::TOKEN_CLOSE_PARENTESIS) {
            att->paramenters.push_back(parseLiteral(parser));
            while(parser->currentToken()->type == Token::TOKEN_COMMA) {
                parser->readToken(Token::TOKEN_COMMA);
                att->paramenters.push_back(parseLiteral(parser));
            }
        }
        parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
        parser->readToken(Token::TOKEN_CLOSE_SQUARE_BRACKETS);
        func_decl->func_decl_attributes.push_back(att);
    }

    declaration->annotations = std::vector<Annotation*>(0);
    declaration->var_decl_pack_offset = nullptr;
    declaration->var_decl_register = nullptr;
    declaration->var_decl_semantic = nullptr;
    declaration->var_decl_default_value = nullptr;

    // Variable Storage Class
    StorageClass storage_class = parseStorageClass(parser);

    declaration->var_decl_storage_class = storage_class;
    func_decl->func_decl_storage_class = storage_class;

    declaration->var_decl_interpolation_modifier = parseInterpolationModifier(parser);
    TypeModifier type_modifier = parseTypeModifier(parser);
    declaration->var_decl_type_modifier = type_modifier;
    func_decl->func_decl_type_modifier = type_modifier;

    ASTType* type = parseType(parser);

    if(parser->currentToken()->type == Token::TOKEN_SEMICOLON) {

        parser->readToken(Token::TOKEN_SEMICOLON);
        delete declaration;
        delete func_decl;
        return type->type;
    }


    declaration->var_decl_type = type;
    func_decl->func_decl_return_type = type;

    // Variable name
    declaration->var_decl_name = parser->currentToken()->value;
    func_decl->func_decl_name = parser->currentToken()->value;

    parser->readToken(Token::Type::TOKEN_IDENTIFIER);

    if(parser->currentToken()->type == Token::TOKEN_OPEN_PARENTESIS) {
        // FUNCTION
        delete declaration; // delete variable declaration
        parseFunctionArguments(func_decl, parser);

        if(parser->currentToken()->type == Token::TOKEN_TWO_POINTS) {
            parser->readToken(Token::TOKEN_TWO_POINTS);
            func_decl->func_decl_semantic = parseSemantic(parser);
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
        // VARIABLE
        delete func_decl; // delete function declaration

        // Variable array
        while(parser->currentToken()->type == Token::Type::TOKEN_OPEN_SQUARE_BRACKETS) {
            if(declaration->var_decl_type->isArray()) {
                printf("ERROR: Array already defined in line '%i'\n", parser->currentToken()->line);
                exit(-1);
            }
            parser->readToken(Token::Type::TOKEN_OPEN_SQUARE_BRACKETS);
            declaration->var_decl_type->dimensions.push_back(parseExpression(parser, true));
            parser->readToken(Token::Type::TOKEN_CLOSE_SQUARE_BRACKETS);
        }

        // Variable PackOffset/Register/Semantic
        while(parser->currentToken()->type == Token::Type::TOKEN_TWO_POINTS) {

            parser->readToken(Token::Type::TOKEN_TWO_POINTS);
            switch (parser->currentToken()->type) {
            case Token::Type::TOKEN_PACKOFFSET:
                declaration->var_decl_pack_offset = parsePackOffset(parser);
                break;
            case Token::Type::TOKEN_REGISTER:
                declaration->var_decl_register = parseRegister(parser);
                break;
            default:
                declaration->var_decl_semantic = parseSemantic(parser);
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

                declaration->annotations.push_back(annotation);

            }
            parser->readToken(Token::Type::TOKEN_LESS);
        }

        if(parser->currentToken()->type == Token::TOKEN_EQUAL) {
            parser->readToken(Token::Type::TOKEN_EQUAL);

            declaration->var_decl_default_value = parseExpression(parser);
            declaration->var_decl_default_value->print();
            declaration->var_decl_type->print();
            printf("ACCEPT %i\n", declaration->var_decl_type->acceptTree(declaration->var_decl_default_value, parser));
            printf("============================\n");
        }

        // Variable Semicolon
        parser->readToken(Token::Type::TOKEN_SEMICOLON);

        // Add var decl to scope
        parser->scope->addVariableDefinition(declaration);

        return declaration;

    }
}

}
