#include "Evaluation.hpp"
#include <stdio.h>

namespace HLSL {

template<typename T>
T evalUnary(T a, UnaryOp op) {
    switch (op) {
        case UnaryOp::UNARY_OP_NEGATIVE: return -a;
        case UnaryOp::UNARY_OP_POSITIVE: return +a;
        case UnaryOp::UNARY_OP_NOT: return !a;
        case UnaryOp::UNARY_OP_PRE_INCREMENT: return ++a;
        case UnaryOp::UNARY_OP_PRE_DECREMENT: return --a;
        case UnaryOp::UNARY_OP_POST_INCREMENT: return a++;
        case UnaryOp::UNARY_OP_POST_DECREMENT: return a--;
        case UnaryOp::UNARY_OP_LOGICAL_NOT: return ~a;
        default:
            printf("Unknow unary operation '%i'\n", op);
            exit(-1);
    }
}


template<typename T>
T evalBinary(T a, T b, BinaryOp op) {
    switch (op) {
        case BinaryOp::BINARY_OP_ADD: return a + b;
        case BinaryOp::BINARY_OP_SUB: return a - b;
        case BinaryOp::BINARY_OP_MUL: return a * b;
        case BinaryOp::BINARY_OP_DIV: return a / b;
        case BinaryOp::BINARY_OP_OR: return a || b;
        case BinaryOp::BINARY_OP_LESS: return a < b;
        case BinaryOp::BINARY_OP_LESS_OR_EQUAL: return a <= b;
        case BinaryOp::BINARY_OP_GREATER: return a > b;
        case BinaryOp::BINARY_OP_GREATER_OR_EQUAL: return a >= b;
        case BinaryOp::BINARY_OP_COMPARISON_EQUAL: return a == b;
        case BinaryOp::BINARY_OP_COMPARISON_NOT_EQUAL: return a != b;
        case BinaryOp::BINARY_OP_MOD: return a % b;
        case BinaryOp::BINARY_OP_BITWISE_OR: return a | b;
        case BinaryOp::BINARY_OP_AND: return a && b;
        case BinaryOp::BINARY_OP_BITWISE_AND: return a & b;
        case BinaryOp::BINARY_OP_BITWISE_EXLUSIVE_OR: return a ^ b;
        case BinaryOp::BINARY_OP_BITWISE_SHIFT_LEFT: return a << b;
        case BinaryOp::BINARY_OP_BITWISE_SHIFT_RIGHT: return a >> b;
        default:
            printf("Unknow binary operation '%i'\n", op);
            exit(-1);
    }
}

template<typename T>
Evaluation<T> evaluateBinaryExpression(AST* expression, Parser* parser) {
    ASTBinaryExpression* bin_exp;
    bin_exp = static_cast<ASTBinaryExpression*>(expression);
    Evaluation<T> left = evaluateConstantExpression<T>(bin_exp->bin_exp_left_operand, parser);
    Evaluation<T> right = evaluateConstantExpression<T>(bin_exp->bin_exp_right_operand, parser);
    
    Evaluation<T> value;
    value.value = evalBinary<T>(right.value, left.value, bin_exp->bin_exp_op);
    return value;
}


template<typename T>
Evaluation<T> evaluateUnaryExpression(AST* expression, Parser* parser) {
    ASTUnaryExpression* un_exp;
    un_exp = static_cast<ASTUnaryExpression*>(expression);
    Evaluation<T> operand = evaluateConstantExpression<T>(un_exp->un_exp_operand, parser);
    
    Evaluation<T> value;
    value.value = evalUnary<T>(operand.value, un_exp->un_exp_op);
    return value;
}


template<typename T>
Evaluation<T> evaluateConstantLiteral(AST* expression, Parser* parser) {
    ASTLiteral* literal = static_cast<ASTLiteral*>(expression);
    Evaluation<T> eval;
    switch (literal->type) {
        case ASTLiteral::Type::LITERAL_BOOL: eval->value = literal->bool_val; break;
        case ASTLiteral::Type::LITERAL_INT:eval->value = literal->int_val; break;
        case ASTLiteral::Type::LITERAL_FLOAT:eval->value = literal->float_val; break;
        case ASTLiteral::Type::LITERAL_STRING:eval->value = literal->string_val; break;
    }
    return eval;
}


template<typename T>
Evaluation<T> evaluateConstantSymbol(AST* expression, Parser* parser) {
    ASTSymbol* symbol = static_cast<ASTSymbol*>(expression);
    Evaluation<T> eval;
    ASTVarDecl* decl = parser->scope->getVariableDefinition(symbol->symbol_name);

    if(decl->var_decl_type_modifier != TypeModifier::TYPEMODIFIER_CONST) {
        printf("ERROR: non const variable '%s' in const expression!\n", decl->var_decl_name);
    }

    return evaluateConstantExpression(decl->var_decl_default_value);
}

template<typename T>
Evaluation<T> evaluateFunctionCall(AST* expression, Parser* parser) {
    ASTSymbol* symbol = static_cast<ASTSymbol*>(expression);
    Evaluation<T> eval;
    ASTVarDecl* decl = parser->scope->getVariableDefinition(symbol->symbol_name);

    if(decl->var_decl_type_modifier != TypeModifier::TYPEMODIFIER_CONST) {
        printf("ERROR: non const variable '%s' in const expression!\n", decl->var_decl_name);
    }

    return evaluateConstantExpression(decl->var_decl_default_value);
}

template<typename T>
Evaluation<T> evaluateConstantExpression(AST* expression, Parser* parser) {
    ASTLiteral* literal;

    switch(expression->ast_type) {
        case NodeType::AST_FUNCTION_CALL:
            return evaluateFunctionCall(expression, parser);
        case NodeType::AST_EXPRESSION_BINARY:
            return evaluateBinaryExpression(expression, parser);
        case NodeType::AST_EXPRESSION_UNARY:
            return evaluateUnaryExpression(expression, parser);
        case NodeType::AST_LITERAL:
            return evaluateConstantLiteral(expression, parser);
        default: printf("Unrrecognized constant expression of typr '%i'!\n", expression->ast_type) exit(-1);
    }
    printf("WARNING: EXPRESSIONS AINT BEING PARSED");
}


}