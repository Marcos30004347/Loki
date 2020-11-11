#include "AST.hpp"
#include "Parser.hpp"
#include "Declarations.hpp"
#include <vector>

namespace GLSL {

struct ASTBuffer: AST {
    explicit ASTBuffer();
    char* name;
    char* extern_name;
    std::vector<AST*> members;
};


ASTBuffer* parseBuffer(Parser* parser);

}