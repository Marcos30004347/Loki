#include "Register.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <cctype>
#include <string.h>

namespace HLSL {
Register* parseRegister(Parser* parser) {    
    Register* reg = new Register();

    parser->readToken(Token::Type::TOKEN_REGISTER);
    parser->readToken(Token::Type::TOKEN_OPEN_PARENTESIS);

    reg->register_profile = parseProfile(parser);
    if(reg->register_profile != Profile::PROFILE_NONE) {
        parser->readToken(Token::Type::TOKEN_COMMA);
    }

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

    if(isdigit(parser->currentToken()->value[1])) {
        int i = 2;
        char* value = (char*)calloc(1, sizeof(char));
        value[0] = parser->currentToken()->value[1];

        while(i < strlen(parser->currentToken()->value) - 1 && isdigit(parser->currentToken()->value[i])) {
            value = (char*)realloc(value, (strlen(value) + 1)*sizeof(char));
            value[strlen(value)] = parser->currentToken()->value[i];
            i++;
        }
        reg->register_number = atoi(value);
        delete value;
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