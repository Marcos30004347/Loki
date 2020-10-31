#include "Lexer.hpp"
#include "Parser.hpp"



// EXPRESSION → EQUALITY;
// EQUALITY → COMPARISON (('!=' | '==') COMPARISON)*;      ex: COMP;     COMP == COMP;     COMP == COMP != COMP == COMP;
// COMPARISON → TERM (('>' | '>=' | '<' | '<=') TERM)* ;
// TERM → FACTOR (('+' | '-') FACTOR)*;
// FACTOR → UNARY (('/' | '*') UNARY)*;
// UNARY → ('!' | '-')UNARY | PRIMARY
// PRIMARY → NUMBER | 'true' | 'false' | 'nil | '('EXPRESSION')';

int main() {
    const char* src0 = "3 + 4";
    const char* src1 = "(3 + 4) + 5";
    const char* src2 = "12 != (3 + 4) + 5";
    const char* src3 = "12 == (3 + 4) + 5";
    const char* src4 = "12 > (3 + 4) + 5";
    const char* src5 = "12 >= (3 + 4) + 5";
    const char* src6 = "12 < (3 - 4) + 5";
    const char* src7 = "12 <= (3 * 4) + 5";
    const char* src8 = "12 <= 4 - (3 + (4 + 3)) + 5";
    const char* src9 = "3 == 3 == 3 != 4";

    Lexer* lexer = initLexer((char*)src0);

    Parser* parser = initParser(lexer, initScope());

    AST* root = parseStart(parser);
    printAST(root);
    return 0;
}