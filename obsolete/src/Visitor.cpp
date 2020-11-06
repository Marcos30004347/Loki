#include "Visitor.hpp"
#include "Utils.hpp"
#include "Writter.hpp"

#include <string.h>
#include <malloc.h>
#include <assert.h>

Visitor* initVisitor() {
    Visitor* visitor = (Visitor*)malloc(sizeof(Visitor));
    visitor->global_scope = initScope(nullptr);
    visitor->current_scope = visitor->global_scope;
    visitor->gles_fragment_shader = initShader(Shader::Type::SHADER_FRAGMENT_SHADER, Program::ProgramType::PROGRAM_GLES);
    visitor->gles_vertex_shader = initShader(Shader::Type::SHADER_VERTERX_SHADER, Program::ProgramType::PROGRAM_GLES);
    return visitor;
}

void visitDeclarations(Visitor* visitor, AST* node) {
    if(node->ast_type == AST::ASTType::DECLARATIONS) {
        for(int i=0; i<node->declarations_list_count; i++) {
            switch(node->declarations_list[i]->ast_type) {
                case AST::ASTType::FUNCTION_DECLARATION:
                        addFunctionToScope(visitor->current_scope, node->declarations_list[i]);
                        visitFunctionDeclaration(visitor, node->declarations_list[i]);
                    break;
                case AST::ASTType::VARIABLES_DECLARATIONS:
                    for(int i=0; i< node->vars_declarations_count; i++) {
                        addVariableToScope(visitor->current_scope, node->vars_declarations[i]);
                        visitVariableDeclaration(visitor, node->vars_declarations[i]);
                    }
                    break;
            }
        }
    }
}

void visitFunctionDeclaration(Visitor* visitor, AST* node) {
    assert(node->ast_type == AST::ASTType::FUNCTION_DECLARATION);

    char* function_return = getGLSLTypeString(node->func_dec_return_type_identifier->type_type);
    char* function_name = getIdentifierString(node->func_dec_identifier);
    // GLES
    char* gles_function_return = function_return;
    char* gles_function_name = function_name;
    char** gles_function_arguments = nullptr;

    char** gles_global_attributes = nullptr;
    char** gles_global_inputs = nullptr;
    char** gles_global_outputs = nullptr;

    unsigned int gles_function_arguments_count = 0;
    unsigned int gles_global_attributes_count = 0;
    unsigned int gles_global_inputs_count = 0;
    unsigned int gles_global_outputs_count = 0;

    for(int i=0; i<node->func_dec_arguments_count; i++) {
        char* gles_argument_str = writeGLSLFunctionArgument(
            getGLSLTypeString(node->func_dec_arguments[i]->func_argument_type_identifier->type_type),
            getIdentifierString(node->func_dec_arguments[i]->func_argument_id)
        );

        gles_function_arguments_count += 1;
        gles_function_arguments = (char**)realloc(gles_function_arguments, gles_function_arguments_count * sizeof(char*));
        gles_function_arguments[gles_function_arguments_count - 1] = gles_argument_str;
    }

    char* gles_func = nullptr;
    gles_func = append(gles_func, gles_function_return);
    gles_func = append(gles_func, " ");
    gles_func = append(gles_func, gles_function_name);
    gles_func = append(gles_func, "(");
    for(int i=0; i<gles_function_arguments_count; i++) {
        gles_func = append(gles_func, gles_function_arguments[i]);
        if(i < gles_function_arguments_count - 1)  gles_func = append(gles_func, ",");
    }
    gles_func = append(gles_func, ")");
    gles_func = append(gles_func, " {\n");
    // Todo translate body
    //node->func_dec_body;
    gles_func = append(gles_func, "}");

    addFuncDeclToShader(visitor->gles_vertex_shader, gles_func);
    addFuncDeclToShader(visitor->gles_fragment_shader, gles_func);
}

void visitVariableDeclaration(Visitor* visitor, AST* node) {
    printf("ERROR: Variables are not being translated yet");
    exit(-1);
}
