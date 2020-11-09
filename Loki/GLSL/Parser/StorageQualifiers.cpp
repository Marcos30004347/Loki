#include "StorageQualifiers.hpp"

namespace GLSL {

ASTStorageQualifiers::ASTStorageQualifiers():AST{AST_STORAGE_QUALIFIER} {
    type = StorageQualifiers::STORAGE_QUALIFIER_NONE;
}

ASTStorageQualifiers* parseStorageQualifier(Parser* parser) {
    ASTStorageQualifiers* sq = new ASTStorageQualifiers();
    switch (parser->currentToken()->type) {
    case Token::TOKEN_CONST:
        parser->readToken(Token::TOKEN_CONST);
        sq->type = StorageQualifiers::STORAGE_QUALIFIER_CONST;
        break;

    case Token::TOKEN_IN:
        parser->readToken(Token::TOKEN_IN);
        sq->type = StorageQualifiers::STORAGE_QUALIFIER_IN;
        break;

    case Token::TOKEN_OUT:
        parser->readToken(Token::TOKEN_OUT);
        sq->type = StorageQualifiers::STORAGE_QUALIFIER_OUT;
        break;
    
    case Token::TOKEN_ATTRIBUTE:
        parser->readToken(Token::TOKEN_ATTRIBUTE);
        sq->type = StorageQualifiers::STORAGE_QUALIFIER_ATTRIBUTE;
        break;
    
    case Token::TOKEN_UNIFORM:
        parser->readToken(Token::TOKEN_UNIFORM);
        sq->type = StorageQualifiers::STORAGE_QUALIFIER_UNIFORM;
        break;

    case Token::TOKEN_VARYING:  
        parser->readToken(Token::TOKEN_VARYING);
        sq->type = StorageQualifiers::STORAGE_QUALIFIER_VARYING;
        break;

    case Token::TOKEN_BUFFER:
        parser->readToken(Token::TOKEN_BUFFER);
        sq->type = StorageQualifiers::STORAGE_QUALIFIER_BUFFER;
        break;

    case Token::TOKEN_SHARED:
        parser->readToken(Token::TOKEN_SHARED);
        sq->type = StorageQualifiers::STORAGE_QUALIFIER_SHARED;
        break;

    case Token::TOKEN_COHERENT:
        parser->readToken(Token::TOKEN_COHERENT);
        sq->type = StorageQualifiers::STORAGE_QUALIFIER_COHERENT;
        break;
    
    case Token::TOKEN_VOLATILE:
        parser->readToken(Token::TOKEN_VOLATILE);
        sq->type = StorageQualifiers::STORAGE_QUALIFIER_VOLATILE;
        break;
    
   case Token::TOKEN_RESTRICT:
        parser->readToken(Token::TOKEN_RESTRICT);
        sq->type = StorageQualifiers::STORAGE_QUALIFIER_RESTRICT;
        break;
   case Token::TOKEN_READONLY:
        parser->readToken(Token::TOKEN_READONLY);
        sq->type = StorageQualifiers::STORAGE_QUALIFIER_READONLY;
        break;

   case Token::TOKEN_WRITEONLY:
        parser->readToken(Token::TOKEN_WRITEONLY);
        sq->type = StorageQualifiers::STORAGE_QUALIFIER_WRITEONLY;
        break;


   case Token::TOKEN_PATCH:
        parser->readToken(Token::TOKEN_PATCH);
        if(parser->currentToken()->type == Token::TOKEN_IN) {
            parser->readToken(Token::TOKEN_IN);
            sq->type = StorageQualifiers::STORAGE_QUALIFIER_PATH_IN;
        } else if(parser->currentToken()->type == Token::TOKEN_IN){
            parser->readToken(Token::TOKEN_OUT);
            sq->type = StorageQualifiers::STORAGE_QUALIFIER_PATCH_OUT;
        } else {
            sq->type = StorageQualifiers::STORAGE_QUALIFIER_PATCH;
        }
        break;

    case Token::TOKEN_SUBROUTINE:
        parser->readToken(Token::TOKEN_SUBROUTINE);
        sq->type = StorageQualifiers::STORAGE_QUALIFIER_SUBROUTINE;
        if (parser->currentToken()->type == Token::TOKEN_OPEN_PARENTESIS) {
            parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
                while(parser->currentToken()->type != Token::TOKEN_CLOSE_PARENTESIS) {
                    sq->type_name_list.push_back(parseDeclarationBaseType(parser));
                }
            parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
        }
        break;
    }

    return sq;
}

}