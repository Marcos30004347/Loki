// https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-variable-register

#ifndef REGISTER_H
#define REGISTER_H

#include "Parser.hpp"
#include "Profiles.hpp"

namespace HLSL {

struct Register {
    Profile register_profile;
    char register_type;

    bool register_has_subcomponent;
    int register_subcomponent;
    int register_number;
};

// REGISTER -> 'register' '(' PROFILE, ('b' | 't' | 'c' | 's' | 'u' )('['INTEGER_LITERAL']')? ')'
Register* parseRegister(Parser* parser);

}

#endif