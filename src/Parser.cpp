// https://craftinginterpreters.com/parsing-expressions.html

#include "Parser.hpp"

#include <string.h>
#include <stdlib.h>
#include <malloc.h>

void addToCompound(AST* compound, AST* item) {
    compound->compound_list_count += 1;
    
    compound->compound_list = (AST**)realloc(
        compound->compound_list,
        compound->compound_list_count * sizeof(AST)
    );
    
    compound->compound_list[ compound->compound_list_count - 1] = item;
}

Parser* initParser(Lexer* lexer, Scope* scope) {
    Parser* parser = (Parser*)malloc(sizeof(Parser));

    parser->lexer = lexer;
    parser->scope = scope;
    parser->token_stack = std::stack<Token*>();
    parser->previous_token = nullptr;
    parser->current_token = lexerGetNextToken(lexer);
    return parser;
}

template <typename T>
bool tokenMatchesTypes(Parser* parser,T t) {
    if(parser->current_token->token_type == t) {
        parser->previous_token = parser->current_token;
        parser->current_token = lexerGetNextToken(parser->lexer);
        return true;
    }
    return false;
}

template<typename T, typename... Args>
bool tokenMatchesTypes(Parser* parser, T t, Args... args) {
    if(parser->current_token->token_type == t) {
        parser->previous_token = parser->current_token;
        parser->current_token = lexerGetNextToken(parser->lexer);
        return true;
    }
    else return tokenMatchesTypes(parser, args...);
}



void parserReadToken(Parser* parser, Token::TokenType type) {
    if(parser->current_token->token_type == type) {
        parser->previous_token = parser->current_token;
        parser->current_token = lexerGetNextToken(parser->lexer);
    } else {
        printf("\033[32;1m Unexpected token \033[0m '%s'\n", parser->current_token->value);
        exit(-1);
    }
}


AST* parseStart(Parser* parser) {
    return parseExpression(parser, parser->scope);
}

// EXPRESSION → EQUALITY;
AST* parseExpression(Parser* parser, Scope* scope) {
    printf("Parsing Expression\n");
    return parseEquality(parser, scope);

}

// EQUALITY → COMPARISON (('!=' | '==') COMPARISON)*;      ex: 1 == 1 != 3 == 3;
AST* parseEquality(Parser* parser, Scope* scope) {
    printf("Parsing Equality\n");
    AST* root = parseComparison(parser, scope);

    while(tokenMatchesTypes(parser, 2, Token::TokenType::DIFFERENT, Token::TokenType::EQUALS_EQUALS)) {
        Token* operation = parser->previous_token;
    
        ExpOperation op;
    
        if(operation->token_type == Token::TokenType::DIFFERENT) {
            op = ExpOperation::DIFFERENT;
        } if(operation->token_type == Token::TokenType::EQUALS_EQUALS) {
            op = ExpOperation::EQUALS;
        }
    
        switch (operation->token_type) {
            case ExpOperation::EQUALS: op = ExpOperation::EQUALS; break;
            case ExpOperation::DIFFERENT: op = ExpOperation::DIFFERENT; break;
            default: printf("Unknow equality operator '%s'!\n", operation->value); exit(-1);
        }
    
        AST* right = parseComparison(parser, scope);

        AST* left = root;
    
        root = initAST(AST::ASTType::BINARY_EXPRESSION);
    
        root->binary_exp_left_operand = left;
        root->binary_exp_operation = op;
        root->binary_exp_right_operand = right;
    }
    printf("Parsed Equality!\n");

    return root;
}

// COMPARISON → TERM (('>' | '>=' | '<' | '<=') TERM)* ;
AST* parseComparison(Parser* parser, Scope* scope) {
    printf("Parsing Comparison\n");
    AST* root = parseTerm(parser, scope);

    while(tokenMatchesTypes(
        parser,
        Token::TokenType::LESS,
        Token::TokenType::GREATER,
        Token::TokenType::LESS_OR_EQUALS,
        Token::TokenType::GREATER_OR_EQUALS
    )) {
        Token* operation = parser->previous_token;
        ExpOperation op;
        switch (operation->token_type) {
            case ExpOperation::LESS: op = ExpOperation::LESS; break;
            case ExpOperation::GREATER: op = ExpOperation::GREATER; break;
            case ExpOperation::LESS_OR_EQUAL: op = ExpOperation::LESS_OR_EQUAL; break;
            case ExpOperation::GREATER_OR_EQUAL: op = ExpOperation::GREATER_OR_EQUAL; break;
            default: printf("Unknow comparison operator '%s'!\n", operation->value); exit(-1);
        }

        AST* right = parseTerm(parser, scope);

        AST* left = root;
    
        root = initAST(AST::ASTType::BINARY_EXPRESSION);
    
        root->binary_exp_left_operand = left;
        root->binary_exp_operation = op;
        root->binary_exp_right_operand = right;
    }
    printf("Parsed Comparison!\n");

    return root;
}

// TERM → FACTOR (('+' | '-') FACTOR)*;
AST* parseTerm(Parser* parser, Scope* scope) {
    printf("Parsing Term\n");

    AST* root = parseFactor(parser, scope);
    while(tokenMatchesTypes(
        parser,
        Token::TokenType::ADDITION,
        Token::TokenType::SUBTRACION
    )) {

        Token* operation = parser->previous_token;
        ExpOperation op;
        switch (operation->token_type) {
            case Token::TokenType::ADDITION: op = ExpOperation::ADDITION; break;
            case Token::TokenType::MINUS: op = ExpOperation::SUBTRACTION; break;
            default: printf("Unknow Term operator '%s'!\n", operation->value); exit(-1);
        }

        AST* right = parseFactor(parser, scope);

        AST* left = root;

        root = initAST(AST::ASTType::BINARY_EXPRESSION);

        root->binary_exp_left_operand = left;
        root->binary_exp_operation = op;
        root->binary_exp_right_operand = right;
    }
    printf("Parsed Term!\n");

    return root;
}

// FACTOR → UNARY (('/' | '*') UNARY)*;
AST* parseFactor(Parser* parser, Scope* scope) {
    printf("Parsing Factor...\n");

    AST* root = parseUnary(parser, scope);

    while(tokenMatchesTypes(
        parser,
        Token::TokenType::DIVISION,
        Token::TokenType::MULTIPLICATION
    )) {

        Token* operation = parser->previous_token;
        ExpOperation op;
        switch (operation->token_type) {
            case Token::TokenType::DIVISION: op = ExpOperation::DIVISION; break;
            case Token::TokenType::MULTIPLICATION: op = ExpOperation::MULTIPLICATION; break;
            default: printf("Unknow factor operator '%s'!\n", operation->value); exit(-1);
        }

        AST* right = parseUnary(parser, scope);

        AST* left = root;

        root = initAST(AST::ASTType::BINARY_EXPRESSION);

        root->binary_exp_left_operand = left;
        root->binary_exp_operation = op;
        root->binary_exp_right_operand = right;
    }

    printf("Parsed Factor!\n");

    return root;
}

// UNARY → ('!' | '-')UNARY | PRIMARY
AST* parseUnary(Parser* parser, Scope* scope) {
    printf("Parsing Unary...\n");

    while(tokenMatchesTypes(
        parser,
        Token::TokenType::MINUS,
        Token::TokenType::EXCLAMATION
    )) {
        UExOperation op;

        switch (parser->current_token->token_type) {
            case Token::TokenType::EXCLAMATION:
                op = UExOperation::EXCLAMATION;
                parserReadToken(parser, Token::TokenType::EXCLAMATION);
                break;
            case Token::TokenType::MINUS:
                op = UExOperation::MINUS;
                parserReadToken(parser, Token::TokenType::MINUS);
                break;
            default:
                printf("Unknow Unary operator '%s'!\n", parser->current_token->value);
                exit(-1);
                break;
        }
        AST* right_operand = parseUnary(parser, scope);
        AST* root = initAST(AST::ASTType::UNARY_EXPRESSION);
        root->unary_binary_exp_operation = op;
        root->unary_binary_exp_right_operand = right_operand;
        return root;
    }
    printf("Parsed Unary!\n");

    return parsePrimary(parser, scope);
}

// PRIMARY → NUMBER | STRING | 'true' | 'false' | 'nil | '('EXPRESSION')';
AST* parsePrimary(Parser* parser, Scope* scope) {
    printf("Parsing Primary\n");

    if(parser->current_token->token_type == Token::TokenType::IDENTIFIER) {
        if(strcmp(parser->current_token->value, "true") == 0 ) {
            printf("\033[32;1m Unsuported primary \033[0m '%s'\n", parser->current_token->value);
            exit(-1);
        } else
        if(strcmp(parser->current_token->value, "false") == 0 ) {
            printf("\033[32;1m Unsuported primary \033[0m '%s'\n", parser->current_token->value);
            exit(-1);
        } else
        if(strcmp(parser->current_token->value, "nil") == 0 ) {
            printf("\033[32;1m Unsuported primary \033[0m '%s'\n", parser->current_token->value);
            exit(-1);
        }
    }

    if(parser->current_token->token_type == Token::TokenType::INTEGER) {
        AST* root = initAST(AST::ASTType::INTEGER);
        root->integer_value = atoi(parser->current_token->value);
        parserReadToken(parser, Token::TokenType::INTEGER);
        printf("Parsed Primary as Integer!\n");

        return root;
    }

    if(parser->current_token->token_type == Token::TokenType::OPEN_PARENTESIS) {
        parserReadToken(parser, Token::TokenType::OPEN_PARENTESIS);
        AST* exp = parseExpression(parser, scope);
        parserReadToken(parser, Token::TokenType::CLOSE_PARENTESIS);
        printf("Parsed Primary as Group!\n");

        return exp;
    }

    printf("\033[32;1m Unsuported primary \033[0m '%s'\n", parser->current_token->value);
    exit(-1);
    return nullptr;
}