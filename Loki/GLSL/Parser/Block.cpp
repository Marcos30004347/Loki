#include "Block.hpp"

namespace GLSL {

ASTBlockDeclaration::ASTBlockDeclaration(): AST{AST_BLOCK_DECLARATION} {}

ASTBlockDeclaration* parseBlock(Parser* parser) {
    ASTBlockDeclaration* block_decl = new ASTBlockDeclaration();
    
    // Parse Layout Qualifiers
    block_decl->layout = parseLayoutQualifier(parser);

    // Parse Storage Qualifiers
    block_decl->storage_qualifier = parseStorageQualifier(parser);
    
    parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);

    while(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
        block_decl->members.push_back(parseVariableDeclaration(parser));
    }

    parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);

    if(parser->currentToken()->type == Token::TOKEN_IDENTIFIER) {
        block_decl->instance_name = parser->currentToken()->value;
        parser->readToken(Token::TOKEN_IDENTIFIER);
        parser->readToken(Token::TOKEN_SEMICOLON);
    }

    return block_decl;
}

}