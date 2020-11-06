#include "Struct.hpp"
#include <stdlib.h>
#include <stdio.h>
namespace HLSL {


ASTStruct::ASTStruct(): AST{NodeType::NODE_TYPE_STRUCT_DECLARATION} {}


ASTStruct* parseStruct(Parser* parser) {
    ASTStruct* strct = new ASTStruct();
    parser->readToken(Token::TOKEN_STRUCT);
    strct->struct_identifier = parser->currentToken()->value;
    parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);
    
    while(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
        StructMember* member = new StructMember();
        member->member_interpolation_modifier = parseInterpolationModifier(parser);
        member->member_base_type = parseDeclarationBaseType(parser);
        member->member_name = parser->currentToken()->value;
        parser->readToken(Token::TOKEN_IDENTIFIER);
        strct->struct_members.push_back(member);
    }

    parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);


}

}