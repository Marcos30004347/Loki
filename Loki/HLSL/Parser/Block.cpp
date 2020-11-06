#include "Block.hpp"
#include "Statement.hpp"

namespace HLSL {
    
ASTBlock::ASTBlock(): AST{NodeType::NODE_TYPE_BLOCK} {}

ASTBlock* parseBlock(Parser* parser) {
    ASTBlock* block = new ASTBlock();
    parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);
    while(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
        block->block_statements.push_back(parseStatement(parser));
    }
    parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);
}

}