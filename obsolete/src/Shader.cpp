#include "Utils.hpp"
#include "Shader.hpp"

#include <malloc.h>

Program* initProgram(Program::ProgramType type) {
    Program* program = (Program*)malloc(sizeof(Program));
    program->type = type;
    program->gles_attributes_count = 0;
    program->gles_inputs_count = 0;
    program->gles_outputs_count = 0;
    program->gles_funcs_defs_count = 0;
    program->gles_funcs_defs = nullptr;
    program->gles_attributes = nullptr;
    program->gles_inputs = nullptr;
    program->gles_outputs = nullptr;
    return program;
}

void addGLESFuncDeclToProgram(Program* program, char* func_dec) {
    program->gles_funcs_defs_count += 1;
    char** old = program->gles_funcs_defs;
    program->gles_funcs_defs = (char**)realloc(
        program->gles_funcs_defs,
        program->gles_funcs_defs_count * sizeof(char*)
    );

    free(old);

    program->gles_funcs_defs[program->gles_funcs_defs_count - 1] = copyString(func_dec);
}


void addGLESAttributeToProgram(Program* program, char* attribute) {
    program->gles_attributes_count += 1;
    char** old = program->gles_attributes;
    program->gles_attributes = (char**)realloc(
        program->gles_attributes,
        program->gles_attributes_count * sizeof(char*)
    );

    free(old);

    program->gles_attributes[program->gles_attributes_count - 1] = copyString(attribute);
}

void addGLESInputToProgram(Program* program, char* input) {
    program->gles_inputs_count += 1;
    char** old = program->gles_inputs;
    program->gles_inputs = (char**)realloc(
        program->gles_inputs,
        program->gles_inputs_count * sizeof(char*)
    );

    free(old);

    program->gles_inputs[program->gles_inputs_count - 1] = copyString(input);
}

void addGLESOutputToProgram(Program* program, char* output) {
    program->gles_outputs_count += 1;
    char** old = program->gles_outputs;
    program->gles_outputs = (char**)realloc(
        program->gles_outputs,
        program->gles_outputs_count * sizeof(char*)
    );

    free(old);

    program->gles_outputs[program->gles_outputs_count - 1] = copyString(output);
}

Shader* initShader(Shader::Type type, Program::ProgramType prog_type) {
    Shader* shader = (Shader*)malloc(sizeof(Shader));
    shader->shader_type = type;
    shader->program = initProgram(prog_type);
    return shader;
}


void addFuncDeclToShader(Shader* shader, char* func_dec) {
    switch(shader->program->type) {
        case Program::ProgramType::PROGRAM_GLES: return addGLESFuncDeclToProgram(shader->program, func_dec);
    }
}

void addAttributeToShader(Shader* shader, char* func_dec) {
    switch(shader->program->type) {
        case Program::ProgramType::PROGRAM_GLES: return addGLESAttributeToProgram(shader->program, func_dec);
    }
}

void addInputToShader(Shader* shader, char* func_dec) {
    switch(shader->program->type) {
        case Program::ProgramType::PROGRAM_GLES: return addGLESInputToProgram(shader->program, func_dec);
    }
}

void addOutputToShader(Shader* shader, char* func_dec) {
    switch(shader->program->type) {
        case Program::ProgramType::PROGRAM_GLES: return addGLESOutputToProgram(shader->program, func_dec);
    }
}
