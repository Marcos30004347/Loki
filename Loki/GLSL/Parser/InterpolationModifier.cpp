#include "InterpolationModifier.hpp"

namespace GLSL {

InterpolationQualifier parseInterpolationQualifier(Parser* parser) {
    InterpolationQualifier modifier = InterpolationQualifier::INTERPQUA_NONE;
    switch (parser->currentToken()->type) {
    case Token::TOKEN_CENTROID:
        modifier = InterpolationQualifier::INTERPQUA_CENTROID;
        parser->readToken(Token::TOKEN_CENTROID);
        break;
    case Token::TOKEN_NOPERSPECTIVE:
        modifier = InterpolationQualifier::INTERPQUA_NOPERSPECTIVE;
        parser->readToken(Token::TOKEN_NOPERSPECTIVE);
        break;
    case Token::TOKEN_FLAT:
        modifier = InterpolationQualifier::INTERPQUA_FLAT;
        parser->readToken(Token::TOKEN_FLAT);
        break;
    case Token::TOKEN_SAMPLE:
        modifier = InterpolationQualifier::INTERPQUA_SAMPLE;
        parser->readToken(Token::TOKEN_SAMPLE);
        break;
    case Token::TOKEN_INVARIANT:
        modifier = InterpolationQualifier::INTERPQUA_INVARIANT;
        parser->readToken(Token::TOKEN_INVARIANT);
        break;

    case Token::TOKEN_SMOOTH:
        modifier = InterpolationQualifier::INTERPQUA_SMOOTH;
        parser->readToken(Token::TOKEN_SMOOTH);
        break;
    default: break;
    }

    return modifier;
}

}
