// https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-variable-syntax

#ifndef VARIABLES_H
#define VARIABLES_H


#include "AST.hpp"
#include "Parser.hpp"

#include "BaseType.hpp"
#include "Literals.hpp"
#include "Semantics.hpp"
#include "Register.hpp"
#include "PackOffset.hpp"

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
    BaseType* annotation_type;
    Literal* annotation_value;
    char* annotation_name;
};



struct ASTVarDecl: AST {
    ASTVarDecl();

    StorageClass var_decl_storage_class;
    TypeModifier var_decl_type_modifier;

    BaseType* var_decl_type;
    char* var_decl_name;

    bool var_decl_is_array;
    unsigned int var_decl_array_size;

    Semantic* var_decl_semantic;
    PackOffset* var_decl_pack_offset;
    Register* var_decl_register;

    std::vector<Annotation*> annotations;

    Literal** var_decl_default_value; // array of literals
};

// VARIABLE_DECLARATION ->  STORAGE_CLASS? TYPE_MODIFIER? TYPE IDENTIFIER('['INDEX']')? (':' SEMANTIC)? (':' PACK_OFFSET)? (':' REGISTER)?';' (ANNOTATIONS)? ('=' LITERAL)? ';'
ASTVarDecl* parseVarDecl(Parser* parser);

}

#endif