#include "Structs.hpp"

namespace GLSL {

ASTStruct::ASTStruct(): AST{AST_STRUCT_DECLARATION} {}

ASTStruct* parseStruct(Parser* parser) {
    ASTStruct* struct_decl = new ASTStruct();
    struct_decl->qualifier = parseStorageQualifier(parser);
    parser->readToken(Token::TOKEN_STRUCT);
    if(parser->currentToken()->value) {
        struct_decl->name = parser->currentToken()->value;    
        parser->readToken(Token::TOKEN_IDENTIFIER); 
    }
    parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS); 
    while(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
        struct_decl->members.push_back(parseVariableDeclaration(parser));
    }
    parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS); 

    if(parser->currentToken()->value) {
        // Fix post initialization
        struct_decl->declaration_name = parser->currentToken()->value;    
        parser->readToken(Token::TOKEN_IDENTIFIER); 
    }
    parser->readToken(Token::TOKEN_SEMICOLON); 
    return struct_decl;
}
}