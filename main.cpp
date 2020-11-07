// https://github.com/microsoft/DirectXShaderCompiler
// http://shader-playground.timjones.io/

#include "Loki/HLSL/Lexer/Lexer.hpp"
#include "Loki/HLSL/Parser/Parser.hpp"
#include "Loki/HLSL/Parser/Expressions.hpp"
#include "Loki/HLSL/Parser/Buffer.hpp"
#include "Loki/HLSL/Parser/Variables.hpp"


#include <fstream>
#include <string>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    if(argc < 2) printf("No source given!");

    std::ifstream t(argv[1]);
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());

    HLSL::Lexer* lexer = new HLSL::Lexer(str.c_str());
    for(int i=0; i<lexer->getTokensCount(); i++) {
        HLSL::Token* token = lexer->getToken(i);
        printf("'%s' ", token->value);
    }
    printf("\n");

    HLSL::Parser* parser = new HLSL::Parser(lexer);
    HLSL::AST* root = parser->parseProgram(HLSL::ProgramType::PROGRAM_VERTEX_SHADER, "main");
    root->print();

    return 0;
}