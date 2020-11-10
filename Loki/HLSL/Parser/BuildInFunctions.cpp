#include "Lib/String.hpp"
#include "BuiltInTypes.hpp"
#include "BuildInFunctions.hpp"
#include "Functions.hpp"

namespace HLSL {

void addBuiltInFunctionDefinition(const char* name) {
    ASTFunctionDeclaration* func = new ASTFunctionDeclaration();
    func->func_decl_name = copyStr(name);
    func->built_in = true;
}

void addBuiltInFuncsToScope(Parser* parser) {
    addBuiltInFunctionDefinition("abort");
    addBuiltInFunctionDefinition("abs");
    addBuiltInFunctionDefinition("acos");
    addBuiltInFunctionDefinition("all");
    addBuiltInFunctionDefinition("AllMemoryBarrier");
    addBuiltInFunctionDefinition("AllMemoryBarrierWithGroupSync");
    addBuiltInFunctionDefinition("any");
    addBuiltInFunctionDefinition("asdouble");
    addBuiltInFunctionDefinition("asfloat");
    addBuiltInFunctionDefinition("asin");
    addBuiltInFunctionDefinition("asint");
    addBuiltInFunctionDefinition("asuint");
    addBuiltInFunctionDefinition("atan");
    addBuiltInFunctionDefinition("atan2");
    addBuiltInFunctionDefinition("ceil");
    addBuiltInFunctionDefinition("CheckAccessFullyMapped");
    addBuiltInFunctionDefinition("clamp");
    addBuiltInFunctionDefinition("clip");
    addBuiltInFunctionDefinition("cos");
    addBuiltInFunctionDefinition("cosh");
    addBuiltInFunctionDefinition("countbits");
    addBuiltInFunctionDefinition("cross");
    addBuiltInFunctionDefinition("D3DCOLORtoUBYTE4");
    addBuiltInFunctionDefinition("ddx");
    addBuiltInFunctionDefinition("ddx_coarse");
    addBuiltInFunctionDefinition("ddx_fine");
    addBuiltInFunctionDefinition("ddy");
    addBuiltInFunctionDefinition("ddy_coarse");
    addBuiltInFunctionDefinition("ddy_coarse");
    addBuiltInFunctionDefinition("degrees");
    addBuiltInFunctionDefinition("determinant");
    addBuiltInFunctionDefinition("DeviceMemoryBarrier");
    addBuiltInFunctionDefinition("DeviceMemoryBarrierWithGroupSync");
    addBuiltInFunctionDefinition("distance");
    addBuiltInFunctionDefinition("dot");
    addBuiltInFunctionDefinition("dst");
    addBuiltInFunctionDefinition("errorf");
    addBuiltInFunctionDefinition("EvaluateAttributeAtCentroid");
    addBuiltInFunctionDefinition("EvaluateAttributeAtSample");
    addBuiltInFunctionDefinition("EvaluateAttributeAtSnapped");
    addBuiltInFunctionDefinition("exp");
    addBuiltInFunctionDefinition("exp2");
    addBuiltInFunctionDefinition("f16tof32");
    addBuiltInFunctionDefinition("f16tof32");
    addBuiltInFunctionDefinition("faceforward");
    addBuiltInFunctionDefinition("firstbithigh");
    addBuiltInFunctionDefinition("firstbitlow");
    addBuiltInFunctionDefinition("floor");
    addBuiltInFunctionDefinition("fma");
    addBuiltInFunctionDefinition("fmod");
    addBuiltInFunctionDefinition("frac");
    addBuiltInFunctionDefinition("frexp");
    addBuiltInFunctionDefinition("fwidth");
    addBuiltInFunctionDefinition("GetRenderTargetSampleCount");
    addBuiltInFunctionDefinition("GetRenderTargetSamplePosition");
    addBuiltInFunctionDefinition("GroupMemoryBarrier");
    addBuiltInFunctionDefinition("GroupMemoryBarrierWithGroupSync");
    addBuiltInFunctionDefinition("InterlockedAdd");
    addBuiltInFunctionDefinition("InterlockedAnd");
    addBuiltInFunctionDefinition("InterlockedCompareExchange");
    addBuiltInFunctionDefinition("InterlockedCompareStore");
    addBuiltInFunctionDefinition("InterlockedExchange");
    addBuiltInFunctionDefinition("InterlockedMax");
    addBuiltInFunctionDefinition("InterlockedMin");
    addBuiltInFunctionDefinition("InterlockedOr");
    addBuiltInFunctionDefinition("InterlockedXor");
    addBuiltInFunctionDefinition("isfinite");
    addBuiltInFunctionDefinition("isinf");
    addBuiltInFunctionDefinition("isnan");
    addBuiltInFunctionDefinition("idexp");
    addBuiltInFunctionDefinition("length");
    addBuiltInFunctionDefinition("lerp");
    addBuiltInFunctionDefinition("lit");
    addBuiltInFunctionDefinition("log");
    addBuiltInFunctionDefinition("log10");
    addBuiltInFunctionDefinition("log2");
    addBuiltInFunctionDefinition("mad");
    addBuiltInFunctionDefinition("max");
    addBuiltInFunctionDefinition("min");
    addBuiltInFunctionDefinition("modf");
    addBuiltInFunctionDefinition("msad4");
    addBuiltInFunctionDefinition("mul");
    addBuiltInFunctionDefinition("noise");
    addBuiltInFunctionDefinition("normalize");
    addBuiltInFunctionDefinition("pow");
    addBuiltInFunctionDefinition("printf");
    addBuiltInFunctionDefinition("Process2DQuadTessFactorsAvg");
    addBuiltInFunctionDefinition("Process2DQuadTessFactorsMax");
    addBuiltInFunctionDefinition("Process2DQuadTessFactorsMin");
    addBuiltInFunctionDefinition("ProcessIsolineTessFactors");
    addBuiltInFunctionDefinition("ProcessQuadTessFactorsAvg");
    addBuiltInFunctionDefinition("ProcessQuadTessFactorsMax");
    addBuiltInFunctionDefinition("ProcessQuadTessFactorsMin");
    addBuiltInFunctionDefinition("ProcessTriTessFactorsAvg");
    addBuiltInFunctionDefinition("ProcessTriTessFactorsMax");
    addBuiltInFunctionDefinition("ProcessTriTessFactorsMin");
    addBuiltInFunctionDefinition("radius");
    addBuiltInFunctionDefinition("rcp");
    addBuiltInFunctionDefinition("reflect");
    addBuiltInFunctionDefinition("refract");
    addBuiltInFunctionDefinition("reversebits");
    addBuiltInFunctionDefinition("round");
    addBuiltInFunctionDefinition("rsqrt");
    addBuiltInFunctionDefinition("saturate");
    addBuiltInFunctionDefinition("sign");
    addBuiltInFunctionDefinition("sin");
    addBuiltInFunctionDefinition("sincos");
    addBuiltInFunctionDefinition("sinh");
    addBuiltInFunctionDefinition("smothstep");
    addBuiltInFunctionDefinition("sqrt");
    addBuiltInFunctionDefinition("step");
    addBuiltInFunctionDefinition("tan");
    addBuiltInFunctionDefinition("tanh");
    addBuiltInFunctionDefinition("tex1D");
    addBuiltInFunctionDefinition("tex1Dbias");
    addBuiltInFunctionDefinition("tex1Dgrad");
    addBuiltInFunctionDefinition("tex1Dlod");
    addBuiltInFunctionDefinition("tex1Dproj");
    addBuiltInFunctionDefinition("tex2Dbias");
    addBuiltInFunctionDefinition("tex2Dgrad");
    addBuiltInFunctionDefinition("tex2Dlod");
    addBuiltInFunctionDefinition("tex2Dproj");
    addBuiltInFunctionDefinition("tex3D");
    addBuiltInFunctionDefinition("tex3Dbias");
    addBuiltInFunctionDefinition("tex3Dgrad");
    addBuiltInFunctionDefinition("tex3Dlod");
    addBuiltInFunctionDefinition("tex3Dproj");
    addBuiltInFunctionDefinition("texCUBE");
    addBuiltInFunctionDefinition("texCUBEbias");
    addBuiltInFunctionDefinition("texCUBEgrad");
    addBuiltInFunctionDefinition("texCUBElod");
    addBuiltInFunctionDefinition("texCUBEproj");
    addBuiltInFunctionDefinition("transpose");
    addBuiltInFunctionDefinition("trunc");
}

}