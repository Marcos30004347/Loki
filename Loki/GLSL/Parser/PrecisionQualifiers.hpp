#ifndef GLSL_PRECISION_QUALIFIERS
#define GLSL_PRECISION_QUALIFIERS

#include "AST.hpp"
#include "Parser.hpp"

namespace GLSL {

enum PrecisionQualifier {
    PRECISION_NONE,
    PRECISION_LOWP,
    PRECISION_MEDIUP,
    PRECISION_HIGHP,
};

PrecisionQualifier parsePrecisionQualifier(Parser* parser);

}

#endif