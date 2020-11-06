#include "ShaderConstants.hpp"

namespace HLSL {

ASTBuffer::ASTBuffer(ASTBuffer::Type type): AST{NodeType::NODE_TYPE_BUFFER_DECLARATION} {
    this->buffer_type = type;
}

// BUFFER -> BufferType IDENTIFIER? (':' REGISTER)? '{' VARIABLE_DECLARATION* '}'';'
ASTBuffer* parseBuffer(Parser* parser) {
    ASTBuffer::Type type;
    if(parser->currentToken()->type == Token::TOKEN_CBUFFER) {
        parser->readToken(Token::TOKEN_CBUFFER);
        type = ASTBuffer::Type::CONSTANT;
    } else {
        parser->readToken(Token::TOKEN_TBUFFER);
        type = ASTBuffer::Type::TEXTURE;
    }
    ASTBuffer* buff = new ASTBuffer(type);

    if(parser->currentToken()->type == Token::TOKEN_IDENTIFIER) {
        buff->buffer_name = parser->currentToken()->value;
        parser->readToken(Token::TOKEN_IDENTIFIER);
    } else {
        buff->buffer_name = new char[1];
        buff->buffer_name[0] = '\0';
    }

    if(parser->currentToken()->type == Token::TOKEN_TWO_POINTS) {
        parser->readToken(Token::TOKEN_TWO_POINTS);
        buff->buffer_register = parseRegister(parser);
    } else {
        buff->buffer_register = nullptr;
    }

    parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);

    while (parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
        buff->buffer_fields.push_back(parseVarDecl(parser));
    }
    
    parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);
    parser->readToken(Token::TOKEN_SEMICOLON);
    return buff;
}

}