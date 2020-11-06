#include "Block.hpp"

namespace HLSL {
    
ASTBlock::ASTBlock(): AST{NodeType::NODE_TYPE_BLOCK} {}

ASTBlock* parseBlock(Parser* parser) {
    parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);
    parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);
}

}