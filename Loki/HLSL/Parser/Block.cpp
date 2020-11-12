#include "Block.hpp"
#include "Statement.hpp"

namespace HLSL {
    
ASTBlock::ASTBlock(): AST{NodeType::AST_BLOCK} {}

ASTBlock* parseBlock(Parser* parser) {
    ASTBlock* block = new ASTBlock();
    parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);

    Scope* tmp = parser->scope;

    parser->scope = new Scope();
    parser->scope->parent = tmp;

    while(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
        block->block_statements.push_back(parseStatement(parser));
    }

    delete parser->scope;
    parser->scope = tmp;

    parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);
    return block;
}

}