#ifndef SEMANTICS_H
#define SEMANTICS_H

#include "Parser.hpp"

namespace HLSL {

struct Semantic {
    char* name;
};

Semantic* parseSemantic(Parser* parser);

}

#endif