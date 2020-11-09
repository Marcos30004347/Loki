#include "AST.hpp"
#include "StorageQualifiers.hpp"
#include "LayoutQualifier.hpp"
#include "PrecisionQualifiers.hpp"
#include "InterpolationModifier.hpp"
#include "BaseType.hpp"
#include <vector>

namespace GLSL {

struct ASTVariableDeclaration: AST {
    explicit ASTVariableDeclaration();
    ASTStorageQualifiers* storage_qualifier;

    PrecisionQualifier precision_qualifier;

    ASTLayout* layout;
    std::vector<InterpolationQualifier> interpolation_qualifiers;
    BaseType* type;
    char* name;
    AST* default_value;
    bool is_array;
    AST* array_size;
};

ASTVariableDeclaration* parseVariableDeclaration(Parser* parser);

}
