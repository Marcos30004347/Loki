#include "AST.hpp"
#include "Types.hpp"
#include "Parser.hpp"

namespace GLSL {

static ASTTypeDecl* void_type = nullptr;
static ASTTypeDecl* bool_type = nullptr;
static ASTTypeDecl* int_type = nullptr;
static ASTTypeDecl* uint_type = nullptr;
static ASTTypeDecl* float_type = nullptr;
static ASTTypeDecl* double_type = nullptr;

// Vectors
static ASTTypeDecl* vec2_type = nullptr;
static ASTTypeDecl* dvec2_type = nullptr;
static ASTTypeDecl* bvec2_type = nullptr;
static ASTTypeDecl* ivec2_type = nullptr;
static ASTTypeDecl* uvec2_type = nullptr;

static ASTTypeDecl* vec3_type = nullptr;
static ASTTypeDecl* dvec3_type = nullptr;
static ASTTypeDecl* bvec3_type = nullptr;
static ASTTypeDecl* ivec3_type = nullptr;
static ASTTypeDecl* uvec3_type = nullptr;

static ASTTypeDecl* vec4_type = nullptr;
static ASTTypeDecl* dvec4_type = nullptr;
static ASTTypeDecl* bvec4_type = nullptr;
static ASTTypeDecl* ivec4_type = nullptr;
static ASTTypeDecl* uvec4_type = nullptr;

static ASTTypeDecl* mat2_type = nullptr;
static ASTTypeDecl* mat3_type = nullptr;
static ASTTypeDecl* mat4_type = nullptr;

static ASTTypeDecl* mat2x2_type = nullptr;
static ASTTypeDecl* mat2x3_type = nullptr;
static ASTTypeDecl* mat2x4_type = nullptr;

static ASTTypeDecl* mat3x2_type = nullptr;
static ASTTypeDecl* mat3x3_type = nullptr;
static ASTTypeDecl* mat3x4_type = nullptr;

static ASTTypeDecl* mat4x2_type = nullptr;
static ASTTypeDecl* mat4x3_type = nullptr;
static ASTTypeDecl* mat4x4_type = nullptr;

static ASTTypeDecl* dmat2_type = nullptr;
static ASTTypeDecl* dmat3_type = nullptr;
static ASTTypeDecl* dmat4_type = nullptr;

static ASTTypeDecl* dmat2x2_type = nullptr;
static ASTTypeDecl* dmat2x3_type = nullptr;
static ASTTypeDecl* dmat2x4_type = nullptr;

static ASTTypeDecl* dmat3x2_type = nullptr;
static ASTTypeDecl* dmat3x3_type = nullptr;
static ASTTypeDecl* dmat3x4_type = nullptr;

static ASTTypeDecl* dmat4x2_type = nullptr;
static ASTTypeDecl* dmat4x3_type = nullptr;
static ASTTypeDecl* dmat4x4_type = nullptr;

static ASTTypeDecl* sampler_type = nullptr;


void addBuiltInTypesToScope(Parser* parser);
}