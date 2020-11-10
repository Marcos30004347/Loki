#include "Types.hpp"
#include "BuiltInTypes.hpp"

#include <stdio.h>
namespace GLSL {

void addSamplerTypes(Parser* parser) {
    sampler_type = new ASTType("sampler");
    parser->scope->addTypeDeclaration(sampler_type);
}

void addScalarsTypesToScope(Parser* parser) {
    void_type = new ASTType("void");

    int_type = new ASTType("int");
    int_type->accept_literals.push_back(ASTLiteral::Type::LITERAL_INT);
    int_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_FLOAT);
    int_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_BOOL);
    int_type->castable_to_types.push_back(float_type);
    int_type->castable_to_types.push_back(uint_type);
    int_type->castable_to_types.push_back(double_type);
    int_type->castable_to_types.push_back(bool_type);
    int_type->castable_to_types.push_back(int_type);
    int_type->constructors.push_back(new ASTConstructor());
    int_type->constructors[0]->arguments.push_back(int_type);


    float_type = new ASTType("float");
    float_type->accept_literals.push_back(ASTLiteral::Type::LITERAL_INT);
    float_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_FLOAT);
    float_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_BOOL);
    float_type->castable_to_types.push_back(float_type);
    float_type->castable_to_types.push_back(uint_type);
    float_type->castable_to_types.push_back(double_type);
    float_type->castable_to_types.push_back(bool_type);
    float_type->castable_to_types.push_back(int_type);
    float_type->constructors.push_back(new ASTConstructor());
    float_type->constructors[0]->arguments.push_back(float_type);


    double_type = new ASTType("double");
    double_type->accept_literals.push_back(ASTLiteral::Type::LITERAL_INT);
    double_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_FLOAT);
    double_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_BOOL);
    double_type->castable_to_types.push_back(float_type);
    double_type->castable_to_types.push_back(uint_type);
    double_type->castable_to_types.push_back(double_type);
    double_type->castable_to_types.push_back(bool_type);
    double_type->castable_to_types.push_back(int_type);
    double_type->constructors.push_back(new ASTConstructor());
    double_type->constructors[0]->arguments.push_back(double_type);


    uint_type = new ASTType("uint");
    uint_type->accept_literals.push_back(ASTLiteral::Type::LITERAL_INT);
    uint_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_FLOAT);
    uint_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_BOOL);
    uint_type->castable_to_types.push_back(float_type);
    uint_type->castable_to_types.push_back(uint_type);
    uint_type->castable_to_types.push_back(double_type);
    uint_type->castable_to_types.push_back(bool_type);
    uint_type->castable_to_types.push_back(int_type);
    uint_type->constructors.push_back(new ASTConstructor());
    uint_type->constructors[0]->arguments.push_back(uint_type);


    bool_type = new ASTType("bool");
    bool_type->accept_literals.push_back(ASTLiteral::Type::LITERAL_BOOL);
    bool_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_FLOAT);
    bool_type->castable_to_literals.push_back(ASTLiteral::Type::LITERAL_BOOL);
    bool_type->castable_to_types.push_back(float_type);
    bool_type->castable_to_types.push_back(uint_type);
    bool_type->castable_to_types.push_back(double_type);
    bool_type->castable_to_types.push_back(bool_type);
    bool_type->castable_to_types.push_back(int_type);
    bool_type->constructors.push_back(new ASTConstructor());
    bool_type->constructors[0]->arguments.push_back(bool_type);

    parser->scope->addTypeDeclaration(int_type);
    parser->scope->addTypeDeclaration(void_type);
    parser->scope->addTypeDeclaration(float_type);
    parser->scope->addTypeDeclaration(double_type);
    parser->scope->addTypeDeclaration(uint_type);
    parser->scope->addTypeDeclaration(bool_type);
}


void addVec2TypesToScope(Parser* parser) {
    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    vec2_type = new ASTType("vec2");
    vec2_type->members.push_back(float_type);
    vec2_type->members.push_back(float_type);
    vec2_type->castable_to_types.push_back(uvec2_type);
    vec2_type->castable_to_types.push_back(vec2_type);
    vec2_type->castable_to_types.push_back(ivec2_type);
    vec2_type->castable_to_types.push_back(dvec2_type);
    vec2_type->castable_to_types.push_back(bvec2_type);
    vec2_type->constructors.push_back(new ASTConstructor());
    vec2_type->constructors[0]->arguments.push_back(int_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    vec2_type->constructors.push_back(constructor0);
    vec2_type->constructors.push_back(constructor1);


    dvec2_type = new ASTType("dvec2");
    dvec2_type->members.push_back(double_type);
    dvec2_type->members.push_back(double_type);
    dvec2_type->castable_to_types.push_back(uvec2_type);
    dvec2_type->castable_to_types.push_back(vec2_type);
    dvec2_type->castable_to_types.push_back(ivec2_type);
    dvec2_type->castable_to_types.push_back(dvec2_type);
    dvec2_type->castable_to_types.push_back(bvec2_type);
    dvec2_type->constructors.push_back(new ASTConstructor());
    dvec2_type->constructors[0]->arguments.push_back(int_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(double_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    dvec2_type->constructors.push_back(constructor0);
    dvec2_type->constructors.push_back(constructor1);


    ivec2_type = new ASTType("ivec2");
    ivec2_type->members.push_back(int_type);
    ivec2_type->members.push_back(int_type);
    ivec2_type->castable_to_types.push_back(uvec2_type);
    ivec2_type->castable_to_types.push_back(vec2_type);
    ivec2_type->castable_to_types.push_back(ivec2_type);
    ivec2_type->castable_to_types.push_back(dvec2_type);
    ivec2_type->castable_to_types.push_back(bvec2_type);
    ivec2_type->constructors.push_back(new ASTConstructor());
    ivec2_type->constructors[0]->arguments.push_back(int_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(int_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    ivec2_type->constructors.push_back(constructor0);
    ivec2_type->constructors.push_back(constructor1);


    bvec2_type = new ASTType("bvec2");
    bvec2_type->members.push_back(int_type);
    bvec2_type->members.push_back(int_type);
    bvec2_type->castable_to_types.push_back(uvec2_type);
    bvec2_type->castable_to_types.push_back(vec2_type);
    bvec2_type->castable_to_types.push_back(ivec2_type);
    bvec2_type->castable_to_types.push_back(bvec2_type);
    bvec2_type->castable_to_types.push_back(dvec2_type);
    bvec2_type->constructors.push_back(new ASTConstructor());
    bvec2_type->constructors[0]->arguments.push_back(bool_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(bool_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(bool_type);
    constructor1->arguments.push_back(bool_type);
    bvec2_type->constructors.push_back(constructor0);
    bvec2_type->constructors.push_back(constructor1);

    uvec2_type = new ASTType("uvec2");
    uvec2_type->members.push_back(uint_type);
    uvec2_type->members.push_back(uint_type);
    uvec2_type->castable_to_types.push_back(uvec2_type);
    uvec2_type->castable_to_types.push_back(vec2_type);
    uvec2_type->castable_to_types.push_back(ivec2_type);
    uvec2_type->castable_to_types.push_back(bvec2_type);
    uvec2_type->castable_to_types.push_back(dvec2_type);
    uvec2_type->constructors.push_back(new ASTConstructor());
    uvec2_type->constructors[0]->arguments.push_back(uint_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(uint_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    uvec2_type->constructors.push_back(constructor0);
    uvec2_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(vec2_type);
    parser->scope->addTypeDeclaration(ivec2_type);
    parser->scope->addTypeDeclaration(uvec2_type);
    parser->scope->addTypeDeclaration(bvec2_type);
    parser->scope->addTypeDeclaration(dvec2_type);
}





void addVec3TypesToScope(Parser* parser) {
    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    vec3_type = new ASTType("vec3");
    vec3_type->members.push_back(float_type);
    vec3_type->members.push_back(float_type);
    vec3_type->members.push_back(float_type);
    vec3_type->castable_to_types.push_back(uvec3_type);
    vec3_type->castable_to_types.push_back(vec3_type);
    vec3_type->castable_to_types.push_back(ivec3_type);
    vec3_type->castable_to_types.push_back(dvec3_type);
    vec3_type->castable_to_types.push_back(bvec3_type);
    vec3_type->constructors.push_back(new ASTConstructor());
    vec3_type->constructors[0]->arguments.push_back(int_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    vec3_type->constructors.push_back(constructor0);
    vec3_type->constructors.push_back(constructor1);


    dvec3_type = new ASTType("dvec3");
    dvec3_type->members.push_back(double_type);
    dvec3_type->members.push_back(double_type);
    dvec3_type->members.push_back(double_type);
    dvec3_type->castable_to_types.push_back(uvec3_type);
    dvec3_type->castable_to_types.push_back(vec3_type);
    dvec3_type->castable_to_types.push_back(ivec3_type);
    dvec3_type->castable_to_types.push_back(dvec3_type);
    dvec3_type->castable_to_types.push_back(bvec3_type);
    dvec3_type->constructors.push_back(new ASTConstructor());
    dvec3_type->constructors[0]->arguments.push_back(int_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(double_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    dvec3_type->constructors.push_back(constructor0);
    dvec3_type->constructors.push_back(constructor1);


    ivec3_type = new ASTType("ivec3");
    ivec3_type->members.push_back(int_type);
    ivec3_type->members.push_back(int_type);
    ivec3_type->members.push_back(int_type);
    ivec3_type->castable_to_types.push_back(uvec3_type);
    ivec3_type->castable_to_types.push_back(vec3_type);
    ivec3_type->castable_to_types.push_back(ivec3_type);
    ivec3_type->castable_to_types.push_back(dvec3_type);
    ivec3_type->castable_to_types.push_back(bvec3_type);
    ivec3_type->constructors.push_back(new ASTConstructor());
    ivec3_type->constructors[0]->arguments.push_back(int_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(int_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    ivec3_type->constructors.push_back(constructor0);
    ivec3_type->constructors.push_back(constructor1);


    bvec3_type = new ASTType("bvec3");
    bvec3_type->members.push_back(int_type);
    bvec3_type->members.push_back(int_type);
    bvec3_type->members.push_back(int_type);
    bvec3_type->castable_to_types.push_back(uvec3_type);
    bvec3_type->castable_to_types.push_back(vec3_type);
    bvec3_type->castable_to_types.push_back(ivec3_type);
    bvec3_type->castable_to_types.push_back(bvec3_type);
    bvec3_type->castable_to_types.push_back(dvec3_type);
    bvec3_type->constructors.push_back(new ASTConstructor());
    bvec3_type->constructors[0]->arguments.push_back(bool_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(bool_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(bool_type);
    constructor1->arguments.push_back(bool_type);
    constructor1->arguments.push_back(bool_type);
    bvec3_type->constructors.push_back(constructor0);
    bvec3_type->constructors.push_back(constructor1);

    uvec3_type = new ASTType("uvec3");
    uvec3_type->members.push_back(uint_type);
    uvec3_type->members.push_back(uint_type);
    uvec3_type->members.push_back(uint_type);
    uvec3_type->castable_to_types.push_back(uvec3_type);
    uvec3_type->castable_to_types.push_back(vec3_type);
    uvec3_type->castable_to_types.push_back(ivec3_type);
    uvec3_type->castable_to_types.push_back(bvec3_type);
    uvec3_type->castable_to_types.push_back(dvec3_type);
    uvec3_type->constructors.push_back(new ASTConstructor());
    uvec3_type->constructors[0]->arguments.push_back(uint_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(uint_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    uvec3_type->constructors.push_back(constructor0);
    uvec3_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(vec3_type);
    parser->scope->addTypeDeclaration(ivec3_type);
    parser->scope->addTypeDeclaration(uvec3_type);
    parser->scope->addTypeDeclaration(bvec3_type);
    parser->scope->addTypeDeclaration(dvec3_type);
}




void addVec4TypesToScope(Parser* parser) {
    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    vec4_type = new ASTType("vec4");
    vec4_type->members.push_back(float_type);
    vec4_type->members.push_back(float_type);
    vec4_type->members.push_back(float_type);
    vec4_type->members.push_back(float_type);
    vec4_type->castable_to_types.push_back(uvec4_type);
    vec4_type->castable_to_types.push_back(vec4_type);
    vec4_type->castable_to_types.push_back(ivec4_type);
    vec4_type->castable_to_types.push_back(dvec4_type);
    vec4_type->castable_to_types.push_back(bvec4_type);
    vec4_type->constructors.push_back(new ASTConstructor());
    vec4_type->constructors[0]->arguments.push_back(int_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    vec4_type->constructors.push_back(constructor0);
    vec4_type->constructors.push_back(constructor1);


    dvec4_type = new ASTType("dvec4");
    dvec4_type->members.push_back(double_type);
    dvec4_type->members.push_back(double_type);
    dvec4_type->members.push_back(double_type);
    dvec4_type->members.push_back(double_type);
    dvec4_type->castable_to_types.push_back(uvec4_type);
    dvec4_type->castable_to_types.push_back(vec4_type);
    dvec4_type->castable_to_types.push_back(ivec4_type);
    dvec4_type->castable_to_types.push_back(dvec4_type);
    dvec4_type->castable_to_types.push_back(bvec4_type);
    dvec4_type->constructors.push_back(new ASTConstructor());
    dvec4_type->constructors[0]->arguments.push_back(int_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(double_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    dvec4_type->constructors.push_back(constructor0);
    dvec4_type->constructors.push_back(constructor1);


    ivec4_type = new ASTType("ivec4");
    ivec4_type->members.push_back(int_type);
    ivec4_type->members.push_back(int_type);
    ivec4_type->members.push_back(int_type);
    ivec4_type->members.push_back(int_type);
    ivec4_type->castable_to_types.push_back(uvec4_type);
    ivec4_type->castable_to_types.push_back(vec4_type);
    ivec4_type->castable_to_types.push_back(ivec4_type);
    ivec4_type->castable_to_types.push_back(dvec4_type);
    ivec4_type->castable_to_types.push_back(bvec4_type);
    ivec4_type->constructors.push_back(new ASTConstructor());
    ivec4_type->constructors[0]->arguments.push_back(int_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(int_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    constructor1->arguments.push_back(int_type);
    ivec4_type->constructors.push_back(constructor0);
    ivec4_type->constructors.push_back(constructor1);


    bvec4_type = new ASTType("bvec4");
    bvec4_type->members.push_back(int_type);
    bvec4_type->members.push_back(int_type);
    bvec4_type->members.push_back(int_type);
    bvec4_type->members.push_back(int_type);
    bvec4_type->castable_to_types.push_back(uvec4_type);
    bvec4_type->castable_to_types.push_back(vec4_type);
    bvec4_type->castable_to_types.push_back(ivec4_type);
    bvec4_type->castable_to_types.push_back(bvec4_type);
    bvec4_type->castable_to_types.push_back(dvec4_type);
    bvec4_type->constructors.push_back(new ASTConstructor());
    bvec4_type->constructors[0]->arguments.push_back(bool_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(bool_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(bool_type);
    constructor1->arguments.push_back(bool_type);
    constructor1->arguments.push_back(bool_type);
    constructor1->arguments.push_back(bool_type);
    bvec4_type->constructors.push_back(constructor0);
    bvec4_type->constructors.push_back(constructor1);

    uvec4_type = new ASTType("uvec4");
    uvec4_type->members.push_back(uint_type);
    uvec4_type->members.push_back(uint_type);
    uvec4_type->members.push_back(uint_type);
    uvec4_type->members.push_back(uint_type);
    uvec4_type->castable_to_types.push_back(uvec4_type);
    uvec4_type->castable_to_types.push_back(vec4_type);
    uvec4_type->castable_to_types.push_back(ivec4_type);
    uvec4_type->castable_to_types.push_back(bvec4_type);
    uvec4_type->castable_to_types.push_back(dvec4_type);
    uvec4_type->constructors.push_back(new ASTConstructor());
    uvec4_type->constructors[0]->arguments.push_back(uint_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(uint_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    constructor1->arguments.push_back(uint_type);
    uvec4_type->constructors.push_back(constructor0);
    uvec4_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(vec4_type);
    parser->scope->addTypeDeclaration(ivec4_type);
    parser->scope->addTypeDeclaration(uvec4_type);
    parser->scope->addTypeDeclaration(bvec4_type);
    parser->scope->addTypeDeclaration(dvec4_type);
}




void addMatrix2TypesToScope(Parser* parser) {

    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    mat2_type = new ASTType("mat2");
    mat2_type->members.push_back(float_type);
    mat2_type->members.push_back(float_type);
    mat2_type->members.push_back(float_type);
    mat2_type->members.push_back(float_type);
    mat2_type->castable_to_types.push_back(mat2_type);
    mat2_type->castable_to_types.push_back(dmat2_type);
    mat2_type->constructors.push_back(new ASTConstructor());
    mat2_type->constructors[0]->arguments.push_back(int_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    mat2_type->constructors.push_back(constructor0);
    mat2_type->constructors.push_back(constructor1);


    dmat2_type = new ASTType("dmat2");
    dmat2_type->members.push_back(float_type);
    dmat2_type->members.push_back(float_type);
    dmat2_type->members.push_back(float_type);
    dmat2_type->members.push_back(float_type);
    dmat2_type->castable_to_types.push_back(dmat2_type);
    dmat2_type->castable_to_types.push_back(mat2_type);
    dmat2_type->constructors.push_back(new ASTConstructor());
    dmat2_type->constructors[0]->arguments.push_back(int_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    dmat2_type->constructors.push_back(constructor0);
    dmat2_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(dmat2_type);
    parser->scope->addTypeDeclaration(mat2_type);
}

void addMatrix3TypesToScope(Parser* parser) {

    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    mat3_type = new ASTType("mat3");
    mat3_type->members.push_back(float_type);
    mat3_type->members.push_back(float_type);
    mat3_type->members.push_back(float_type);
    mat3_type->members.push_back(float_type);
    mat3_type->members.push_back(float_type);
    mat3_type->members.push_back(float_type);
    mat3_type->members.push_back(float_type);
    mat3_type->members.push_back(float_type);
    mat3_type->members.push_back(float_type);
    mat3_type->castable_to_types.push_back(mat3_type);
    mat3_type->castable_to_types.push_back(dmat3_type);
    mat3_type->constructors.push_back(new ASTConstructor());
    mat3_type->constructors[0]->arguments.push_back(int_type);
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
    mat3_type->constructors.push_back(constructor0);
    mat3_type->constructors.push_back(constructor1);


    dmat3_type = new ASTType("dmat3");
    dmat3_type->members.push_back(double_type);
    dmat3_type->members.push_back(double_type);
    dmat3_type->members.push_back(double_type);
    dmat3_type->members.push_back(double_type);
    dmat3_type->members.push_back(double_type);
    dmat3_type->members.push_back(double_type);
    dmat3_type->members.push_back(double_type);
    dmat3_type->members.push_back(double_type);
    dmat3_type->members.push_back(double_type);
    dmat3_type->castable_to_types.push_back(dmat3_type);
    dmat3_type->castable_to_types.push_back(mat3_type);
    dmat3_type->constructors.push_back(new ASTConstructor());
    dmat3_type->constructors[0]->arguments.push_back(int_type);
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
    dmat3_type->constructors.push_back(constructor0);
    dmat3_type->constructors.push_back(constructor1);


    parser->scope->addTypeDeclaration(dmat3_type);
    parser->scope->addTypeDeclaration(mat3_type);
}



void addMatrix4TypesToScope(Parser* parser) {

    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    mat4_type = new ASTType("mat4");
    mat4_type->members.push_back(float_type);
    mat4_type->members.push_back(float_type);
    mat4_type->members.push_back(float_type);
    mat4_type->members.push_back(float_type);
    mat4_type->members.push_back(float_type);
    mat4_type->members.push_back(float_type);
    mat4_type->members.push_back(float_type);
    mat4_type->members.push_back(float_type);
    mat4_type->members.push_back(float_type);
    mat4_type->members.push_back(float_type);
    mat4_type->members.push_back(float_type);
    mat4_type->members.push_back(float_type);
    mat4_type->members.push_back(float_type);
    mat4_type->members.push_back(float_type);
    mat4_type->members.push_back(float_type);
    mat4_type->members.push_back(float_type);
    mat4_type->castable_to_types.push_back(mat4_type);
    mat4_type->castable_to_types.push_back(dmat4_type);
    mat4_type->constructors.push_back(new ASTConstructor());
    mat4_type->constructors[0]->arguments.push_back(int_type);
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
    mat4_type->constructors.push_back(constructor0);
    mat4_type->constructors.push_back(constructor1);


    dmat4_type = new ASTType("dmat4");
    dmat4_type->members.push_back(double_type);
    dmat4_type->members.push_back(double_type);
    dmat4_type->members.push_back(double_type);
    dmat4_type->members.push_back(double_type);
    dmat4_type->members.push_back(double_type);
    dmat4_type->members.push_back(double_type);
    dmat4_type->members.push_back(double_type);
    dmat4_type->members.push_back(double_type);
    dmat4_type->members.push_back(double_type);
    dmat4_type->members.push_back(double_type);
    dmat4_type->members.push_back(double_type);
    dmat4_type->members.push_back(double_type);
    dmat4_type->members.push_back(double_type);
    dmat4_type->members.push_back(double_type);
    dmat4_type->members.push_back(double_type);
    dmat4_type->members.push_back(double_type);
    dmat4_type->castable_to_types.push_back(dmat4_type);
    dmat4_type->castable_to_types.push_back(mat4_type);
    dmat4_type->constructors.push_back(new ASTConstructor());
    dmat4_type->constructors[0]->arguments.push_back(int_type);
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
    dmat4_type->constructors.push_back(constructor0);
    dmat4_type->constructors.push_back(constructor1);


    parser->scope->addTypeDeclaration(dmat4_type);
    parser->scope->addTypeDeclaration(mat4_type);
}


void addMatrix3x3TypesToScope(Parser* parser) {

    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    mat3x3_type = new ASTType("mat3x3");
    mat3x3_type->members.push_back(float_type);
    mat3x3_type->members.push_back(float_type);
    mat3x3_type->members.push_back(float_type);
    mat3x3_type->members.push_back(float_type);
    mat3x3_type->members.push_back(float_type);
    mat3x3_type->members.push_back(float_type);
    mat3x3_type->members.push_back(float_type);
    mat3x3_type->members.push_back(float_type);
    mat3x3_type->members.push_back(float_type);
    mat3x3_type->castable_to_types.push_back(mat3x3_type);
    mat3x3_type->castable_to_types.push_back(dmat3x3_type);
    mat3x3_type->constructors.push_back(new ASTConstructor());
    mat3x3_type->constructors[0]->arguments.push_back(int_type);
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
    mat3x3_type->constructors.push_back(constructor0);
    mat3x3_type->constructors.push_back(constructor1);


    dmat3x3_type = new ASTType("dmat3x3");
    dmat3x3_type->members.push_back(double_type);
    dmat3x3_type->members.push_back(double_type);
    dmat3x3_type->members.push_back(double_type);
    dmat3x3_type->members.push_back(double_type);
    dmat3x3_type->members.push_back(double_type);
    dmat3x3_type->members.push_back(double_type);
    dmat3x3_type->members.push_back(double_type);
    dmat3x3_type->members.push_back(double_type);
    dmat3x3_type->members.push_back(double_type);
    dmat3x3_type->castable_to_types.push_back(dmat3x3_type);
    dmat3x3_type->castable_to_types.push_back(mat3x3_type);
    dmat3x3_type->constructors.push_back(new ASTConstructor());
    dmat3x3_type->constructors[0]->arguments.push_back(int_type);
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
    dmat3x3_type->constructors.push_back(constructor0);
    dmat3x3_type->constructors.push_back(constructor1);


    parser->scope->addTypeDeclaration(dmat3x3_type);
    parser->scope->addTypeDeclaration(mat3x3_type);
}



void addMatrix4x4TypesToScope(Parser* parser) {

    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    mat4x4_type = new ASTType("mat4x4");
    mat4x4_type->members.push_back(float_type);
    mat4x4_type->members.push_back(float_type);
    mat4x4_type->members.push_back(float_type);
    mat4x4_type->members.push_back(float_type);
    mat4x4_type->members.push_back(float_type);
    mat4x4_type->members.push_back(float_type);
    mat4x4_type->members.push_back(float_type);
    mat4x4_type->members.push_back(float_type);
    mat4x4_type->members.push_back(float_type);
    mat4x4_type->members.push_back(float_type);
    mat4x4_type->members.push_back(float_type);
    mat4x4_type->members.push_back(float_type);
    mat4x4_type->members.push_back(float_type);
    mat4x4_type->members.push_back(float_type);
    mat4x4_type->members.push_back(float_type);
    mat4x4_type->members.push_back(float_type);
    mat4x4_type->castable_to_types.push_back(mat4x4_type);
    mat4x4_type->castable_to_types.push_back(dmat4x4_type);
    mat4x4_type->constructors.push_back(new ASTConstructor());
    mat4x4_type->constructors[0]->arguments.push_back(int_type);
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
    mat4x4_type->constructors.push_back(constructor0);
    mat4x4_type->constructors.push_back(constructor1);


    dmat4x4_type = new ASTType("dmat4x4");
    dmat4x4_type->members.push_back(double_type);
    dmat4x4_type->members.push_back(double_type);
    dmat4x4_type->members.push_back(double_type);
    dmat4x4_type->members.push_back(double_type);
    dmat4x4_type->members.push_back(double_type);
    dmat4x4_type->members.push_back(double_type);
    dmat4x4_type->members.push_back(double_type);
    dmat4x4_type->members.push_back(double_type);
    dmat4x4_type->members.push_back(double_type);
    dmat4x4_type->members.push_back(double_type);
    dmat4x4_type->members.push_back(double_type);
    dmat4x4_type->members.push_back(double_type);
    dmat4x4_type->members.push_back(double_type);
    dmat4x4_type->members.push_back(double_type);
    dmat4x4_type->members.push_back(double_type);
    dmat4x4_type->members.push_back(double_type);
    dmat4x4_type->castable_to_types.push_back(dmat4x4_type);
    dmat4x4_type->castable_to_types.push_back(mat4x4_type);
    dmat4x4_type->constructors.push_back(new ASTConstructor());
    dmat4x4_type->constructors[0]->arguments.push_back(int_type);
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
    dmat4x4_type->constructors.push_back(constructor0);
    dmat4x4_type->constructors.push_back(constructor1);


    parser->scope->addTypeDeclaration(dmat4x4_type);
    parser->scope->addTypeDeclaration(mat4x4_type);
}



void addMatrix2x2TypesToScope(Parser* parser) {

    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    mat2x2_type = new ASTType("mat2x2");
    mat2x2_type->members.push_back(float_type);
    mat2x2_type->members.push_back(float_type);
    mat2x2_type->members.push_back(float_type);
    mat2x2_type->members.push_back(float_type);
    mat2x2_type->castable_to_types.push_back(mat2x2_type);
    mat2x2_type->castable_to_types.push_back(dmat2x2_type);
    mat2x2_type->constructors.push_back(new ASTConstructor());
    mat2x2_type->constructors[0]->arguments.push_back(int_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    mat2x2_type->constructors.push_back(constructor0);
    mat2x2_type->constructors.push_back(constructor1);


    dmat2x2_type = new ASTType("dmat2x2");
    dmat2x2_type->members.push_back(double_type);
    dmat2x2_type->members.push_back(double_type);
    dmat2x2_type->members.push_back(double_type);
    dmat2x2_type->members.push_back(double_type);
    dmat2x2_type->castable_to_types.push_back(dmat2x2_type);
    dmat2x2_type->castable_to_types.push_back(mat2x2_type);
    dmat2x2_type->constructors.push_back(new ASTConstructor());
    dmat2x2_type->constructors[0]->arguments.push_back(int_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(double_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    dmat2x2_type->constructors.push_back(constructor0);
    dmat2x2_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(dmat2x2_type);
    parser->scope->addTypeDeclaration(mat2x2_type);
}




void addMatrix3x2TypesToScope(Parser* parser) {

    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    mat3x2_type = new ASTType("mat3x2");
    mat3x2_type->members.push_back(float_type);
    mat3x2_type->members.push_back(float_type);
    mat3x2_type->members.push_back(float_type);
    mat3x2_type->members.push_back(float_type);
    mat3x2_type->members.push_back(float_type);
    mat3x2_type->members.push_back(float_type);
    mat3x2_type->castable_to_types.push_back(mat3x2_type);
    mat3x2_type->castable_to_types.push_back(dmat3x2_type);
    mat3x2_type->constructors.push_back(new ASTConstructor());
    mat3x2_type->constructors[0]->arguments.push_back(int_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    mat3x2_type->constructors.push_back(constructor0);
    mat3x2_type->constructors.push_back(constructor1);


    dmat3x2_type = new ASTType("dmat3x2");
    dmat3x2_type->members.push_back(double_type);
    dmat3x2_type->members.push_back(double_type);
    dmat3x2_type->members.push_back(double_type);
    dmat3x2_type->members.push_back(double_type);
    dmat3x2_type->members.push_back(double_type);
    dmat3x2_type->members.push_back(double_type);
    dmat3x2_type->castable_to_types.push_back(dmat3x2_type);
    dmat3x2_type->castable_to_types.push_back(mat3x2_type);
    dmat3x2_type->constructors.push_back(new ASTConstructor());
    dmat3x2_type->constructors[0]->arguments.push_back(int_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(double_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    dmat3x2_type->constructors.push_back(constructor0);
    dmat3x2_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(dmat3x2_type);
    parser->scope->addTypeDeclaration(mat3x2_type);
}




void addMatrix2x3TypesToScope(Parser* parser) {

    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    mat2x3_type = new ASTType("mat2x3");
    mat2x3_type->members.push_back(float_type);
    mat2x3_type->members.push_back(float_type);
    mat2x3_type->members.push_back(float_type);
    mat2x3_type->members.push_back(float_type);
    mat2x3_type->members.push_back(float_type);
    mat2x3_type->members.push_back(float_type);
    mat2x3_type->castable_to_types.push_back(mat2x3_type);
    mat2x3_type->castable_to_types.push_back(dmat2x3_type);
    mat2x3_type->constructors.push_back(new ASTConstructor());
    mat2x3_type->constructors[0]->arguments.push_back(int_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(float_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    constructor1->arguments.push_back(float_type);
    mat2x3_type->constructors.push_back(constructor0);
    mat2x3_type->constructors.push_back(constructor1);


    dmat2x3_type = new ASTType("dmat2x3");
    dmat2x3_type->members.push_back(double_type);
    dmat2x3_type->members.push_back(double_type);
    dmat2x3_type->members.push_back(double_type);
    dmat2x3_type->members.push_back(double_type);
    dmat2x3_type->members.push_back(double_type);
    dmat2x3_type->members.push_back(double_type);
    dmat2x3_type->castable_to_types.push_back(dmat2x3_type);
    dmat2x3_type->castable_to_types.push_back(mat2x3_type);
    dmat2x3_type->constructors.push_back(new ASTConstructor());
    dmat2x3_type->constructors[0]->arguments.push_back(int_type);
    constructor0 = new ASTConstructor();
    constructor0->arguments.push_back(double_type);
    constructor1 = new ASTConstructor();
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    constructor1->arguments.push_back(double_type);
    dmat2x3_type->constructors.push_back(constructor0);
    dmat2x3_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(dmat2x3_type);
    parser->scope->addTypeDeclaration(mat2x3_type);
}

void addMatrix4x2TypesToScope(Parser* parser) {

    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    mat4x2_type = new ASTType("mat4x2");
    mat4x2_type->members.push_back(float_type);
    mat4x2_type->members.push_back(float_type);
    mat4x2_type->members.push_back(float_type);
    mat4x2_type->members.push_back(float_type);
    mat4x2_type->members.push_back(float_type);
    mat4x2_type->members.push_back(float_type);
    mat4x2_type->members.push_back(float_type);
    mat4x2_type->members.push_back(float_type);
    mat4x2_type->castable_to_types.push_back(mat4x2_type);
    mat4x2_type->castable_to_types.push_back(dmat4x2_type);
    mat4x2_type->constructors.push_back(new ASTConstructor());
    mat4x2_type->constructors[0]->arguments.push_back(int_type);
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
    mat4x2_type->constructors.push_back(constructor0);
    mat4x2_type->constructors.push_back(constructor1);


    dmat4x2_type = new ASTType("dmat4x2");
    dmat4x2_type->members.push_back(double_type);
    dmat4x2_type->members.push_back(double_type);
    dmat4x2_type->members.push_back(double_type);
    dmat4x2_type->members.push_back(double_type);
    dmat4x2_type->members.push_back(double_type);
    dmat4x2_type->members.push_back(double_type);
    dmat4x2_type->members.push_back(double_type);
    dmat4x2_type->members.push_back(double_type);
    dmat4x2_type->castable_to_types.push_back(dmat4x2_type);
    dmat4x2_type->castable_to_types.push_back(mat4x2_type);
    dmat4x2_type->constructors.push_back(new ASTConstructor());
    dmat4x2_type->constructors[0]->arguments.push_back(int_type);
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
    dmat4x2_type->constructors.push_back(constructor0);
    dmat4x2_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(dmat4x2_type);
    parser->scope->addTypeDeclaration(mat4x2_type);
}


void addMatrix2x4TypesToScope(Parser* parser) {

    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    mat2x4_type = new ASTType("mat2x4");
    mat2x4_type->members.push_back(float_type);
    mat2x4_type->members.push_back(float_type);
    mat2x4_type->members.push_back(float_type);
    mat2x4_type->members.push_back(float_type);
    mat2x4_type->members.push_back(float_type);
    mat2x4_type->members.push_back(float_type);
    mat2x4_type->members.push_back(float_type);
    mat2x4_type->members.push_back(float_type);
    mat2x4_type->castable_to_types.push_back(mat2x4_type);
    mat2x4_type->castable_to_types.push_back(dmat2x4_type);
    mat2x4_type->constructors.push_back(new ASTConstructor());
    mat2x4_type->constructors[0]->arguments.push_back(int_type);
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
    mat2x4_type->constructors.push_back(constructor0);
    mat2x4_type->constructors.push_back(constructor1);


    dmat2x4_type = new ASTType("dmat2x4");
    dmat2x4_type->members.push_back(double_type);
    dmat2x4_type->members.push_back(double_type);
    dmat2x4_type->members.push_back(double_type);
    dmat2x4_type->members.push_back(double_type);
    dmat2x4_type->members.push_back(double_type);
    dmat2x4_type->members.push_back(double_type);
    dmat2x4_type->members.push_back(double_type);
    dmat2x4_type->members.push_back(double_type);
    dmat2x4_type->castable_to_types.push_back(dmat2x4_type);
    dmat2x4_type->castable_to_types.push_back(mat2x4_type);
    dmat2x4_type->constructors.push_back(new ASTConstructor());
    dmat2x4_type->constructors[0]->arguments.push_back(int_type);
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
    dmat2x4_type->constructors.push_back(constructor0);
    dmat2x4_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(dmat2x4_type);
    parser->scope->addTypeDeclaration(mat2x4_type);
}

void addMatrix3x4TypesToScope(Parser* parser) {

    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    mat3x4_type = new ASTType("mat3x4");
    mat3x4_type->members.push_back(float_type);
    mat3x4_type->members.push_back(float_type);
    mat3x4_type->members.push_back(float_type);
    mat3x4_type->members.push_back(float_type);
    mat3x4_type->members.push_back(float_type);
    mat3x4_type->members.push_back(float_type);
    mat3x4_type->members.push_back(float_type);
    mat3x4_type->members.push_back(float_type);
    mat3x4_type->members.push_back(float_type);
    mat3x4_type->members.push_back(float_type);
    mat3x4_type->members.push_back(float_type);
    mat3x4_type->members.push_back(float_type);
    mat3x4_type->castable_to_types.push_back(mat3x4_type);
    mat3x4_type->castable_to_types.push_back(dmat3x4_type);
    mat3x4_type->constructors.push_back(new ASTConstructor());
    mat3x4_type->constructors[0]->arguments.push_back(int_type);
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
    mat3x4_type->constructors.push_back(constructor0);
    mat3x4_type->constructors.push_back(constructor1);


    dmat3x4_type = new ASTType("dmat3x4");
    dmat3x4_type->members.push_back(double_type);
    dmat3x4_type->members.push_back(double_type);
    dmat3x4_type->members.push_back(double_type);
    dmat3x4_type->members.push_back(double_type);
    dmat3x4_type->members.push_back(double_type);
    dmat3x4_type->members.push_back(double_type);
    dmat3x4_type->members.push_back(double_type);
    dmat3x4_type->members.push_back(double_type);
    dmat3x4_type->members.push_back(double_type);
    dmat3x4_type->members.push_back(double_type);
    dmat3x4_type->members.push_back(double_type);
    dmat3x4_type->members.push_back(double_type);
    dmat3x4_type->castable_to_types.push_back(dmat3x4_type);
    dmat3x4_type->castable_to_types.push_back(mat3x4_type);
    dmat3x4_type->constructors.push_back(new ASTConstructor());
    dmat3x4_type->constructors[0]->arguments.push_back(int_type);
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
    dmat3x4_type->constructors.push_back(constructor0);
    dmat3x4_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(dmat3x4_type);
    parser->scope->addTypeDeclaration(mat3x4_type);
}



void addMatrix4x3TypesToScope(Parser* parser) {

    ASTConstructor* constructor0;
    ASTConstructor* constructor1;

    mat4x3_type = new ASTType("mat4x3");
    mat4x3_type->members.push_back(float_type);
    mat4x3_type->members.push_back(float_type);
    mat4x3_type->members.push_back(float_type);
    mat4x3_type->members.push_back(float_type);
    mat4x3_type->members.push_back(float_type);
    mat4x3_type->members.push_back(float_type);
    mat4x3_type->members.push_back(float_type);
    mat4x3_type->members.push_back(float_type);
    mat4x3_type->members.push_back(float_type);
    mat4x3_type->members.push_back(float_type);
    mat4x3_type->members.push_back(float_type);
    mat4x3_type->members.push_back(float_type);
    mat4x3_type->castable_to_types.push_back(mat4x3_type);
    mat4x3_type->castable_to_types.push_back(dmat4x3_type);
    mat4x3_type->constructors.push_back(new ASTConstructor());
    mat4x3_type->constructors[0]->arguments.push_back(int_type);
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
    mat4x3_type->constructors.push_back(constructor0);
    mat4x3_type->constructors.push_back(constructor1);


    dmat4x3_type = new ASTType("dmat4x3");
    dmat4x3_type->members.push_back(double_type);
    dmat4x3_type->members.push_back(double_type);
    dmat4x3_type->members.push_back(double_type);
    dmat4x3_type->members.push_back(double_type);
    dmat4x3_type->members.push_back(double_type);
    dmat4x3_type->members.push_back(double_type);
    dmat4x3_type->members.push_back(double_type);
    dmat4x3_type->members.push_back(double_type);
    dmat4x3_type->members.push_back(double_type);
    dmat4x3_type->members.push_back(double_type);
    dmat4x3_type->members.push_back(double_type);
    dmat4x3_type->members.push_back(double_type);
    dmat4x3_type->castable_to_types.push_back(dmat4x3_type);
    dmat4x3_type->castable_to_types.push_back(mat4x3_type);
    dmat4x3_type->constructors.push_back(new ASTConstructor());
    dmat4x3_type->constructors[0]->arguments.push_back(int_type);
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
    dmat4x3_type->constructors.push_back(constructor0);
    dmat4x3_type->constructors.push_back(constructor1);

    parser->scope->addTypeDeclaration(dmat4x3_type);
    parser->scope->addTypeDeclaration(mat4x3_type);
}


void addBuiltInTypesToScope(Parser* parser) {
    addScalarsTypesToScope(parser);
    addVec2TypesToScope(parser);
    addVec3TypesToScope(parser);
    addVec4TypesToScope(parser);
    addMatrix2TypesToScope(parser);
    addMatrix3TypesToScope(parser);
    addMatrix4TypesToScope(parser);

    addMatrix2x2TypesToScope(parser);
    addMatrix2x3TypesToScope(parser);
    addMatrix2x4TypesToScope(parser);

    addMatrix3x2TypesToScope(parser);
    addMatrix3x3TypesToScope(parser);
    addMatrix3x4TypesToScope(parser);

    addMatrix4x2TypesToScope(parser);
    addMatrix4x3TypesToScope(parser);
    addMatrix4x4TypesToScope(parser);

    addSamplerTypes(parser);
}

}