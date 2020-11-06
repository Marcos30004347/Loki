#include "Writter.hpp"
#include "Utils.hpp"

char* writeGLSLAttribute(char* type, char* location, char* id) {
    char* attribute = nullptr;

    attribute = append(attribute, "attribute ");
    attribute = append(attribute, type);
    attribute = append(attribute, " ");
    if(location) {
        attribute = append(attribute, "(location=");
        attribute = append(attribute, location);
        attribute = append(attribute, ") ");
    }
    attribute = append(attribute, id);
    attribute = append(attribute, ";");

    return attribute;
}

char* writeGLSLFunctionArgument(char* type, char* id) {
    char* argument = nullptr;

    argument = append(argument, type);
    argument = append(argument, " ");
    argument = append(argument, id);

    return argument;
}

char* writeGLSLVariableDeclaration(char* type, char* id, char* value) {
    char* argument = nullptr;

    argument = append(argument, type);
    argument = append(argument, " ");
    argument = append(argument, id);
    if(value) {
        argument = append(argument, " = ");
        argument = append(argument, value);
    }
    argument = append(argument, ";");

    return argument;
}

char* writeGLSLInput(char* type, char* id) {
    char* argument = nullptr;

    argument = append(argument, "in ");
    argument = append(argument, type);
    argument = append(argument, " ");
    argument = append(argument, id);
    argument = append(argument, ";");

    return argument;
}
char* writeGLSLOutput(char* type, char* id) {
    char* argument = nullptr;

    argument = append(argument, "out ");
    argument = append(argument, type);
    argument = append(argument, " ");
    argument = append(argument, id);
    argument = append(argument, ";");

    return argument;
}

char* getGLSLTypeString(Type type) {
    const char* TypesNames[] = {
        "void",
        "struct",
        "int",
        "uint",
        "float",
        "bool",
        "vec2",
        "vec3",
        "vec4",
        "mat2",
        "mat2x2",
        "mat2x3",
        "mat2x4",
        "mat3",
        "mat3x2",
        "mat3x3",
        "mat3x4",
        "mat4",
        "mat4x2",
        "mat4x3",
        "mat4x4",
        "sampler",
        "sampler3d"
    };

    return copyString(TypesNames[type]);
}