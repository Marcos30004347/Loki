#include "Statement.hpp"
#include "Block.hpp"
#include "Expressions.hpp"
#include "FlowControl.hpp"

namespace GLSL {

ASTReturn::ASTReturn(): AST{NodeType::AST_RETURN_STATEMENT} {}

ASTReturn* parseReturn(Parser* parser) {
    ASTReturn* return_ast = new ASTReturn();
    parser->readToken(Token::TOKEN_RETURN);

    if(parser->currentToken()->type != Token::TOKEN_SEMICOLON) {
        return_ast->return_expression = parseExpression(parser);
    }

    parser->readToken(Token::TOKEN_SEMICOLON);
    return return_ast;
}

AST* parseStatement(Parser* parser) {
    AST* statement = nullptr;
    while(parser->currentToken() && parser->currentToken()->type == Token::TOKEN_SEMICOLON) parser->readToken(Token::TOKEN_SEMICOLON);
    
    // Variable Declaration
    if(parser->scope->getTypeDefinition(parser->currentToken()->value)) statement = parseDeclaration(parser);
    else switch (parser->currentToken()->type) {
        // FLow Controll
        case Token::TOKEN_OPEN_CURLY_BRACKETS:
            statement = parseBlock(parser); break;
            break;
        case Token::TOKEN_IF: statement = parseIf(parser); break;
        case Token::TOKEN_FOR: statement = parseFor(parser); break;
        case Token::TOKEN_WHILE: statement = parseWhile(parser); break;
        case Token::TOKEN_DO: statement = parseDoWhile(parser); break;
        case Token::TOKEN_SWITCH: statement = parseSwitch(parser); break;
        case Token::TOKEN_BREAK:
            statement = parseBreak(parser); break;
            break;
        case Token::TOKEN_CONTINUE:
            statement = parseContinue(parser);
            break;
        case Token::TOKEN_DISCARD:
            statement = parseDiscard(parser);
            break;
        case Token::TOKEN_RETURN:
            statement = parseReturn(parser);
            break;
        
        // Expresssion
        default:
            statement = parseExpression(parser); 
            parser->readToken(Token::TOKEN_SEMICOLON);
            break;
    }

    return statement;
}

}