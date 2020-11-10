// https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-function-syntax
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "AST.hpp"
#include "Types.hpp"
#include "Semantics.hpp"
#include "Block.hpp"
#include "InterpolationModifier.hpp"
#include <vector>

namespace HLSL {

// FUNC_STORAGE_CLASS -> 'inline' | ''
enum FuncStorageClass {
    FUNCSTORAGECLASS_NONE,
    FUNCSTORAGECLASS_INLINE,
};

// MODIFIER? TYPE IDENTIFIER (':' SEMANTIC)? (':' INTERPOLATION_MODIFIER)? ('=' Initializer(s))?
// MODIFIER -> 'in' | 'inout' | 'out' | 'uniform'
enum Modifier {
    MODIFIER_NONE,
    MODIFIER_IN,
    MODIFIER_INOUT,
    MODIFIER_OUT,
    MODIFIER_UNIFORM,
};

// https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-function-parameters
struct FunctionArgument {
    Modifier argument_modifier;
    ASTType* argument_type;
    char* argument_name;
    Semantic* argument_semantic;
    InterpolationModifier argument_interpolation_modifier;
    ASTLiteral* argument_initializer;
};

struct FuncAttribute {
    std::vector<AST*> paramenters;
    const char* name;
};

struct ASTFunctionDeclaration: AST {
    explicit ASTFunctionDeclaration();

    FuncStorageClass func_decl_storage_class;
    std::vector<FuncAttribute*> func_decl_attributes;
    ASTType* func_decl_return_type;
    AST* return_type;
    bool precise;
    char* func_decl_name;
    std::vector<FunctionArgument*> func_decl_arguments;
    Semantic* func_decl_semantic;
    ASTBlock* func_decl_body;
};


// FUNC_STORAGE_CLASS CLIP_PLANES? ('precise')? TYPE INTENTIFIER '(' ARGUMENT_LIST ')' (':' SEMANTIC)? BLOCK
ASTFunctionDeclaration* parseFunctionDeclaration(Parser* parser);

}

#endif
