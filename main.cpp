#include "Loki/HLSL/Lexer/Lexer.hpp"
#include "Loki/HLSL/Parser/Parser.hpp"
#include "Loki/HLSL/Parser/Expressions.hpp"
#include "Loki/HLSL/Parser/ShaderConstants.hpp"

#include <fstream>
#include <string>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    HLSL::Lexer* lexer = new HLSL::Lexer("(3 | +4) + 5");

    for(int i=0; i<lexer->getTokensCount(); i++) {
        HLSL::Token* token = lexer->getToken(i);
        printf("%s\n", token->value);
    }

    HLSL::Parser* parser = new HLSL::Parser(lexer);
    HLSL::AST* ast = HLSL::parseExpression(parser);

    printf("AST:\n");
    printf("%i\n", ast->ast_type);
    HLSL::ASTBinaryExpression* exp = static_cast<HLSL::ASTBinaryExpression*>(ast);
    printf("%i\n", exp->bin_exp_left_operand->ast_type);
    printf("%i\n", exp->bin_exp_op);
    printf("%i\n", exp->bin_exp_right_operand->ast_type);
    return 0;
}