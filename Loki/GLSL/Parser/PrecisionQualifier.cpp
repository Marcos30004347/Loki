#include "PrecisionQualifiers.hpp"

namespace GLSL {
PrecisionQualifier parsePrecisionQualifier(Parser* parser) {
    switch (parser->currentToken()->type) {
        case Token::TOKEN_MEDIUMP: return PrecisionQualifier::PRECISION_MEDIUP; break;
        case Token::TOKEN_LOWP: return PrecisionQualifier::PRECISION_LOWP; break;
        case Token::TOKEN_HIGHP: return PrecisionQualifier::PRECISION_HIGHP; break;
    }
    return PrecisionQualifier::PRECISION_NONE;
}
}