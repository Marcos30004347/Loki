#include "Lexer.hpp"
#include "Parser.hpp"

int main() {
    const char* src = "3 + 4";

    Lexer* lexer = initLexer((char*)src);

    Parser* parser = initParser(lexer, initScope());

    AST* root = parseStart(parser);
    printAST(root);
    return 0;
}