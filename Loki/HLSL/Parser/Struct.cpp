#include "Struct.hpp"
#include <stdlib.h>
#include <stdio.h>
namespace HLSL {


ASTStruct::ASTStruct(): AST{NodeType::AST_STRUCT_DECLARATION} {}

void ASTStruct::assertInitializationList(ASTLiteral* literal) {
    if(!literal->is_initialization_list) {
        printf("Error: Cant initialize struct of type %s because literal isnt an initialization list!\n", this->struct_identifier);
        exit(-1);
    }

    if(literal->initialization_list_values.size() != this->struct_members.size()) {
        printf("Error: Cant initialize struct of type %s because list dont initialize all memebers!\n", this->struct_identifier);
        exit(-1);
    }

    for(int i=0; i<literal->initialization_list_values.size(); i++) {
        if(!isLiteralCastableTo(literal->initialization_list_values[i]->value, this->struct_members[i]->struct_member_variable->var_decl_type->type)) {
            printf(
                "Error: Cant initialize struct of type %s because list parameter %i of type %i inst castable to type %i!\n",
                this->struct_identifier,
                i,
                literal->initialization_list_values[i]->value->literal_type,
                this->struct_members[i]->struct_member_variable->var_decl_type->type
            );
            exit(-1);
        }
    }
}

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
        strct->struct_declarator = parser->currentToken()->value;
        if(!strct->struct_identifier) {
            strct->struct_identifier = strct->struct_declarator;
        }
        parser->readToken(Token::TOKEN_IDENTIFIER);
        parser->readToken(Token::TOKEN_SEMICOLON);
    }

    // add Struct to current scope
    parser->scope->addStructDefinition(strct);

    return strct;
}

}