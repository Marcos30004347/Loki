#include "AST.hpp"
#include "Parser.hpp"

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

struct ASTFunctionCall: AST {
    explicit ASTFunctionCall();
    bool constexp;
    bool func_call_is_build_in;
    AST* func_call_symbol;
    std::vector<AST*> func_call_arguments;
};

struct FunctionArgument {
    ASTType* argument_type;
    char* argument_name;
    ASTLiteral* argument_initializer;
};

struct ASTFunctionDeclaration: AST {
    explicit ASTFunctionDeclaration();

    ASTType* func_decl_return_type;
    AST* return_type;
    bool precise;
    char* func_decl_name;
    std::vector<FunctionArgument*> func_decl_arguments;
    AST* func_decl_body;
};


AST* parseCall(Parser* parser, bool constant = false);


AST* parseExpression(Parser* parser, bool constant = false);

}