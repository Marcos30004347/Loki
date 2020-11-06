#include "Loki/HLSL/Lexer/Lexer.hpp"
#include "Loki/HLSL/Parser/Parser.hpp"
#include "Loki/HLSL/Parser/Buffer.hpp"

#include <fstream>
#include <string>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    HLSL::Lexer* lexer = new HLSL::Lexer(
        "cbuffer MyBuffer : register(b3)"
        "{"
        "float4 Element1 : packoffset(c0);"
        "float1 Element2 : packoffset(c1);"
        "float1 Element3 : packoffset(c1.y);"
        "};"
    );

    // for(int i=0; i<lexer->getTokensCount(); i++) {
    //     HLSL::Token* token = lexer->getToken(i);
    //     printf("%i\n", token->type);
    //     printf("%s\n", token->value);
    // }

    HLSL::Parser* parser = new HLSL::Parser(lexer);
    HLSL::ASTBuffer* buffer = HLSL::parseBuffer(parser);

    return 0;
}