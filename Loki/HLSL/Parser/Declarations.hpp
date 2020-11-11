// https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-variable-syntax

#ifndef VARIABLES_H
#define VARIABLES_H


#include "AST.hpp"
#include "Parser.hpp"

#include "Types.hpp"
#include "Semantics.hpp"
#include "Register.hpp"
#include "PackOffset.hpp"
#include "InterpolationModifier.hpp"
#include "Block.hpp"


#include <vector>

namespace HLSL {

// STORAGE_Class -> 'extern' | 'nointerpolation' | 'precise' | 'shared' | 'groupshared' | 'static' | 'uniform' | 'volatile'
enum StorageClass {
    STORAGECLASS_NONE,
    STORAGECLASS_EXTERN,
    STORAGECLASS_NOINTERPOLATION,
    STORAGECLASS_PRECISE,
    STORAGECLASS_SHARED,
    STORAGECLASS_GROUPSHARED,
    STORAGECLASS_STATIC,
    STORAGECLASS_UNIFORM,
    STORAGECLASS_VOLATILE,
    STORAGECLASS_INLINE,
};

// TYPE_MODIFIER -> 'const' | 'row_major' | 'column_major'
enum TypeModifier {
    TYPEMODIFIER_NONE,
    TYPEMODIFIER_CONST,
    TYPEMODIFIER_ROW_MAJOR,
    TYPEMODIFIER_COLUMN_MAJOR
};

// https://docs.microsoft.com/en-us/windows/win32/direct3d10/d3d10-effect-annotation-syntax
// ANNOTATIONS -> '<'(TYPE IDENTIFIER '=' LITERAL';')*'>'
struct Annotation {
    ASTType* annotation_type;
    ASTLiteral* annotation_value;
    char* annotation_name;
};



struct ASTVarDecl: AST {
    ASTVarDecl();

    StorageClass var_decl_storage_class;
    InterpolationModifier var_decl_interpolation_modifier;
    TypeModifier var_decl_type_modifier;

    ASTType* var_decl_type;
    
    char* var_decl_name;

    bool is_build_in = false;

    Semantic* var_decl_semantic;
    PackOffset* var_decl_pack_offset;
    Register* var_decl_register;

    std::vector<Annotation*> annotations;

    AST* var_decl_default_value; // array of literals
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
    AST* argument_initializer;
};

struct FuncAttribute {
    std::vector<AST*> paramenters;
    const char* name;
};

struct ASTFunctionDeclaration: AST {
    explicit ASTFunctionDeclaration();

    StorageClass func_decl_storage_class;
    TypeModifier func_decl_type_modifier;

    std::vector<FuncAttribute*> func_decl_attributes;
    ASTType* func_decl_return_type;
    bool built_in;
    char* func_decl_name;
    std::vector<FunctionArgument*> func_decl_arguments;
    Semantic* func_decl_semantic;
    ASTBlock* func_decl_body;
};


// VARIABLE_DECLARATION ->  STORAGE_CLASS? TYPE_MODIFIER? TYPE IDENTIFIER('['INDEX']')? (':' SEMANTIC)? (':' PACK_OFFSET)? (':' REGISTER)?';' (ANNOTATIONS)? ('=' LITERAL)? ';'
AST* parseDeclaration(Parser* parser);
StorageClass parseStorageClass(Parser* parser);

}

#endif