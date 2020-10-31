#include "Lexer.hpp"
#include "Parser.hpp"



// EXPRESSION → EQUALITY;                                           ex: EQ
// EQUALITY → COMPARISON (('!=' | '==') COMPARISON)*;               ex: COMP;     COMP == COMP;      COMP == COMP != COMP == COMP;
// COMPARISON → TERM (('>' | '>=' | '<' | '<=') TERM)*;             ex: TERM;     TERN > TERM;       TERM >= TERM <= TERM;
// TERM → FACTOR (('+' | '-') FACTOR)*;                             ex: FAC;      FAC+FAC+FAC;       FAC-FAC+FAC;
// FACTOR → UNARY (('/' | '*') UNARY)*;                             ex: UN;       UN/UN*UN;          UN*UN*UN;
// UNARY → ('!' | '-')UNARY | PRIMARY                               ex: !PRIM;    !!!PRIM;           -PRIM;
// PRIMARY → NUMBER | 'true' | 'false' | 'nil | '('EXPRESSION')';   ex: NUM;      (EXP);

int main() {
    const char* src0 = "3 + 4;";
    const char* src1 = "(3 + 4) + 5;";
    const char* src2 = "12 != (3 + 4) + 5;";
    const char* src3 = "12 == (3 + 4) + 5;";
    const char* src4 = "12 > (3 + 4) + 5;";
    const char* src5 = "12 >= (3 + 4) + 5;";
    const char* src6 = "12 < (3 - 4) + 5;";
    const char* src7 = "12 <= (3 * 4) + 5;";
    const char* src8 = "12 <= 4 - (3 + (4 + 3)) + 5;";
    const char* src9 = "3 == 3 == 3 != 4;";

    const char* src10 = "int teste = 4, teste2, teste3 = 6;";
    
    const char* src11 = "int teste = 4;"
                        "3 = 4;"
                        "teste = 4;";
    
    Lexer* lexer = initLexer((char*)src11);
    Parser* parser = initParser(lexer, initScope());
    AST* root = parseStart(parser);

    printAST(root);
    return 0;
}