#include "Buffer.hpp"

namespace GLSL {

// ASTBuffer::ASTBuffer(): AST{AST_BUFFER_DECLARATION} {}

// ASTBuffer* parseBuffer(Parser* parser) {
//     ASTBuffer* buffer = new ASTBuffer();

//     parser->readToken(Token::TOKEN_BUFFER);
//     buffer->name = parser->currentToken()->value;    
//     parser->readToken(Token::TOKEN_IDENTIFIER); 
//     parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS); 
//     while(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
//         buffer->members.push_back(parseDeclaration(parser));
//     }

//     parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS); 

//     buffer->extern_name = parser->currentToken()->value;

//     parser->readToken(Token::TOKEN_IDENTIFIER); 
//     parser->readToken(Token::TOKEN_SEMICOLON); 

//     return buffer;
// }
}