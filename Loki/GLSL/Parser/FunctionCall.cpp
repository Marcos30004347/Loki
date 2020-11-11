#include "Lib/String.hpp"
#include "FunctionCall.hpp"
#include "Expressions.hpp"
#include "Declarations.hpp"
#include <stdio.h>

namespace GLSL {
// CALL → PRIMARY('('ARGUMENTS?')')?
AST* parseCall(Parser* parser, bool constant) {
    AST* root = parsePostfixSuffixUnary(parser, constant);


    if(parser->currentToken() && parser->currentToken()->type == Token::TOKEN_OPEN_PARENTESIS) {
        if(root->ast_type != NodeType::AST_SYMBOL) {
            printf("Unexpected function name at line %i\n", parser->currentToken()->line);
        }

        ASTFunctionCall* func_call = new ASTFunctionCall();
        func_call->func_call_symbol = root;
        func_call->constexp = constant;
    
        parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
        if(parser->currentToken() && parser->currentToken()->type != Token::TOKEN_CLOSE_PARENTESIS) {
            func_call->func_call_arguments.push_back(parseExpression(parser, constant));
            while(parser->currentToken() && parser->currentToken()->type == Token::TOKEN_COMMA) {
                parser->readToken(Token::TOKEN_COMMA);
                func_call->func_call_arguments.push_back(parseExpression(parser, constant));
            }
        }
        parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);

        // ASTFunctionDeclaration* decl = static_cast<ASTFunctionDeclaration*>(parser->scope->getFunctionDefinition(static_cast<ASTSymbol*>(root)->symbol_name));
        // // Verify if var is constant
        // if(!decl) {
        //     printf("Undefined function '%s' at line '%i'!\n", static_cast<ASTSymbol*>(root)->symbol_name, parser->currentToken()->line);
        //     exit(-1);
        // }

        if(constant) {
            printf("Cant use function '%s' for constant expresiion at line '%i'!\n", static_cast<ASTSymbol*>(root)->symbol_name, parser->currentToken()->line);
            exit(-1);
        }

        root = func_call;
    }

    return root;
}

}