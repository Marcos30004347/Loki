#ifndef GLSL_BLOCK_H
#define GLSL_BLOCK_H

#include "AST.hpp"
#include "Parser.hpp"

#include <vector>

namespace GLSL {

struct ASTBlock: AST {
    explicit ASTBlock();
    std::vector<AST*> block_statements;
};

ASTBlock* parseBlock(Parser* parser);

}

#endif