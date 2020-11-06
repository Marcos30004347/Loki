#include "Statement.hpp"
#include "Block.hpp"
#include "Expressions.hpp"
#include "FlowControl.hpp"


namespace HLSL {

AST* parseStatement(Parser* parser) {
    AST* statement = nullptr;
    switch (parser->currentToken()->type) {
        case Token::TOKEN_IF: statement = parseIf(parser); break;
        case Token::TOKEN_FOR: statement = parseFor(parser); break;
        case Token::TOKEN_WHILE: statement = parseWhile(parser); break;
        case Token::TOKEN_BREAK: statement = parseBreak(parser); break;
        case Token::TOKEN_CONTINUE: statement = parseContinue(parser); break;
        case Token::TOKEN_DISCARD: statement = parseDiscard(parser); break;
        case Token::TOKEN_DO: statement = parseDoWhile(parser); break;
        case Token::TOKEN_SWITCH: statement = parseSwitch(parser); break;
        default: statement = parseExpression(parser); break;
    }

    parser->readToken(Token::TOKEN_SEMICOLON);
    return statement;
}

}