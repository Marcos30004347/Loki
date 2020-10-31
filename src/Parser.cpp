// https://craftinginterpreters.com/parsing-expressions.html

#include "Parser.hpp"

#include <string.h>
#include <stdlib.h>
#include <malloc.h>

void addStatement(AST* statements, AST* item) {
    statements->statements_list_count += 1;
    
    statements->statements_list = (AST**)realloc(
        statements->statements_list,
        statements->statements_list_count * sizeof(AST*)
    );
    
    statements->statements_list[ statements->statements_list_count - 1] = item;
}

bool isIdentifier(Token* tok) {
    if(strcmp(tok->value, "int") == 0) return false;
    if(strcmp(tok->value, "void") == 0) return false;

    return true;
}   

void increaseVariableDefinitions(AST* variables) {
    variables->vars_def_count += 1;
    
    variables->vars_def_name = (char**)realloc(
        variables->vars_def_name,
        variables->vars_def_count * sizeof(char*)
    );

    variables->vars_def_value = (AST**)realloc(
        variables->vars_def_value,
        variables->vars_def_count * sizeof(AST*)
    );
}
AST* getTypeDefaultValue(BuildInType type) {
    AST* default_value = nullptr; 

    switch (type) {
        case BuildInType::TYPE_INT:
            default_value = initAST(AST::ASTType::INTEGER);
            default_value->integer_value = 0;
            return default_value;
        case BuildInType::TYPE_VOID:
            return default_value;
        default: break;
    }

    printf("\033[31mNo default value for type '%i'!\033[0m\n", type);
    exit(-1);

    return nullptr;
}

void addVariableDefinitionName(AST* variables, char* name) {
    variables->vars_def_name[ variables->vars_def_count - 1] = name;
}

void addVariableDefinitionValue(AST* variables, AST* value) {
    variables->vars_def_value[ variables->vars_def_count - 1] = value;
}

BuildInType getTypeFromId(const char* type_id) {
    if(strcmp(type_id, "int") == 0) return BuildInType::TYPE_INT;
    if(strcmp(type_id, "void") == 0) return BuildInType::TYPE_VOID;

    printf("\033[31mUnexpected type '%s'!\033[m\n", type_id);
    exit(-1);
    return BuildInType::TYPE_VOID; // Never reached
}

char* copyString(const char* str) {
    unsigned int size = strlen(str);
    char* copy = new char[size + 1];
    strcpy(copy, str);
    copy[size] = '\0';
    return copy;
}

Parser* initParser(Lexer* lexer) {
    Parser* parser = (Parser*)malloc(sizeof(Parser));

    parser->lexer = lexer;
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
        printf("\033[31mUnexpected token \033[0m '%s', \033[31mExpecting \033[0m'%i'\033[31m!\033[0m\n", parser->current_token->value, type);
        exit(-1);
    }
}

// PROGRAM → STATEMENT* EOF
AST* parseStart(Parser* parser) {
    AST* root = initAST(AST::ASTType::STATEMETNS);

    while(parser->current_token->token_type != Token::TokenType::TOKEN_EOF) {
        AST* statement = parseDeclaration(parser);
        addStatement(root, statement);
    }

    return root;
}

// DECLARATION → VAR_DECL | STATEMENT;
AST* parseDeclaration(Parser* parser) {
    printf("Parsing Declaration...\n");

    printf("ASDASDASDA\n");
    if(parser->current_token->token_type == Token::TokenType::IDENTIFIER && !isIdentifier(parser->current_token)) {
        AST* var_decl = parseVariableDeclaration(parser);
        printf("Parsed Statement!\n");
        return var_decl;
    }

    AST* statement = parseStatement(parser);

    printf("Parsed Declaration!\n");
    return statement;
}

// STATEMENT → EXPRESSION_STATEMENT | BLOCK
AST* parseStatement(Parser* parser) {
    printf("Parsing Statement...\n");

    if(parser->current_token->token_type == Token::TokenType::OPEN_BRACKET) {
        AST* block = parseBlock(parser);
        printf("Parsed Statement!\n");
        return block;
    }

    AST* exp_sttmnt = parseExpressionStatement(parser);
    printf("Parsed Statement!\n");
    return exp_sttmnt;
}

// BLOCK → '{' DECLARATION '}'
AST* parseBlock(Parser* parser) {
    AST* block = initAST(AST::ASTType::BLOCK);

    parserReadToken(parser, Token::TokenType::OPEN_BRACKET);
    block->block_statements = parseDeclaration(parser);
    parserReadToken(parser, Token::TokenType::CLOSE_BRACKET);
    return block;
}

// VAR_DECL → TYPE (IDENTIFIER ('=' EXPRESSION)?) (IDENTIFIER ('=' EXPRESSION)?,)* ';'
AST* parseVariableDeclaration(Parser* parser) {
    printf("Parsing Variable Definition...\n");

    AST* variables_definitions = initAST(AST::ASTType::VARIABLES_DECLARATIONS);

    char* type_id = copyString(parser->current_token->value);
    parserReadToken(parser, Token::TokenType::IDENTIFIER);
    char* id = copyString(parser->current_token->value);
    parserReadToken(parser, Token::TokenType::IDENTIFIER);

    variables_definitions->vars_def_type = getTypeFromId(type_id);

    increaseVariableDefinitions(variables_definitions);
    addVariableDefinitionName(variables_definitions, id);


    if(parser->current_token->token_type == Token::TokenType::EQUALS) {
        parserReadToken(parser, Token::TokenType::EQUALS);
        addVariableDefinitionValue(variables_definitions, parseExpression(parser));
    } else {
        addVariableDefinitionValue(variables_definitions, getTypeDefaultValue(variables_definitions->vars_def_type));
    }


    while(parser->current_token->token_type == Token::TokenType::COMMA) {
        printf("Parsed Compound Variable Definition!\n");
        parserReadToken(parser, Token::TokenType::COMMA);

        char* id = copyString(parser->current_token->value);
        parserReadToken(parser, Token::TokenType::IDENTIFIER);
    
        increaseVariableDefinitions(variables_definitions);
        addVariableDefinitionName(variables_definitions, id);


        if(parser->current_token->token_type == Token::TokenType::EQUALS) {
            parserReadToken(parser, Token::TokenType::EQUALS);
            addVariableDefinitionValue(variables_definitions, parseExpression(parser));
        } else {
            addVariableDefinitionValue(variables_definitions, getTypeDefaultValue(variables_definitions->vars_def_type));
        }
    }

    parserReadToken(parser, Token::TokenType::SEMICOLON);
    
    printf("Parsed Variable Definition!\n");
    return variables_definitions;
}

// EXPRESSION_STATEMENT → EXPRESSION';'
AST* parseExpressionStatement(Parser* parser) {
    AST* expression = parseExpression(parser);
    parserReadToken(parser, Token::TokenType::SEMICOLON);
    return expression;
}

// EXPRESSION → ASSIGNMENT;
AST* parseExpression(Parser* parser) {
    printf("Parsing Expression...\n");
    AST* assignment = parseAssignment(parser);
    printf("Parsed Expression!\n");
    return assignment;
}

// ASSIGNMENT → IDENTIFIER '=' ASSIGNMENT | EQUALITY
AST* parseAssignment(Parser* parser) {
    printf("Parsing Assignment...\n");
    
    AST* root = parseEquality(parser);

    while(parser->current_token->token_type == Token::TokenType::EQUALS) {
        parserReadToken(parser, Token::TokenType::EQUALS);
        AST* left = root;

        if(root->type != AST::ASTType::IDENTIFIER) {
            printf("\033[33mWARNING: First operand of assignment isn't a identifier!\033[0m\n");
        }

        AST* right = parseAssignment(parser);
       
        root = initAST(AST::ASTType::ASSIGNMENT);
       
        root->assignment_left = left;
        root->assignment_right = right;
    }

    printf("Parsed Assignment!\n");
    return root;
}

// EQUALITY → COMPARISON (('!=' | '==') COMPARISON)*;      ex: 1 == 1 != 3 == 3;
AST* parseEquality(Parser* parser) {
    printf("Parsing Equality\n");
    AST* root = parseComparison(parser);

    while(tokenMatchesTypes(parser, 2, Token::TokenType::DIFFERENT, Token::TokenType::EQUALS_EQUALS)) {
        Token* operation = parser->previous_token;
    
        BinaryOperation op;
    
        switch (operation->token_type) {
            case Token::TokenType::EQUALS_EQUALS: op = BinaryOperation::EQUALS_EQUALS; break;
            case Token::TokenType::DIFFERENT: op = BinaryOperation::DIFFERENT; break;
            default: printf("\033[1mERROR: Unknow equality operator '%s'!\033[0m\n", operation->value); exit(-1);
        }
    
        AST* right = parseComparison(parser);

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
AST* parseComparison(Parser* parser) {
    printf("Parsing Comparison\n");
    AST* root = parseTerm(parser);

    while(tokenMatchesTypes(
        parser,
        Token::TokenType::LESS,
        Token::TokenType::GREATER,
        Token::TokenType::LESS_OR_EQUALS,
        Token::TokenType::GREATER_OR_EQUALS
    )) {
        Token* operation = parser->previous_token;
        BinaryOperation op;
        switch (operation->token_type) {
            case Token::TokenType::LESS: op = BinaryOperation::LESS; break;
            case Token::TokenType::GREATER: op = BinaryOperation::GREATER; break;
            case Token::TokenType::LESS_OR_EQUALS: op = BinaryOperation::LESS_OR_EQUAL; break;
            case Token::TokenType::GREATER_OR_EQUALS: op = BinaryOperation::GREATER_OR_EQUAL; break;
            default: printf("\033[1mERROR: Unknow comparison operator '%s'!\033[0m\n", operation->value); exit(-1);
        }

        AST* right = parseTerm(parser);

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
AST* parseTerm(Parser* parser) {
    printf("Parsing Term\n");

    AST* root = parseFactor(parser);

    while(tokenMatchesTypes(
        parser,
        Token::TokenType::ADDITION,
        Token::TokenType::SUBTRACION
    )) {
    
    
        Token* operation = parser->previous_token;
        BinaryOperation op;
        switch (operation->token_type) {
            case Token::TokenType::ADDITION: op = BinaryOperation::ADDITION; break;
            case Token::TokenType::SUBTRACION: op = BinaryOperation::SUBTRACTION; break;
            default: printf("\033[1mERROR: Unknow Term operator '%s'!\033[0m\n", operation->value); exit(-1);
        }


        AST* right = parseFactor(parser);
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
AST* parseFactor(Parser* parser) {
    printf("Parsing Factor...\n");

    AST* root = parseUnary(parser);

    while(tokenMatchesTypes(
        parser,
        Token::TokenType::DIVISION,
        Token::TokenType::MULTIPLICATION
    )) {

        Token* operation = parser->previous_token;
        BinaryOperation op;
        switch (operation->token_type) {
            case Token::TokenType::DIVISION: op = BinaryOperation::DIVISION; break;
            case Token::TokenType::MULTIPLICATION: op = BinaryOperation::MULTIPLICATION; break;
            default: printf("\033[1mERROR: Unknow factor operator '%s'!\033[0m\n", operation->value); exit(-1);
        }

        AST* right = parseUnary(parser);

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
AST* parseUnary(Parser* parser) {
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
                printf("\033[31mUnknow Unary operator '%s'!\033[0m\n", parser->current_token->value);
                exit(-1);
                break;
        }
        AST* right_operand = parseUnary(parser);
        AST* root = initAST(AST::ASTType::UNARY_EXPRESSION);
        root->unary_binary_exp_operation = op;
        root->unary_binary_exp_right_operand = right_operand;
        return root;
    }
    AST* tmp = parsePrimary(parser);
    printf("Parsed Unary!\n");
    return tmp;
}

// PRIMARY → NUMBER | STRING | 'true' | 'false' | 'nil | IDENTIFIER | '('EXPRESSION')';
AST* parsePrimary(Parser* parser) {
    printf("Parsing Primary\n");

    if(parser->current_token->token_type == Token::TokenType::IDENTIFIER) {
        if(isIdentifier(parser->current_token)) {
            AST* root = initAST(AST::ASTType::IDENTIFIER);
            root->identifier = parser->current_token->value;
            parserReadToken(parser, Token::TokenType::IDENTIFIER);
            printf("Parsed Primary as Identifier '%s'!\n", root->identifier);

            return root;
        }

        if(strcmp(parser->current_token->value, "true") == 0 ) {
            printf("\033[31mUnsuported primary\033[0m'%s'\n", parser->current_token->value);
            exit(-1);
        } else
        if(strcmp(parser->current_token->value, "false") == 0 ) {
            printf("\033[31mUnsuported primary\033[0m'%s'\n", parser->current_token->value);
            exit(-1);
        } else
        if(strcmp(parser->current_token->value, "nil") == 0 ) {
            printf("\033[31mUnsuported primary\033[0m'%s'\n", parser->current_token->value);
            exit(-1);
        }
    }

    if(parser->current_token->token_type == Token::TokenType::INTEGER) {
        AST* root = initAST(AST::ASTType::INTEGER);
        root->integer_value = atoi(parser->current_token->value);
        parserReadToken(parser, Token::TokenType::INTEGER);
        printf("Parsed Primary as Integer '%i'!\n", root->integer_value);

        return root;
    }

    if(parser->current_token->token_type == Token::TokenType::OPEN_PARENTESIS) {
        parserReadToken(parser, Token::TokenType::OPEN_PARENTESIS);
        AST* exp = parseExpression(parser);
        parserReadToken(parser, Token::TokenType::CLOSE_PARENTESIS);
        printf("Parsed Primary as Group!\n");

        return exp;
    }

    printf("\033[31mUnsuported primary \033[0m'%s'\n", parser->current_token->value);
    exit(-1);
    return nullptr;
}