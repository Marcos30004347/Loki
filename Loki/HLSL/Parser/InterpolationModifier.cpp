#include "InterpolationModifier.hpp"

namespace HLSL {

InterpolationModifier parseInterpolationModifier(Parser* parser) {
    InterpolationModifier modifier = InterpolationModifier::INTERPMOD_NONE;
    switch (parser->currentToken()->type) {
    case Token::TOKEN_LINEAR:
        modifier = InterpolationModifier::INTERPMOD_LINEAR;
        parser->readToken(Token::TOKEN_LINEAR);
        break;
    case Token::TOKEN_CENTROID:
        modifier = InterpolationModifier::INTERPMOD_CENTROID;
        parser->readToken(Token::TOKEN_CENTROID);
        break;
    case Token::TOKEN_NOINTERPOLATION:
        modifier = InterpolationModifier::INTERPMOD_NOINTERPOLATION;
        parser->readToken(Token::TOKEN_NOINTERPOLATION);
        break;
    case Token::TOKEN_SAMPLE:
        modifier = InterpolationModifier::INTERPMOD_SAMPLE;
        parser->readToken(Token::TOKEN_SAMPLE);
        break;
    default: break;
    }
    return modifier;
}

}
