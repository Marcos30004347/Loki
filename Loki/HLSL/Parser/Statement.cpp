#include "Statement.hpp"
#include "Block.hpp"
#include "Expressions.hpp"
#include "FlowControl.hpp"

namespace HLSL {

ASTReturn::ASTReturn(): AST{NodeType::NODE_TYPE_RETURN_STATEMENT} {}

ASTReturn* parseReturn(Parser* parser) {
    ASTReturn* return_ast = new ASTReturn();
    if(parser->currentToken()->type != Token::TOKEN_SEMICOLON) {
        return_ast->return_expression = parseExpression(parser);
    }
    return return_ast;
}

AST* parseStatement(Parser* parser) {
    AST* statement = nullptr;

    // Variable Declaration
    if(isDeclaration(parser)) statement = parseVarDecl(parser);
    else switch (parser->currentToken()->type) {
        // FLow Controll
        case Token::TOKEN_IF: statement = parseIf(parser); break;
        case Token::TOKEN_FOR: statement = parseFor(parser); break;
        case Token::TOKEN_WHILE: statement = parseWhile(parser); break;
        case Token::TOKEN_DO: statement = parseDoWhile(parser); break;
        case Token::TOKEN_SWITCH: statement = parseSwitch(parser); break;
        case Token::TOKEN_BREAK:
            statement = parseBreak(parser); break;
            parser->readToken(Token::TOKEN_SEMICOLON);
            break;
        case Token::TOKEN_CONTINUE:
            statement = parseContinue(parser);
            parser->readToken(Token::TOKEN_SEMICOLON);
            break;
        case Token::TOKEN_DISCARD:
            statement = parseDiscard(parser);
            parser->readToken(Token::TOKEN_SEMICOLON);
            break;
        case Token::TOKEN_RETURN:
            statement = parseReturn(parser); break;
            parser->readToken(Token::TOKEN_SEMICOLON);
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