#include "Register.hpp"
#include <stdlib.h>
#include <stdio.h>
namespace HLSL {
Register* parseRegister(Parser* parser) {    
    Register* reg = new Register();

    parser->readToken(Token::Type::TOKEN_REGISTER);
    parser->readToken(Token::Type::TOKEN_OPEN_PARENTESIS);
    reg->register_profile = parseProfile(parser);

    parser->readToken(Token::Type::TOKEN_COMMA);

    switch(parser->currentToken()->value[0]) {
        case 'b':
        reg->register_type = 'b';
        break;
        case 't':
        reg->register_type = 't';
        break;
        case 'c':
        reg->register_type = 'c';
        break;
        case 's':
        reg->register_type = 's';
        break;
        case 'u':
        reg->register_type = 'u';
        break;
        default:
        printf("Unknow register type '%s' at line '%u'!\n", parser->currentToken()->value, parser->currentToken()->line);
        exit(-1);
        break;
    }
    parser->readToken(Token::Type::TOKEN_IDENTIFIER);

    if(parser->currentToken()->type == Token::TOKEN_OPEN_SQUARE_BRACKETS) {
        reg->register_has_subcomponent = true;
        parser->readToken(Token::Type::TOKEN_OPEN_SQUARE_BRACKETS);
        reg->register_subcomponent = atoi(parser->currentToken()->value);
        parser->readToken(Token::Type::TOKEN_CLOSE_SQUARE_BRACKETS);
    } else {
        reg->register_has_subcomponent = false;
    }

    parser->readToken(Token::Type::TOKEN_CLOSE_PARENTESIS);

    return reg;
}
}