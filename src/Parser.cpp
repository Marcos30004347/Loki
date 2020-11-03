// https://craftinginterpreters.com/parsing-expressions.html

#include "Parser.hpp"
#include "Utils.hpp"   

#include <string.h>
#include <stdlib.h>
#include <malloc.h>


Parser* initParser(Lexer* lexer) {
    Parser* parser = (Parser*)malloc(sizeof(Parser));

    parser->lexer = lexer;
    parser->previous_token = nullptr;
    parser->current_token = lexerGetNextToken(lexer);
    return parser;
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

// TYPE → TYPEID | IDENTIFIER
AST* parseType(Parser* parser) {
    AST* ast = nullptr;

    switch(parser->current_token->token_type) {
        case Token::TokenType::VOID:
            ast = initAST(AST::ASTType::TYPE);
            ast->type_type = BuildInType::TYPE_VOID;
            break;
        case Token::TokenType::FLOAT:
            ast = initAST(AST::ASTType::TYPE);
            ast->type_type = BuildInType::TYPE_FLOAT;
            break;
        case Token::TokenType::INT:
            ast = initAST(AST::ASTType::TYPE);
            ast->type_type = BuildInType::TYPE_INT;
            break;
        case Token::TokenType::UINT:
            ast = initAST(AST::ASTType::TYPE);
            ast->type_type = BuildInType::TYPE_UINT;
            break;
        case Token::TokenType::BOOL:
            ast = initAST(AST::ASTType::TYPE);
            ast->type_type = BuildInType::TYPE_BOOL;
            break;
        case Token::TokenType::MAT2:
            ast = initAST(AST::ASTType::TYPE);
            ast->type_type = BuildInType::TYPE_MAT2;
            break;
        case Token::TokenType::MAT2X2:
            ast = initAST(AST::ASTType::TYPE);
            ast->type_type = BuildInType::TYPE_MAT2X2;
            break;
        case Token::TokenType::MAT2X3:
            ast = initAST(AST::ASTType::TYPE);
            ast->type_type = BuildInType::TYPE_MAT2X3;
            break;
        case Token::TokenType::MAT2X4:
            ast = initAST(AST::ASTType::TYPE);
            ast->type_type = BuildInType::TYPE_MAT2X4;
            break;
        case Token::TokenType::MAT3:
            ast = initAST(AST::ASTType::TYPE);
            ast->type_type = BuildInType::TYPE_MAT3;
            break;
        case Token::TokenType::MAT3X2:
            ast = initAST(AST::ASTType::TYPE);
            ast->type_type = BuildInType::TYPE_MAT3X2;
            break;
        case Token::TokenType::MAT3X3:
            ast = initAST(AST::ASTType::TYPE);
            ast->type_type = BuildInType::TYPE_MAT3X3;
            break;
        case Token::TokenType::MAT3X4:
            ast = initAST(AST::ASTType::TYPE);
            ast->type_type = BuildInType::TYPE_MAT3X4;
            break;
        case Token::TokenType::MAT4:
            ast = initAST(AST::ASTType::TYPE);
            ast->type_type = BuildInType::TYPE_MAT4;
            break;
        case Token::TokenType::MAT4X2:
            ast = initAST(AST::ASTType::TYPE);
            ast->type_type = BuildInType::TYPE_MAT4X2;
            break;
        case Token::TokenType::MAT4X3:
            ast = initAST(AST::ASTType::TYPE);
            ast->type_type = BuildInType::TYPE_MAT4X3;
            break;
        case Token::TokenType::MAT4X4:
            ast = initAST(AST::ASTType::TYPE);
            ast->type_type = BuildInType::TYPE_MAT4X4;
            break;
        case Token::TokenType::IDENTIFIER:
            ast = initAST(AST::ASTType::IDENTIFIER);
            ast->type_type = BuildInType::TYPE_STRUCT;
            ast->type_struct_identifier = parsePrimary(parser);
            break;
        default: break;
    }

    if(!ast) {
        printf("ERROR: Undefined Symbol '%s'\n", parser->current_token->value);
        exit(-1);
    }

    parserReadToken(parser, parser->current_token->token_type);
    return ast;
}


// FUNC_VAR_DECL → FUNC_DECL | VAR_DECL
AST* parseFuncVarDecl(Parser* parser) {
    // Save parser and lexer state
    int i = parser->lexer->i;
    char c = parser->lexer->c;

    Token* current = parser->current_token;
    Token* previous = parser->previous_token;

    parseType(parser);
    parserReadToken(parser, Token::TokenType::IDENTIFIER);

    Token* tok = parser->current_token;
    
    // Restore parser and lexer state
    parser->lexer->i = i;
    parser->lexer->c = c;
    parser->current_token = current;
    parser->previous_token = previous;

    if(tok->token_type == Token::TokenType::OPEN_PARENTESIS) {
        return parseFunctionDeclaration(parser);
    }

   
    AST* var_decl = parseVariableDeclaration(parser);
    parserReadToken(parser, Token::TokenType::SEMICOLON);
    return var_decl;
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

    if(identifier->ast_type != AST::ASTType::IDENTIFIER) {
        printf("\033[1mERROR: Struct have invalid name of type '%i'!\033[0m\n", identifier->ast_type);
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

//CHANNEL → ('<-' | '->') IDENTIFIER
AST* parseChannel(Parser* parser) {
    AST* root = initAST(AST::ASTType::CHANNEL);

    if(parser->current_token->token_type == Token::TokenType::FORWARD_ARROW) {
        root->channel_type = ChannelType::CHANNEL_OUT;
        parserReadToken(parser, Token::TokenType::FORWARD_ARROW);
        AST* identifier = parsePrimary(parser);
        if(identifier->ast_type != AST::ASTType::IDENTIFIER) {
            printf("\033[1mERROR: Argument %s have channel name of type '%i'!\033[0m\n", identifier->identifier, identifier->ast_type);
            exit(-1);
        }
        root->channel_identifier = identifier;
    } else if(parser->current_token->token_type == Token::TokenType::BACKWARD_ARROW) {
        root->channel_type = ChannelType::CHANNEL_IN;
        parserReadToken(parser, Token::TokenType::BACKWARD_ARROW);
        AST* identifier = parsePrimary(parser);
        if(identifier->ast_type != AST::ASTType::IDENTIFIER) {
            printf("\033[1mERROR: Argument %s have channel name of type '%i'!\033[0m\n", identifier->identifier, identifier->ast_type);
            exit(-1);
        }
        root->channel_identifier = identifier;
    } else {
        root->channel_type = ChannelType::CHANNEL_NONE;
    }

    return root;
}

// FUNC_DECL → TYPE IDENTIFIER'('( TYPE IDENTIFIER CHANNEL? ( "," TYPE IDENTIFIER CHANNEL? )*')' BLOCK
AST* parseFunctionDeclaration(Parser* parser) {
    AST* root = initAST(AST::ASTType::FUNCTION_DECLARATION);

    root->func_dec_return_type_identifier = parseType(parser);
    root->func_dec_identifier = parsePrimary(parser);

    parserReadToken(parser, Token::TokenType::OPEN_PARENTESIS);

    if(parser->current_token->token_type != Token::TokenType::CLOSE_PARENTESIS) {
        // IDENTIFIER IDEDNTIFIER
        AST* argument = initAST(AST::ASTType::FUNCTION_ARGUMENT);
        argument->func_argument_type_identifier = parseType(parser);
        argument->func_argument_id = parsePrimary(parser);       
     
        if(argument->func_argument_id->ast_type != AST::ASTType::IDENTIFIER) {
            printf("\033[1mERROR: Function have invalid name of type '%i'!\033[0m\n", argument->func_argument_id->ast_type);
            exit(-1);
        }
    
        argument->func_argument_channel = parseChannel(parser);
        addFuncDecArgument(root, argument);

        // (','IDENTIFIER IDEDNTIFIER)*
        while(parser->current_token->token_type == Token::TokenType::COMMA) {
            parserReadToken(parser, Token::TokenType::COMMA);
        
            AST* argument = initAST(AST::ASTType::FUNCTION_ARGUMENT);
        
            argument->func_argument_type_identifier = parseType(parser);
            argument->func_argument_id = parsePrimary(parser);
            
            if(argument->func_argument_id->ast_type != AST::ASTType::IDENTIFIER) {
                printf("\033[1mERROR: Function have invalid name of type '%i'!\033[0m\n", argument->func_argument_id->ast_type);
                exit(-1);

            }
            argument->func_argument_channel = parseChannel(parser);
            addFuncDecArgument(root, argument);
        }
    }

    parserReadToken(parser, Token::TokenType::CLOSE_PARENTESIS);
    root->func_dec_body = parseBlock(parser);

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

    if(parser->current_token->token_type == Token::TokenType::IDENTIFIER) {
        AST* var_decl = parseVariableDeclaration(parser);
        parserReadToken(parser, Token::TokenType::SEMICOLON);
        return var_decl;
    }

    if(
        parser->current_token->token_type == Token::TokenType::INT
        || parser->current_token->token_type == Token::TokenType::UINT
        || parser->current_token->token_type == Token::TokenType::FLOAT
        || parser->current_token->token_type == Token::TokenType::BOOL
        || parser->current_token->token_type == Token::TokenType::MAT2
        || parser->current_token->token_type == Token::TokenType::MAT2X2
        || parser->current_token->token_type == Token::TokenType::MAT2X3
        || parser->current_token->token_type == Token::TokenType::MAT2X4
        || parser->current_token->token_type == Token::TokenType::MAT3
        || parser->current_token->token_type == Token::TokenType::MAT3X2
        || parser->current_token->token_type == Token::TokenType::MAT3X3
        || parser->current_token->token_type == Token::TokenType::MAT3X4
        || parser->current_token->token_type == Token::TokenType::MAT4
        || parser->current_token->token_type == Token::TokenType::MAT4X2
        || parser->current_token->token_type == Token::TokenType::MAT4X3
        || parser->current_token->token_type == Token::TokenType::MAT4X4
        || parser->current_token->token_type == Token::TokenType::IDENTIFIER
    ) {
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

    parserReadToken(parser, Token::TokenType::DO); // do keyword
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
    
    if(
        parser->current_token->token_type == Token::TokenType::INT
        || parser->current_token->token_type == Token::TokenType::UINT
        || parser->current_token->token_type == Token::TokenType::FLOAT
        || parser->current_token->token_type == Token::TokenType::BOOL
        || parser->current_token->token_type == Token::TokenType::MAT2
        || parser->current_token->token_type == Token::TokenType::MAT2X2
        || parser->current_token->token_type == Token::TokenType::MAT2X3
        || parser->current_token->token_type == Token::TokenType::MAT2X4
        || parser->current_token->token_type == Token::TokenType::MAT3
        || parser->current_token->token_type == Token::TokenType::MAT3X2
        || parser->current_token->token_type == Token::TokenType::MAT3X3
        || parser->current_token->token_type == Token::TokenType::MAT3X4
        || parser->current_token->token_type == Token::TokenType::MAT4
        || parser->current_token->token_type == Token::TokenType::MAT4X2
        || parser->current_token->token_type == Token::TokenType::MAT4X3
        || parser->current_token->token_type == Token::TokenType::MAT4X4
        || parser->current_token->token_type == Token::TokenType::IDENTIFIER
    ) {
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

// VAR_DECL → TYPE IDENTIFIER CHANNEL? ('=' EXPRESSION)? (','IDENTIFIER CHANNEL? ('=' EXPRESSION)?)* ';'
AST* parseVariableDeclaration(Parser* parser) {
    AST* variables_definitions = initAST(AST::ASTType::VARIABLES_DECLARATIONS);
    AST* type = parseType(parser);

    AST* identifier = parsePrimary(parser);
    if(identifier->ast_type != AST::ASTType::IDENTIFIER) {
        printf("\033[1mERROR: Variable have invalid name of type '%i'!\033[0m\n", identifier->ast_type);
        exit(-1);

    }

    AST* var = initAST(AST::ASTType::VARIABLE_DECLARATION);
    var->var_def_identifier = identifier;
    var->var_def_channel = parseChannel(parser);
    var->var_def_type_identifier = type;

    if(parser->current_token->token_type == Token::TokenType::EQUALS) {
        parserReadToken(parser, Token::TokenType::EQUALS);
        var->var_def_value = parseExpression(parser);
    } else {
        var->var_def_value = initAST(AST::ASTType::UNDEFINED);
    }

    addVariableDefinitions(variables_definitions, var);

    while(parser->current_token->token_type == Token::TokenType::COMMA) {
        parserReadToken(parser, Token::TokenType::COMMA);

        AST* identifier = parsePrimary(parser);

        if(identifier->ast_type != AST::ASTType::IDENTIFIER) {
            printf("\033[1mERROR: Variable have invalid name of type '%i'!\033[0m\n", identifier->ast_type);
            exit(-1);

        }
    
        AST* var = initAST(AST::ASTType::VARIABLE_DECLARATION);
        var->var_def_identifier = identifier;
        var->var_def_channel = parseChannel(parser);
        var->var_def_type_identifier = type;

        if(parser->current_token->token_type == Token::TokenType::EQUALS) {
            parserReadToken(parser, Token::TokenType::EQUALS);
            var->var_def_value = parseExpression(parser);
        } else {
            var->var_def_value = initAST(AST::ASTType::UNDEFINED);
        }

        addVariableDefinitions(variables_definitions, var);

    }

    return variables_definitions;
}

// EXPRESSION → IDENTIFIER ('=' | '|=' | '&=' | '+=' | '-=' ) ASSIGNMENT | EQUALITY
AST* parseExpression(Parser* parser) {
    AST* root = parseEquality(parser);

    while(
        tokenMatchesTypes(parser,
            Token::TokenType::EQUALS,
            Token::TokenType::PIPE_EQUALS,
            Token::TokenType::AMPERSAND_EQUALS,
            Token::TokenType::DIVIDE_EQUALS,
            Token::TokenType::MULTIPLICATION_EQUALS
        )
    ) {
        AssingmentType op;
        Token* operation = parser->previous_token;

        switch (operation->token_type) {
            case Token::TokenType::EQUALS: op = AssingmentType::ASSIGN_ASSIGN; break;
            case Token::TokenType::PIPE_EQUALS: op = AssingmentType::ASSIGN_PIPE_ASSIGN; break;
            case Token::TokenType::AMPERSAND_EQUALS: op = AssingmentType::ASSIGN_AMPERSAND_ASSIGN; break;
            case Token::TokenType::DIVIDE_EQUALS: op = AssingmentType::ASSIGN_DIVIDE_ASSIGN; break;
            case Token::TokenType::MULTIPLICATION_EQUALS: op = AssingmentType::ASSIGN_MULTIPLY_ASSIGN; break;
            default: printf("\033[1mERROR: Unknow equality operator '%s'!\033[0m\n", operation->value); exit(-1);
        }
    
        parserReadToken(parser, Token::TokenType::EQUALS);
        AST* left = root;

        if(root->ast_type != AST::ASTType::IDENTIFIER) {
            printf("\033[33mWARNING: First operand of assignment isn't a identifier!\033[0m\n");
        }

        AST* right = parseExpression(parser);
       
        root = initAST(AST::ASTType::ASSIGNMENT);
    
        root->assignment_type = op;
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
            case Token::TokenType::EQUALS_EQUALS: op = BinaryOperation::BINARY_EQUALS_EQUALS; break;
            case Token::TokenType::DIFFERENT: op = BinaryOperation::BINARY_DIFFERENT; break;
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

// COMPARISON → TERM (('>' | '>=' | '<' | '<=' | '|' | '&' | '&&' | '||' ) TERM)* 
AST* parseComparison(Parser* parser) {
    AST* root = parseTerm(parser);

    while(tokenMatchesTypes(
        parser,
        Token::TokenType::LESS,
        Token::TokenType::GREATER,
        Token::TokenType::LESS_OR_EQUALS,
        Token::TokenType::GREATER_OR_EQUALS,
        Token::TokenType::PIPE,
        Token::TokenType::PIPE_PIPE,
        Token::TokenType::AMPERSAND,
        Token::TokenType::AMPERSAND_AMPERSAND
    )) {
        Token* operation = parser->previous_token;
        BinaryOperation op;
        switch (operation->token_type) {
            case Token::TokenType::LESS: op = BinaryOperation::BINARY_LESS; break;
            case Token::TokenType::GREATER: op = BinaryOperation::BINARY_GREATER; break;
            case Token::TokenType::LESS_OR_EQUALS: op = BinaryOperation::BINARY_LESS_OR_EQUAL; break;
            case Token::TokenType::GREATER_OR_EQUALS: op = BinaryOperation::BINARY_GREATER_OR_EQUAL; break;
            case Token::TokenType::PIPE: op = BinaryOperation::BINARY_OR; break;
            case Token::TokenType::PIPE_PIPE: op = BinaryOperation::BINARY_OR; break;
            case Token::TokenType::AMPERSAND: op = BinaryOperation::BINARY_AND; break;
            case Token::TokenType::AMPERSAND_AMPERSAND: op = BinaryOperation::BINARY_AND; break;
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
        Token::TokenType::PLUS,
        Token::TokenType::MINUS
    )) {
    
    
        Token* operation = parser->previous_token;
        BinaryOperation op;
        switch (operation->token_type) {
            case Token::TokenType::PLUS: op = BinaryOperation::BINARY_ADDITION; break;
            case Token::TokenType::MINUS: op = BinaryOperation::BINARY_SUBTRACTION; break;
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

    if(root->ast_type == AST::ASTType::IDENTIFIER) {
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
            case Token::TokenType::DIVISION: op = BinaryOperation::BINARY_DIVISION; break;
            case Token::TokenType::MULTIPLICATION: op = BinaryOperation::BINARY_MULTIPLICATION; break;
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

// UNARY → ('!' | '-' | '++' | '--')UNARY | UNARY('++' | '--') | PRIMARY
AST* parseUnary(Parser* parser) {
    while(tokenMatchesTypes(
        parser,
        Token::TokenType::MINUS,
        Token::TokenType::EXCLAMATION,
        Token::TokenType::PLUSS_PLUSS,
        Token::TokenType::MINUS_MINUS
    )) {
        UnaryOperation op;

        switch (parser->current_token->token_type) {
            case Token::TokenType::EXCLAMATION:
                op = UnaryOperation::UNARY_EXCLAMATION;
                parserReadToken(parser, Token::TokenType::EXCLAMATION);
                break;
            case Token::TokenType::MINUS:
                op = UnaryOperation::UNARY_MINUS;
                parserReadToken(parser, Token::TokenType::MINUS);
                break;
            case Token::TokenType::MINUS_MINUS:
                op = UnaryOperation::UNARY_PRE_MINUS_MINUS;
                parserReadToken(parser, Token::TokenType::MINUS_MINUS);
                break;
            case Token::TokenType::PLUSS_PLUSS:
                op = UnaryOperation::UNARY_PRE_ADD_ADD;
                parserReadToken(parser, Token::TokenType::PLUSS_PLUSS);
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

    while(tokenMatchesTypes(
        parser,
        Token::TokenType::PLUSS_PLUSS,
        Token::TokenType::MINUS_MINUS
    )) {
        UnaryOperation op;

        switch (parser->current_token->token_type) {
            case Token::TokenType::MINUS_MINUS:
                op = UnaryOperation::UNARY_AFTER_MINUS_MINUS;
                parserReadToken(parser, Token::TokenType::MINUS_MINUS);
                break;
            case Token::TokenType::PLUSS_PLUSS:
                op = UnaryOperation::UNARY_AFTER_ADD_ADD;
                parserReadToken(parser, Token::TokenType::PLUSS_PLUSS);
                break;
            default:
                printf("\033[31mUnknow Unary operator '%s'!\033[0m\n", parser->current_token->value);
                exit(-1);
                break;
    
            AST* root = initAST(AST::ASTType::UNARY_EXPRESSION);
            root->unary_binary_exp_operation = op;
            root->unary_binary_exp_right_operand = tmp;
            return root;

        }
    }

    return tmp;
}

// PRIMARY → INTEGER | FLOAT | IDENTIFIER | 'true' | 'false' | '('EXPRESSION')'
AST* parsePrimary(Parser* parser) {

    if(
        parser->current_token->token_type == Token::TokenType::INT
        || parser->current_token->token_type == Token::TokenType::UINT
        || parser->current_token->token_type == Token::TokenType::FLOAT
        || parser->current_token->token_type == Token::TokenType::BOOL
        || parser->current_token->token_type == Token::TokenType::MAT2
        || parser->current_token->token_type == Token::TokenType::MAT2X2
        || parser->current_token->token_type == Token::TokenType::MAT2X3
        || parser->current_token->token_type == Token::TokenType::MAT2X4
        || parser->current_token->token_type == Token::TokenType::MAT3
        || parser->current_token->token_type == Token::TokenType::MAT3X2
        || parser->current_token->token_type == Token::TokenType::MAT3X3
        || parser->current_token->token_type == Token::TokenType::MAT3X4
        || parser->current_token->token_type == Token::TokenType::MAT4
        || parser->current_token->token_type == Token::TokenType::MAT4X2
        || parser->current_token->token_type == Token::TokenType::MAT4X3
        || parser->current_token->token_type == Token::TokenType::MAT4X4
    ) {
        printf("\033[31mUnsuported primary \033[0m'%s'\n", parser->current_token->value);
        exit(-1);
    }

    if( parser->current_token->token_type == Token::TokenType::IDENTIFIER) {
        AST* root = initAST(AST::ASTType::IDENTIFIER);
        root->identifier = parser->current_token->value;
        parserReadToken(parser, Token::TokenType::IDENTIFIER);
        return root;
    }

    if(parser->current_token->token_type == Token::TokenType::TRUE) {
        AST* root = initAST(AST::ASTType::BOOL);
        root->bool_value = true;
        return root;
    }

    if(parser->current_token->token_type == Token::TokenType::FALSE) {
        AST* root = initAST(AST::ASTType::BOOL);
        root->bool_value = false;
        return root;
    }

    if(parser->current_token->token_type == Token::TokenType::INTEGER) {
        AST* root = initAST(AST::ASTType::INTEGER);
        root->integer_value = atoi(parser->current_token->value);
        parserReadToken(parser, Token::TokenType::INTEGER);
        return root;
    }


    if(parser->current_token->token_type == Token::TokenType::FLOATING) {
        AST* root = initAST(AST::ASTType::FLOAT);
        root->integer_value = atof(parser->current_token->value);
        parserReadToken(parser, Token::TokenType::FLOATING);
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