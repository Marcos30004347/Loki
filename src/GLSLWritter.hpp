#ifndef GLSL_WRITTER
#define GLSL_WRITTER

#include "Types.hpp"

char* writeGLSLAttribute(char* type, char* location, char* id);
char* writeGLSLFunctionArgument(char* type, char* id);
char* writeGLSLInput(char* type, char* id);
char* writeGLSLOutput(char* type, char* id);
char* writeGLSLVariableDeclaration(char* type, char* id, char* value);
char* getGLSLTypeString(BuildInType type);

#endif