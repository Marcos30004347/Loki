#ifndef GLES_TRANSLATOR
#define GLES_TRANSLATOR

#include "AST/AST.hpp"

enum ShaderType {
    VERTEX_SHADER,
    FRAGMENT_SHADER,
};

struct Shader {
    char** attributes;
    unsigned int attributes_count;
    char** uniforms;
    unsigned int uniforms_count;
    char** functions;
    unsigned int functions_count;
    ShaderType shader_type;
};


Shader* initShader(ShaderType type);
char* translateDeclarations(Shader* shader, AST* root);
char* translateFunctionDeclaration(Shader* shader, AST* root);
char* translateVariableDeclarations(Shader* shader, AST* root);
char* translateVariableDeclaration(Shader* shader, AST* root);
char* translateBlock(Shader* shader, AST* root);
char* translateFunctionArgument(Shader* shader, AST* root);
char* translateIdentifier(Shader* shader, AST* root);
char* translateExpression(Shader* shader, AST* root);
char* translateIf(Shader* shader, AST* root);
char* translateFor(Shader* shader, AST* root);
char* translateDoWhile(Shader* shader, AST* root);
char* translateWhile(Shader* shader, AST* root);
char* translateSwitch(Shader* shader, AST* root);
char* translateBreak(Shader* shader, AST* root);
char* translateInteger(Shader* shader, AST* root);
char* translateFloat(Shader* shader, AST* root);
char* translateStatement(Shader* shader, AST* root);
char* translateAssignment(Shader* shader, AST* root);
#endif
