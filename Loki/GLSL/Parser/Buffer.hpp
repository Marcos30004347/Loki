#include "AST.hpp"
#include "Parser.hpp"
#include "Variables.hpp"
#include <vector>

namespace GLSL {

struct ASTBuffer: AST {
    explicit ASTBuffer();
    char* name;
    char* extern_name;
    std::vector<ASTVariableDeclaration*> members;
};


ASTBuffer* parseBuffer(Parser* parser);

}