#include "AST.hpp"
#include "StorageQualifiers.hpp"
#include "Variables.hpp"
#include "LayoutQualifier.hpp"
#include "PrecisionQualifiers.hpp"
#include "InterpolationModifier.hpp"
#include "BaseType.hpp"
#include <vector>

namespace GLSL {

struct ASTBlockDeclaration: AST {
    explicit ASTBlockDeclaration();
    AST* layout;
    AST* storage_qualifier;
    std::vector<InterpolationQualifier> interpolation_qualifiers;
    char* name;
    char* instance_name;

    std::vector<ASTVariableDeclaration*> members;
};

ASTBlockDeclaration* parseBlock(Parser* parser);

}