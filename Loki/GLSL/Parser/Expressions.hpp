// https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-expressions
// https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-operators

#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "AST.hpp"
#include "Parser.hpp"
#include "Declarations.hpp"
#include "FunctionCall.hpp"

namespace GLSL {

enum BinaryOp {
    BINARY_OP_AND, // a&&y
    BINARY_OP_OR, // a||y
    BINARY_OP_ADD, // a+y
    BINARY_OP_SUB, // a-y
    BINARY_OP_MUL, // a*y
    BINARY_OP_DIV, // a/y
    BINARY_OP_LESS, // a<y
    BINARY_OP_GREATER, // a>y
    BINARY_OP_LESS_OR_EQUAL, // a<=b
    BINARY_OP_GREATER_OR_EQUAL, // a>=b
    BINARY_OP_COMPARISON_EQUAL, // a == b
    BINARY_OP_COMPARISON_NOT_EQUAL, // a != b
    BINARY_OP_MOD, // a%b

    // Bitwise operators
    BINARY_OP_BITWISE_AND, // '&'
    BINARY_OP_BITWISE_OR, // '|'
    BINARY_OP_BITWISE_EXLUSIVE_OR, // '^'
    BINARY_OP_BITWISE_SHIFT_LEFT, // '<<'
    BINARY_OP_BITWISE_SHIFT_RIGHT, // '>>'
    BINARY_LOGICAL_EXCLUSIVE_OR, // "^^"
};

enum UnaryOp {
    UNARY_OP_NEGATIVE,       // -x
    UNARY_OP_POSITIVE,       // +x
    UNARY_OP_NOT,            // !x
    UNARY_OP_PRE_INCREMENT,   // ++x
    UNARY_OP_PRE_DECREMENT,   // --x
    UNARY_OP_POST_INCREMENT,  // x++
    UNARY_OP_POST_DECREMENT,  // x--
    UNARY_OP_LOGICAL_NOT // ~x
};

enum AssignmentOp {
    ASSIGNMENT_EQUAL, // =
    ASSIGNMENT_TIMES_EQUAL, // *=
    ASSIGNMENT_PLUS_EQUAL, // +=
    ASSIGNMENT_MINUS_EQUAL, // -=
    ASSIGNMENT_DIVIDE_EQUAL, // /=
    ASSIGNMENT_XOR_EQUAL, // ^/
    ASSIGNMENT_OR_EQUAL, // |=
    ASSIGNMENT_AND_EQUAL, // &=
    ASSIGNMENT_LEFT_SHIFT_EQUAL, // <<=
    ASSIGNMENT_RIGHT_SHIFT_EQUAL, // >>=
    ASSIGNMENT_MOD_EQUAL, // %=
};

struct ASTAssignment: AST {
    explicit ASTAssignment();

    AssignmentOp assignment_op;

    AST* assignment_left_operand;
    AST* assignment_right_operand;
};


struct ASTBinaryExpression: AST {
    explicit ASTBinaryExpression();

    BinaryOp bin_exp_op;

    AST* bin_exp_left_operand;
    AST* bin_exp_right_operand;
};

struct ASTUnaryExpression: AST {
    explicit ASTUnaryExpression();
    UnaryOp un_exp_operator;
    AST* un_exp_operand;
};

struct ASTSymbol: AST {
    explicit ASTSymbol();
    char* symbol_name;
};


struct ASTMemberAccess: AST {
    explicit ASTMemberAccess();
    AST* member_left;
    AST* member_right;
};

struct ASTArrayAccess: AST {
    explicit ASTArrayAccess();
    AST* member_left;
    AST* arra_index;
    AST* member_right;
};

struct ASTTernary: AST {
    explicit ASTTernary();
    AST* ternary_expression;
    AST* ternary_left;
    AST* ternary_right;
};

AST* parseExpression(Parser* parser, bool constant = false);
AST* parseTernary(Parser* parser, bool constant = false);
AST* parseEquality(Parser* parser, bool constant = false);
AST* parseBooleans(Parser* parser, bool constant = false);
AST* parseBitwise(Parser* parser, bool constant = false);
AST* parseComparison(Parser* parser, bool constant = false);
AST* parseBitwiseShift(Parser* parser, bool constant = false);
AST* parseTerm(Parser* parser, bool constant = false);
AST* parseFactor(Parser* parser, bool constant = false);
AST* parseUnary(Parser* parser, bool constant = false);
AST* parseArrayAccess(Parser* parser, bool constant = false);
AST* parseMemberAccess(Parser* parser, bool constant = false);
AST* parsePostfixSuffixUnary(Parser* parser, bool constant = false);
AST* parsePrimary(Parser* parser, bool constant = false);

}

#endif