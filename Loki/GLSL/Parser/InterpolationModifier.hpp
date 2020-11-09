#ifndef INTERPOLATION_MODIFIER 
#define INTERPOLATION_MODIFIER 

#include "Parser.hpp"
namespace GLSL {

// INTERPOLATION_MODIFIER -> 'linear' | 'centroid' | 'nointerpolation' | 'sample'
enum InterpolationQualifier {
    // Invariants qualifiers
    INTERPQUA_NONE,
    INTERPQUA_INVARIANT,
    INTERPQUA_CENTROID,
    INTERPQUA_NOPERSPECTIVE,

    // Interpolation qualifiers
    INTERPQUA_FLAT,
    INTERPOLATION_QUALIFIERS_START = INTERPQUA_FLAT,
    INTERPQUA_SMOOTH,
    INTERPQUA_SAMPLE,
    INTERPOLATION_QUALIFIERS_END = INTERPQUA_SAMPLE,
};

InterpolationQualifier parseInterpolationQualifier(Parser* parser);

}

#endif