#include "Lib/String.hpp"
#include "FunctionCall.hpp"
#include "Expressions.hpp"
#include <stdio.h>
namespace HLSL {

bool isFuncNameIntrinsic(char* func_name) {
    if(strcmp(func_name, "abort") == 0) return true;
    if(strcmp(func_name, "abs") == 0) return true;
    if(strcmp(func_name, "acos") == 0) return true;
    if(strcmp(func_name, "all") == 0) return true;
    if(strcmp(func_name, "AllMemoryBarrier") == 0) return true;
    if(strcmp(func_name, "AllMemoryBarrierWithGroupSync") == 0) return true;
    if(strcmp(func_name, "any") == 0) return true;
    if(strcmp(func_name, "asdouble") == 0) return true;
    if(strcmp(func_name, "asfloat") == 0) return true;
    if(strcmp(func_name, "asin") == 0) return true;
    if(strcmp(func_name, "asint") == 0) return true;
    if(strcmp(func_name, "asuint") == 0) return true;
    if(strcmp(func_name, "atan") == 0) return true;
    if(strcmp(func_name, "atan2") == 0) return true;
    if(strcmp(func_name, "ceil") == 0) return true;
    if(strcmp(func_name, "CheckAccessFullyMapped") == 0) return true;
    if(strcmp(func_name, "clamp") == 0) return true;
    if(strcmp(func_name, "clip") == 0) return true;
    if(strcmp(func_name, "cos") == 0) return true;
    if(strcmp(func_name, "cosh") == 0) return true;
    if(strcmp(func_name, "countbits") == 0) return true;
    if(strcmp(func_name, "cross") == 0) return true;
    if(strcmp(func_name, "D3DCOLORtoUBYTE4") == 0) return true;
    if(strcmp(func_name, "ddx") == 0) return true;
    if(strcmp(func_name, "ddx_coarse") == 0) return true;
    if(strcmp(func_name, "ddx_fine") == 0) return true;
    if(strcmp(func_name, "ddy") == 0) return true;
    if(strcmp(func_name, "ddy_coarse") == 0) return true;
    if(strcmp(func_name, "ddy_coarse") == 0) return true;
    if(strcmp(func_name, "degrees") == 0) return true;
    if(strcmp(func_name, "determinant") == 0) return true;
    if(strcmp(func_name, "DeviceMemoryBarrier") == 0) return true;
    if(strcmp(func_name, "DeviceMemoryBarrierWithGroupSync") == 0) return true;
    if(strcmp(func_name, "distance") == 0) return true;
    if(strcmp(func_name, "dot") == 0) return true;
    if(strcmp(func_name, "dst") == 0) return true;
    if(strcmp(func_name, "errorf") == 0) return true;
    if(strcmp(func_name, "EvaluateAttributeAtCentroid") == 0) return true;
    if(strcmp(func_name, "EvaluateAttributeAtSample") == 0) return true;
    if(strcmp(func_name, "EvaluateAttributeAtSnapped") == 0) return true;
    if(strcmp(func_name, "exp") == 0) return true;
    if(strcmp(func_name, "exp2") == 0) return true;
    if(strcmp(func_name, "f16tof32") == 0) return true;
    if(strcmp(func_name, "f16tof32") == 0) return true;
    if(strcmp(func_name, "faceforward") == 0) return true;
    if(strcmp(func_name, "firstbithigh") == 0) return true;
    if(strcmp(func_name, "firstbitlow") == 0) return true;
    if(strcmp(func_name, "floor") == 0) return true;
    if(strcmp(func_name, "fma") == 0) return true;
    if(strcmp(func_name, "fmod") == 0) return true;
    if(strcmp(func_name, "frac") == 0) return true;
    if(strcmp(func_name, "frexp") == 0) return true;
    if(strcmp(func_name, "fwidth") == 0) return true;
    if(strcmp(func_name, "GetRenderTargetSampleCount") == 0) return true;
    if(strcmp(func_name, "GetRenderTargetSamplePosition") == 0) return true;
    if(strcmp(func_name, "GroupMemoryBarrier") == 0) return true;
    if(strcmp(func_name, "GroupMemoryBarrierWithGroupSync") == 0) return true;
    if(strcmp(func_name, "InterlockedAdd") == 0) return true;
    if(strcmp(func_name, "InterlockedAnd") == 0) return true;
    if(strcmp(func_name, "InterlockedCompareExchange") == 0) return true;
    if(strcmp(func_name, "InterlockedCompareStore") == 0) return true;
    if(strcmp(func_name, "InterlockedExchange") == 0) return true;
    if(strcmp(func_name, "InterlockedMax") == 0) return true;
    if(strcmp(func_name, "InterlockedMin") == 0) return true;
    if(strcmp(func_name, "InterlockedOr") == 0) return true;
    if(strcmp(func_name, "InterlockedXor") == 0) return true;
    if(strcmp(func_name, "isfinite") == 0) return true;
    if(strcmp(func_name, "isinf") == 0) return true;
    if(strcmp(func_name, "isnan") == 0) return true;
    if(strcmp(func_name, "idexp") == 0) return true;
    if(strcmp(func_name, "length") == 0) return true;
    if(strcmp(func_name, "lerp") == 0) return true;
    if(strcmp(func_name, "lit") == 0) return true;
    if(strcmp(func_name, "log") == 0) return true;
    if(strcmp(func_name, "log10") == 0) return true;
    if(strcmp(func_name, "log2") == 0) return true;
    if(strcmp(func_name, "mad") == 0) return true;
    if(strcmp(func_name, "max") == 0) return true;
    if(strcmp(func_name, "min") == 0) return true;
    if(strcmp(func_name, "modf") == 0) return true;
    if(strcmp(func_name, "msad4") == 0) return true;
    if(strcmp(func_name, "mul") == 0) return true;
    if(strcmp(func_name, "noise") == 0) return true;
    if(strcmp(func_name, "normalize") == 0) return true;
    if(strcmp(func_name, "pow") == 0) return true;
    if(strcmp(func_name, "printf") == 0) return true;
    if(strcmp(func_name, "Process2DQuadTessFactorsAvg") == 0) return true;
    if(strcmp(func_name, "Process2DQuadTessFactorsMax") == 0) return true;
    if(strcmp(func_name, "Process2DQuadTessFactorsMin") == 0) return true;
    if(strcmp(func_name, "ProcessIsolineTessFactors") == 0) return true;
    if(strcmp(func_name, "ProcessQuadTessFactorsAvg") == 0) return true;
    if(strcmp(func_name, "ProcessQuadTessFactorsMax") == 0) return true;
    if(strcmp(func_name, "ProcessQuadTessFactorsMin") == 0) return true;
    if(strcmp(func_name, "ProcessTriTessFactorsAvg") == 0) return true;
    if(strcmp(func_name, "ProcessTriTessFactorsMax") == 0) return true;
    if(strcmp(func_name, "ProcessTriTessFactorsMin") == 0) return true;
    if(strcmp(func_name, "radius") == 0) return true;
    if(strcmp(func_name, "rcp") == 0) return true;
    if(strcmp(func_name, "reflect") == 0) return true;
    if(strcmp(func_name, "refract") == 0) return true;
    if(strcmp(func_name, "reversebits") == 0) return true;
    if(strcmp(func_name, "round") == 0) return true;
    if(strcmp(func_name, "rsqrt") == 0) return true;
    if(strcmp(func_name, "saturate") == 0) return true;
    if(strcmp(func_name, "sign") == 0) return true;
    if(strcmp(func_name, "sin") == 0) return true;
    if(strcmp(func_name, "sincos") == 0) return true;
    if(strcmp(func_name, "sinh") == 0) return true;
    if(strcmp(func_name, "smothstep") == 0) return true;
    if(strcmp(func_name, "sqrt") == 0) return true;
    if(strcmp(func_name, "step") == 0) return true;
    if(strcmp(func_name, "tan") == 0) return true;
    if(strcmp(func_name, "tanh") == 0) return true;
    if(strcmp(func_name, "tex1D") == 0) return true;
    if(strcmp(func_name, "tex1Dbias") == 0) return true;
    if(strcmp(func_name, "tex1Dgrad") == 0) return true;
    if(strcmp(func_name, "tex1Dlod") == 0) return true;
    if(strcmp(func_name, "tex1Dproj") == 0) return true;
    if(strcmp(func_name, "tex2Dbias") == 0) return true;
    if(strcmp(func_name, "tex2Dgrad") == 0) return true;
    if(strcmp(func_name, "tex2Dlod") == 0) return true;
    if(strcmp(func_name, "tex2Dproj") == 0) return true;
    if(strcmp(func_name, "tex3D") == 0) return true;
    if(strcmp(func_name, "tex3Dbias") == 0) return true;
    if(strcmp(func_name, "tex3Dgrad") == 0) return true;
    if(strcmp(func_name, "tex3Dlod") == 0) return true;
    if(strcmp(func_name, "tex3Dproj") == 0) return true;
    if(strcmp(func_name, "texCUBE") == 0) return true;
    if(strcmp(func_name, "texCUBEbias") == 0) return true;
    if(strcmp(func_name, "texCUBEgrad") == 0) return true;
    if(strcmp(func_name, "texCUBElod") == 0) return true;
    if(strcmp(func_name, "texCUBEproj") == 0) return true;
    if(strcmp(func_name, "transpose") == 0) return true;
    if(strcmp(func_name, "trunc") == 0) return true;

    return false;
}

// CALL → PRIMARY('('ARGUMENTS?')')?
AST* parseCall(Parser* parser, bool constant) {
    AST* root = parsePrimary(parser, constant);


    if(parser->currentToken() && parser->currentToken()->type == Token::TOKEN_OPEN_PARENTESIS) {
        if(root->ast_type != NodeType::AST_SYMBOL) {
            printf("Unexpected function name at line %i\n", parser->currentToken()->line);
        }

        ASTFunctionCall* func_call = new ASTFunctionCall();
        func_call->func_call_is_build_in = isFuncNameIntrinsic(static_cast<ASTSymbol*>(root)->symbol_name);
        func_call->func_call_symbol = root;
        func_call->constexp = constant;
    
        parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
        if(parser->currentToken() && parser->currentToken()->type != Token::TOKEN_CLOSE_PARENTESIS) {
            func_call->func_call_arguments.push_back(parseExpression(parser, constant));
            while(parser->currentToken() && parser->currentToken()->type == Token::TOKEN_COMMA) {
                parser->readToken(Token::TOKEN_COMMA);
                func_call->func_call_arguments.push_back(parseExpression(parser, constant));
            }
        }
        parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
        root = func_call;
    } else {
        if(root->ast_type == NodeType::AST_SYMBOL && constant) {
            printf("Cant use variables in constant expression at line '%i'!\n", parser->currentToken()->line);
        }
    }

    return root;
}

}