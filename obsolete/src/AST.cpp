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

const char* TypesNames[] = {
    "void",
    "struct",
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

AST* initAST(AST::ASTTypeDecl type) {
    AST* ast = (AST*)malloc(sizeof(AST));
    ast->ast_type = type;

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
    ast->var_def_identifier = nullptr;

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
    ast->func_dec_return_type_identifier = nullptr;
    ast->func_dec_identifier = nullptr;
    ast->func_dec_arguments = nullptr;
    ast->func_dec_arguments_count = 0;
    ast->func_dec_body = nullptr;

    //FUNCTION_ARGUMENT
    ast->func_argument_type_identifier = nullptr;
    ast->func_argument_id = nullptr;

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

    // CONTEXT
    ast->context_declarations = nullptr;
    ast->context_identifier = nullptr;

    // EXPORT
    ast->export_keys_identifiers = nullptr;
    ast->export_values_identifiers = nullptr;
    ast->export_pairs_count = 0;

    // UNIFORM
    ast->uniform_type = nullptr;
    ast->uniform_identifier = nullptr;

    // BUFFER
    ast->buffer_declarations = nullptr;
    ast->buffer_identifier = nullptr;
}

void printAST(AST* root, int tabs) {

    if(root->ast_type == AST::ASTTypeDecl::FOR) {
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

    if(root->ast_type == AST::ASTTypeDecl::RETURN) {
        printf("%*cRETURN:\n", tabs, ' ');
        printf("%*cRETURN VALUE:\n", tabs, ' ');
        printAST( root->return_value, tabs+3);
    }

    if(root->ast_type == AST::ASTTypeDecl::FUNCTION_DECLARATION) {
        printf("%*cFUNCTION DECLARATION:\n", tabs, ' ');
        printf("%*cFUNCTION RETURN TYPE:\n", tabs, ' ');
        printAST( root->func_dec_return_type_identifier, tabs+3);

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

    if(root->ast_type == AST::ASTTypeDecl::FUNCTION_ARGUMENT) {
        printf("%*cFUNCTION ARGUMENT:\n", tabs, ' ');
        printf("%*cTYPE:\n", tabs, ' ');
        printAST(root->func_argument_type_identifier, tabs + 3);

        printf("%*cFUNCTION INDENTIFIER:\n", tabs, ' ');
        printAST(root->func_argument_id, tabs + 3);
    }

    if(root->ast_type == AST::ASTTypeDecl::IF) {
        printf("%*cIF:\n", tabs, ' ');
        printf("%*cCONDITION:\n", tabs, ' ');
        printAST(root->if_condition, tabs + 3);
        printf("%*cSTATEMENTS:\n", tabs, ' ');
        printAST(root->if_statements, tabs + 3);
        printf("%*cELSE:\n", tabs, ' ');
        printAST(root->if_else_ast, tabs + 3);
    }

    if(root->ast_type == AST::ASTTypeDecl::WHILE) {
        printf("%*cWHILE:\n", tabs, ' ');
        printf("%*cCONDITION:\n", tabs, ' ');
        printAST(root->while_condition, tabs + 3);
        printf("%*cSTATEMENTS:\n", tabs, ' ');
        printAST(root->while_statements, tabs + 3);
    }

    if(root->ast_type == AST::ASTTypeDecl::DO_WHILE) {
        printf("%*cDO WHILE:\n", tabs, ' ');
        printf("%*cSTATEMENTS:\n", tabs, ' ');
        printAST(root->do_while_statements, tabs + 3);
        printf("%*cCONDITION:\n", tabs, ' ');
        printAST(root->do_while_condition, tabs + 3);
    }

    if(root->ast_type == AST::ASTTypeDecl::UNDEFINED) {
        printf("%*cUNDEFINED!\n", tabs, ' ');
    }

    if(root->ast_type == AST::ASTTypeDecl::BLOCK) {
        printf("%*cBLOCK:\n", tabs, ' ');
        printAST(root->block_statements, tabs + 3);
    }

    if(root->ast_type == AST::ASTTypeDecl::STATEMETNS) {
        printf("%*cSTATEMENTS:\n", tabs, ' ');
        for(int i=0; i<root->statements_list_count; i++) {
            printf("%*cSTATEMENT %i:\n", tabs, ' ', i);
            printAST(root->statements_list[i], tabs + 3);
        }
    }
    

    if(root->ast_type == AST::ASTTypeDecl::DECLARATIONS) {
        printf("%*cDECLARATIONS:\n", tabs, ' ');
        for(int i=0; i<root->declarations_list_count; i++) {
            printf("%*cDECLARATION %i:\n", tabs, ' ', i);
            printAST(root->declarations_list[i], tabs + 3);
        }
    }

    if(root->ast_type == AST::ASTTypeDecl::IDENTIFIER) {
        printf("%*cIDENTIFIER = '%s'\n", tabs, ' ', root->identifier);
    }

    if(root->ast_type == AST::ASTTypeDecl::VARIABLE_DECLARATION) {
        printf("%*cVARIABLE DECLARATION\n", tabs, ' ');
        printf("%*cTYPE:", tabs, ' ');
        printAST(root->var_def_type_identifier, tabs + 3);
        printf("%*cVARIABLE IDENTIFIER:\n", tabs, ' ');
        printAST(root->var_def_identifier, tabs+ 3);
        printf("%*cVARIABLE VALUE:\n", tabs, ' ');
        printAST(root->var_def_value, tabs + 3);
        printf("%*cVARIABLE CHANNEL:\n", tabs, ' ');
        printAST(root->var_def_channel, tabs + 3);
    }


    if(root->ast_type == AST::ASTTypeDecl::VARIABLES_DECLARATIONS) {
        printf("%*cVARIABLES DECLARATIONS:\n", tabs, ' ');
        for(int i=0; i<root->vars_declarations_count; i++) {
            printAST(root->vars_declarations[i], tabs+ 3);
        }
    }

    if(root->ast_type == AST::ASTTypeDecl::BINARY_EXPRESSION) {
        printf("%*cBYNARY OPERATION:\n", tabs, ' ');
        printf("%*cOPERATION = '%s'\n", tabs, ' ', BinaryOperationNames[root->binary_exp_operation]);
        printf("%*cLEFT:\n", tabs, ' ');
        printAST(root->binary_exp_left_operand, tabs+3);
        printf("%*cRIGHT:\n", tabs, ' ');
        printAST(root->binary_exp_right_operand, tabs+3);
    }

    if(root->ast_type == AST::ASTTypeDecl::CHANNEL) {
        printf("%*cCHANNEL:\n", tabs, ' ');
        printf("%*cCHANNEL TYPE = '%s'\n", tabs, ' ', ChannelTypeName[root->channel_type]);
        if(root->channel_type != ChannelType::CHANNEL_NONE) {
            printf("%*cCHANNEL IDENTIFIER:\n", tabs, ' ');
            printAST(root->channel_identifier, tabs+3);
        }
    }

    if(root->ast_type == AST::ASTTypeDecl::UNARY_EXPRESSION) {
        printf("%*cUNARY OPERATION:\n",tabs, ' ');
        printf("%*ccOPERATION = '%i'\n",tabs, ' ', root->unary_binary_exp_operation);
        printAST(root->unary_binary_exp_right_operand, tabs+3);
    }

    if(root->ast_type  == AST::ASTTypeDecl::ASSIGNMENT) {
        printf("%*cASSIGNMENT:\n",tabs, ' ');
        printf("%*cLEFT:\n",tabs, ' ');
        printAST(root->assignment_left, tabs+3);
        printf("%*cRIGHT:\n",tabs, ' ');
        printAST(root->assignment_right, tabs+3);
    }

    if(root->ast_type == AST::ASTTypeDecl::INTEGER) {
        printf("%*cINTEGER '%i'\n", tabs, ' ', root->integer_value);
    }

    if(root->ast_type == AST::ASTTypeDecl::STRUCT) {
        printf("%*cSTRUCT:\n", tabs, ' ');
        printf("%*cSTRUCT IDENTIFIER:\n", tabs, ' ');
        printAST(root->struct_identifier, tabs+3);
        printf("%*cSTRUCT DECLARATIONS:\n", tabs, ' ');
        printAST(root->struct_declarations, tabs+3);
    }

    if(root->ast_type == AST::ASTTypeDecl::SWITCH) {
        printf("%*cSWITCH:\n", tabs, ' ');
        printf("%*cDEFAULT:\n", tabs, ' ');
        printAST(root->switch_default_case, tabs+3);
        for(int i=0; i<root->switch_cases_count; i++) {
            printf("%*cCASE %i:\n", tabs, ' ', i);
            printAST(root->switch_cases[i], tabs+3);
        }
    }

    if(root->ast_type == AST::ASTTypeDecl::BREAK) {
        printf("%*cBREAK:\n", tabs, ' ');
    }

    if(root->ast_type == AST::ASTTypeDecl::CASE) {
        printf("%*cCASE:\n", tabs, ' ');
        printf("%*cEXPRESSION:\n", tabs, ' ');
        printAST(root->case_expression, tabs+3);
        printf("%*cSTATEMENT:\n", tabs, ' ');
        printAST(root->case_statement, tabs+3);
    }

    if(root->ast_type == AST::ASTTypeDecl::TYPE) {
        printf("%*cTYPE: %s\n", tabs, ' ', TypesNames[root->type_type]);
        if(root->type_type == Type::TYPE_STRUCT) {
            printf("%*cSTRUCT IDENTIFIER:\n", tabs, ' ');
            printAST(root->type_struct_identifier, tabs+3);
        }
    }

    if(root->ast_type == AST::ASTTypeDecl::CONTEXT) {
        printf("%*cCONTEXT:\n", tabs, ' ');
        printf("%*cIDENTIFIER:\n", tabs, ' ');
        printAST(root->context_identifier, tabs+3);
        printf("%*cDECLARATIONS:\n", tabs, ' ');
        printAST(root->context_declarations, tabs+3);
    }

    if(root->ast_type == AST::ASTTypeDecl::UNIFORM) {
        printf("%*cUNIFORM:\n", tabs, ' ');
        printf("%*cTYPE:\n", tabs, ' ');
        printAST(root->uniform_type, tabs+3);
        printf("%*cIDENTIFIER:\n", tabs, ' ');
        printAST(root->uniform_identifier, tabs+3);
    }

    if(root->ast_type == AST::ASTTypeDecl::EXPORT) {
        printf("%*cEXPORT:\n", tabs, ' ');
        for(int i=0; i<root->export_pairs_count; i++) {
            printf("%*cKEY[%i]:\n", tabs, ' ', i);
            printAST(root->export_keys_identifiers[i], tabs+3);
            printf("%*cVALUE[%i]:\n", tabs, ' ', i);
            printAST(root->export_values_identifiers[i], tabs+3);
        }
    }
}