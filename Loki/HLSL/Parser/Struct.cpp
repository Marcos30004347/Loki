#include "Struct.hpp"
#include <stdlib.h>
#include <stdio.h>
namespace HLSL {


ASTStruct::ASTStruct(): AST{NodeType::AST_STRUCT_DECLARATION} {}


ASTStruct* parseStruct(Parser* parser) {
    ASTStruct* strct = new ASTStruct();
    parser->readToken(Token::TOKEN_STRUCT);
    bool post_naming = false;
    if(parser->currentToken()->type == Token::TOKEN_OPEN_CURLY_BRACKETS) {
        post_naming = true;
    }

    if(!post_naming) {
        strct->struct_identifier = parser->currentToken()->value;
        parser->readToken(Token::TOKEN_IDENTIFIER);
    }

    parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);
    
    while(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
        StructMember* member = new StructMember();
        member->member_interpolation_modifier = parseInterpolationModifier(parser);
        member->struct_member_variable = parseVarDecl(parser);
        strct->struct_members.push_back(member);
    }

    parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);

    if(post_naming) {
        strct->struct_identifier = parser->currentToken()->value;
        parser->readToken(Token::TOKEN_IDENTIFIER);
        parser->readToken(Token::TOKEN_SEMICOLON);
    }

    return strct;
}

}