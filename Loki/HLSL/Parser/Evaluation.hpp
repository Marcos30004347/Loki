#include "Expressions.hpp"

namespace HLSL {

template<typename T>
struct Evaluation {
    T value;
};

Evaluation<int> a;
Evaluation<int> c;

Evaluation<float> b;

template<typename T>
Evaluation<T> evaluateConstantExpression(AST* expression, Parser* parser);

}