#ifndef GLSL_STATEMENT_H
#define GLSL_STATEMENT_H

#include "AST.hpp"
#include "Parser.hpp"

namespace GLSL {

struct ASTReturn: AST {
    explicit ASTReturn();
    AST* return_expression;
};

AST* parseStatement(Parser* parser);

}

#endif