#include "Structs.hpp"
#include "Lib/String.hpp"
#include "Expressions.hpp"

namespace GLSL {

// ASTStruct::ASTStruct(): AST{AST_STRUCT_DECLARATION} {}

ASTTypeDecl* parseStruct(Parser* parser) {
    ASTTypeDecl* type_decl = new ASTTypeDecl(false);
    type_decl->is_struct = true;

    // struct_decl->qualifier = parseStorageQualifier(parser);
    parser->readToken(Token::TOKEN_STRUCT);
    if(parser->currentToken()->value) {
        type_decl->type_name = parser->currentToken()->value;
        parser->readToken(Token::TOKEN_IDENTIFIER); 
    }
    parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS); 

    while(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
        AST* decl = parseDeclaration(parser);

        type_decl->members.push_back(decl);
    
        ASTFunctionDeclaration* func;
        ASTVarDecl* var;
    
        switch (decl->ast_type) {
        case NodeType::AST_FUNCTION_DECLARATION:
            func = static_cast<ASTFunctionDeclaration*>(decl);
            type_decl->members_names.push_back(func->func_decl_name);
            break;
        case NodeType::AST_VARIABLE_DECLARATION:
            var = static_cast<ASTVarDecl*>(decl);
            type_decl->members_names.push_back(var->name);
            break;
        }
    }

    parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS); 

    // if(parser->currentToken()->value) {
    //     // Fix post initialization
    //     struct_decl->declaration_name = parser->currentToken()->value; 
    //     ASTVarDecl* decl = new ASTVarDecl();
    //     decl->var_decl_type = type;

    //    if(parser->currentToken()->type == Token::TOKEN_EQUAL) {
    //         parser->readToken(Token::TOKEN_EQUAL);
    //         decl->default_value = parseExpression(parser);
    //     }

    //     parser->readToken(Token::TOKEN_IDENTIFIER); 
    // }
    parser->scope->addTypeDeclaration(type_decl);

    return type_decl;
}
}