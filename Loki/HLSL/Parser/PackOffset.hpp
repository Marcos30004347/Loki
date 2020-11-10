// https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-variable-packoffset

#ifndef PACKOFFSET_H
#define PACKOFFSET_H

#include "Parser.hpp"

namespace HLSL {

struct PackOffset {
    int pack_offset_sumcomponent;
    char pack_ofsset_component;
};

// PACK_OFFSET -> 'packoffset' '(' 'c'INTEGER_LITERAL('.w'|'.x'|'.y'|'.z')? ')'
PackOffset* parsePackOffset(Parser* parser);

}

#endif