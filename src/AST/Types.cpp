#include "Types.hpp"
#include <string.h>
#include <stdlib.h>
#include <cstdio>

bool isTokenType(Token* tok) {
    if(strcmp(tok->value, "void") == 0) return true; 
    if(strcmp(tok->value, "int") == 0) return true;
    if(strcmp(tok->value, "uint") == 0) return true; 
    if(strcmp(tok->value, "float") == 0) return true;
    if(strcmp(tok->value, "bool") == 0) return true; 
    if(strcmp(tok->value, "vec2") == 0) return true; 
    if(strcmp(tok->value, "vec3") == 0) return true;
    if(strcmp(tok->value, "vec4") == 0) return true;
    if(strcmp(tok->value, "mat2") == 0) return true;
    if(strcmp(tok->value, "mat2x2") == 0) return true;
    if(strcmp(tok->value, "mat2x3") == 0) return true;
    if(strcmp(tok->value, "mat2x4") == 0) return true;
    if(strcmp(tok->value, "mat3") == 0) return true;
    if(strcmp(tok->value, "mat3x2") == 0) return true;
    if(strcmp(tok->value, "mat3x3") == 0) return true;
    if(strcmp(tok->value, "mat3x4") == 0) return true;
    if(strcmp(tok->value, "mat4") == 0) return true;
    if(strcmp(tok->value, "mat4x2") == 0) return true;
    if(strcmp(tok->value, "mat4x3") == 0) return true;
    if(strcmp(tok->value, "mat4x4") == 0) return true;
    return false;
}


BuildInType getTypeFromString(const char* type_id) {
    if(strcmp(type_id, "void") == 0) return BuildInType::TYPE_VOID;
    if(strcmp(type_id, "int") == 0) return BuildInType::TYPE_INT;
    if(strcmp(type_id, "uint") == 0) return BuildInType::TYPE_UINT;
    if(strcmp(type_id, "float") == 0) return BuildInType::TYPE_FLOAT;
    if(strcmp(type_id, "bool") == 0) return BuildInType::TYPE_BOOL;
    if(strcmp(type_id, "vec2") == 0) return BuildInType::TYPE_VEC2;
    if(strcmp(type_id, "vec3") == 0) return BuildInType::TYPE_VEC3;
    if(strcmp(type_id, "vec4") == 0) return BuildInType::TYPE_VEC4;
    if(strcmp(type_id, "mat2") == 0) return BuildInType::TYPE_MAT2;
    if(strcmp(type_id, "mat2x2") == 0) return BuildInType::TYPE_MAT2X2;
    if(strcmp(type_id, "mat2x3") == 0) return BuildInType::TYPE_MAT2X3;
    if(strcmp(type_id, "mat2x4") == 0) return BuildInType::TYPE_MAT2X4;
    if(strcmp(type_id, "mat3") == 0) return BuildInType::TYPE_MAT3;
    if(strcmp(type_id, "mat3x2") == 0) return BuildInType::TYPE_MAT3X2;
    if(strcmp(type_id, "mat3x3") == 0) return BuildInType::TYPE_MAT3X3;
    if(strcmp(type_id, "mat3x4") == 0) return BuildInType::TYPE_MAT3X4;
    if(strcmp(type_id, "mat4") == 0) return BuildInType::TYPE_MAT4;
    if(strcmp(type_id, "mat4x2") == 0) return BuildInType::TYPE_MAT4X2;
    if(strcmp(type_id, "mat4x3") == 0) return BuildInType::TYPE_MAT4X3;
    if(strcmp(type_id, "mat4x4") == 0) return BuildInType::TYPE_MAT4X4;

    printf("\033[31mUnexpected type '%s'!\033[m\n", type_id);
    exit(-1);
    return BuildInType::TYPE_VOID; // Never reached
}
