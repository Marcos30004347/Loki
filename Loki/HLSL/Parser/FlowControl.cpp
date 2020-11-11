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
    parser->readToken(Token::TOKEN_SEMICOLON);
    return do_while_ast;
}


ASTBreak* parseBreak(Parser* parser) {
    ASTBreak* break_ast = new ASTBreak();
    parser->readToken(Token::TOKEN_BREAK);
    parser->readToken(Token::TOKEN_SEMICOLON);
    return break_ast;
}

ASTContinue* parseContinue(Parser* parser) {
    ASTContinue* continue_ast = new ASTContinue();
    parser->readToken(Token::TOKEN_CONTINUE);
    parser->readToken(Token::TOKEN_SEMICOLON);
    return continue_ast;
}

ASTDiscard* parseDiscard(Parser* parser) {
    ASTDiscard* discard_ast = new ASTDiscard();
    parser->readToken(Token::TOKEN_DISCARD);
    parser->readToken(Token::TOKEN_SEMICOLON);
    return discard_ast;
}

ASTFor* parseFor(Parser* parser) {


    ASTFor* for_ast = new ASTFor();
    parser->readToken(Token::TOKEN_FOR);
    parser->readToken(Token::TOKEN_OPEN_PARENTESIS);

    if(parser->currentToken()->type != Token::TOKEN_SEMICOLON) {
        if(parser->scope->getTypeDefinition(parser->currentToken()->value))
            for_ast->for_init_statement = parseDeclaration(parser);        
        else {
            for_ast->for_init_statement = parseExpression(parser);
            parser->readToken(Token::TOKEN_SEMICOLON);
        }
    }

    if(parser->currentToken()->type != Token::TOKEN_SEMICOLON) {
        if(parser->scope->getTypeDefinition(parser->currentToken()->value))
            for_ast->for_cond_expression = parseDeclaration(parser);
        else {
            for_ast->for_cond_expression = parseExpression(parser);
            parser->readToken(Token::TOKEN_SEMICOLON);
        }
    }

    if(parser->currentToken()->type != Token::TOKEN_SEMICOLON) 
        if(!parser->scope->getTypeDefinition(parser->currentToken()->value))
            for_ast->for_loop_expression = parseExpression(parser);
        else {
            printf("Error: Type name is no allowed in line %i\n", parser->currentToken()->line);
            exit(-1);
        }

    parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);

    for_ast->for_body_statement = parseStatement(parser);

    return for_ast;
}


void addSwitchCase(ASTSwitch* s, Parser* parser) {
    std::vector<ASTCase*> cases;
    
    unsigned int last_case_line = 0;
    while(parser->currentToken()->type == Token::TOKEN_CASE) {
        last_case_line = parser->currentToken()->line;
    
        cases.push_back(new ASTCase());
        parser->readToken(Token::TOKEN_CASE);
        cases.back()->case_expression = parseExpression(parser);
        parser->readToken(Token::TOKEN_TWO_POINTS);
    }

    std::vector<AST*> statements;
    while(parser->currentToken()->type != Token::TOKEN_BREAK && parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
        while(parser->currentToken()->type == Token::TOKEN_CASE) {
            parser->readToken(Token::TOKEN_CASE);
            AST* expression = parseExpression(parser);
            delete expression;
            parser->readToken(Token::TOKEN_TWO_POINTS);
            printf("Warning: Case label in line %i jumps to line %i\n", last_case_line, parser->currentToken()->line);
        }
    
        while(parser->currentToken()->type == Token::TOKEN_DEFAULT) {
            parser->readToken(Token::TOKEN_DEFAULT);
            parser->readToken(Token::TOKEN_TWO_POINTS);
            printf("Warning: Default label in line %i jumps to line %i\n", last_case_line, parser->currentToken()->line);
        }
    
        statements.push_back(parseStatement(parser));
    }

    if(parser->currentToken()->type == Token::TOKEN_BREAK) {
        statements.push_back(parseBreak(parser));
    }

    for(int i=0; i<cases.size(); i++) {
        cases[i]->case_statements = statements;
        s->switch_case_statements.push_back(cases[i]);
    }
}

void addSwitchDefault(ASTSwitch* s, Parser* parser) {
    std::vector<ASTDefault*> cases;
    
    unsigned int last_case_line = 0;
    while(parser->currentToken()->type == Token::TOKEN_DEFAULT) {
        last_case_line = parser->currentToken()->line;
        cases.push_back(new ASTDefault());
        parser->readToken(Token::TOKEN_DEFAULT);
        parser->readToken(Token::TOKEN_TWO_POINTS);
    }

    std::vector<AST*> statements;
    while(parser->currentToken()->type != Token::TOKEN_BREAK && parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
        while(parser->currentToken()->type == Token::TOKEN_CASE) {
            parser->readToken(Token::TOKEN_CASE);
            AST* exp = parseExpression(parser);
            delete exp;
            parser->readToken(Token::TOKEN_TWO_POINTS);
            printf("Warning: Default label in line %i jumps to line %i\n", last_case_line, parser->currentToken()->line);
        }

        while(parser->currentToken()->type == Token::TOKEN_DEFAULT) {
            parser->readToken(Token::TOKEN_DEFAULT);
            parser->readToken(Token::TOKEN_TWO_POINTS);
            printf("Warning: Default label in line %i jumps to line %i\n", last_case_line, parser->currentToken()->line);
        }


        statements.push_back(parseStatement(parser));
    }
    if(parser->currentToken()->type == Token::TOKEN_BREAK) {
        statements.push_back(parseBreak(parser));
    }

    for(int i=0; i<cases.size(); i++) {
        cases[i]->default_statements = statements;
        s->swtich_default = cases[i];
    }
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
            addSwitchCase(switch_ast, parser);
            break;
        case Token::TOKEN_DEFAULT:
            addSwitchDefault(switch_ast, parser);
            break;
        default:
            printf("Invalid statement %s inside switch in line %i\n", parser->currentToken()->value, parser->currentToken()->line);
            exit(-1);
            break;
        }
    }

    parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);
    return switch_ast;
}


}