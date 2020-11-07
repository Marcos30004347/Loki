#ifndef INTRINSIC_FUNCTIONS_H
#define INTRINSIC_FUNCTIONS_H

#include "AST.hpp"
#include "Parser.hpp"
#include<vector>

namespace HLSL {

struct ASTFunctionCall: AST {
    explicit ASTFunctionCall();
    bool constexp;
    bool func_call_is_build_in;
    AST* func_call_symbol;
    std::vector<AST*> func_call_arguments;
};

AST* parseCall(Parser* parser, bool constant = false);


}

#endif