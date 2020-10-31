
#ifndef ABSTRACT_SYNTAX_TREE
#define ABSTRACT_SYNTAX_TREE

struct Scope;

enum Type {
    VOID,
    INT,
};

enum BinaryOperation {
    BINARY_NONE,
    ADDITION,
    SUBTRACTION,
    DIVISION,
    MULTIPLICATION,
    DIFFERENT,
    EQUALS_EQUALS,
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

enum BuildInType {
    TYPE_VOID = 0,
    TYPE_INT,
};

struct AST {
    enum ASTType {
        NO_OP,
        INTEGER,
        BINARY_EXPRESSION,
        UNARY_EXPRESSION,
        IDENTIFIER,
        VARIABLES_DECLARATIONS,
        COMPOUND,
        ASSIGNMENT,
    };

    //AST data:
    ASTType type;
    Scope* scope;

    //INTEGER
    int integer_value;

    // BINARY EXPRESSION
    AST* binary_exp_left_operand;
    BinaryOperation binary_exp_operation;
    AST* binary_exp_right_operand;

    // UNARY EXPRESSION
    UExOperation unary_binary_exp_operation;
    AST* unary_binary_exp_right_operand;

    // IDENTIFIER
    char* identifier;

    // VARIABLES_DECLARATIONS
    char** vars_def_name;
    BuildInType vars_def_type;
    AST** vars_def_value;
    unsigned int vars_def_count;

    // ASSIGNMENT
    AST* assignment_right;
    AST* assignment_left;

    //COMPOUND
    AST** compound_list;
    unsigned int compound_list_count;
};

AST* initAST(AST::ASTType type);
void printAST(AST* root, int tabs = 0);
#endif