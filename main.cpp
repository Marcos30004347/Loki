#include "Loki/HLSL/Lexer/Lexer.hpp"
#include "Loki/HLSL/Parser/Parser.hpp"
#include "Loki/HLSL/Parser/Variables.hpp"

#include <fstream>
#include <string>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    HLSL::Lexer* lexer = new HLSL::Lexer("float4x4 variable : SV_POSITION = {float(1),2,3,4,1,2,3,4,1,2,float(3),4,1,2,3,4};");

    // for(int i=0; i<lexer->getTokensCount(); i++) {
    //     HLSL::Token* token = lexer->getToken(i);
    //     printf("%i\n", token->type);
    //     printf("%s\n", token->value);
    // }

    HLSL::Parser* parser = new HLSL::Parser(lexer);
    HLSL::ASTVarDecl* var_decl = parseVarDecl(parser);

    printf("%i\n", var_decl->var_decl_storage_class);
    printf("%s\n", var_decl->var_decl_type->name);
    printf("%s\n", var_decl->var_decl_name);
    printf("%f\n", var_decl->var_decl_default_value[0]->float4x4_value[0]);
    printf("%f\n", var_decl->var_decl_default_value[0]->float4x4_value[1]);
    printf("%f\n", var_decl->var_decl_default_value[0]->float4x4_value[3]);
    printf("%f\n", var_decl->var_decl_default_value[0]->float4x4_value[4]);
    printf("%f\n", var_decl->var_decl_default_value[0]->float4x4_value[5]);

    return 0;
}