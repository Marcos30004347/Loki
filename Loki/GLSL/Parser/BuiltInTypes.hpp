#include "AST.hpp"
#include "Types.hpp"
#include "Parser.hpp"

namespace GLSL {

static ASTType* void_type = nullptr;
static ASTType* bool_type = nullptr;
static ASTType* int_type = nullptr;
static ASTType* uint_type = nullptr;
static ASTType* float_type = nullptr;
static ASTType* double_type = nullptr;

// Vectors
static ASTType* vec2_type = nullptr;
static ASTType* dvec2_type = nullptr;
static ASTType* bvec2_type = nullptr;
static ASTType* ivec2_type = nullptr;
static ASTType* uvec2_type = nullptr;

static ASTType* vec3_type = nullptr;
static ASTType* dvec3_type = nullptr;
static ASTType* bvec3_type = nullptr;
static ASTType* ivec3_type = nullptr;
static ASTType* uvec3_type = nullptr;

static ASTType* vec4_type = nullptr;
static ASTType* dvec4_type = nullptr;
static ASTType* bvec4_type = nullptr;
static ASTType* ivec4_type = nullptr;
static ASTType* uvec4_type = nullptr;

static ASTType* mat2_type = nullptr;
static ASTType* mat3_type = nullptr;
static ASTType* mat4_type = nullptr;

static ASTType* mat2x2_type = nullptr;
static ASTType* mat2x3_type = nullptr;
static ASTType* mat2x4_type = nullptr;

static ASTType* mat3x2_type = nullptr;
static ASTType* mat3x3_type = nullptr;
static ASTType* mat3x4_type = nullptr;

static ASTType* mat4x2_type = nullptr;
static ASTType* mat4x3_type = nullptr;
static ASTType* mat4x4_type = nullptr;

static ASTType* dmat2_type = nullptr;
static ASTType* dmat3_type = nullptr;
static ASTType* dmat4_type = nullptr;

static ASTType* dmat2x2_type = nullptr;
static ASTType* dmat2x3_type = nullptr;
static ASTType* dmat2x4_type = nullptr;

static ASTType* dmat3x2_type = nullptr;
static ASTType* dmat3x3_type = nullptr;
static ASTType* dmat3x4_type = nullptr;

static ASTType* dmat4x2_type = nullptr;
static ASTType* dmat4x3_type = nullptr;
static ASTType* dmat4x4_type = nullptr;

static ASTType* sampler_type = nullptr;


void addBuiltInTypesToScope(Parser* parser);
}