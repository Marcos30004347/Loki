#include "Lib/String.hpp"
#include "Semantics.hpp"

#include <stdio.h>

namespace HLSL {

Semantic* parseSemantic(Parser* parser) {
    if(parser->currentToken()->type != Token::TOKEN_IDENTIFIER) {
        printf("Invalid semantic %s at line %i\n", parser->currentToken()->value, parser->currentToken()->line);
        exit(-1);
    }
    Semantic* semantic = new Semantic();
    semantic->name = copyStr(parser->currentToken()->value);
    parser->readToken(Token::TOKEN_IDENTIFIER);
    return semantic;
}

}

