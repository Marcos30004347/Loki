#include "AST.hpp"

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <vector>

AST* initAST(AST::ASTType type) {
    AST* ast = (AST*)malloc(sizeof(AST));
    ast->scope = nullptr;
    ast->type = type;

    //INTEGER
    ast->integer_value = 0;

    // COMPOUND
    ast->compound_list = nullptr;
    ast->compound_list_count = 0;

    // BINARY EXPRESSION
    ast->binary_exp_left_operand = nullptr;
    ast->binary_exp_operation = ExpOperation::BINARY_NONE;
    ast->binary_exp_right_operand = nullptr;

    // UNARY EXPRESSION
    ast->unary_binary_exp_operation = UExOperation::UNARY_NONE;
    ast->unary_binary_exp_right_operand = nullptr;
    return ast;
}

void printAST(AST* root) {

    if(root->type == AST::ASTType::BINARY_EXPRESSION) {
        printf("BYNARY OPERATION:\n");
        printAST(root->binary_exp_left_operand);
        printf("op: %i:\n", root->binary_exp_operation);
        printAST(root->binary_exp_right_operand);
    }

    if(root->type == AST::ASTType::UNARY_EXPRESSION) {
        printf("UNARY OPERATION:\n");
        printf("op: %i:\n", root->unary_binary_exp_operation);
        printAST(root->unary_binary_exp_right_operand);
    }

    if(root->type == AST::ASTType::INTEGER) {
        printf("INTEGER:\n");
        printf("int value: %i:\n", root->integer_value);
    }

}