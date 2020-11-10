#ifndef HLSL_AST_H
#define HLSL_AST_H

namespace HLSL {

enum NodeType {

    AST_PROGRAM,
    AST_LITERAL,
    AST_TYPE_DECL,

    AST_VARIABLE_DECLARATION,
    AST_FUNCTION_DECLARATION,
    AST_BUFFER_DECLARATION,
    AST_STRUCT_DECLARATION,
    AST_TYPE_CONSTRUCTOR,

    AST_BLOCK,

    AST_EXPRESSION_BINARY,
    AST_EXPRESSION_UNARY,

    AST_FUNCTION_CALL,
    AST_SYMBOL, // defined variables, ...
    AST_ASSIGNMENT,
    AST_MEMBER_ACCESS,
    AST_ARRAY_ACCESS,
    AST_TERNARY,

    AST_RETURN_STATEMENT,
    AST_DISCARD_STATEMENT,
    AST_BREAK_STATEMENT,
    AST_CONTINUE_STATEMENT,
    AST_IF_STATEMENT,
    AST_FOR_STATEMENT,
    AST_WHILE_STATEMENT,
    AST_DO_WHILE_STATEMENT,
    AST_SWITCH_STATEMENT,
    AST_CASE_STATEMENT,
    AST_DEFAULT_STATEMENT,
};


struct AST {
    NodeType ast_type;
    explicit AST(NodeType type): ast_type{type} {}
    void print(int tabs = 0);
    // Reconstruct the string as a hlsl valid shader in the stdout
    void write(bool semicollon = true);
};


}

#endif