#include "PackOffset.hpp"
#include <stdlib.h>
#include <stdio.h>

namespace HLSL {

PackOffset* parsePackOffset(Parser* parser) {
    PackOffset* offset = new PackOffset();
    parser->readToken(Token::TOKEN_PACKOFFSET);
    parser->readToken(Token::TOKEN_OPEN_PARENTESIS);


    if(parser->currentToken()->value[0] != 'c') {
        printf("Unknow Packing '%s' at line '%i'\n", parser->currentToken()->value, parser->currentToken()->line);
        exit(-1);
    }
    offset->pack_offset_sumcomponent = atoi(&parser->currentToken()->value[1]);
    parser->readToken(Token::TOKEN_IDENTIFIER);

    if(parser->currentToken()->type == Token::TOKEN_POINT) {
        parser->readToken(Token::TOKEN_POINT);
        switch (parser->currentToken()->value[0]) {
            case 'w':
                offset->pack_ofsset_component = 'w';
                parser->readToken(Token::TOKEN_IDENTIFIER);
                break;
            case 'x':
                offset->pack_ofsset_component = 'x';
                parser->readToken(Token::TOKEN_IDENTIFIER);
                break;
            case 'y':
                offset->pack_ofsset_component = 'y';
                parser->readToken(Token::TOKEN_IDENTIFIER);
                break;
            case 'z':
                offset->pack_ofsset_component = 'z';
                parser->readToken(Token::TOKEN_IDENTIFIER);
                break;
            default:
                printf("Unknow Component '%s' at line '%i'\n", parser->currentToken()->value, parser->currentToken()->line);
                exit(-1);
                break;
        }
    }
    parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
    return offset;
}

}
