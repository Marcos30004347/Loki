#include "Declarations.hpp"
#include "Expressions.hpp"
#include "Block.hpp"
#include <stdio.h>
#include <stdlib.h>

namespace GLSL {

ASTVarDecl::ASTVarDecl(): AST { AST_VARIABLE_DECLARATION } {}
ASTFunctionDeclaration::ASTFunctionDeclaration(): AST{AST_FUNCTION_DECLARATION} {}
ASTBuffer::ASTBuffer(): AST{AST_BUFFER_DECLARATION} {}

// Modifier parseModifier(Parser* parser) {
//     Modifier modifier = Modifier::MODIFIER_NONE;
//     switch (parser->currentToken()->type) {
//     case Token::TOKEN_IN:
//         modifier = Modifier::MODIFIER_IN;
//         parser->readToken(Token::TOKEN_IN);
//         break;
//     case Token::TOKEN_INOUT:
//         modifier = Modifier::MODIFIER_INOUT;
//         parser->readToken(Token::TOKEN_INOUT);
//         break;
//     case Token::TOKEN_OUT:
//         modifier = Modifier::MODIFIER_OUT;
//         parser->readToken(Token::TOKEN_OUT);
//         break;
//     default:
//         break;
//     }
//     return modifier;
// }


FunctionArgument* parseArgument(Parser* parser) {
    FunctionArgument* argument = new FunctionArgument();
    argument->argument_modifier = parseStorageQualifier(parser);
    argument->argument_type = parseType(parser);

    if(parser->currentToken()->type == Token::TOKEN_IDENTIFIER) {
        argument->argument_name = parser->currentToken()->value;
        parser->readToken(Token::TOKEN_IDENTIFIER);
        if(parser->currentToken()->type == Token::TOKEN_EQUAL) {
            parser->readToken(Token::TOKEN_EQUAL);
            argument->argument_initializer = parseExpression(parser);
        }
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
    ASTBuffer* buff_decl = new ASTBuffer();

    var_decl->is_build_in = false;

    // Parse Layout Qualifiers
    ASTLayout* layout = parseLayoutQualifier(parser);
    var_decl->layout = layout;
    buff_decl->layout = layout;

    func_decl->built_in = false;

    // Parse Interpolation Qualifiers
    var_decl->interpolation_qualifiers.push_back(parseInterpolationQualifier(parser));
    while(var_decl->interpolation_qualifiers.back() != InterpolationQualifier::INTERPQUA_NONE) {
        var_decl->interpolation_qualifiers.push_back(parseInterpolationQualifier(parser));
    }

    // Parse Storage Qualifiers
    ASTStorageQualifiers* qualifier =  parseStorageQualifier(parser);
    var_decl->storage_qualifier = qualifier;
    buff_decl->storage_qualifier = qualifier;

    if(parser->currentToken()->type == Token::TOKEN_SEMICOLON) {
        parser->readToken(Token::TOKEN_SEMICOLON);
        /********************************************************
        *********************** LAYOUT **************************
        *********************************************************/
        // Global Layout
        delete func_decl;
        delete var_decl;
        delete buff_decl;
    
        return layout;
    }

    // Parse Precision Qualifier
    var_decl->precision_qualifier = parsePrecisionQualifier(parser);
    if(parser->currentToken()->type == Token::TOKEN_BUFFER) {
        parser->readToken(Token::TOKEN_SEMICOLON);
        /*********************************************************
         *********************** BUFFER **************************
         *********************************************************/
        parser->readToken(Token::TOKEN_BUFFER);
        buff_decl->name = parser->currentToken()->value;    
        parser->readToken(Token::TOKEN_IDENTIFIER); 
        parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS); 
        while(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
            buff_decl->members.push_back(parseDeclaration(parser));
        }

        parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS); 

        buff_decl->extern_name = parser->currentToken()->value;

        parser->readToken(Token::TOKEN_IDENTIFIER); 
        parser->readToken(Token::TOKEN_SEMICOLON); 
        delete func_decl;
        delete var_decl;

        parser->scope->addBufferDefinition(buff_decl);

        return buff_decl;
    }
    // Parse Variable Type
    ASTType* type = parseType(parser);

    if(parser->currentToken()->type == Token::TOKEN_SEMICOLON) {
        parser->readToken(Token::TOKEN_SEMICOLON);
        /*********************************************************
         *********************** STRUCT **************************
         *********************************************************/
        delete func_decl;
        delete var_decl;
        delete buff_decl;

        return type->type;
    }
    func_decl->func_decl_return_type = type;
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
        /*********************************************************
         *********************** FUNCTION ************************
         *********************************************************/
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
        /*********************************************************
         *********************** VARIABLE ************************
         *********************************************************/
        delete func_decl;

        if(parser->currentToken()->type == Token::Type::TOKEN_OPEN_SQUARE_BRACKETS && var_decl->var_decl_dim_lenghts.size()) {
            printf("Error: size of array already defined previous to variable name '%s' at line '%i'\n", var_decl->name, parser->currentToken()->line);
            exit(-1);
        }

        // Variable array
        while(parser->currentToken()->type == Token::Type::TOKEN_OPEN_SQUARE_BRACKETS) {
            parser->readToken(Token::Type::TOKEN_OPEN_SQUARE_BRACKETS);
            if(parser->currentToken()->type != Token::TOKEN_CLOSE_SQUARE_BRACKETS)
                var_decl->var_decl_type->dimensions.push_back(parseExpression(parser));
            else 
                var_decl->var_decl_type->dimensions.push_back(nullptr);
            parser->readToken(Token::Type::TOKEN_CLOSE_SQUARE_BRACKETS);
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

}