#include "AST.hpp"
#include "Parser.hpp"
#include "Variables.hpp"
#include "Types.hpp"
#include "StorageQualifiers.hpp"

#include <vector>

namespace GLSL {

struct ASTStruct: AST {
    explicit ASTStruct();
    AST* qualifier;
    char* name;
    char* declaration_name;

    std::vector<ASTVarDecl*> members;
};


ASTStruct* parseStruct(Parser* parser);

}