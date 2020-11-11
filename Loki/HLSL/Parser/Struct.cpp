#include "Struct.hpp"
#include "Expressions.hpp"
#include "Lib/String.hpp"
#include <stdlib.h>
#include <stdio.h>
namespace HLSL {


// ASTStruct::ASTStruct(): AST{NodeType::AST_STRUCT_DECLARATION} {}


ASTTypeDecl* parseStruct(Parser* parser) {
    // ASTStruct* struct_decl = new ASTStruct();

    ASTTypeDecl* type_decl = new ASTTypeDecl(false);

    // type_decl->struct_declaration = struct_decl; // set reference to the struct declaration
    type_decl->is_struct = true;
    type_decl->build_in = false;

    parser->readToken(Token::TOKEN_STRUCT);

    if(parser->currentToken()->type == Token::TOKEN_IDENTIFIER) {
        
        // struct_decl->struct_identifier = parser->currentToken()->value;
        type_decl->type_name = parser->currentToken()->value;

        parser->readToken(Token::TOKEN_IDENTIFIER);
    }

    parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);
    
    while(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
        AST* declaration = parseDeclaration(parser);
        type_decl->members.push_back(declaration);

        ASTFunctionDeclaration* func;
        ASTVarDecl* var;
        // ASTStruct* struct_decl;

        switch (declaration->ast_type) {
            case NodeType::AST_FUNCTION_DECLARATION:
                func = static_cast<ASTFunctionDeclaration*>(declaration);
                type_decl->members_names.push_back(func->func_decl_name);
                break;
            case NodeType::AST_VARIABLE_DECLARATION:
                var = static_cast<ASTVarDecl*>(declaration);
                type_decl->members_names.push_back(var->var_decl_name);
                break;
            // case NodeType::AST_STRUCT_DECLARATION:
            //     struct_decl = static_cast<ASTStruct*>(declaration);
            //     type_decl->members_names.push_back(struct_decl->struct_identifier);
            //     break;
        }
    }

    parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);

    // if(parser->currentToken()->type == Token::TOKEN_IDENTIFIER) {
    //     // Post initialization
    //     ASTVarDecl* decl = new ASTVarDecl();
    //     ASTType* type = new ASTType(type_decl);
    
    //     decl->var_decl_type = type;

    //     // struct_decl->struct_declarator = parser->currentToken()->value;

    //     parser->readToken(Token::TOKEN_IDENTIFIER);

    //     if(parser->currentToken()->type == Token::TOKEN_EQUAL) {
    //         parser->readToken(Token::TOKEN_EQUAL);
    //         decl->var_decl_default_value = parseExpression(parser);
    //     }
    
    //     parser->readToken(Token::TOKEN_SEMICOLON);
    //     parser->scope->addVariableDefinition(decl);
    // }

    // struct_decl->struct_type = type_decl;

    parser->scope->addTypeDeclaration(type_decl);
    // parser->scope->addStructDefinition(struct_decl);
    return type_decl;
}

}