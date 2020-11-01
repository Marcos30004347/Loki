#include "AST.hpp"

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <vector>

const char* BinaryOperationNames[] = {
    "None",
    "+",
    "-",
    "/",
    "*",
    "!=",
    "==",
    ">",
    "<",
    ">=",
    "<=",
};

const char* BuildInTypesNames[] = {
    "void",
    "int"
};

AST* initAST(AST::ASTType type) {
    AST* ast = (AST*)malloc(sizeof(AST));
    ast->scope = nullptr;
    ast->type = type;

    //INTEGER
    ast->integer_value = 0;

    // STATEMENTS
    ast->statements_list = nullptr;
    ast->statements_list_count = 0;

    // BINARY EXPRESSION
    ast->binary_exp_left_operand = nullptr;
    ast->binary_exp_operation = BinaryOperation::BINARY_NONE;
    ast->binary_exp_right_operand = nullptr;

    // UNARY EXPRESSION
    ast->unary_binary_exp_operation = UExOperation::UNARY_NONE;
    ast->unary_binary_exp_right_operand = nullptr;
    return ast;

    // IDENTIFIER
    ast->identifier = nullptr;

    // VARIABLES_DECLARATIONS
    ast->vars_def_name = nullptr;
    ast->vars_def_type = BuildInType::TYPE_VOID;
    ast->vars_def_value = nullptr;
    ast->vars_def_count = 0;

    //BLOCK
    ast->block_statements = nullptr;

    // ASSIGNMENT
    ast->assignment_right = nullptr;
    ast->assignment_left = nullptr;

    // IF
    ast->if_condition = nullptr;
    ast->if_statements = nullptr;
    ast->if_else_ast = nullptr;

    // WHILE
    ast->while_condition = nullptr;
    ast->while_statements = nullptr;

    // DO_WHILE
    ast->do_while_statements = nullptr;
    ast->do_while_condition = nullptr;

    // FOR
    ast->for_statement1 = nullptr;
    ast->for_statement2 = nullptr;
    ast->for_statement3 = nullptr;
    ast->for_body = nullptr;
}

void printAST(AST* root, int tabs) {

    if(root->type == AST::ASTType::FOR) {
        printf("%*cFOR:\n", tabs, ' ');
        printf("%*cSTATEMENT0:\n", tabs, ' ');
        printAST(root->for_statement1, tabs + 3);
        printf("%*cSTATEMENT1:\n", tabs, ' ');
        printAST(root->for_statement2, tabs + 3);
        printf("%*cSTATEMENT0:\n", tabs, ' ');
        printAST(root->for_statement3, tabs + 3);
        printf("%*cBODY:\n", tabs, ' ');
        printAST(root->for_body, tabs + 3);
    }


    if(root->type == AST::ASTType::IF) {
        printf("%*cIF:\n", tabs, ' ');
        printf("%*cCONDITION:\n", tabs, ' ');
        printAST(root->if_condition, tabs + 3);
        printf("%*cSTATEMENTS:\n", tabs, ' ');
        printAST(root->if_statements, tabs + 3);
        printf("%*cELSE:\n", tabs, ' ');
        printAST(root->if_else_ast, tabs + 3);
    }

    if(root->type == AST::ASTType::WHILE) {
        printf("%*cWHILE:\n", tabs, ' ');
        printf("%*cCONDITION:\n", tabs, ' ');
        printAST(root->while_condition, tabs + 3);
        printf("%*cSTATEMENTS:\n", tabs, ' ');
        printAST(root->while_statements, tabs + 3);
    }

    if(root->type == AST::ASTType::DO_WHILE) {
        printf("%*cDO WHILE:\n", tabs, ' ');
        printf("%*cSTATEMENTS:\n", tabs, ' ');
        printAST(root->do_while_statements, tabs + 3);
        printf("%*cCONDITION:\n", tabs, ' ');
        printAST(root->do_while_condition, tabs + 3);
    }

    if(root->type == AST::ASTType::NO_OP) {
        printf("%*cNO_OP:\n", tabs, ' ');
    }

    if(root->type == AST::ASTType::BLOCK) {
        printf("%*cBLOCK:\n", tabs, ' ');
        printAST(root->block_statements, tabs + 3);
    }

    if(root->type == AST::ASTType::STATEMETNS) {
        printf("%*cSTATEMENTS:\n", tabs, ' ');
        for(int i=0; i<root->statements_list_count; i++) {
            printf("%*cSTATEMENT %i:\n", tabs, ' ', i);
            printAST(root->statements_list[i], tabs + 3);
        }
    }
    
    if(root->type == AST::ASTType::IDENTIFIER) {
        printf("%*cIDENTIFIER = '%s'\n", tabs, ' ', root->identifier);
    }

    if(root->type == AST::ASTType::VARIABLES_DECLARATIONS) {
        printf("%*cVARIABLES DECLARATIONS:\n", tabs, ' ');
        printf("%*cTYPE: %s\n", tabs, ' ', BuildInTypesNames[root->vars_def_type]);
        for(int i=0; i<root->vars_def_count; i++) {
            printf("%*cVARIABLE NAME = %s\n", tabs, ' ', root->vars_def_name[i]);
            printf("%*cVARIABLE VALUE:\n", tabs, ' ');
            printAST(root->vars_def_value[i], tabs + 3);
        }
    }

    if(root->type == AST::ASTType::BINARY_EXPRESSION) {
        printf("%*cBYNARY OPERATION:\n", tabs, ' ');
        printf("%*cOPERATION = '%s'\n", tabs, ' ', BinaryOperationNames[root->binary_exp_operation]);
        printf("%*cLEFT:\n", tabs, ' ');
        printAST(root->binary_exp_left_operand, tabs+3);
        printf("%*cRIGHT:\n", tabs, ' ');
        printAST(root->binary_exp_right_operand, tabs+3);
    }

    if(root->type == AST::ASTType::UNARY_EXPRESSION) {
        printf("%*cUNARY OPERATION:\n",tabs, ' ');
        printf("%*ccOPERATION = '%i'\n",tabs, ' ', root->unary_binary_exp_operation);
        printAST(root->unary_binary_exp_right_operand, tabs+3);
    }

    if(root->type  == AST::ASTType::ASSIGNMENT) {
        printf("%*cASSIGNMENT:\n",tabs, ' ');
        printf("%*cLEFT:\n",tabs, ' ');
        printAST(root->assignment_left, tabs+3);
        printf("%*cRIGHT:\n",tabs, ' ');
        printAST(root->assignment_right, tabs+3);
    }

    if(root->type == AST::ASTType::INTEGER) {
        printf("%*cINTEGER = %i\n", tabs, ' ', root->integer_value);
    }

}