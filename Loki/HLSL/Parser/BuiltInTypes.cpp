#include "BuiltInTypes.hpp"
#include "stdio.h"
namespace HLSL {


void addBuiltInScalarsToScope(Parser* parser) {
    void_type = new ASTType("void");

    //string 
    string_type = new ASTType("string");
    string_type->accept_literals.push_back(ASTLiteral::Type::LITERAL_STRING);
    string_type->constructors.push_back(new ASTConstructor());
    string_type->constructors[0]->arguments.push_back(string_type);

    // int
    int_type = new ASTType("int");
    int_type->accept_literals.push_back(ASTLiteral::Type::LITERAL_INT);
    int_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_FLOAT);
    int_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_BOOL);
    int_type->castable_to_types.push_back(float_type);
    int_type->castable_to_types.push_back(half_type);
    int_type->castable_to_types.push_back(uint_type);
    int_type->castable_to_types.push_back(double_type);
    int_type->castable_to_types.push_back(bool_type);
    int_type->castable_to_types.push_back(int_type);
    int_type->constructors.push_back(new ASTConstructor());
    int_type->constructors[0]->arguments.push_back(int_type);

    // float
    float_type = new ASTType("float");
    float_type->accept_literals.push_back(ASTLiteral::Type::LITERAL_FLOAT);
    float_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_INT);
    float_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_BOOL);
    float_type->castable_to_types.push_back(int_type);
    float_type->castable_to_types.push_back(float_type);
    float_type->castable_to_types.push_back(half_type);
    float_type->castable_to_types.push_back(uint_type);
    float_type->castable_to_types.push_back(double_type);
    float_type->castable_to_types.push_back(bool_type);
    float_type->constructors.push_back(new ASTConstructor());
    float_type->constructors[0]->arguments.push_back(float_type);

    // half type
    half_type = new ASTType("half");
    half_type->accept_literals.push_back(ASTLiteral::Type::LITERAL_INT);
    half_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_FLOAT);
    half_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_BOOL);
    half_type->castable_to_types.push_back(int_type);
    half_type->castable_to_types.push_back(float_type);
    half_type->castable_to_types.push_back(half_type);
    half_type->castable_to_types.push_back(uint_type);
    half_type->castable_to_types.push_back(double_type);
    half_type->castable_to_types.push_back(bool_type);
    half_type->constructors.push_back(new ASTConstructor());
    half_type->constructors[0]->arguments.push_back(half_type);

    // double
    double_type = new ASTType("double");
    double_type->accept_literals.push_back(ASTLiteral::Type::LITERAL_FLOAT);
    double_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_INT);
    double_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_BOOL);
    double_type->castable_to_types.push_back(int_type);
    double_type->castable_to_types.push_back(float_type);
    double_type->castable_to_types.push_back(half_type);
    double_type->castable_to_types.push_back(uint_type);
    double_type->castable_to_types.push_back(double_type);
    double_type->castable_to_types.push_back(bool_type);
    double_type->constructors.push_back(new ASTConstructor());
    double_type->constructors[0]->arguments.push_back(double_type);

    // uint
    uint_type = new ASTType("uint");
    uint_type->accept_literals.push_back(ASTLiteral::Type::LITERAL_INT);
    uint_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_FLOAT);
    uint_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_BOOL);
    uint_type->castable_to_types.push_back(int_type);
    uint_type->castable_to_types.push_back(float_type);
    uint_type->castable_to_types.push_back(half_type);
    uint_type->castable_to_types.push_back(uint_type);
    uint_type->castable_to_types.push_back(double_type);
    uint_type->castable_to_types.push_back(bool_type);
    uint_type->constructors.push_back(new ASTConstructor());
    uint_type->constructors[0]->arguments.push_back(uint_type);

    // bool
    bool_type = new ASTType("bool");
    bool_type->accept_literals.push_back(ASTLiteral::Type::LITERAL_BOOL);
    bool_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_FLOAT);
    bool_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_INT);
    bool_type->castable_to_types.push_back(int_type);
    bool_type->castable_to_types.push_back(float_type);
    bool_type->castable_to_types.push_back(half_type);
    bool_type->castable_to_types.push_back(bool_type);
    bool_type->castable_to_types.push_back(double_type);
    bool_type->castable_to_types.push_back(bool_type);
    bool_type->constructors.push_back(new ASTConstructor());
    bool_type->constructors[0]->arguments.push_back(uint_type);


    parser->scope->addTypeDeclaration(int_type);
    parser->scope->addTypeDeclaration(uint_type);
    parser->scope->addTypeDeclaration(half_type);
    parser->scope->addTypeDeclaration(double_type);
    parser->scope->addTypeDeclaration(float_type);
    parser->scope->addTypeDeclaration(bool_type);
    parser->scope->addTypeDeclaration(string_type);
    parser->scope->addTypeDeclaration(void_type);
}

void addBuiltIn2VectorsToScope(Parser* parser) {
    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    // Floats
    float2_type = new ASTType("float2");
    // 2 float members
    float2_type->members.push_back(float_type);
    float2_type->members.push_back(float_type);

    float2_type->castable_to_types.push_back(int2_type);
    float2_type->castable_to_types.push_back(half2_type);
    float2_type->castable_to_types.push_back(double2_type);
    float2_type->castable_to_types.push_back(float2_type);
    float2_type->castable_to_types.push_back(uint2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);

    float2_type->constructors.push_back(constructor0);
    float2_type->constructors.push_back(constructor1);


    // Doubles
    double2_type = new ASTType("double2");
    // 2 double members
    double2_type->members.push_back(double_type);
    double2_type->members.push_back(double_type);

    double2_type->castable_to_types.push_back(int2_type);
    double2_type->castable_to_types.push_back(half2_type);
    double2_type->castable_to_types.push_back(double2_type);
    double2_type->castable_to_types.push_back(float2_type);
    double2_type->castable_to_types.push_back(uint2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(double_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);

    double2_type->constructors.push_back(constructor0);
    double2_type->constructors.push_back(constructor1);


    // Int
    int2_type = new ASTType("int2");
    // 2 float members
    int2_type->members.push_back(int_type);
    int2_type->members.push_back(int_type);

    int2_type->castable_to_types.push_back(int2_type);
    int2_type->castable_to_types.push_back(half2_type);
    int2_type->castable_to_types.push_back(double2_type);
    int2_type->castable_to_types.push_back(float2_type);
    int2_type->castable_to_types.push_back(uint2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(int_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);

    int2_type->constructors.push_back(constructor0);
    int2_type->constructors.push_back(constructor1);



    // Half
    half2_type = new ASTType("half2");
    // 2 float members
    half2_type->members.push_back(half_type);
    half2_type->members.push_back(half_type);

    half2_type->castable_to_types.push_back(int2_type);
    half2_type->castable_to_types.push_back(half2_type);
    half2_type->castable_to_types.push_back(double2_type);
    half2_type->castable_to_types.push_back(float2_type);
    half2_type->castable_to_types.push_back(uint2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(half_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);

    half2_type->constructors.push_back(constructor0);
    half2_type->constructors.push_back(constructor1);


    // Half
    uint2_type = new ASTType("uint2");
    // 2 float members
    uint2_type->members.push_back(uint_type);
    uint2_type->members.push_back(uint_type);

    uint2_type->castable_to_types.push_back(int2_type);
    uint2_type->castable_to_types.push_back(half2_type);
    uint2_type->castable_to_types.push_back(double2_type);
    uint2_type->castable_to_types.push_back(float2_type);
    uint2_type->castable_to_types.push_back(uint2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(uint_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);

    uint2_type->constructors.push_back(constructor0);
    uint2_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(float2_type);
    parser->scope->addTypeDeclaration(int2_type);
    parser->scope->addTypeDeclaration(double2_type);
    parser->scope->addTypeDeclaration(half2_type);
    parser->scope->addTypeDeclaration(uint2_type);
}



void addBuiltIn3VectorsToScope(Parser* parser) {
    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    // Floats
    float3_type = new ASTType("float3");
    // 2 float members
    float3_type->members.push_back(float_type);
    float3_type->members.push_back(float_type);
    float3_type->members.push_back(float_type);

    float3_type->castable_to_types.push_back(int3_type);
    float3_type->castable_to_types.push_back(half3_type);
    float3_type->castable_to_types.push_back(double3_type);
    float3_type->castable_to_types.push_back(float3_type);
    float3_type->castable_to_types.push_back(uint3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);

    float3_type->constructors.push_back(constructor0);
    float3_type->constructors.push_back(constructor1);


    // Floats
    double3_type = new ASTType("double3");
    // 2 float members
    double3_type->members.push_back(double_type);
    double3_type->members.push_back(double_type);
    double3_type->members.push_back(double_type);

    double3_type->castable_to_types.push_back(int3_type);
    double3_type->castable_to_types.push_back(half3_type);
    double3_type->castable_to_types.push_back(double3_type);
    double3_type->castable_to_types.push_back(float3_type);
    double3_type->castable_to_types.push_back(uint3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(double_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);

    double3_type->constructors.push_back(constructor0);
    double3_type->constructors.push_back(constructor1);


    // Int
    int3_type = new ASTType("int3");
    // 2 int members
    int3_type->members.push_back(int_type);
    int3_type->members.push_back(int_type);
    int3_type->members.push_back(int_type);

    int3_type->castable_to_types.push_back(int3_type);
    int3_type->castable_to_types.push_back(half3_type);
    int3_type->castable_to_types.push_back(double3_type);
    int3_type->castable_to_types.push_back(float3_type);
    int3_type->castable_to_types.push_back(uint3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(int_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);

    int3_type->constructors.push_back(constructor0);
    int3_type->constructors.push_back(constructor1);


    // Half
    half3_type = new ASTType("half3");
    // 2 half members
    half3_type->members.push_back(half_type);
    half3_type->members.push_back(half_type);
    half3_type->members.push_back(half_type);

    half3_type->castable_to_types.push_back(int3_type);
    half3_type->castable_to_types.push_back(half3_type);
    half3_type->castable_to_types.push_back(double3_type);
    half3_type->castable_to_types.push_back(float3_type);
    half3_type->castable_to_types.push_back(uint3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(half_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);

    half3_type->constructors.push_back(constructor0);
    half3_type->constructors.push_back(constructor1);


    // Half
    uint3_type = new ASTType("uint3");
    // 2 uint members
    uint3_type->members.push_back(uint_type);
    uint3_type->members.push_back(uint_type);
    uint3_type->members.push_back(uint_type);

    uint3_type->castable_to_types.push_back(int3_type);
    uint3_type->castable_to_types.push_back(half3_type);
    uint3_type->castable_to_types.push_back(double3_type);
    uint3_type->castable_to_types.push_back(float3_type);
    uint3_type->castable_to_types.push_back(uint3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(uint_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);

    uint3_type->constructors.push_back(constructor0);
    uint3_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(uint3_type);
    parser->scope->addTypeDeclaration(int3_type);
    parser->scope->addTypeDeclaration(float3_type);
    parser->scope->addTypeDeclaration(double3_type);
    parser->scope->addTypeDeclaration(half3_type);

}



void addBuiltIn4VectorsToScope(Parser* parser) {
    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    // Floats
    float4_type = new ASTType("float4");
    // 2 float members
    float4_type->members.push_back(float_type);
    float4_type->members.push_back(float_type);
    float4_type->members.push_back(float_type);
    float4_type->members.push_back(float_type);

    float4_type->castable_to_types.push_back(int4_type);
    float4_type->castable_to_types.push_back(half4_type);
    float4_type->castable_to_types.push_back(double4_type);
    float4_type->castable_to_types.push_back(float4_type);
    float4_type->castable_to_types.push_back(uint4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);

    float4_type->constructors.push_back(constructor0);
    float4_type->constructors.push_back(constructor1);


    // Floats
    double4_type = new ASTType("double4");
    // 2 float members
    double4_type->members.push_back(double_type);
    double4_type->members.push_back(double_type);
    double4_type->members.push_back(double_type);
    double4_type->members.push_back(double_type);

    double4_type->castable_to_types.push_back(int4_type);
    double4_type->castable_to_types.push_back(half4_type);
    double4_type->castable_to_types.push_back(double4_type);
    double4_type->castable_to_types.push_back(float4_type);
    double4_type->castable_to_types.push_back(uint4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(double_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);

    double4_type->constructors.push_back(constructor0);
    double4_type->constructors.push_back(constructor1);


    // Int
    int4_type = new ASTType("int4");
    // 2 int members
    int4_type->members.push_back(int_type);
    int4_type->members.push_back(int_type);
    int4_type->members.push_back(int_type);
    int4_type->members.push_back(int_type);

    int4_type->castable_to_types.push_back(int4_type);
    int4_type->castable_to_types.push_back(half4_type);
    int4_type->castable_to_types.push_back(double4_type);
    int4_type->castable_to_types.push_back(float4_type);
    int4_type->castable_to_types.push_back(uint4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(int_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);

    int4_type->constructors.push_back(constructor0);
    int4_type->constructors.push_back(constructor1);


    // Half
    half4_type = new ASTType("half4");
    // 2 half members
    half4_type->members.push_back(half_type);
    half4_type->members.push_back(half_type);
    half4_type->members.push_back(half_type);
    half4_type->members.push_back(half_type);

    half4_type->castable_to_types.push_back(int4_type);
    half4_type->castable_to_types.push_back(half4_type);
    half4_type->castable_to_types.push_back(double4_type);
    half4_type->castable_to_types.push_back(float4_type);
    half4_type->castable_to_types.push_back(uint4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(half_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);

    half4_type->constructors.push_back(constructor0);
    half4_type->constructors.push_back(constructor1);


    // Half
    uint4_type = new ASTType("uint4");
    // 2 uint members
    uint4_type->members.push_back(uint_type);
    uint4_type->members.push_back(uint_type);
    uint4_type->members.push_back(uint_type);
    uint4_type->members.push_back(uint_type);

    uint4_type->castable_to_types.push_back(int4_type);
    uint4_type->castable_to_types.push_back(half4_type);
    uint4_type->castable_to_types.push_back(double4_type);
    uint4_type->castable_to_types.push_back(float4_type);
    uint4_type->castable_to_types.push_back(uint4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(uint_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);

    uint4_type->constructors.push_back(constructor0);
    uint4_type->constructors.push_back(constructor1);
    parser->scope->addTypeDeclaration(uint4_type);
    parser->scope->addTypeDeclaration(int4_type);
    parser->scope->addTypeDeclaration(float4_type);
    parser->scope->addTypeDeclaration(double4_type);
    parser->scope->addTypeDeclaration(half4_type);
}


void addBuiltIn2x2MatricessToScope(Parser* parser) {
    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    // Floats
    float2x2_type = float4_type;
    int2x2_type = int4_type;
    uint2x2_type = uint4_type;
    double2x2_type = double4_type;
    half2x2_type = half4_type;


    // Floats
    float2x2_type = new ASTType("float2x2");
    // 2 float members
    float2x2_type->members.push_back(float_type);
    float2x2_type->members.push_back(float_type);
    float2x2_type->members.push_back(float_type);
    float2x2_type->members.push_back(float_type);

    float2x2_type->castable_to_types.push_back(int2x2_type);
    float2x2_type->castable_to_types.push_back(half2x2_type);
    float2x2_type->castable_to_types.push_back(double2x2_type);
    float2x2_type->castable_to_types.push_back(float2x2_type);
    float2x2_type->castable_to_types.push_back(uint2x2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);

    float2x2_type->constructors.push_back(constructor0);
    float2x2_type->constructors.push_back(constructor1);


    // Floats
    double2x2_type = new ASTType("double2x2");
    // 2 float members
    double2x2_type->members.push_back(double_type);
    double2x2_type->members.push_back(double_type);
    double2x2_type->members.push_back(double_type);
    double2x2_type->members.push_back(double_type);

    double2x2_type->castable_to_types.push_back(int2x2_type);
    double2x2_type->castable_to_types.push_back(half2x2_type);
    double2x2_type->castable_to_types.push_back(double2x2_type);
    double2x2_type->castable_to_types.push_back(float2x2_type);
    double2x2_type->castable_to_types.push_back(uint2x2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(double_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);

    double2x2_type->constructors.push_back(constructor0);
    double2x2_type->constructors.push_back(constructor1);


    // Int
    int2x2_type = new ASTType("int2x2");
    // 2 int members
    int2x2_type->members.push_back(int_type);
    int2x2_type->members.push_back(int_type);
    int2x2_type->members.push_back(int_type);
    int2x2_type->members.push_back(int_type);

    int2x2_type->castable_to_types.push_back(int2x2_type);
    int2x2_type->castable_to_types.push_back(half2x2_type);
    int2x2_type->castable_to_types.push_back(double2x2_type);
    int2x2_type->castable_to_types.push_back(float2x2_type);
    int2x2_type->castable_to_types.push_back(uint2x2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(int_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);

    int2x2_type->constructors.push_back(constructor0);
    int2x2_type->constructors.push_back(constructor1);


    // Half
    half2x2_type = new ASTType("half2x2");
    // 2 half members
    half2x2_type->members.push_back(half_type);
    half2x2_type->members.push_back(half_type);
    half2x2_type->members.push_back(half_type);
    half2x2_type->members.push_back(half_type);

    half2x2_type->castable_to_types.push_back(int2x2_type);
    half2x2_type->castable_to_types.push_back(half2x2_type);
    half2x2_type->castable_to_types.push_back(double2x2_type);
    half2x2_type->castable_to_types.push_back(float2x2_type);
    half2x2_type->castable_to_types.push_back(uint2x2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(half_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);

    half2x2_type->constructors.push_back(constructor0);
    half2x2_type->constructors.push_back(constructor1);


    // Half
    uint2x2_type = new ASTType("uint2x2");
    // 2 uint members
    uint2x2_type->members.push_back(uint_type);
    uint2x2_type->members.push_back(uint_type);
    uint2x2_type->members.push_back(uint_type);
    uint2x2_type->members.push_back(uint_type);

    uint2x2_type->castable_to_types.push_back(int2x2_type);
    uint2x2_type->castable_to_types.push_back(half2x2_type);
    uint2x2_type->castable_to_types.push_back(double2x2_type);
    uint2x2_type->castable_to_types.push_back(float2x2_type);
    uint2x2_type->castable_to_types.push_back(uint2x2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(uint_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);

    uint2x2_type->constructors.push_back(constructor0);
    uint2x2_type->constructors.push_back(constructor1);
    parser->scope->addTypeDeclaration(uint4_type);
    parser->scope->addTypeDeclaration(int4_type);
    parser->scope->addTypeDeclaration(float4_type);
    parser->scope->addTypeDeclaration(double4_type);
    parser->scope->addTypeDeclaration(half4_type);
}



void addBuiltIn3x2MatricessToScope(Parser* parser) {
    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    // Floats
    float3x2_type = new ASTType("float3x2");
    // 2 float members
    float3x2_type->members.push_back(float_type);
    float3x2_type->members.push_back(float_type);
    float3x2_type->members.push_back(float_type);
    float3x2_type->members.push_back(float_type);
    float3x2_type->members.push_back(float_type);
    float3x2_type->members.push_back(float_type);

    float3x2_type->castable_to_types.push_back(int3x2_type);
    float3x2_type->castable_to_types.push_back(half3x2_type);
    float3x2_type->castable_to_types.push_back(double3x2_type);
    float3x2_type->castable_to_types.push_back(float3x2_type);
    float3x2_type->castable_to_types.push_back(uint3x2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);

    float3x2_type->constructors.push_back(constructor0);
    float3x2_type->constructors.push_back(constructor1);




    // Floats
    double3x2_type = new ASTType("double3x2");
    // 2 double members
    double3x2_type->members.push_back(double_type);
    double3x2_type->members.push_back(double_type);
    double3x2_type->members.push_back(double_type);
    double3x2_type->members.push_back(double_type);
    double3x2_type->members.push_back(double_type);
    double3x2_type->members.push_back(double_type);

    double3x2_type->castable_to_types.push_back(int3x2_type);
    double3x2_type->castable_to_types.push_back(half3x2_type);
    double3x2_type->castable_to_types.push_back(double3x2_type);
    double3x2_type->castable_to_types.push_back(float3x2_type);
    double3x2_type->castable_to_types.push_back(uint3x2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(double_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);

    double3x2_type->constructors.push_back(constructor0);
    double3x2_type->constructors.push_back(constructor1);




    // Floats
    int3x2_type = new ASTType("int3x2");
    // 2 int members
    int3x2_type->members.push_back(int_type);
    int3x2_type->members.push_back(int_type);
    int3x2_type->members.push_back(int_type);
    int3x2_type->members.push_back(int_type);
    int3x2_type->members.push_back(int_type);
    int3x2_type->members.push_back(int_type);

    int3x2_type->castable_to_types.push_back(int3x2_type);
    int3x2_type->castable_to_types.push_back(half3x2_type);
    int3x2_type->castable_to_types.push_back(double3x2_type);
    int3x2_type->castable_to_types.push_back(float3x2_type);
    int3x2_type->castable_to_types.push_back(uint3x2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(int_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);

    int3x2_type->constructors.push_back(constructor0);
    int3x2_type->constructors.push_back(constructor1);




    // Floats
    uint3x2_type = new ASTType("uint3x2");
    // 2 uint members
    uint3x2_type->members.push_back(uint_type);
    uint3x2_type->members.push_back(uint_type);
    uint3x2_type->members.push_back(uint_type);
    uint3x2_type->members.push_back(uint_type);
    uint3x2_type->members.push_back(uint_type);
    uint3x2_type->members.push_back(uint_type);

    uint3x2_type->castable_to_types.push_back(uint3x2_type);
    uint3x2_type->castable_to_types.push_back(half3x2_type);
    uint3x2_type->castable_to_types.push_back(double3x2_type);
    uint3x2_type->castable_to_types.push_back(float3x2_type);
    uint3x2_type->castable_to_types.push_back(int3x2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(uint_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);

    uint3x2_type->constructors.push_back(constructor0);
    uint3x2_type->constructors.push_back(constructor1);


    // Floats
    half3x2_type = new ASTType("half3x2");
    // 2 half members
    half3x2_type->members.push_back(half_type);
    half3x2_type->members.push_back(half_type);
    half3x2_type->members.push_back(half_type);
    half3x2_type->members.push_back(half_type);
    half3x2_type->members.push_back(half_type);
    half3x2_type->members.push_back(half_type);

    half3x2_type->castable_to_types.push_back(int3x2_type);
    half3x2_type->castable_to_types.push_back(half3x2_type);
    half3x2_type->castable_to_types.push_back(double3x2_type);
    half3x2_type->castable_to_types.push_back(float3x2_type);
    half3x2_type->castable_to_types.push_back(int3x2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(half_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);

    half3x2_type->constructors.push_back(constructor0);
    half3x2_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(float3x2_type);
    parser->scope->addTypeDeclaration(double3x2_type);
    parser->scope->addTypeDeclaration(int3x2_type);
    parser->scope->addTypeDeclaration(uint3x2_type);
    parser->scope->addTypeDeclaration(half3x2_type);
}





void addBuiltIn2x3MatricessToScope(Parser* parser) {
    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    // Floats
    float2x3_type = new ASTType("float2x3");
    // 2 float members
    float2x3_type->members.push_back(float_type);
    float2x3_type->members.push_back(float_type);
    float2x3_type->members.push_back(float_type);
    float2x3_type->members.push_back(float_type);
    float2x3_type->members.push_back(float_type);
    float2x3_type->members.push_back(float_type);

    float2x3_type->castable_to_types.push_back(int2x3_type);
    float2x3_type->castable_to_types.push_back(half2x3_type);
    float2x3_type->castable_to_types.push_back(double2x3_type);
    float2x3_type->castable_to_types.push_back(float2x3_type);
    float2x3_type->castable_to_types.push_back(uint2x3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);

    float2x3_type->constructors.push_back(constructor0);
    float2x3_type->constructors.push_back(constructor1);




    // Floats
    double2x3_type = new ASTType("double2x3");
    // 2 double members
    double2x3_type->members.push_back(double_type);
    double2x3_type->members.push_back(double_type);
    double2x3_type->members.push_back(double_type);
    double2x3_type->members.push_back(double_type);
    double2x3_type->members.push_back(double_type);
    double2x3_type->members.push_back(double_type);

    double2x3_type->castable_to_types.push_back(int2x3_type);
    double2x3_type->castable_to_types.push_back(half2x3_type);
    double2x3_type->castable_to_types.push_back(double2x3_type);
    double2x3_type->castable_to_types.push_back(float2x3_type);
    double2x3_type->castable_to_types.push_back(uint2x3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(double_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);

    double2x3_type->constructors.push_back(constructor0);
    double2x3_type->constructors.push_back(constructor1);




    // Floats
    int2x3_type = new ASTType("int2x3");
    // 2 int members
    int2x3_type->members.push_back(int_type);
    int2x3_type->members.push_back(int_type);
    int2x3_type->members.push_back(int_type);
    int2x3_type->members.push_back(int_type);
    int2x3_type->members.push_back(int_type);
    int2x3_type->members.push_back(int_type);

    int2x3_type->castable_to_types.push_back(int2x3_type);
    int2x3_type->castable_to_types.push_back(half2x3_type);
    int2x3_type->castable_to_types.push_back(double2x3_type);
    int2x3_type->castable_to_types.push_back(float2x3_type);
    int2x3_type->castable_to_types.push_back(uint2x3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(int_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);

    int2x3_type->constructors.push_back(constructor0);
    int2x3_type->constructors.push_back(constructor1);




    // Floats
    uint2x3_type = new ASTType("uint2x3");
    // 2 uint members
    uint2x3_type->members.push_back(uint_type);
    uint2x3_type->members.push_back(uint_type);
    uint2x3_type->members.push_back(uint_type);
    uint2x3_type->members.push_back(uint_type);
    uint2x3_type->members.push_back(uint_type);
    uint2x3_type->members.push_back(uint_type);

    uint2x3_type->castable_to_types.push_back(uint2x3_type);
    uint2x3_type->castable_to_types.push_back(half2x3_type);
    uint2x3_type->castable_to_types.push_back(double2x3_type);
    uint2x3_type->castable_to_types.push_back(float2x3_type);
    uint2x3_type->castable_to_types.push_back(int2x3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(uint_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);

    uint2x3_type->constructors.push_back(constructor0);
    uint2x3_type->constructors.push_back(constructor1);


    // Floats
    half2x3_type = new ASTType("half2x3");
    // 2 half members
    half2x3_type->members.push_back(half_type);
    half2x3_type->members.push_back(half_type);
    half2x3_type->members.push_back(half_type);
    half2x3_type->members.push_back(half_type);
    half2x3_type->members.push_back(half_type);
    half2x3_type->members.push_back(half_type);

    half2x3_type->castable_to_types.push_back(int2x3_type);
    half2x3_type->castable_to_types.push_back(half2x3_type);
    half2x3_type->castable_to_types.push_back(double2x3_type);
    half2x3_type->castable_to_types.push_back(float2x3_type);
    half2x3_type->castable_to_types.push_back(int2x3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(half_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);

    half2x3_type->constructors.push_back(constructor0);
    half2x3_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(float2x3_type);
    parser->scope->addTypeDeclaration(double2x3_type);
    parser->scope->addTypeDeclaration(int2x3_type);
    parser->scope->addTypeDeclaration(uint2x3_type);
    parser->scope->addTypeDeclaration(half2x3_type);
}



void addBuiltIn4x2MatricessToScope(Parser* parser) {
    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    // Floats
    float4x2_type = new ASTType("float4x2");
    // 2 float members
    float4x2_type->members.push_back(float_type);
    float4x2_type->members.push_back(float_type);
    float4x2_type->members.push_back(float_type);
    float4x2_type->members.push_back(float_type);
    float4x2_type->members.push_back(float_type);
    float4x2_type->members.push_back(float_type);
    float4x2_type->members.push_back(float_type);
    float4x2_type->members.push_back(float_type);

    float4x2_type->castable_to_types.push_back(int4x2_type);
    float4x2_type->castable_to_types.push_back(half4x2_type);
    float4x2_type->castable_to_types.push_back(double4x2_type);
    float4x2_type->castable_to_types.push_back(float4x2_type);
    float4x2_type->castable_to_types.push_back(uint4x2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);

    float4x2_type->constructors.push_back(constructor0);
    float4x2_type->constructors.push_back(constructor1);




    // Floats
    double4x2_type = new ASTType("double4x2");
    // 2 double members
    double4x2_type->members.push_back(double_type);
    double4x2_type->members.push_back(double_type);
    double4x2_type->members.push_back(double_type);
    double4x2_type->members.push_back(double_type);
    double4x2_type->members.push_back(double_type);
    double4x2_type->members.push_back(double_type);
    double4x2_type->members.push_back(double_type);
    double4x2_type->members.push_back(double_type);

    double4x2_type->castable_to_types.push_back(int4x2_type);
    double4x2_type->castable_to_types.push_back(half4x2_type);
    double4x2_type->castable_to_types.push_back(double4x2_type);
    double4x2_type->castable_to_types.push_back(float4x2_type);
    double4x2_type->castable_to_types.push_back(uint4x2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(double_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);

    double4x2_type->constructors.push_back(constructor0);
    double4x2_type->constructors.push_back(constructor1);




    // Floats
    int4x2_type = new ASTType("int4x2");
    // 2 int members
    int4x2_type->members.push_back(int_type);
    int4x2_type->members.push_back(int_type);
    int4x2_type->members.push_back(int_type);
    int4x2_type->members.push_back(int_type);
    int4x2_type->members.push_back(int_type);
    int4x2_type->members.push_back(int_type);
    int4x2_type->members.push_back(int_type);
    int4x2_type->members.push_back(int_type);

    int4x2_type->castable_to_types.push_back(int4x2_type);
    int4x2_type->castable_to_types.push_back(half4x2_type);
    int4x2_type->castable_to_types.push_back(double4x2_type);
    int4x2_type->castable_to_types.push_back(float4x2_type);
    int4x2_type->castable_to_types.push_back(uint4x2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(int_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);

    int4x2_type->constructors.push_back(constructor0);
    int4x2_type->constructors.push_back(constructor1);




    // Floats
    uint4x2_type = new ASTType("uint4x2");
    // 2 uint members
    uint4x2_type->members.push_back(uint_type);
    uint4x2_type->members.push_back(uint_type);
    uint4x2_type->members.push_back(uint_type);
    uint4x2_type->members.push_back(uint_type);
    uint4x2_type->members.push_back(uint_type);
    uint4x2_type->members.push_back(uint_type);
    uint4x2_type->members.push_back(uint_type);
    uint4x2_type->members.push_back(uint_type);

    uint4x2_type->castable_to_types.push_back(int4x2_type);
    uint4x2_type->castable_to_types.push_back(half4x2_type);
    uint4x2_type->castable_to_types.push_back(double4x2_type);
    uint4x2_type->castable_to_types.push_back(float4x2_type);
    uint4x2_type->castable_to_types.push_back(uint4x2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(uint_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);

    uint4x2_type->constructors.push_back(constructor0);
    uint4x2_type->constructors.push_back(constructor1);




    // Floats
    half4x2_type = new ASTType("half4x2");
    // 2 half members
    half4x2_type->members.push_back(half_type);
    half4x2_type->members.push_back(half_type);
    half4x2_type->members.push_back(half_type);
    half4x2_type->members.push_back(half_type);
    half4x2_type->members.push_back(half_type);
    half4x2_type->members.push_back(half_type);
    half4x2_type->members.push_back(half_type);
    half4x2_type->members.push_back(half_type);

    half4x2_type->castable_to_types.push_back(int4x2_type);
    half4x2_type->castable_to_types.push_back(half4x2_type);
    half4x2_type->castable_to_types.push_back(double4x2_type);
    half4x2_type->castable_to_types.push_back(float4x2_type);
    half4x2_type->castable_to_types.push_back(uint4x2_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(half_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);

    half4x2_type->constructors.push_back(constructor0);
    half4x2_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(float4x2_type);
    parser->scope->addTypeDeclaration(uint4x2_type);
    parser->scope->addTypeDeclaration(int4x2_type);
    parser->scope->addTypeDeclaration(half4x2_type);
    parser->scope->addTypeDeclaration(double4x2_type);
}





void addBuiltIn2x4MatricessToScope(Parser* parser) {
    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    // Floats
    float2x4_type = new ASTType("float2x4");
    // 2 float members
    float2x4_type->members.push_back(float_type);
    float2x4_type->members.push_back(float_type);
    float2x4_type->members.push_back(float_type);
    float2x4_type->members.push_back(float_type);
    float2x4_type->members.push_back(float_type);
    float2x4_type->members.push_back(float_type);
    float2x4_type->members.push_back(float_type);
    float2x4_type->members.push_back(float_type);

    float2x4_type->castable_to_types.push_back(int2x4_type);
    float2x4_type->castable_to_types.push_back(half2x4_type);
    float2x4_type->castable_to_types.push_back(double2x4_type);
    float2x4_type->castable_to_types.push_back(float2x4_type);
    float2x4_type->castable_to_types.push_back(uint2x4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);

    float2x4_type->constructors.push_back(constructor0);
    float2x4_type->constructors.push_back(constructor1);




    // Floats
    double2x4_type = new ASTType("double2x4");
    // 2 double members
    double2x4_type->members.push_back(double_type);
    double2x4_type->members.push_back(double_type);
    double2x4_type->members.push_back(double_type);
    double2x4_type->members.push_back(double_type);
    double2x4_type->members.push_back(double_type);
    double2x4_type->members.push_back(double_type);
    double2x4_type->members.push_back(double_type);
    double2x4_type->members.push_back(double_type);

    double2x4_type->castable_to_types.push_back(int2x4_type);
    double2x4_type->castable_to_types.push_back(half2x4_type);
    double2x4_type->castable_to_types.push_back(double2x4_type);
    double2x4_type->castable_to_types.push_back(float2x4_type);
    double2x4_type->castable_to_types.push_back(uint2x4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(double_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);

    double2x4_type->constructors.push_back(constructor0);
    double2x4_type->constructors.push_back(constructor1);




    // Floats
    int2x4_type = new ASTType("int2x4");
    // 2 int members
    int2x4_type->members.push_back(int_type);
    int2x4_type->members.push_back(int_type);
    int2x4_type->members.push_back(int_type);
    int2x4_type->members.push_back(int_type);
    int2x4_type->members.push_back(int_type);
    int2x4_type->members.push_back(int_type);
    int2x4_type->members.push_back(int_type);
    int2x4_type->members.push_back(int_type);

    int2x4_type->castable_to_types.push_back(int2x4_type);
    int2x4_type->castable_to_types.push_back(half2x4_type);
    int2x4_type->castable_to_types.push_back(double2x4_type);
    int2x4_type->castable_to_types.push_back(float2x4_type);
    int2x4_type->castable_to_types.push_back(uint2x4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(int_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);

    int2x4_type->constructors.push_back(constructor0);
    int2x4_type->constructors.push_back(constructor1);




    // Floats
    uint2x4_type = new ASTType("uint2x4");
    // 2 uint members
    uint2x4_type->members.push_back(uint_type);
    uint2x4_type->members.push_back(uint_type);
    uint2x4_type->members.push_back(uint_type);
    uint2x4_type->members.push_back(uint_type);
    uint2x4_type->members.push_back(uint_type);
    uint2x4_type->members.push_back(uint_type);
    uint2x4_type->members.push_back(uint_type);
    uint2x4_type->members.push_back(uint_type);

    uint2x4_type->castable_to_types.push_back(int2x4_type);
    uint2x4_type->castable_to_types.push_back(half2x4_type);
    uint2x4_type->castable_to_types.push_back(double2x4_type);
    uint2x4_type->castable_to_types.push_back(float2x4_type);
    uint2x4_type->castable_to_types.push_back(uint2x4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(uint_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);

    uint2x4_type->constructors.push_back(constructor0);
    uint2x4_type->constructors.push_back(constructor1);




    // Floats
    half2x4_type = new ASTType("half2x4");
    // 2 half members
    half2x4_type->members.push_back(half_type);
    half2x4_type->members.push_back(half_type);
    half2x4_type->members.push_back(half_type);
    half2x4_type->members.push_back(half_type);
    half2x4_type->members.push_back(half_type);
    half2x4_type->members.push_back(half_type);
    half2x4_type->members.push_back(half_type);
    half2x4_type->members.push_back(half_type);

    half2x4_type->castable_to_types.push_back(int2x4_type);
    half2x4_type->castable_to_types.push_back(half2x4_type);
    half2x4_type->castable_to_types.push_back(double2x4_type);
    half2x4_type->castable_to_types.push_back(float2x4_type);
    half2x4_type->castable_to_types.push_back(uint2x4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(half_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);

    half2x4_type->constructors.push_back(constructor0);
    half2x4_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(float2x4_type);
    parser->scope->addTypeDeclaration(uint2x4_type);
    parser->scope->addTypeDeclaration(int2x4_type);
    parser->scope->addTypeDeclaration(half2x4_type);
    parser->scope->addTypeDeclaration(double2x4_type);
}




void addBuiltIn3x3MatricessToScope(Parser* parser) {
    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    // Floats
    float3x3_type = new ASTType("float3x3");
    // 2 float members
    float3x3_type->members.push_back(float_type);
    float3x3_type->members.push_back(float_type);
    float3x3_type->members.push_back(float_type);
    float3x3_type->members.push_back(float_type);
    float3x3_type->members.push_back(float_type);
    float3x3_type->members.push_back(float_type);
    float3x3_type->members.push_back(float_type);
    float3x3_type->members.push_back(float_type);
    float3x3_type->members.push_back(float_type);

    float3x3_type->castable_to_types.push_back(int3x3_type);
    float3x3_type->castable_to_types.push_back(half3x3_type);
    float3x3_type->castable_to_types.push_back(double3x3_type);
    float3x3_type->castable_to_types.push_back(float3x3_type);
    float3x3_type->castable_to_types.push_back(uint3x3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);

    float3x3_type->constructors.push_back(constructor0);
    float3x3_type->constructors.push_back(constructor1);




    // Floats
    double3x3_type = new ASTType("double3x3");
    // 2 double members
    double3x3_type->members.push_back(double_type);
    double3x3_type->members.push_back(double_type);
    double3x3_type->members.push_back(double_type);
    double3x3_type->members.push_back(double_type);
    double3x3_type->members.push_back(double_type);
    double3x3_type->members.push_back(double_type);
    double3x3_type->members.push_back(double_type);
    double3x3_type->members.push_back(double_type);
    double3x3_type->members.push_back(double_type);

    double3x3_type->castable_to_types.push_back(int3x3_type);
    double3x3_type->castable_to_types.push_back(half3x3_type);
    double3x3_type->castable_to_types.push_back(double3x3_type);
    double3x3_type->castable_to_types.push_back(float3x3_type);
    double3x3_type->castable_to_types.push_back(uint3x3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(double_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);

    double3x3_type->constructors.push_back(constructor0);
    double3x3_type->constructors.push_back(constructor1);




    // Floats
    int3x3_type = new ASTType("int3x3");
    // 2 int members
    int3x3_type->members.push_back(int_type);
    int3x3_type->members.push_back(int_type);
    int3x3_type->members.push_back(int_type);
    int3x3_type->members.push_back(int_type);
    int3x3_type->members.push_back(int_type);
    int3x3_type->members.push_back(int_type);
    int3x3_type->members.push_back(int_type);
    int3x3_type->members.push_back(int_type);
    int3x3_type->members.push_back(int_type);

    int3x3_type->castable_to_types.push_back(int3x3_type);
    int3x3_type->castable_to_types.push_back(half3x3_type);
    int3x3_type->castable_to_types.push_back(double3x3_type);
    int3x3_type->castable_to_types.push_back(float3x3_type);
    int3x3_type->castable_to_types.push_back(uint3x3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(int_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);

    int3x3_type->constructors.push_back(constructor0);
    int3x3_type->constructors.push_back(constructor1);




    // Floats
    uint3x3_type = new ASTType("uint3x3");
    // 2 uint members
    uint3x3_type->members.push_back(uint_type);
    uint3x3_type->members.push_back(uint_type);
    uint3x3_type->members.push_back(uint_type);
    uint3x3_type->members.push_back(uint_type);
    uint3x3_type->members.push_back(uint_type);
    uint3x3_type->members.push_back(uint_type);
    uint3x3_type->members.push_back(uint_type);
    uint3x3_type->members.push_back(uint_type);
    uint3x3_type->members.push_back(uint_type);

    uint3x3_type->castable_to_types.push_back(int3x3_type);
    uint3x3_type->castable_to_types.push_back(half3x3_type);
    uint3x3_type->castable_to_types.push_back(double3x3_type);
    uint3x3_type->castable_to_types.push_back(float3x3_type);
    uint3x3_type->castable_to_types.push_back(uint3x3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(uint_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);

    uint3x3_type->constructors.push_back(constructor0);
    uint3x3_type->constructors.push_back(constructor1);




    // Floats
    half3x3_type = new ASTType("half3x3");
    // 2 half members
    half3x3_type->members.push_back(half_type);
    half3x3_type->members.push_back(half_type);
    half3x3_type->members.push_back(half_type);
    half3x3_type->members.push_back(half_type);
    half3x3_type->members.push_back(half_type);
    half3x3_type->members.push_back(half_type);
    half3x3_type->members.push_back(half_type);
    half3x3_type->members.push_back(half_type);
    half3x3_type->members.push_back(half_type);

    half3x3_type->castable_to_types.push_back(int3x3_type);
    half3x3_type->castable_to_types.push_back(half3x3_type);
    half3x3_type->castable_to_types.push_back(double3x3_type);
    half3x3_type->castable_to_types.push_back(float3x3_type);
    half3x3_type->castable_to_types.push_back(uint3x3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(half_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);

    half3x3_type->constructors.push_back(constructor0);
    half3x3_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(float3x3_type);
    parser->scope->addTypeDeclaration(uint3x3_type);
    parser->scope->addTypeDeclaration(int3x3_type);
    parser->scope->addTypeDeclaration(half3x3_type);
    parser->scope->addTypeDeclaration(double3x3_type);
}





void addBuiltIn4x3MatricessToScope(Parser* parser) {
    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    // Floats
    float4x3_type = new ASTType("float4x3");
    // 2 float members
    float4x3_type->members.push_back(float_type);
    float4x3_type->members.push_back(float_type);
    float4x3_type->members.push_back(float_type);
    float4x3_type->members.push_back(float_type);
    float4x3_type->members.push_back(float_type);
    float4x3_type->members.push_back(float_type);
    float4x3_type->members.push_back(float_type);
    float4x3_type->members.push_back(float_type);
    float4x3_type->members.push_back(float_type);
    float4x3_type->members.push_back(float_type);
    float4x3_type->members.push_back(float_type);
    float4x3_type->members.push_back(float_type);

    float4x3_type->castable_to_types.push_back(int4x3_type);
    float4x3_type->castable_to_types.push_back(half4x3_type);
    float4x3_type->castable_to_types.push_back(double4x3_type);
    float4x3_type->castable_to_types.push_back(float4x3_type);
    float4x3_type->castable_to_types.push_back(uint4x3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);

    float4x3_type->constructors.push_back(constructor0);
    float4x3_type->constructors.push_back(constructor1);




    // Floats
    double4x3_type = new ASTType("double4x3");
    // 2 double members
    double4x3_type->members.push_back(double_type);
    double4x3_type->members.push_back(double_type);
    double4x3_type->members.push_back(double_type);
    double4x3_type->members.push_back(double_type);
    double4x3_type->members.push_back(double_type);
    double4x3_type->members.push_back(double_type);
    double4x3_type->members.push_back(double_type);
    double4x3_type->members.push_back(double_type);
    double4x3_type->members.push_back(double_type);
    double4x3_type->members.push_back(double_type);
    double4x3_type->members.push_back(double_type);
    double4x3_type->members.push_back(double_type);

    double4x3_type->castable_to_types.push_back(int4x3_type);
    double4x3_type->castable_to_types.push_back(half4x3_type);
    double4x3_type->castable_to_types.push_back(double4x3_type);
    double4x3_type->castable_to_types.push_back(float4x3_type);
    double4x3_type->castable_to_types.push_back(uint4x3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(double_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);

    double4x3_type->constructors.push_back(constructor0);
    double4x3_type->constructors.push_back(constructor1);




    // Floats
    int4x3_type = new ASTType("int4x3");
    // 2 int members
    int4x3_type->members.push_back(int_type);
    int4x3_type->members.push_back(int_type);
    int4x3_type->members.push_back(int_type);
    int4x3_type->members.push_back(int_type);
    int4x3_type->members.push_back(int_type);
    int4x3_type->members.push_back(int_type);
    int4x3_type->members.push_back(int_type);
    int4x3_type->members.push_back(int_type);
    int4x3_type->members.push_back(int_type);
    int4x3_type->members.push_back(int_type);
    int4x3_type->members.push_back(int_type);
    int4x3_type->members.push_back(int_type);

    int4x3_type->castable_to_types.push_back(int4x3_type);
    int4x3_type->castable_to_types.push_back(half4x3_type);
    int4x3_type->castable_to_types.push_back(double4x3_type);
    int4x3_type->castable_to_types.push_back(float4x3_type);
    int4x3_type->castable_to_types.push_back(uint4x3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(int_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);

    int4x3_type->constructors.push_back(constructor0);
    int4x3_type->constructors.push_back(constructor1);




    // Floats
    uint4x3_type = new ASTType("uint4x3");
    // 2 uint members
    uint4x3_type->members.push_back(uint_type);
    uint4x3_type->members.push_back(uint_type);
    uint4x3_type->members.push_back(uint_type);
    uint4x3_type->members.push_back(uint_type);
    uint4x3_type->members.push_back(uint_type);
    uint4x3_type->members.push_back(uint_type);
    uint4x3_type->members.push_back(uint_type);
    uint4x3_type->members.push_back(uint_type);
    uint4x3_type->members.push_back(uint_type);
    uint4x3_type->members.push_back(uint_type);
    uint4x3_type->members.push_back(uint_type);
    uint4x3_type->members.push_back(uint_type);

    uint4x3_type->castable_to_types.push_back(int4x3_type);
    uint4x3_type->castable_to_types.push_back(half4x3_type);
    uint4x3_type->castable_to_types.push_back(double4x3_type);
    uint4x3_type->castable_to_types.push_back(float4x3_type);
    uint4x3_type->castable_to_types.push_back(uint4x3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(uint_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);

    uint4x3_type->constructors.push_back(constructor0);
    uint4x3_type->constructors.push_back(constructor1);




    // Floats
    half4x3_type = new ASTType("half4x3");
    // 2 half members
    half4x3_type->members.push_back(half_type);
    half4x3_type->members.push_back(half_type);
    half4x3_type->members.push_back(half_type);
    half4x3_type->members.push_back(half_type);
    half4x3_type->members.push_back(half_type);
    half4x3_type->members.push_back(half_type);
    half4x3_type->members.push_back(half_type);
    half4x3_type->members.push_back(half_type);
    half4x3_type->members.push_back(half_type);
    half4x3_type->members.push_back(half_type);
    half4x3_type->members.push_back(half_type);
    half4x3_type->members.push_back(half_type);

    half4x3_type->castable_to_types.push_back(int4x3_type);
    half4x3_type->castable_to_types.push_back(half4x3_type);
    half4x3_type->castable_to_types.push_back(double4x3_type);
    half4x3_type->castable_to_types.push_back(float4x3_type);
    half4x3_type->castable_to_types.push_back(uint4x3_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(half_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);

    half4x3_type->constructors.push_back(constructor0);
    half4x3_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(float4x3_type);
    parser->scope->addTypeDeclaration(uint4x3_type);
    parser->scope->addTypeDeclaration(int4x3_type);
    parser->scope->addTypeDeclaration(half4x3_type);
    parser->scope->addTypeDeclaration(double4x3_type);
}





void addBuiltIn3x4MatricessToScope(Parser* parser) {
    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    // Floats
    float3x4_type = new ASTType("float3x4");
    // 2 float members
    float3x4_type->members.push_back(float_type);
    float3x4_type->members.push_back(float_type);
    float3x4_type->members.push_back(float_type);
    float3x4_type->members.push_back(float_type);
    float3x4_type->members.push_back(float_type);
    float3x4_type->members.push_back(float_type);
    float3x4_type->members.push_back(float_type);
    float3x4_type->members.push_back(float_type);
    float3x4_type->members.push_back(float_type);
    float3x4_type->members.push_back(float_type);
    float3x4_type->members.push_back(float_type);
    float3x4_type->members.push_back(float_type);

    float3x4_type->castable_to_types.push_back(int3x4_type);
    float3x4_type->castable_to_types.push_back(half3x4_type);
    float3x4_type->castable_to_types.push_back(double3x4_type);
    float3x4_type->castable_to_types.push_back(float3x4_type);
    float3x4_type->castable_to_types.push_back(uint3x4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);

    float3x4_type->constructors.push_back(constructor0);
    float3x4_type->constructors.push_back(constructor1);




    // Floats
    double3x4_type = new ASTType("double3x4");
    // 2 double members
    double3x4_type->members.push_back(double_type);
    double3x4_type->members.push_back(double_type);
    double3x4_type->members.push_back(double_type);
    double3x4_type->members.push_back(double_type);
    double3x4_type->members.push_back(double_type);
    double3x4_type->members.push_back(double_type);
    double3x4_type->members.push_back(double_type);
    double3x4_type->members.push_back(double_type);
    double3x4_type->members.push_back(double_type);
    double3x4_type->members.push_back(double_type);
    double3x4_type->members.push_back(double_type);
    double3x4_type->members.push_back(double_type);

    double3x4_type->castable_to_types.push_back(int3x4_type);
    double3x4_type->castable_to_types.push_back(half3x4_type);
    double3x4_type->castable_to_types.push_back(double3x4_type);
    double3x4_type->castable_to_types.push_back(float3x4_type);
    double3x4_type->castable_to_types.push_back(uint3x4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(double_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);

    double3x4_type->constructors.push_back(constructor0);
    double3x4_type->constructors.push_back(constructor1);




    // Floats
    int3x4_type = new ASTType("int3x4");
    // 2 int members
    int3x4_type->members.push_back(int_type);
    int3x4_type->members.push_back(int_type);
    int3x4_type->members.push_back(int_type);
    int3x4_type->members.push_back(int_type);
    int3x4_type->members.push_back(int_type);
    int3x4_type->members.push_back(int_type);
    int3x4_type->members.push_back(int_type);
    int3x4_type->members.push_back(int_type);
    int3x4_type->members.push_back(int_type);
    int3x4_type->members.push_back(int_type);
    int3x4_type->members.push_back(int_type);
    int3x4_type->members.push_back(int_type);

    int3x4_type->castable_to_types.push_back(int3x4_type);
    int3x4_type->castable_to_types.push_back(half3x4_type);
    int3x4_type->castable_to_types.push_back(double3x4_type);
    int3x4_type->castable_to_types.push_back(float3x4_type);
    int3x4_type->castable_to_types.push_back(uint3x4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(int_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);

    int3x4_type->constructors.push_back(constructor0);
    int3x4_type->constructors.push_back(constructor1);




    // Floats
    uint3x4_type = new ASTType("uint3x4");
    // 2 uint members
    uint3x4_type->members.push_back(uint_type);
    uint3x4_type->members.push_back(uint_type);
    uint3x4_type->members.push_back(uint_type);
    uint3x4_type->members.push_back(uint_type);
    uint3x4_type->members.push_back(uint_type);
    uint3x4_type->members.push_back(uint_type);
    uint3x4_type->members.push_back(uint_type);
    uint3x4_type->members.push_back(uint_type);
    uint3x4_type->members.push_back(uint_type);
    uint3x4_type->members.push_back(uint_type);
    uint3x4_type->members.push_back(uint_type);
    uint3x4_type->members.push_back(uint_type);

    uint3x4_type->castable_to_types.push_back(int3x4_type);
    uint3x4_type->castable_to_types.push_back(half3x4_type);
    uint3x4_type->castable_to_types.push_back(double3x4_type);
    uint3x4_type->castable_to_types.push_back(float3x4_type);
    uint3x4_type->castable_to_types.push_back(uint3x4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(uint_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);

    uint3x4_type->constructors.push_back(constructor0);
    uint3x4_type->constructors.push_back(constructor1);




    // Floats
    half3x4_type = new ASTType("half3x4");
    // 2 half members
    half3x4_type->members.push_back(half_type);
    half3x4_type->members.push_back(half_type);
    half3x4_type->members.push_back(half_type);
    half3x4_type->members.push_back(half_type);
    half3x4_type->members.push_back(half_type);
    half3x4_type->members.push_back(half_type);
    half3x4_type->members.push_back(half_type);
    half3x4_type->members.push_back(half_type);
    half3x4_type->members.push_back(half_type);
    half3x4_type->members.push_back(half_type);
    half3x4_type->members.push_back(half_type);
    half3x4_type->members.push_back(half_type);

    half3x4_type->castable_to_types.push_back(int3x4_type);
    half3x4_type->castable_to_types.push_back(half3x4_type);
    half3x4_type->castable_to_types.push_back(double3x4_type);
    half3x4_type->castable_to_types.push_back(float3x4_type);
    half3x4_type->castable_to_types.push_back(uint3x4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(half_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);

    half3x4_type->constructors.push_back(constructor0);
    half3x4_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(float3x4_type);
    parser->scope->addTypeDeclaration(uint3x4_type);
    parser->scope->addTypeDeclaration(int3x4_type);
    parser->scope->addTypeDeclaration(half3x4_type);
    parser->scope->addTypeDeclaration(double3x4_type);
}








void addBuiltIn4x4MatricessToScope(Parser* parser) {
    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    // Floats
    float4x4_type = new ASTType("float4x4");
    // 2 float members
    float4x4_type->members.push_back(float_type);
    float4x4_type->members.push_back(float_type);
    float4x4_type->members.push_back(float_type);
    float4x4_type->members.push_back(float_type);
    float4x4_type->members.push_back(float_type);
    float4x4_type->members.push_back(float_type);
    float4x4_type->members.push_back(float_type);
    float4x4_type->members.push_back(float_type);
    float4x4_type->members.push_back(float_type);
    float4x4_type->members.push_back(float_type);
    float4x4_type->members.push_back(float_type);
    float4x4_type->members.push_back(float_type);
    float4x4_type->members.push_back(float_type);
    float4x4_type->members.push_back(float_type);
    float4x4_type->members.push_back(float_type);
    float4x4_type->members.push_back(float_type);

    float4x4_type->castable_to_types.push_back(int4x4_type);
    float4x4_type->castable_to_types.push_back(half4x4_type);
    float4x4_type->castable_to_types.push_back(double4x4_type);
    float4x4_type->castable_to_types.push_back(float4x4_type);
    float4x4_type->castable_to_types.push_back(uint4x4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);

    float4x4_type->constructors.push_back(constructor0);
    float4x4_type->constructors.push_back(constructor1);




    // Floats
    double4x4_type = new ASTType("double4x4");
    // 2 double members
    double4x4_type->members.push_back(double_type);
    double4x4_type->members.push_back(double_type);
    double4x4_type->members.push_back(double_type);
    double4x4_type->members.push_back(double_type);
    double4x4_type->members.push_back(double_type);
    double4x4_type->members.push_back(double_type);
    double4x4_type->members.push_back(double_type);
    double4x4_type->members.push_back(double_type);
    double4x4_type->members.push_back(double_type);
    double4x4_type->members.push_back(double_type);
    double4x4_type->members.push_back(double_type);
    double4x4_type->members.push_back(double_type);
    double4x4_type->members.push_back(double_type);
    double4x4_type->members.push_back(double_type);
    double4x4_type->members.push_back(double_type);
    double4x4_type->members.push_back(double_type);

    double4x4_type->castable_to_types.push_back(int4x4_type);
    double4x4_type->castable_to_types.push_back(half4x4_type);
    double4x4_type->castable_to_types.push_back(double4x4_type);
    double4x4_type->castable_to_types.push_back(float4x4_type);
    double4x4_type->castable_to_types.push_back(uint4x4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(double_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);

    double4x4_type->constructors.push_back(constructor0);
    double4x4_type->constructors.push_back(constructor1);




    // Floats
    int4x4_type = new ASTType("int4x4");
    // 2 int members
    int4x4_type->members.push_back(int_type);
    int4x4_type->members.push_back(int_type);
    int4x4_type->members.push_back(int_type);
    int4x4_type->members.push_back(int_type);
    int4x4_type->members.push_back(int_type);
    int4x4_type->members.push_back(int_type);
    int4x4_type->members.push_back(int_type);
    int4x4_type->members.push_back(int_type);
    int4x4_type->members.push_back(int_type);
    int4x4_type->members.push_back(int_type);
    int4x4_type->members.push_back(int_type);
    int4x4_type->members.push_back(int_type);
    int4x4_type->members.push_back(int_type);
    int4x4_type->members.push_back(int_type);
    int4x4_type->members.push_back(int_type);
    int4x4_type->members.push_back(int_type);

    int4x4_type->castable_to_types.push_back(int4x4_type);
    int4x4_type->castable_to_types.push_back(half4x4_type);
    int4x4_type->castable_to_types.push_back(double4x4_type);
    int4x4_type->castable_to_types.push_back(float4x4_type);
    int4x4_type->castable_to_types.push_back(uint4x4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(int_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);

    int4x4_type->constructors.push_back(constructor0);
    int4x4_type->constructors.push_back(constructor1);




    // Floats
    uint4x4_type = new ASTType("uint4x4");
    // 2 uint members
    uint4x4_type->members.push_back(uint_type);
    uint4x4_type->members.push_back(uint_type);
    uint4x4_type->members.push_back(uint_type);
    uint4x4_type->members.push_back(uint_type);
    uint4x4_type->members.push_back(uint_type);
    uint4x4_type->members.push_back(uint_type);
    uint4x4_type->members.push_back(uint_type);
    uint4x4_type->members.push_back(uint_type);
    uint4x4_type->members.push_back(uint_type);
    uint4x4_type->members.push_back(uint_type);
    uint4x4_type->members.push_back(uint_type);
    uint4x4_type->members.push_back(uint_type);
    uint4x4_type->members.push_back(uint_type);
    uint4x4_type->members.push_back(uint_type);
    uint4x4_type->members.push_back(uint_type);
    uint4x4_type->members.push_back(uint_type);

    uint4x4_type->castable_to_types.push_back(int4x4_type);
    uint4x4_type->castable_to_types.push_back(half4x4_type);
    uint4x4_type->castable_to_types.push_back(double4x4_type);
    uint4x4_type->castable_to_types.push_back(float4x4_type);
    uint4x4_type->castable_to_types.push_back(uint4x4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(uint_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);

    uint4x4_type->constructors.push_back(constructor0);
    uint4x4_type->constructors.push_back(constructor1);




    // Floats
    half4x4_type = new ASTType("half4x4");
    // 2 half members
    half4x4_type->members.push_back(half_type);
    half4x4_type->members.push_back(half_type);
    half4x4_type->members.push_back(half_type);
    half4x4_type->members.push_back(half_type);
    half4x4_type->members.push_back(half_type);
    half4x4_type->members.push_back(half_type);
    half4x4_type->members.push_back(half_type);
    half4x4_type->members.push_back(half_type);
    half4x4_type->members.push_back(half_type);
    half4x4_type->members.push_back(half_type);
    half4x4_type->members.push_back(half_type);
    half4x4_type->members.push_back(half_type);
    half4x4_type->members.push_back(half_type);
    half4x4_type->members.push_back(half_type);
    half4x4_type->members.push_back(half_type);
    half4x4_type->members.push_back(half_type);

    half4x4_type->castable_to_types.push_back(int4x4_type);
    half4x4_type->castable_to_types.push_back(half4x4_type);
    half4x4_type->castable_to_types.push_back(double4x4_type);
    half4x4_type->castable_to_types.push_back(float4x4_type);
    half4x4_type->castable_to_types.push_back(uint4x4_type);

    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(half_type);

    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);
    constructor1->arguments.push_back(half_type);

    half4x4_type->constructors.push_back(constructor0);
    half4x4_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(float4x4_type);
    parser->scope->addTypeDeclaration(uint4x4_type);
    parser->scope->addTypeDeclaration(int4x4_type);
    parser->scope->addTypeDeclaration(half4x4_type);
    parser->scope->addTypeDeclaration(double4x4_type);
}


void addBuiltSamplersToScope(Parser* parser) {
    sampler_type = new ASTType("sampler");
    sampler1D_type = new ASTType("sampler1D");
    sampler2D_type = new ASTType("sampler2D");
    sampler3D_type = new ASTType("sampler3D");
    samplerCUBE_type = new ASTType("samplerCUBE");
    sampler_state_type = new ASTType("sampler_state");
    SamplerState_type = new ASTType("SamplerState");

    parser->scope->addTypeDeclaration(sampler_type);
    parser->scope->addTypeDeclaration(sampler1D_type);
    parser->scope->addTypeDeclaration(sampler2D_type);
    parser->scope->addTypeDeclaration(sampler3D_type);
    parser->scope->addTypeDeclaration(samplerCUBE_type);
    parser->scope->addTypeDeclaration(sampler_type);
    parser->scope->addTypeDeclaration(SamplerState_type);
}

void addBuiltTexturesToScope(Parser* parser) {
    texture1D_type = new ASTType("texture1D");
    texture1DArray_type = new ASTType("texture1DArray");
    texture2D_type = new ASTType("texture2D");
    texture2DArray_type = new ASTType("texture2DArray");
    texture3D_type = new ASTType("texture3D");
    texture3DArray_type = new ASTType("texture3DArray");
    textureCube_type = new ASTType("textureCube");

    parser->scope->addTypeDeclaration(texture1D_type);
    parser->scope->addTypeDeclaration(texture1DArray_type);
    parser->scope->addTypeDeclaration(texture2D_type);
    parser->scope->addTypeDeclaration(texture2DArray_type);
    parser->scope->addTypeDeclaration(texture3D_type);
    parser->scope->addTypeDeclaration(texture3DArray_type);
    parser->scope->addTypeDeclaration(textureCube_type);
}



void addBuiltInTypesToScope(Parser* parser) {
    addBuiltInScalarsToScope(parser);
    addBuiltIn2VectorsToScope(parser);
    addBuiltIn3VectorsToScope(parser);
    addBuiltIn4VectorsToScope(parser);

    addBuiltIn2x2MatricessToScope(parser);
    addBuiltIn3x2MatricessToScope(parser);
    addBuiltIn4x2MatricessToScope(parser);

    addBuiltIn2x3MatricessToScope(parser);
    addBuiltIn3x3MatricessToScope(parser);
    addBuiltIn4x3MatricessToScope(parser);

    addBuiltIn2x4MatricessToScope(parser);
    addBuiltIn3x4MatricessToScope(parser);
    addBuiltIn4x4MatricessToScope(parser);

    addBuiltSamplersToScope(parser);
    addBuiltTexturesToScope(parser);
}



}