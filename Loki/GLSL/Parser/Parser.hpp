#ifndef PARSER_H
#define PARSER_H

#include "../Lexer/Lexer.hpp"
#include "AST.hpp"
#include "Scope.hpp"

namespace GLSL {

enum ProgramType {
    PROGRAM_MESH_SHADER,
    PROGRAM_VERTEX_SHADER,
    PROGRAM_GEOMETRY_SHADER,
    PROGRAM_TESSELATION_SHADER,
    PROGRAM_COMPUTE_SHADER,
    PROGRAM_PIXEL_SHADER,
};

struct ASTProgram: AST {
    explicit ASTProgram();
    ProgramType program_type;
    std::vector<AST*> program_declarations;
    char* program_main;
};

class Parser {
private:
    Lexer* lexer;
    unsigned int current_token_index;
public:
    Scope* scope;
    Parser(Lexer* lexer);

    void readToken(Token::Type tokenType);
    void readNumeric();
    bool isNumeric();

    Token* currentToken();
    Token* previousToken();
    Token* getToken(unsigned int index);
    void setTokenIndex(unsigned int index);
    unsigned int getTokenIndex();
    ASTProgram* parseProgram(ProgramType type, const char* prorgamMain);
};

}

#endif
