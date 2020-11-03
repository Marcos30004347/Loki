#include "AST.hpp"

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <vector>


#include "Operators.hpp"

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
    "|",
    "&"
    "||",
    "&&",
};


const char* UnaryOperationNames[] = {
    "None",
    "!",
    "++",
    "++",
    "--",
    "--",
    "-",
};

const char* ChannelTypeName[] = {
    "None",
    "Output",
    "Input",
};

const char* BuildInTypesNames[] = {
    "void",
    "int",
    "uint",
    "float",
    "bool",
    "vec2",
    "vec3",
    "vec4",
    "mat2",
    "mat2x2",
    "mat2x3",
    "mat2x4",
    "mat3",
    "mat3x2",
    "mat3x3",
    "mat3x4",
    "mat4",
    "mat4x2",
    "mat4x3",
    "mat4x4",
    "sampler",
    "sampler3d"
};

AST* initAST(AST::ASTType type) {
    AST* ast = (AST*)malloc(sizeof(AST));
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
    ast->unary_binary_exp_operation = UnaryOperation::UNARY_NONE;
    ast->unary_binary_exp_right_operand = nullptr;
    return ast;

    // IDENTIFIER
    ast->identifier = nullptr;

    // VARIABLES_DECLARATIONS
    ast->vars_declarations = nullptr;
    ast->vars_declarations_count = 0;

    // VARIABLE DECLARATION
    ast->var_def_identifier = nullptr;
    ast->var_def_value = nullptr;
    ast->var_def_channel = nullptr;
    ast->var_def_type = BuildInType::TYPE_VOID;

    //BLOCK
    ast->block_statements = nullptr;

    // ASSIGNMENT
    ast->assignment_right = nullptr;
    ast->assignment_left = nullptr;
    ast->assignment_type = AssingmentType::ASSIGN_NONE;

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

    // FUNCTION CALL
    ast->func_call_identifier = nullptr;
    ast->func_call_arguments = nullptr;
    ast->func_call_arguments_count = 0;

    // FUNCTION DECLARATION
    ast->func_dec_return_type = BuildInType::TYPE_VOID;
    ast->func_dec_identifier = nullptr;
    ast->func_dec_arguments = nullptr;
    ast->func_dec_arguments_count = 0;
    ast->func_dec_body = nullptr;


    //FUNCTION_ARGUMENT
    ast->func_argument_type = BuildInType::TYPE_VOID;
    ast->func_argument_id = nullptr;
    ast->func_argument_channel = nullptr;

    //RETURN
    ast->return_value = nullptr;

    //DECLARATIONS
    ast->declarations_list = nullptr;
    ast->declarations_list_count = 0;

    // STRUCT
    ast->struct_declarations = nullptr;
    ast->struct_identifier = nullptr;

    // SWITCH
    ast->switch_expression = nullptr;
    ast->switch_default_case = nullptr;
    ast->switch_cases = nullptr;
    ast->switch_cases_count = 0;

    // CASE
    ast->case_expression = nullptr;
    ast->case_statement = nullptr;

    // CHANNEL
    ast->channel_identifier = nullptr;
    ast->channel_type = ChannelType::CHANNEL_NONE;

    //FLOAT
    ast->float_value = 0;

    //BOOL
    ast->bool_value = false;
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

    if(root->type == AST::ASTType::RETURN) {
        printf("%*cRETURN:\n", tabs, ' ');
        printf("%*cRETURN VALUE:\n", tabs, ' ');
        printAST( root->return_value, tabs+3);
    }

    if(root->type == AST::ASTType::FUNCTION_DECLARATION) {
        printf("%*cFUNCTION DECLARATION:\n", tabs, ' ');
        printf("%*cFUNCTION RETURN TYPE = '%s'\n", tabs, ' ', BuildInTypesNames[root->func_dec_return_type]);
        printf("%*cFUNCTION IDENTIFIER:\n", tabs, ' ');

        printAST( root->func_dec_identifier, tabs+3);
        printf("%*cARGUMENTS = %i\n", tabs, ' ', root->func_dec_arguments_count);

        for(int i=0; i<root->func_dec_arguments_count; i++) {
            printf("%*cARGUMENT %i\n", tabs, ' ', i);
            printAST(root->func_dec_arguments[i], tabs+3);
        }

        printf("%*cBODY:\n", tabs, ' ');
        printAST(root->func_dec_body, tabs+3);
    }

    if(root->type == AST::ASTType::FUNCTION_ARGUMENT) {
        printf("%*cFUNCTION ARGUMENT:\n", tabs, ' ');
        printf("%*cTYPE = '%i'\n", tabs, ' ', root->func_argument_type);
        printf("%*cFUNCTION INDENTIFIER:\n", tabs, ' ');
        printAST(root->func_argument_id, tabs + 3);
        printf("%*cFUNCTION CHANNEL:\n", tabs, ' ');
        printAST(root->func_argument_channel, tabs + 3);
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

    if(root->type == AST::ASTType::UNDEFINED) {
        printf("%*cUNDEFINED!\n", tabs, ' ');
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
    

    if(root->type == AST::ASTType::DECLARATIONS) {
        printf("%*cDECLARATIONS:\n", tabs, ' ');
        for(int i=0; i<root->declarations_list_count; i++) {
            printf("%*cDECLARATION %i:\n", tabs, ' ', i);
            printAST(root->declarations_list[i], tabs + 3);
        }
    }

    if(root->type == AST::ASTType::IDENTIFIER) {
        printf("%*cIDENTIFIER = '%s'\n", tabs, ' ', root->identifier);
    }

    if(root->type == AST::ASTType::VARIABLE_DECLARATION) {
        printf("%*cVARIABLE DECLARATION\n", tabs, ' ');
        printf("%*cTYPE: %s\n", tabs, ' ', BuildInTypesNames[root->var_def_type]);
        printf("%*cVARIABLE IDENTIFIER:\n", tabs, ' ');
        printAST(root->var_def_identifier, tabs+ 3);
        printf("%*cVARIABLE VALUE:\n", tabs, ' ');
        printAST(root->var_def_value, tabs + 3);
        printf("%*cVARIABLE CHANNEL:\n", tabs, ' ');
        printAST(root->var_def_channel, tabs + 3);
    }


    if(root->type == AST::ASTType::VARIABLES_DECLARATIONS) {
        printf("%*cVARIABLES DECLARATIONS:\n", tabs, ' ');
        for(int i=0; i<root->vars_declarations_count; i++) {
            printAST(root->vars_declarations[i], tabs+ 3);
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

    if(root->type == AST::ASTType::CHANNEL) {
        printf("%*cCHANNEL:\n", tabs, ' ');
        printf("%*cCHANNEL TYPE = '%s'\n", tabs, ' ', ChannelTypeName[root->channel_type]);
        printf("%*cCHANNEL IDENTIFIER:\n", tabs, ' ');
        printAST(root->channel_identifier, tabs+3);
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
        printf("%*cINTEGER '%i'\n", tabs, ' ', root->integer_value);
    }

    if(root->type == AST::ASTType::STRUCT) {
        printf("%*cSTRUCT:\n", tabs, ' ');
        printf("%*cSTRUCT IDENTIFIER:\n", tabs, ' ');
        printAST(root->struct_identifier, tabs+3);
        printf("%*cSTRUCT DECLARATIONS:\n", tabs, ' ');
        printAST(root->struct_declarations, tabs+3);
    }

    if(root->type == AST::ASTType::SWITCH) {
        printf("%*cSWITCH:\n", tabs, ' ');
        printf("%*cDEFAULT:\n", tabs, ' ');
        printAST(root->switch_default_case, tabs+3);
        for(int i=0; i<root->switch_cases_count; i++) {
            printf("%*cCASE %i:\n", tabs, ' ', i);
            printAST(root->switch_cases[i], tabs+3);
        }
    }

    if(root->type == AST::ASTType::BREAK) {
        printf("%*cBREAK:\n", tabs, ' ');
    }

    if(root->type == AST::ASTType::CASE) {
        printf("%*cCASE:\n", tabs, ' ');
        printf("%*cEXPRESSION:\n", tabs, ' ');
        printAST(root->case_expression, tabs+3);
        printf("%*cSTATEMENT:\n", tabs, ' ');
        printAST(root->case_statement, tabs+3);
    }
}