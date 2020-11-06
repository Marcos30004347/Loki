#ifndef SHADER
#define SHADER



struct Program {
    enum ProgramType {
        PROGRAM_GLES,
    };
    
    ProgramType type;

    // GLES
    char** gles_funcs_defs;
    unsigned int gles_funcs_defs_count;

    char** gles_attributes;
    unsigned int gles_attributes_count;

    char** gles_inputs;
    unsigned int gles_inputs_count;

    char** gles_outputs;
    unsigned int gles_outputs_count;
};



Program* initProgram(Program::ProgramType type);
void addFuncDeclToProgram(Program* program, const char* func_dec);

struct Shader {
    enum Type {
        SHADER_VERTERX_SHADER,
        SHADER_FRAGMENT_SHADER,
    };
    // Shader
    Type shader_type;
    Program* program;
};

Shader* initShader(Shader::Type type, Program::ProgramType prog_type);

void addGLESFuncDeclToProgram(Program* program, char* func_dec);
void addGLESAttributeToProgram(Program* program, char* attribute);
void addGLESInputToProgram(Program* program, char* input);
void addGLESOutputToProgram(Program* program, char* output);


void addFuncDeclToShader(Shader* shader, char* func_dec);
void addAttributeToShader(Shader* shader, char* func_dec);
void addInputToShader(Shader* shader, char* func_dec);
void addOutputToShader(Shader* shader, char* func_dec);

#endif