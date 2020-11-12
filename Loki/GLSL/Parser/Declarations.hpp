#ifndef GLSL_DECLARATIONS
#define GLSL_DECLARATIONS

#include "AST.hpp"
#include "StorageQualifiers.hpp"
#include "LayoutQualifier.hpp"
#include "PrecisionQualifiers.hpp"
#include "InterpolationModifier.hpp"
#include "Types.hpp"
#include "Block.hpp"
#include <vector>

namespace GLSL {
// MODIFIER? TYPE IDENTIFIER (':' SEMANTIC)? (':' INTERPOLATION_MODIFIER)? ('=' Initializer(s))?
// MODIFIER -> 'in' | 'inout' | 'out' | 'uniform'

// https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-function-parameters
struct FunctionArgument {
    ASTStorageQualifiers* argument_modifier;
    ASTType* argument_type;
    char* argument_name;
    AST* argument_initializer;
};

struct ASTFunctionDeclaration: AST {
    explicit ASTFunctionDeclaration();

    ASTType* func_decl_return_type;
    bool built_in;
    char* func_decl_name;
    std::vector<FunctionArgument*> func_decl_arguments;
    ASTBlock* func_decl_body;
};


// FUNC_STORAGE_CLASS CLIP_PLANES? ('precise')? TYPE INTENTIFIER '(' ARGUMENT_LIST ')' (':' SEMANTIC)? BLOCK
ASTFunctionDeclaration* parseFunctionDeclaration(Parser* parser);



struct ASTVarDecl: AST {
    explicit ASTVarDecl();
    ASTStorageQualifiers* storage_qualifier;
    PrecisionQualifier precision_qualifier;

    bool is_build_in = true;

    ASTLayout* layout;
    std::vector<InterpolationQualifier> interpolation_qualifiers;
    ASTType* var_decl_type;
    char* name;
    AST* default_value;
    std::vector<AST*> var_decl_dim_lenghts;
};

struct ASTBuffer: AST {
    explicit ASTBuffer();
    char* name;
    char* extern_name;

    ASTLayout* layout;
    ASTStorageQualifiers* storage_qualifier;

    std::vector<AST*> members;
};

AST* parseDeclaration(Parser* parser);

}
#endif
