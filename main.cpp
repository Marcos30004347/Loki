#include "src/Lexer.hpp"
#include "src/Parser.hpp"

#include <fstream>
#include <string>

int main(int argc, char *argv[]) {
    if(argc < 2) { printf("No code given!\n"); exit(-1); }

    printf("%s\n", argv[1]);

    std::ifstream ifs(argv[1]);
    if(!ifs.is_open()) { printf("File %s not found!\n", argv[1]); exit(-1); }
    std::string code = std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());

    Lexer* lexer = initLexer((char*)code.c_str());

    Parser* parser = initParser(lexer);
    AST* root = parseStart(parser);

    printAST(root);
    return 0;
}