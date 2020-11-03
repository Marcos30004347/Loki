#include "src/Lexer.hpp"
#include "src/Parser.hpp"
#include "src/Visitor.hpp"

#include <fstream>
#include <string>


int main(int argc, char *argv[]) {
    if(argc < 2) { printf("No code given!\n"); exit(-1); }

    std::ifstream ifs(argv[1]);
    if(!ifs.is_open()) { printf("File %s not found!\n", argv[1]); exit(-1); }
    std::string code = std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());

    Lexer* lexer = initLexer((char*)code.c_str());

    Parser* parser = initParser(lexer);
    AST* root = parseStart(parser);

    Visitor* visitor = initVisitor();

    printAST(root);

    visitDeclarations(visitor, root);

    for(int i=0; i<visitor->gles_vertex_shader->program->gles_funcs_defs_count; i++) {
        printf("%s\n", visitor->gles_vertex_shader->program->gles_funcs_defs[i]);
    }
    for(int i=0; i<visitor->gles_vertex_shader->program->gles_attributes_count; i++) {
        printf("%s\n", visitor->gles_vertex_shader->program->gles_attributes[i]);
    }
    for(int i=0; i<visitor->gles_vertex_shader->program->gles_inputs_count; i++) {
        printf("%s\n", visitor->gles_vertex_shader->program->gles_inputs[i]);
    }
    for(int i=0; i<visitor->gles_vertex_shader->program->gles_outputs_count; i++) {
        printf("%s\n", visitor->gles_vertex_shader->program->gles_outputs[i]);
    }
    return 0;
}