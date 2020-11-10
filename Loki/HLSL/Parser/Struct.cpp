#include "Struct.hpp"
#include "Expressions.hpp"
#include "Lib/String.hpp"
#include <stdlib.h>
#include <stdio.h>
namespace HLSL {


ASTStruct::ASTStruct(): AST{NodeType::AST_STRUCT_DECLARATION} {}

// void ASTStruct::assertInitializationList(ASTLiteral* literal) {
//     if(!literal->is_initialization_list) {
//         printf("Error: Cant initialize struct of type %s because literal isnt an initialization list!\n", this->struct_identifier);
//         exit(-1);
//     }

//     if(literal->initialization_list_values.size() != this->struct_members.size()) {
//         printf("Error: Cant initialize struct of type %s because list dont initialize all memebers!\n", this->struct_identifier);
//         exit(-1);
//     }

//     for(int i=0; i<literal->initialization_list_values.size(); i++) {
//         if(!isLiteralCastableTo(literal->initialization_list_values[i]->value, this->struct_members[i]->struct_member_variable->var_decl_type->type)) {
//             printf(
//                 "Error: Cant initialize struct of type %s because list parameter %i of type %i inst castable to type %i!\n",
//                 this->struct_identifier,
//                 i,
//                 literal->initialization_list_values[i]->value->literal_type,
//                 this->struct_members[i]->struct_member_variable->var_decl_type->type
//             );
//             exit(-1);
//         }
//     }
// }

int last_struct = 0;

ASTStruct* parseStruct(Parser* parser) {
    ASTStruct* strct = new ASTStruct();

    ASTType* strct_type = new ASTType(std::to_string(last_struct++).c_str(), false);
    strct_type->type_struct = strct;

    parser->readToken(Token::TOKEN_STRUCT);


    if(!parser->currentToken()->type == Token::TOKEN_OPEN_CURLY_BRACKETS) {
    
        strct->struct_identifier = parser->currentToken()->value;
        strct_type->type_name = parser->currentToken()->value;
        parser->readToken(Token::TOKEN_IDENTIFIER);
    }

    parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);
    
    while(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
        StructMember* member = new StructMember();
        member->member_interpolation_modifier = parseInterpolationModifier(parser);
        member->struct_member_variable = parseVarDecl(parser);
        strct_type->members.push_back(member->struct_member_variable->var_decl_type);
        strct->struct_members.push_back(member);
    }

    parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);

    if(parser->currentToken()->type == Token::TOKEN_IDENTIFIER) {
        ASTVarDecl* decl = new ASTVarDecl();
        strct->struct_declarator = parser->currentToken()->value;
        decl->var_decl_type = strct_type;
    
        parser->readToken(Token::TOKEN_IDENTIFIER);

        if(parser->currentToken()->type == Token::TOKEN_EQUAL) {
            parser->readToken(Token::TOKEN_EQUAL);
            decl->var_decl_default_value = parseExpression(parser);
        }
    
        parser->readToken(Token::TOKEN_SEMICOLON);
        parser->scope->addVariableDefinition(decl);
    }

    // add Struct to current scope
    parser->scope->addTypeDeclaration(strct_type);
    parser->scope->addStructDefinition(strct);

    return strct;
}

}