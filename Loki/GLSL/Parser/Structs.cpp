#include "Structs.hpp"
#include "Lib/String.hpp"
#include "Expression.hpp"

namespace GLSL {

ASTStruct::ASTStruct(): AST{AST_STRUCT_DECLARATION} {}

int last = 0;

ASTStruct* parseStruct(Parser* parser) {
    ASTStruct* struct_decl = new ASTStruct();
    ASTType* struct_type = new ASTType(std::to_string(last++).c_str(), false);
    struct_decl->qualifier = parseStorageQualifier(parser);
    parser->readToken(Token::TOKEN_STRUCT);
    if(parser->currentToken()->value) {
        struct_decl->name = parser->currentToken()->value;    
        struct_type->type_name = parser->currentToken()->value;
        parser->readToken(Token::TOKEN_IDENTIFIER); 
    }
    parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS); 

    while(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
        ASTVarDecl* decl = parseVariableDeclaration(parser);
        struct_decl->members.push_back(decl);
        struct_type->members.push_back(decl->var_decl_type);
    }

    parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS); 

    if(parser->currentToken()->value) {
        // Fix post initialization
        struct_decl->declaration_name = parser->currentToken()->value; 
        ASTVarDecl* decl = new ASTVarDecl();
        decl->var_decl_type = struct_type;

       if(parser->currentToken()->type == Token::TOKEN_EQUAL) {
            parser->readToken(Token::TOKEN_EQUAL);
            decl->default_value = parseExpression(parser);
        }

        parser->readToken(Token::TOKEN_IDENTIFIER); 
    }
    parser->readToken(Token::TOKEN_SEMICOLON); 
    parser->scope->addTypeDeclaration(struct_type);
    return struct_decl;
}
}