#include "Parser.hpp"

namespace HLSL {

// INTERPOLATION_MODIFIER -> 'linear' | 'centroid' | 'nointerpolation' | 'sample'
enum InterpolationModifier {
    INTERPMOD_NONE,
    INTERPMOD_LINEAR,
    INTERPMOD_CENTROID,
    INTERPMOD_NOINTERPOLATION,
    INTERPMOD_SAMPLE,
};

InterpolationModifier parseInterpolationModifier(Parser* parser);

}