
// https://github.com/microsoft/DirectXShaderCompiler
// http://shader-playground.timjones.io/

#include "HLSL/Lexer/Lexer.hpp"
#include "HLSL/Parser/Parser.hpp"
#include "HLSL/Parser/Expressions.hpp"
#include "HLSL/Parser/Buffer.hpp"
#include "HLSL/Parser/Declarations.hpp"
#include "HLSL/Parser/Types.hpp"

// #include "GLSL/Lexer/Lexer.hpp"
// #include "GLSL/Parser/Parser.hpp"
// #include "GLSL/Parser/Expressions.hpp"
// #include "GLSL/Parser/Buffer.hpp"
// #include "GLSL/Parser/Variables.hpp"
// #include "GLSL/Parser/Types.hpp"


#include <fstream>
#include <string>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    // if(argc < 2) {
    //     printf("No source given!\n");
    //     exit(-1);
    // }

    // std::ifstream t(argv[1]);
    // std::string str((std::istreambuf_iterator<char>(t)),
    //                 std::istreambuf_iterator<char>());

    // GLSL::Lexer* lexer = new GLSL::Lexer(str.c_str());
    // for(int i=0; i<lexer->getTokensCount(); i++) {
    //     GLSL::Token* token = lexer->getToken(i);
    //     printf("'%s' ", token->value);
    // }
    // printf("\n");
    // GLSL::Parser* parser = new GLSL::Parser(lexer);


    // GLSL::AST* root = parser->parseProgram(GLSL::ProgramType::PROGRAM_VERTEX_SHADER, "main");
    // // root->print();


    if(argc < 2) {
        return 0;
    }

    std::ifstream tm(argv[1]);
    std::string strm((std::istreambuf_iterator<char>(tm)),
                    std::istreambuf_iterator<char>());

    HLSL::Lexer* lexerm = new HLSL::Lexer(strm.c_str());
    // for(int i=0; i<lexer->getTokensCount(); i++) {
    //     HLSL::Token* token = lexer->getToken(i);
    //     printf("'%s' ", token->value);
    // }
    // printf("\n");
    HLSL::Parser* parserm = new HLSL::Parser(lexerm);


    HLSL::AST* rootm = parserm->parseProgram(HLSL::ProgramType::PROGRAM_VERTEX_SHADER, "main");
    // root->print();
    rootm->write();

    return 0;

}


