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

void addDeclaration(AST* declarations, AST* declaration) {
    declarations->declarations_list_count += 1;
    
    declarations->declarations_list = (AST**)realloc(
        declarations->declarations_list,
        declarations->declarations_list_count * sizeof(AST*)
    );
    
    declarations->declarations_list[ declarations->declarations_list_count - 1] = declaration;
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

void addVariableDefinitionName(AST* variables, AST* name) {
    variables->vars_def_name[ variables->vars_def_count - 1] = name;
}

void addVariableDefinitionValue(AST* variables, AST* value) {
    variables->vars_def_value[ variables->vars_def_count - 1] = value;
}


void addSwitchCase(AST* swtch, AST* cs) {
    swtch->switch_cases_count += 1;
    swtch->switch_cases = (AST**)realloc(
        swtch->switch_cases,
        swtch->switch_cases_count * sizeof(AST*)
    );
    swtch->switch_cases[swtch->switch_cases_count - 1] = cs;
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

// DECLARATIONS → DECLARATION* EOF
AST* parseStart(Parser* parser) {
    AST* declarations = initAST(AST::ASTType::DECLARATIONS);

    while(parser->current_token->token_type != Token::TokenType::TOKEN_EOF) {
        AST* declaration = parseDeclaration(parser);
        addDeclaration(declarations, declaration);
    }

    return declarations;
}

// FUNC_VAR_DECL → FUNC_DECL | VAR_DECL
AST* parseFuncVarDecl(Parser* parser) {
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
            return parseFunctionDeclaration(parser);
        } else {
            AST* var_decl = parseVariableDeclaration(parser);
            parserReadToken(parser, Token::TokenType::SEMICOLON);
            return var_decl;
        }
    }

    printf("\033[1mERROR: Unknow Global declaration '%s'!\033[0m\n", parser->current_token->value);
    exit(-1);
    return nullptr;
}


// DECLARATION → FUNC_DECL | VAR_DECL | STRUCT_DECL
AST* parseDeclaration(Parser* parser) {
    if(parser->current_token->token_type == Token::TokenType::STRUCT) {
        AST* struct_sttmnt = parseStruct(parser);
        return struct_sttmnt;
    }

    AST* decl = parseFuncVarDecl(parser);
    return decl;
}


// STRUCT → 'struct' IDENTIFIER '{' DECLARATIONS '}'';'
AST* parseStruct(Parser* parser) {
    AST* root = initAST(AST::ASTType::STRUCT);
    parserReadToken(parser, Token::TokenType::STRUCT);
    AST* identifier = parsePrimary(parser);

    if(identifier->type != AST::ASTType::IDENTIFIER) {
        printf("\033[1mERROR: Struct have invalid name of type '%i'!\033[0m\n", identifier->type);
        exit(-1);
    }

    root->struct_identifier = identifier;

    parserReadToken(parser, Token::TokenType::OPEN_BRACKET);
    AST* declarations = initAST(AST::ASTType::DECLARATIONS);

    while(parser->current_token->token_type != Token::TokenType::CLOSE_BRACKET) {
        AST* decl = parseFuncVarDecl(parser);
        addDeclaration(declarations, decl);
    }

    root->struct_declarations = declarations;

    parserReadToken(parser, Token::TokenType::CLOSE_BRACKET);
    parserReadToken(parser, Token::TokenType::SEMICOLON);
    return root;
}

// RETURN → 'return' EXPRESSION?';'
AST* parseReturn(Parser* parser) {
    AST* return_sttmnt = initAST(AST::ASTType::RETURN);
    parserReadToken(parser, Token::TokenType::RETURN);

    if(parser->current_token->token_type != Token::TokenType::SEMICOLON) {
        return_sttmnt->return_value = parseExpression(parser);
    } else {
        return_sttmnt->return_value = initAST(AST::ASTType::UNDEFINED);
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
        if(returnStatementFound && root->func_dec_body->block_statements->statements_list[returnStatementIndex]->return_value->type != AST::ASTType::UNDEFINED) {
            printf("\033[33mWARNING: Return Statement returning value in void function %s!\033[0m\n", root->func_dec_identifier->identifier);
        }
    }
    // TODO check return statement
    return root;
}


// STATEMENT → VAR_DECL';' | EXPRESSION | IF | WHILE | DO_WHILE | FOR |  BLOCK | RETURN | BREAK | SWITCH
AST* parseStatement(Parser* parser) {
    AST* root = initAST(AST::ASTType::STATEMETNS);

    if(parser->current_token->token_type == Token::TokenType::BREAK) {
        parserReadToken(parser, Token::TokenType::BREAK);
        parserReadToken(parser, Token::TokenType::SEMICOLON);
        return initAST(AST::ASTType::BREAK);
    }

    if(parser->current_token->token_type == Token::TokenType::SWITCH) {
        return parseSwitch(parser);
    }

    if(parser->current_token->token_type == Token::TokenType::RETURN) {
        return parseReturn(parser);
    }

    if(parser->current_token->token_type == Token::TokenType::OPEN_BRACKET) {
        return parseBlock(parser);
    }

    if(parser->current_token->token_type == Token::TokenType::IF) {
        return parseIf(parser);
    }

    if(parser->current_token->token_type == Token::TokenType::DO) {
        return parseDoWhile(parser);
    }

    if(parser->current_token->token_type == Token::TokenType::WHILE) {
        return parseWhile(parser);
    }

    if(parser->current_token->token_type == Token::TokenType::FOR) {
        return parseFor(parser);
    }

    if(parser->current_token->token_type == Token::TokenType::IDENTIFIER && isBuiltInType(parser->current_token)) {
        AST* var_decl = parseVariableDeclaration(parser);
        parserReadToken(parser, Token::TokenType::SEMICOLON);
        return var_decl;
    }


    AST* exp_sttmnt = parseExpression(parser);
    parserReadToken(parser, Token::TokenType::SEMICOLON);

    return exp_sttmnt;
}

// IF → 'if' '(' EXPRESSION ')' STATEMENT (else STATEMENT)? 
AST* parseIf(Parser* parser) {
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
        AST* else_statements = initAST(AST::ASTType::UNDEFINED);
        if_sttnt->if_else_ast = else_statements; 
    }
    

    return if_sttnt;
}


// WHILE  → 'while' '(' EXPRESSION ')' STATEMENT; 
AST* parseWhile(Parser* parser) {
    AST* while_sttnt = initAST(AST::ASTType::WHILE);

    parserReadToken(parser, Token::TokenType::WHILE); // while keyword
    parserReadToken(parser, Token::TokenType::OPEN_PARENTESIS);
    
    AST* condition = parseExpression(parser);
    while_sttnt->while_condition = condition; 
    
    parserReadToken(parser, Token::TokenType::CLOSE_PARENTESIS);
    
    AST* statements = parseStatement(parser);

    while_sttnt->while_statements = statements;
    

    return while_sttnt;
}

// DO_WHILE → 'do' '(' EXPRESSION ')' STATEMENT 'while'('EXPRESSION')'';' 
AST* parseDoWhile(Parser* parser) {
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


    return do_while_sttmnt;
}

// FOR → 'for' '('(EXPRESSION | VAR_DECL)?';' EXPRESSION? ';' EXPRESSION? ')' STATEMENT 
AST* parseFor(Parser* parser) {
    parserReadToken(parser, Token::TokenType::FOR);
    AST* for_sttmnt = initAST(AST::ASTType::FOR);
    parserReadToken(parser, Token::TokenType::OPEN_PARENTESIS);

    AST* statement1 = nullptr;
    
    if(parser->current_token->token_type == Token::TokenType::IDENTIFIER && isBuiltInType(parser->current_token)) {
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


// SWITCH  → 'switch' '(' EXPRESSION ')' '{' ('case' expression ':' STATEMENT? 'break'? )* ('default'':' STATEMENT? 'break'?)'}'; 
AST* parseSwitch(Parser* parser) {
    AST* root = initAST(AST::ASTType::SWITCH);

    parserReadToken(parser, Token::TokenType::SWITCH);
    parserReadToken(parser, Token::TokenType::OPEN_PARENTESIS);
    root->switch_expression = parseExpression(parser);
    parserReadToken(parser, Token::TokenType::CLOSE_PARENTESIS);
    parserReadToken(parser, Token::TokenType::OPEN_BRACKET);

    while(parser->current_token->token_type != Token::TokenType::CLOSE_BRACKET) {
        if(parser->current_token->token_type == Token::TokenType::DEFAULT) {
            AST* cs = initAST(AST::ASTType::CASE);
            parserReadToken(parser, Token::TokenType::DEFAULT);
            cs->case_expression = initAST(AST::ASTType::UNDEFINED);
            parserReadToken(parser, Token::TokenType::TWO_POINTS);
            AST* statements = initAST(AST::ASTType::STATEMETNS);
            while (parser->current_token->token_type != Token::TokenType::CLOSE_BRACKET && parser->current_token->token_type != Token::TokenType::CASE && parser->current_token->token_type != Token::TokenType::DEFAULT) {
                addStatement(statements, parseStatement(parser));
            }
            cs->case_statement = statements;
            root->switch_default_case = cs;
        } else {
            AST* cs = initAST(AST::ASTType::CASE);
            parserReadToken(parser, Token::TokenType::CASE);
            cs->case_expression = parseExpression(parser);
            AST* statements = initAST(AST::ASTType::STATEMETNS);
            parserReadToken(parser, Token::TokenType::TWO_POINTS);

            while (parser->current_token->token_type != Token::TokenType::CLOSE_BRACKET && parser->current_token->token_type != Token::TokenType::CASE && parser->current_token->token_type != Token::TokenType::DEFAULT) {
                addStatement(statements, parseStatement(parser));
            }

            cs->case_statement = statements;
            addSwitchCase(root, cs);
        }
    }
    parserReadToken(parser, Token::TokenType::CLOSE_BRACKET);
    if(!root->switch_default_case) {
        printf("\033[33mWARNING: Switch operator dont have a default case!\033[0m\n");
        root->switch_default_case = initAST(AST::ASTType::UNDEFINED);
    }

    //TODO check if cases have a break statement

    return root;
}

// BLOCK → '{' DECLARATION* '}'
AST* parseBlock(Parser* parser) {
    AST* block = initAST(AST::ASTType::BLOCK);

    parserReadToken(parser, Token::TokenType::OPEN_BRACKET);
    AST* statements = initAST(AST::ASTType::STATEMETNS);

    while (parser->current_token->token_type != Token::TokenType::CLOSE_BRACKET) {
        addStatement(statements, parseStatement(parser));
    }

    block->block_statements = statements;
    parserReadToken(parser, Token::TokenType::CLOSE_BRACKET);
    return block;
}

// VAR_DECL → TYPE (IDENTIFIER ('=' EXPRESSION)?) (IDENTIFIER ('=' EXPRESSION)?,)* ';'
AST* parseVariableDeclaration(Parser* parser) {
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
        addVariableDefinitionValue(variables_definitions, initAST(AST::ASTType::UNDEFINED));
    }


    while(parser->current_token->token_type == Token::TokenType::COMMA) {
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
            addVariableDefinitionValue(variables_definitions, initAST(AST::ASTType::UNDEFINED));
        }
    }

    return variables_definitions;
}

// EXPRESSION → IDENTIFIER '=' ASSIGNMENT | EQUALITY
AST* parseExpression(Parser* parser) {
    AST* root = parseEquality(parser);

    while(parser->current_token->token_type == Token::TokenType::EQUALS) {
        parserReadToken(parser, Token::TokenType::EQUALS);
        AST* left = root;

        if(root->type != AST::ASTType::IDENTIFIER) {
            printf("\033[33mWARNING: First operand of assignment isn't a identifier!\033[0m\n");
        }

        AST* right = parseExpression(parser);
       
        root = initAST(AST::ASTType::ASSIGNMENT);
       
        root->assignment_left = left;
        root->assignment_right = right;
    }

    return root;
}

// EQUALITY → COMPARISON (('!=' | '==') COMPARISON)*;      ex: 1 == 1 != 3 == 3;
AST* parseEquality(Parser* parser) {
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

    return root;
}

// COMPARISON → TERM (('>' | '>=' | '<' | '<=') TERM)* ;
AST* parseComparison(Parser* parser) {
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

    return root;
}

// TERM → FACTOR (('+' | '-') FACTOR)*;
AST* parseTerm(Parser* parser) {
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

    return root;
}

// UNARY → ('!' | '-')UNARY | PRIMARY
AST* parseUnary(Parser* parser) {
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
    return tmp;
}

// PRIMARY → NUMBER | STRING | 'true' | 'false' | 'nil | IDENTIFIER | '('EXPRESSION')';
AST* parsePrimary(Parser* parser) {
    if(parser->current_token->token_type == Token::TokenType::IDENTIFIER) {
        if(!isBuiltInType(parser->current_token)) {
            AST* root = initAST(AST::ASTType::IDENTIFIER);
            root->identifier = parser->current_token->value;
            parserReadToken(parser, Token::TokenType::IDENTIFIER);
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
        return root;
    }

    if(parser->current_token->token_type == Token::TokenType::OPEN_PARENTESIS) {
        parserReadToken(parser, Token::TokenType::OPEN_PARENTESIS);
        AST* exp = parseExpression(parser);
        parserReadToken(parser, Token::TokenType::CLOSE_PARENTESIS);
        return exp;
    }

    printf("\033[31mUnsuported primary \033[0m'%s'\n", parser->current_token->value);
    exit(-1);
    return nullptr;
}