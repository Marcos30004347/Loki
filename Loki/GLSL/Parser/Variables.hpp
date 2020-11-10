#ifndef GLSL_VARIABLES
#define GLSL_VARIABLES

#include "AST.hpp"
#include "StorageQualifiers.hpp"
#include "LayoutQualifier.hpp"
#include "PrecisionQualifiers.hpp"
#include "InterpolationModifier.hpp"
#include "Types.hpp"
#include <vector>

namespace GLSL {

struct ASTVarDecl: AST {
    explicit ASTVarDecl();
    ASTStorageQualifiers* storage_qualifier;

    PrecisionQualifier precision_qualifier;

    ASTLayout* layout;
    std::vector<InterpolationQualifier> interpolation_qualifiers;
    ASTType* var_decl_type;
    char* name;
    AST* default_value;
    std::vector<AST*> var_decl_dim_lenghts;
};

ASTVarDecl* parseVarDecl(Parser* parser);
bool isVariableDeclaration(Parser* parser);

}
#endif
