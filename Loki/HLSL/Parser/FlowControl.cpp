#include "FlowControl.hpp"
#include <stdio.h>
#include <stdlib.h>

namespace HLSL {

ASTIf::ASTIf(): AST{NodeType::AST_IF_STATEMENT} {}
ASTWhile::ASTWhile(): AST{NodeType::AST_WHILE_STATEMENT} {}
ASTDoWhile::ASTDoWhile(): AST{NodeType::AST_DO_WHILE_STATEMENT} {}
ASTBreak::ASTBreak(): AST{NodeType::AST_BREAK_STATEMENT} {}
ASTContinue::ASTContinue(): AST{NodeType::AST_CONTINUE_STATEMENT} {}
ASTDiscard::ASTDiscard(): AST{NodeType::AST_DISCARD_STATEMENT} {}
ASTCase::ASTCase(): AST{NodeType::AST_CASE_STATEMENT} {}
ASTSwitch::ASTSwitch(): AST{NodeType::AST_SWITCH_STATEMENT} {}
ASTFor::ASTFor(): AST{NodeType::AST_FOR_STATEMENT} {}
ASTDefault::ASTDefault(): AST{NodeType::AST_DEFAULT_STATEMENT} {}

ASTIf* parseIf(Parser* parser) {
    ASTIf* if_ast = new ASTIf();
    parser->readToken(Token::TOKEN_IF);
    parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
    if_ast->if_expression = parseExpression(parser);
    parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
    if_ast->if_statement = parseStatement(parser);
    if(parser->currentToken()->type == Token::TOKEN_ELSE) {
        parser->readToken(Token::TOKEN_ELSE);
        if_ast->if_else = parseStatement(parser);
    }
    return if_ast;
}

ASTWhile* parseWhile(Parser* parser) {
    ASTWhile* while_ast = new ASTWhile();
    parser->readToken(Token::TOKEN_WHILE);
    parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
    while_ast->while_expression = parseExpression(parser);
    parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
    while_ast->while_statement = parseStatement(parser);
    return while_ast;
}

ASTDoWhile* parseDoWhile(Parser* parser) {
    ASTDoWhile* do_while_ast = new ASTDoWhile();
    parser->readToken(Token::TOKEN_DO);
    do_while_ast->do_while_statement = parseStatement(parser);
    parser->readToken(Token::TOKEN_WHILE);
    parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
    do_while_ast->do_while_expression = parseExpression(parser);
    parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
    return do_while_ast;
}


ASTBreak* parseBreak(Parser* parser) {
    ASTBreak* break_ast = new ASTBreak();
    parser->readToken(Token::TOKEN_BREAK);
    return break_ast;
}

ASTContinue* parseContinue(Parser* parser) {
    ASTContinue* continue_ast = new ASTContinue();
    parser->readToken(Token::TOKEN_CONTINUE);
    return continue_ast;
}

ASTDiscard* parseDiscard(Parser* parser) {
    ASTDiscard* discard_ast = new ASTDiscard();
    parser->readToken(Token::TOKEN_DISCARD);
    return discard_ast;
}

ASTFor* parseFor(Parser* parser) {


    ASTFor* for_ast = new ASTFor();
    parser->readToken(Token::TOKEN_FOR);
    parser->readToken(Token::TOKEN_OPEN_PARENTESIS);

    if(parser->currentToken()->type != Token::TOKEN_SEMICOLON)
        if(isDeclaration(parser)) for_ast->for_init_statement = parseVarDecl(parser);
        else for_ast->for_init_statement = parseExpression(parser);
    parser->readToken(Token::TOKEN_SEMICOLON);

    if(parser->currentToken()->type != Token::TOKEN_SEMICOLON)
        if(isDeclaration(parser)) for_ast->for_cond_expression = parseVarDecl(parser);
        else for_ast->for_cond_expression = parseExpression(parser);
    parser->readToken(Token::TOKEN_SEMICOLON);

    if(parser->currentToken()->type != Token::TOKEN_SEMICOLON) 
        if(!isDeclaration(parser)) for_ast->for_loop_expression = parseExpression(parser);
        else {
            printf("Error: Type name is no allowed in line %i\n", parser->currentToken()->line);
            exit(-1);
        }
    parser->readToken(Token::TOKEN_SEMICOLON);

    parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);

    for_ast->for_body_statement = parseStatement(parser);

    return for_ast;
}

ASTCase* parseCase(Parser* parser) {
    unsigned int line = parser->currentToken()->line;

    ASTCase* case_ast = new ASTCase();
    parser->readToken(Token::TOKEN_CASE);

    case_ast->case_expression = parseExpression(parser, true);
    parser->readToken(Token::TOKEN_TWO_POINTS);

    while(
        parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS
        && parser->currentToken()->type != Token::TOKEN_BREAK
    ) {
        if(
            parser->currentToken()->type == Token::TOKEN_CASE
            || parser->currentToken()->type == Token::TOKEN_DEFAULT
        ) {
            printf("Case statement of line '%u' jumps to case statement of line '%u'!\n", line, parser->currentToken()->line);
        }
        case_ast->case_statements.push_back(parseStatement(parser));
    }

    if(parser->currentToken()->type == Token::TOKEN_BREAK) {
        parser->readToken(Token::TOKEN_BREAK);
    } else {
        printf("No Break statement found for case statement in line '%u'!\n", line);
    }
    return case_ast;
}



ASTDefault* parseDefault(Parser* parser) {
    unsigned int line = parser->currentToken()->line;

    ASTDefault* default_ast = new ASTDefault();
    parser->readToken(Token::TOKEN_CASE);

    parser->readToken(Token::TOKEN_TWO_POINTS);

    while(
        parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS
        && parser->currentToken()->type != Token::TOKEN_BREAK
    ) {
        if(
            parser->currentToken()->type == Token::TOKEN_CASE
            || parser->currentToken()->type == Token::TOKEN_DEFAULT
        ) {
            printf("Case statement of line '%u' jumps to case statement of line '%u'!\n", line, parser->currentToken()->line);
        }
        default_ast->default_statements.push_back(parseStatement(parser));
    }

    if(parser->currentToken()->type == Token::TOKEN_BREAK) {
        parser->readToken(Token::TOKEN_BREAK);
    } else {
        printf("No Break statement found for default statement in line '%u'!\n", line);
    }
    return default_ast;
}

ASTSwitch* parseSwitch(Parser* parser) {
    ASTSwitch* switch_ast = new ASTSwitch();
    parser->readToken(Token::TOKEN_SWITCH);
    parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
    switch_ast->switch_expression = parseExpression(parser);
    parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
    parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);


    while(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
        switch (parser->currentToken()->type) {
        case Token::TOKEN_CASE:
            switch_ast->switch_case_statements.push_back(parseCase(parser));
            break;
        case Token::TOKEN_DEFAULT:
            break;
            switch_ast->swtich_default = parseDefault(parser);
        default:
            printf("Invalid statement inside switch in line %i\n", parser->currentToken()->line);
            parseStatement(parser);
            break;
        }
    }

    parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);
    return switch_ast;
}

}