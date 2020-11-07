#ifndef STATEMENT_H
#define STATEMENT_H

#include "AST.hpp"
#include "Parser.hpp"

namespace HLSL {

struct ASTReturn: AST {
    explicit ASTReturn();
    AST* return_expression;
};

AST* parseStatement(Parser* parser);

}

#endif