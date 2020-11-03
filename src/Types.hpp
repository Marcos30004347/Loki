#ifndef BUILD_IN_TYPES
#define BUILD_IN_TYPES

#include "Lexer.hpp"

enum BuildInType {
    TYPE_VOID = 0,
    TYPE_STRUCT,
    TYPE_INT,
    TYPE_UINT,
    TYPE_FLOAT,
    TYPE_BOOL,
    TYPE_VEC2,
    TYPE_VEC3,
    TYPE_VEC4,
    TYPE_MAT2,
    TYPE_MAT2X2,
    TYPE_MAT2X3,
    TYPE_MAT2X4,
    TYPE_MAT3,
    TYPE_MAT3X2,
    TYPE_MAT3X3,
    TYPE_MAT3X4,
    TYPE_MAT4,
    TYPE_MAT4X2,
    TYPE_MAT4X3,
    TYPE_MAT4X4,
    TYPE_SAMPLER,
    TYPE_SAMPLER3D,
};


// bool isTokenType(Token* tok);

#endif