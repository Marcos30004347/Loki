#ifndef ABSTRACT_SYNTAX_TREE
#define ABSTRACT_SYNTAX_TREE


enum ChannelType {
    CHANNEL_NONE,
    CHANNEL_OUT,
    CHANNEL_IN,
};

enum AssingmentType {
    ASSIGN_NONE,
    ASSIGN_ASSIGN,
    ASSIGN_PIPE_ASSIGN,
    ASSIGN_AMPERSAND_ASSIGN,
    ASSIGN_MULTIPLY_ASSIGN,
    ASSIGN_DIVIDE_ASSIGN,
};

enum Type {
    TYPE_VOID = 0,
    TYPE_STRUCT,
    TYPE_INT,
    TYPE_UINT,
    TYPE_FLOAT,
    TYPE_BOOL,
    TYPE_VEC2,
    TYPE_VEC3,
    TYPE_VEC4,
    TYPE_MAT2,
    TYPE_MAT2X2,
    TYPE_MAT2X3,
    TYPE_MAT2X4,
    TYPE_MAT3,
    TYPE_MAT3X2,
    TYPE_MAT3X3,
    TYPE_MAT3X4,
    TYPE_MAT4,
    TYPE_MAT4X2,
    TYPE_MAT4X3,
    TYPE_MAT4X4,
    TYPE_SAMPLER,
    TYPE_SAMPLER3D,
};


enum BinaryOperation {
    BINARY_NONE,
    BINARY_ADDITION,
    BINARY_SUBTRACTION,
    BINARY_DIVISION,
    BINARY_MULTIPLICATION,
    BINARY_DIFFERENT,
    BINARY_EQUALS_EQUALS,
    BINARY_GREATER,
    BINARY_LESS,
    BINARY_GREATER_OR_EQUAL,
    BINARY_LESS_OR_EQUAL,
    BINARY_BINARY_OR,
    BINARY_BINARY_AND,
    BINARY_OR,
    BINARY_AND
};

enum UnaryOperation {
    UNARY_NONE,
    UNARY_EXCLAMATION,
    UNARY_PRE_ADD_ADD,
    UNARY_AFTER_ADD_ADD,
    UNARY_PRE_MINUS_MINUS,
    UNARY_AFTER_MINUS_MINUS,
    UNARY_MINUS,
};


struct AST {
    enum ASTTypeDecl {
        UNDEFINED,
        INTEGER,
        BINARY_EXPRESSION,
        UNARY_EXPRESSION,
        IDENTIFIER,
        VARIABLES_DECLARATIONS,
        VARIABLE_DECLARATION,
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
        CHANNEL,
        FLOAT,
        BOOL,
        TYPE,
        CONTEXT,
        EXPORT,
        UNIFORM,
        BUFFER,
    };

    //AST data:
    ASTTypeDecl ast_type;

    //INTEGER
    int integer_value;

    //FLOAT
    int float_value;

    // BINARY EXPRESSION
    AST* binary_exp_left_operand;
    BinaryOperation binary_exp_operation;
    AST* binary_exp_right_operand;

    // UNARY EXPRESSION
    UnaryOperation unary_binary_exp_operation;
    AST* unary_binary_exp_right_operand;

    // IDENTIFIER
    char* identifier;

    // VARIABLES_DECLARATIONS
    AST** vars_declarations;
    unsigned int vars_declarations_count;

    // VARIABLE DECLARATION
    AST* var_def_identifier;
    AST* var_def_value;
    AST* var_def_channel;
    AST* var_def_type_identifier;

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
    AST* func_dec_return_type_identifier;
    AST* func_dec_identifier;
    AST* func_dec_body;
    AST** func_dec_arguments;
    unsigned int func_dec_arguments_count;

    //FUNCTION_ARGUMENT
    AST* func_argument_type_identifier;
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

    // CHANNEL
    AST* channel_identifier;
    ChannelType channel_type;

    // BOOL
    bool bool_value;

    // TYPE
    Type type_type;
    AST* type_struct_identifier;

    // CONTEXT
    AST* context_declarations;
    AST* context_identifier;

    // EXPORT
    AST** export_keys_identifiers;
    AST** export_values_identifiers;
    unsigned int export_pairs_count;

    // UNIFORM
    AST* uniform_type;
    AST* uniform_identifier;

    // BUFFER
    AST* buffer_declarations;
    AST* buffer_identifier;
};

AST* initAST(AST::ASTTypeDecl type);

void printAST(AST* root, int tabs = 0);

#endif