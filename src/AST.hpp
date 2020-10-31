
#ifndef ABSTRACT_SYNTAX_TREE
#define ABSTRACT_SYNTAX_TREE

struct Scope;

enum Type {
    VOID,
    INT,
};

enum ExpOperation {
    BINARY_NONE,
    ADDITION,
    SUBTRACTION,
    DIVISION,
    MULTIPLICATION,
    DIFFERENT,
    EQUALS,
    GREATER,
    LESS,
    GREATER_OR_EQUAL,
    LESS_OR_EQUAL,
};


enum UExOperation {
    UNARY_NONE,
    EXCLAMATION,
    MINUS,
};


struct AST {
    enum ASTType {
        NO_OP,
        INTEGER,
        BINARY_EXPRESSION,
        UNARY_EXPRESSION,
        COMPOUND,
    };

    //AST data:
    ASTType type;
    Scope* scope;

    //INTEGER
    int integer_value;

    // BINARY EXPRESSION
    AST* binary_exp_left_operand;
    ExpOperation binary_exp_operation;
    AST* binary_exp_right_operand;

    // UNARY EXPRESSION
    UExOperation unary_binary_exp_operation;
    AST* unary_binary_exp_right_operand;

    //COMPOUND
    AST** compound_list;
    unsigned int compound_list_count;
};

AST* initAST(AST::ASTType type);
void printAST(AST* root);
#endif