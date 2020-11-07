// https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-constants
#ifndef BUFFER_H
#define BUFFER_H

#include "AST.hpp"
#include "Variables.hpp"
#include "Register.hpp"
#include "Parser.hpp"
#include <vector>

namespace HLSL {


struct ASTBuffer : AST {
    enum Type {
        CONSTANT,
        TEXTURE,
    };

    explicit ASTBuffer(Type type);

    Type buffer_type;
    char* buffer_name;
    Register* buffer_register;
    std::vector<AST*> buffer_fields;
};

// BUFFER -> BufferType IDENTIFIER? (':' REGISTER)? '{' VARIABLE_DECLARATION* '}'';'
ASTBuffer* parseBuffer(Parser* parser);

}

#endif
