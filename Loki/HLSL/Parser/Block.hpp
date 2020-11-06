#include "AST.hpp"
#include "Parser.hpp"

#include <vector>

namespace HLSL {

struct ASTBlock: AST {
    explicit ASTBlock();
    std::vector<AST*> block_statements;
};

ASTBlock* parseBlock(Parser* parser);

}