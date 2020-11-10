#include "Expressions.hpp"

namespace HLSL {

template<typename T>
struct Evaluation {
    T value;
};

template<typename T>
Evaluation<T> evaluateConstantExpression(AST* expression, Parser* parser);

}