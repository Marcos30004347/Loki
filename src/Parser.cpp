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

void addProgramDeclaration(AST* program, AST* declaration) {
    program->program_declarations_count += 1;
    
    program->program_declarations = (AST**)realloc(
        program->program_declarations,
        program->program_declarations_count * sizeof(AST*)
    );
    
    program->program_declarations[ program->program_declarations_count - 1] = declaration;
}


void addFuncCallArgument(AST* func_call, AST* argument) {
    func_call->func_call_arguments_count += 1;
    
    func_call->func_call_arguments = (AST**)realloc(
        func_call->func_call_arguments,
        func_call->func_call_arguments_count * sizeof(AST*)
    );
    
    func_call->func_call_arguments[ func_call->func_call_arguments_count - 1] = argument;
}

void addFuncDecArgument(AST* func_dec, AST* argument) {
    func_dec->func_dec_arguments_count += 1;
    
    func_dec->func_dec_arguments = (AST**)realloc(
        func_dec->func_dec_arguments,
        func_dec->func_dec_arguments_count * sizeof(AST*)
    );
    
    func_dec->func_dec_arguments[func_dec->func_dec_arguments_count - 1] = argument;
}


bool isBuiltInType(Token* tok) {
    if(strcmp(tok->value, "int") == 0) return true;
    if(strcmp(tok->value, "void") == 0) return true;

    return false;
}

void increaseVariableDefinitions(AST* variables) {
    variables->vars_def_count += 1;
    
    variables->vars_def_name = (AST**)realloc(
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

void addVariableDefinitionName(AST* variables, AST* name) {
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

// PROGRAM → DECLARATION* EOF
AST* parseStart(Parser* parser) {
    AST* program = initAST(AST::ASTType::PROGRAM);

    while(parser->current_token->token_type != Token::TokenType::TOKEN_EOF) {
        AST* declaration = parseProgram(parser);
        addProgramDeclaration(program, declaration);
    }

    return program;
}

// GLOBAL_DECLARATION → FUNC_DECL | VAR_DECL
AST* parseProgram(Parser* parser) {
    printf("Parsing Program...\n");

    if(parser->current_token->token_type == Token::TokenType::IDENTIFIER && isBuiltInType(parser->current_token)) {
        // Save parser and lexer state
        int i = parser->lexer->i;
        char c = parser->lexer->c;

        Token* current = parser->current_token;
        Token* previous = parser->previous_token;

        parserReadToken(parser, Token::TokenType::IDENTIFIER);
        parserReadToken(parser, Token::TokenType::IDENTIFIER);
        Token* tok = parser->current_token;
        
        // Restore parser and lexer state
        parser->lexer->i = i;
        parser->lexer->c = c;
        parser->current_token = current;
        parser->previous_token = previous;
        if(tok->token_type == Token::TokenType::OPEN_PARENTESIS) {
            AST* function = parseFunctionDeclaration(parser);
            printf("Parsed Program as Function Declaration!\n");
            return function;
        } else {
            AST* var_decl = parseVariableDeclaration(parser);
            parserReadToken(parser, Token::TokenType::SEMICOLON);
            printf("Parsed Program as Variable Declaration!\n");
            return var_decl;
        }
    }

    printf("\033[1mERROR: Unknow Global declaration '%s'!\033[0m\n", parser->current_token->value);
    exit(-1);
    return nullptr;
}


// DECLARATION →  VAR_DECL | STATEMENT
AST* parseDeclaration(Parser* parser) {
    printf("Parsing Declaration...\n");

    if(parser->current_token->token_type == Token::TokenType::IDENTIFIER && isBuiltInType(parser->current_token)) {
        AST* var_decl = parseVariableDeclaration(parser);
        parserReadToken(parser, Token::TokenType::SEMICOLON);
        printf("Parsed Statement as Variable Declaration!\n");
        return var_decl;
    }

    AST* statement = parseStatement(parser);

    printf("Parsed Declaration!\n");
    return statement;
}

// RETURN → 'return' EXPRESSION?';'
AST* parseReturn(Parser* parser) {
    AST* return_sttmnt = initAST(AST::ASTType::RETURN);
    parserReadToken(parser, Token::TokenType::RETURN);

    if(parser->current_token->token_type != Token::TokenType::SEMICOLON) {
        return_sttmnt->return_value = parseExpression(parser);
    } else {
        return_sttmnt->return_value = initAST(AST::ASTType::NO_OP);
    }

    parserReadToken(parser, Token::TokenType::SEMICOLON);
    return return_sttmnt;
}

// FUNC_DECL → IDENTIFIER IDENTIFIER'('(IDENTIFIER IDENRIFIER)? (',' IDENTIFIER IDENTIFIER)*')' BLOCK
AST* parseFunctionDeclaration(Parser* parser) {
    AST* root = initAST(AST::ASTType::FUNCTION_DECLARATION);
    BuildInType return_type = getTypeFromId(parser->current_token->value);
    root->func_dec_return_type = return_type;
    parserReadToken(parser, Token::TokenType::IDENTIFIER);
    root->func_dec_identifier = parsePrimary(parser);
    parserReadToken(parser, Token::TokenType::OPEN_PARENTESIS);
    if(parser->current_token->token_type != Token::TokenType::CLOSE_PARENTESIS) {
        // IDENTIFIER IDEDNTIFIER
        AST* argument = initAST(AST::ASTType::FUNCTION_ARGUMENT);
        BuildInType type = getTypeFromId(parser->current_token->value);
        parserReadToken(parser, Token::TokenType::IDENTIFIER);
        AST* identifier = parsePrimary(parser);
        
        if(identifier->type != AST::ASTType::IDENTIFIER) {
            printf("\033[1mERROR: Function have invalid name of type '%i'!\033[0m\n", identifier->type);
            exit(-1);
        }

        argument->func_argument_id = identifier;
        argument->func_argument_type = type;
    
        addFuncDecArgument(root, argument);


        // (','IDENTIFIER IDEDNTIFIER)*
        while(parser->current_token->token_type == Token::TokenType::COMMA) {
            parserReadToken(parser, Token::TokenType::COMMA);
            AST* argument = initAST(AST::ASTType::FUNCTION_ARGUMENT);
            BuildInType type = getTypeFromId(parser->current_token->value);
            parserReadToken(parser, Token::TokenType::IDENTIFIER);

            AST* identifier = parsePrimary(parser);
            
            if(identifier->type != AST::ASTType::IDENTIFIER) {
                printf("\033[1mERROR: Function have invalid name of type '%i'!\033[0m\n", identifier->type);
                exit(-1);

            }
            argument->func_argument_id = identifier;
            argument->func_argument_type = type;
            addFuncDecArgument(root, argument);
        }
    }

    parserReadToken(parser, Token::TokenType::CLOSE_PARENTESIS);
    root->func_dec_body = parseBlock(parser);
    
    int returnStatementIndex = 0;
    bool returnStatementFound = false;
    
    for(int i=0; i<root->func_dec_body->block_statements->statements_list_count; i++) {

        if(root->func_dec_body->block_statements->statements_list[i]->type == AST::ASTType::RETURN) {
            returnStatementFound = true;
            returnStatementIndex = i;
            break;
        }
    }
    if(return_type != BuildInType::TYPE_VOID) {
        if(returnStatementFound) {
            if(returnStatementIndex < root->func_dec_body->block_statements->statements_list_count - 1) {
                printf("\033[33mWARNING: Return Statement reached bedore end of function %s!\033[0m\n", root->func_dec_identifier->identifier);
            }
        } else {
            printf("\033[33mWARNING: Return Statement not found for function %s!\033[0m\n", root->func_dec_identifier->identifier);
        }
    } else {
        if(returnStatementFound && root->func_dec_body->block_statements->statements_list[returnStatementIndex]->return_value->type != AST::ASTType::NO_OP) {
            printf("\033[33mWARNING: Return Statement returning value in void function %s!\033[0m\n", root->func_dec_identifier->identifier);
        }
    }
    // TODO check return statement
    return root;
}


// STATEMENT → EXPRESSION_STATEMENT | IF | WHILE | DO_WHILE | FOR |  BLOCK | RETURN
AST* parseStatement(Parser* parser) {
    printf("Parsing Statement...\n");
    AST* root = initAST(AST::ASTType::STATEMETNS);

    if(parser->current_token->token_type == Token::TokenType::RETURN) {
        return parseReturn(parser);
    }

    if(parser->current_token->token_type == Token::TokenType::OPEN_BRACKET) {
        AST* block = parseBlock(parser);
        printf("Parsed Statement as Block!\n");
        return block;
    }
    if(parser->current_token->token_type == Token::TokenType::IF) {
        AST* ifsttmnt = parseIf(parser);
        printf("Parsed Statement as If Statement!\n");
        return ifsttmnt;
    }

    if(parser->current_token->token_type == Token::TokenType::DO) {
        AST* ifsttmnt = parseDoWhile(parser);
        printf("Parsed Statement as do While Statement!\n");
        return ifsttmnt;
    }

    if(parser->current_token->token_type == Token::TokenType::WHILE) {
        AST* ifsttmnt = parseWhile(parser);
        printf("Parsed Statement as While Statement!\n");
        return ifsttmnt;
    }

    if(parser->current_token->token_type == Token::TokenType::FOR) {
        AST* ifsttmnt = parseFor(parser);
        printf("Parsed Statement as For Statement!\n");
        return ifsttmnt;
    }

    AST* exp_sttmnt = parseExpression(parser);
    parserReadToken(parser, Token::TokenType::SEMICOLON);



    printf("Parsed Statement as Expression!\n");
    return exp_sttmnt;
}

// IF → 'if' '(' EXPRESSION ')' STATEMENT (else STATEMENT)? 
AST* parseIf(Parser* parser) {
    printf("Parsing If Statement...\n");
    AST* if_sttnt = initAST(AST::ASTType::IF);

    parserReadToken(parser, Token::TokenType::IF); // if keyword
    parserReadToken(parser, Token::TokenType::OPEN_PARENTESIS);
    
    AST* condition = parseExpression(parser);
    if_sttnt->if_condition = condition; 
    
    parserReadToken(parser, Token::TokenType::CLOSE_PARENTESIS);
    
    AST* statements = parseStatement(parser);
    if_sttnt->if_statements = statements;

    if(parser->current_token->token_type == Token::TokenType::ELSE) {
        parserReadToken(parser, Token::TokenType::ELSE);
        AST* else_statements = parseStatement(parser);
        if_sttnt->if_else_ast = else_statements; 
    } else {
        AST* else_statements = initAST(AST::ASTType::NO_OP);
        if_sttnt->if_else_ast = else_statements; 
    }
    
    printf("Parsed If Statement!\n");

    return if_sttnt;
}


// WHILE  → 'while' '(' EXPRESSION ')' STATEMENT; 
AST* parseWhile(Parser* parser) {
    printf("Parsing While Statement...\n");
    AST* while_sttnt = initAST(AST::ASTType::WHILE);

    parserReadToken(parser, Token::TokenType::WHILE); // while keyword
    parserReadToken(parser, Token::TokenType::OPEN_PARENTESIS);
    
    AST* condition = parseExpression(parser);
    while_sttnt->while_condition = condition; 
    
    parserReadToken(parser, Token::TokenType::CLOSE_PARENTESIS);
    
    AST* statements = parseStatement(parser);

    while_sttnt->while_statements = statements;
    
    printf("Parsed While Statement!\n");

    return while_sttnt;
}

// DO_WHILE → 'do' '(' EXPRESSION ')' STATEMENT 'while'('EXPRESSION')'';' 
AST* parseDoWhile(Parser* parser) {
    printf("Parsing While Statement...\n");
    AST* do_while_sttmnt = initAST(AST::ASTType::DO_WHILE);

    parserReadToken(parser, Token::TokenType::DO); // while keyword
    AST* statements = parseStatement(parser);
    do_while_sttmnt->do_while_statements = statements;
    
    parserReadToken(parser, Token::TokenType::WHILE);
    parserReadToken(parser, Token::TokenType::OPEN_PARENTESIS);
    
    AST* condition = parseExpression(parser);
    do_while_sttmnt->do_while_condition = condition; 
    
    parserReadToken(parser, Token::TokenType::CLOSE_PARENTESIS);
    parserReadToken(parser, Token::TokenType::SEMICOLON);

    printf("Parsed While Statement!\n");

    return do_while_sttmnt;
}

// FOR → 'for' '('(EXPRESSION | VAR_DECL)?';' EXPRESSION? ';' EXPRESSION? ')' STATEMENT 
AST* parseFor(Parser* parser) {
    parserReadToken(parser, Token::TokenType::FOR);
    AST* for_sttmnt = initAST(AST::ASTType::FOR);
    parserReadToken(parser, Token::TokenType::OPEN_PARENTESIS);

    AST* statement1 = nullptr;
    
    // KKKKK thats strange
    if(parser->current_token->token_type == Token::TokenType::IDENTIFIER && isBuiltInType(parser->current_token)) {
        printf("ACTUALY GET THERE\n");
        statement1 = parseVariableDeclaration(parser);
    } else statement1 = parseExpression(parser);

    parserReadToken(parser, Token::TokenType::SEMICOLON);
    AST* statement2 = parseExpression(parser);
    parserReadToken(parser, Token::TokenType::SEMICOLON);
    AST* statement3 = parseExpression(parser);


    for_sttmnt->for_statement1 = statement1;
    for_sttmnt->for_statement2 = statement2;
    for_sttmnt->for_statement3 = statement3;

    parserReadToken(parser, Token::TokenType::CLOSE_PARENTESIS);
    for_sttmnt->for_body = parseStatement(parser);
    return for_sttmnt;
}

// BLOCK → '{' DECLARATION* '}'
AST* parseBlock(Parser* parser) {
    AST* block = initAST(AST::ASTType::BLOCK);

    parserReadToken(parser, Token::TokenType::OPEN_BRACKET);
    AST* statements = initAST(AST::ASTType::STATEMETNS);

    while (parser->current_token->token_type != Token::TokenType::CLOSE_BRACKET) {
        addStatement(statements, parseDeclaration(parser));
    }

    block->block_statements = statements;
    parserReadToken(parser, Token::TokenType::CLOSE_BRACKET);
    return block;
}

// VAR_DECL → TYPE (IDENTIFIER ('=' EXPRESSION)?) (IDENTIFIER ('=' EXPRESSION)?,)* ';'
AST* parseVariableDeclaration(Parser* parser) {
    printf("Parsing Variable Definition...\n");

    AST* variables_definitions = initAST(AST::ASTType::VARIABLES_DECLARATIONS);

    char* type_id = copyString(parser->current_token->value);
    parserReadToken(parser, Token::TokenType::IDENTIFIER);
    AST* identifier = parsePrimary(parser);

    if(identifier->type != AST::ASTType::IDENTIFIER) {
        printf("\033[1mERROR: Variable have invalid name of type '%i'!\033[0m\n", identifier->type);
        exit(-1);

    }

    variables_definitions->vars_def_type = getTypeFromId(type_id);

    increaseVariableDefinitions(variables_definitions);
    addVariableDefinitionName(variables_definitions, identifier);


    if(parser->current_token->token_type == Token::TokenType::EQUALS) {
        parserReadToken(parser, Token::TokenType::EQUALS);
        addVariableDefinitionValue(variables_definitions, parseExpression(parser));
    } else {
        addVariableDefinitionValue(variables_definitions, getTypeDefaultValue(variables_definitions->vars_def_type));
    }


    while(parser->current_token->token_type == Token::TokenType::COMMA) {
        printf("Parsed Compound Variable Definition!\n");
        parserReadToken(parser, Token::TokenType::COMMA);

        AST* identifier = parsePrimary(parser);

        if(identifier->type != AST::ASTType::IDENTIFIER) {
            printf("\033[1mERROR: Variable have invalid name of type '%i'!\033[0m\n", identifier->type);
            exit(-1);

        }
    
        increaseVariableDefinitions(variables_definitions);
        addVariableDefinitionName(variables_definitions, identifier);


        if(parser->current_token->token_type == Token::TokenType::EQUALS) {
            parserReadToken(parser, Token::TokenType::EQUALS);
            addVariableDefinitionValue(variables_definitions, parseExpression(parser));
        } else {
            addVariableDefinitionValue(variables_definitions, getTypeDefaultValue(variables_definitions->vars_def_type));
        }
    }

    printf("Parsed Variable Definition!\n");
    return variables_definitions;
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

// CALL → PRIMARY('('ARGUMENTS?')')?
AST* parseCall(Parser* parser) {
    AST* root = parsePrimary(parser);

    if(root->type == AST::ASTType::IDENTIFIER) {
        // Function call
        // TODO: Maybe this is a good spot to check if the function is
        // making a call to a defined function
        AST* func_call = initAST(AST::ASTType::FUNCTION_CALL);
        func_call->func_call_identifier = root;
    
        parserReadToken(parser, Token::TokenType::OPEN_PARENTESIS);
        if(parser->current_token->token_type != Token::TokenType::CLOSE_PARENTESIS) {
            // Exist arguments fot the call
            AST* argument = parseExpression(parser);
            addFuncCallArgument(func_call, argument);

            while(parser->current_token->token_type == Token::TokenType::COMMA) {
                parserReadToken(parser, Token::TokenType::COMMA);
                AST* argument = parseExpression(parser);
                addFuncCallArgument(func_call, argument);
            }
        }
        parserReadToken(parser, Token::TokenType::CLOSE_PARENTESIS);
        root = func_call;
    } else {
        // Variable Access
        // TODO: Maybe this is a good spot to check if the variable is
        // defined.
    }

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
        if(!isBuiltInType(parser->current_token)) {
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