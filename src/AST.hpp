
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
    BINARY_OR,
    BINARY_AND,
    OR,
    AND
};



enum UExOperation {
    UNARY_NONE,
    EXCLAMATION,
    PRE_ADD_ADD,
    AFTER_ADD_ADD,
    PRE_MINUS_MINUS,
    AFTER_MINUS_MINUS,
    MINUS,
};

enum BuildInType {
    TYPE_VOID = 0,
    TYPE_INT,
};

enum AssingmentType {
    ASSIGN_NONE,
    ASSIGN_ASSIGN,
    ASSIGN_PIPE_ASSIGN,
    ASSIGN_AMPERSAND_ASSIGN,
    ASSIGN_MULTIPLY_ASSIGN,
    ASSIGN_DIVIDE_ASSIGN,
};

struct AST {
    enum ASTType {
        UNDEFINED,
        INTEGER,
        BINARY_EXPRESSION,
        UNARY_EXPRESSION,
        IDENTIFIER,
        VARIABLES_DECLARATIONS,
        DECLARATIONS,
        STATEMETNS,
        BLOCK,
        ASSIGNMENT,
        IF,
        WHILE,
        DO_WHILE,
        SWITCH,
        CASE,
        FOR,
        FUNCTION_CALL,
        FUNCTION_DECLARATION,
        FUNCTION_ARGUMENT,
        RETURN,
        STRUCT,
        BREAK,
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
    AST** vars_def_name;
    AST** vars_def_value;
    BuildInType vars_def_type;
    unsigned int vars_def_count;

    // ASSIGNMENT
    AST* assignment_right;
    AST* assignment_left;
    AssingmentType assignment_type;

    // BLOCK
    AST* block_statements;

    //STATEMETNS
    AST** statements_list;
    unsigned int statements_list_count;

    // IF
    AST* if_condition;
    AST* if_statements;
    AST* if_else_ast;

    // WHILE
    AST* while_condition;
    AST* while_statements;

    // DO_WHILE
    AST* do_while_statements;
    AST* do_while_condition;

    // FOR
    AST* for_statement1;
    AST* for_statement2;
    AST* for_statement3;
    AST* for_body;

    //FUNCTION CALL
    AST* func_call_identifier;
    AST** func_call_arguments;
    unsigned int func_call_arguments_count;
    
    //FUNCTION DEFINITION
    BuildInType func_dec_return_type;
    AST* func_dec_identifier;
    AST* func_dec_body;
    AST** func_dec_arguments;
    unsigned int func_dec_arguments_count;

    //FUNCTION_ARGUMENT
    BuildInType func_argument_type;
    AST* func_argument_id;

    // RETURN
    AST* return_value;

    //DECLARATINONS
    AST** declarations_list;
    unsigned int declarations_list_count;

    // STRUCT
    AST* struct_declarations;
    AST* struct_identifier;

    //SWITCH
    AST* switch_expression;
    AST** switch_cases;
    AST* switch_default_case;
    unsigned int switch_cases_count;

    // CASE
    AST* case_expression;
    AST* case_statement;
};

AST* initAST(AST::ASTType type);
void printAST(AST* root, int tabs = 0);
#endif