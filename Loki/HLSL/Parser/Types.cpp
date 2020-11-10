#include "Types.hpp"
#include "Expressions.hpp"
#include "Functions.hpp"
#include "Lib/String.hpp"

#include <stdio.h>
#include <stdlib.h>

namespace HLSL {

const char* literal_names[] = {
    "int",
    "float",
    "string",
    "bool"
};

ASTType::ASTType(const char* id, bool builtIn): AST{AST_TYPE_DECL}, type_name{copyStr(id)}, build_in{builtIn} {}
ASTType::ASTType(char* id, bool builtIn): AST{AST_TYPE_DECL}, type_name{id}, build_in{builtIn} {}
ASTLiteral::ASTLiteral(): AST{AST_LITERAL} {}
ASTConstructor::ASTConstructor(): AST{AST_TYPE_CONSTRUCTOR} {}

bool ASTType::isCastableToLiteral(ASTLiteral* type) {
    for(int i=0; i<this->castable_to_literals.size(); i++) {
        if(type->type == this->castable_to_literals[i]) return true;
    }
    return false;
}

bool ASTType::acceptLiteral(ASTLiteral* t, Parser* parser) {
    for(int i=0; i<this->accept_literals.size(); i++) {
        if(this->accept_literals[i] == t->type || this->isCastableToLiteral(t)) return true;
    }



    return false;
}

bool ASTType::acceptSymbol(AST* symbol, Parser* parser) {
    AST* decl = parser->scope->getVariableDefinition(
        static_cast<ASTSymbol*>(symbol)->symbol_name
    );

    ASTVarDecl* var_decl = static_cast<ASTVarDecl*>(decl);

    return var_decl->var_decl_type == this || this->isCastableTo(var_decl->var_decl_type);
}

bool ASTType::acceptFunction(AST* func, Parser* parser) {
    ASTSymbol* symbol = static_cast<ASTSymbol*>(static_cast<ASTFunctionCall*>(func)->func_call_symbol);

    if(strcmp(symbol->symbol_name, this->type_name) == 0) {
        return this->acceptConstructor(func, parser);
    }

    AST* tmp = parser->scope->getFunctionDefinition(symbol->symbol_name);
    ASTFunctionDeclaration* call = static_cast<ASTFunctionDeclaration*>(tmp);
    return this->isCastableTo(static_cast<ASTType*>(call->return_type));
}


bool ASTType::isCastableTo(ASTType* type) {
    if(type->members.size() != this->members.size()) {
        return false;
    }

    if(type->members.size()) {
        for(int i=0; i<this->members.size(); i++) {
            if(!this->members[i]->isCastableTo(static_cast<ASTType*>(type->members[i]))) {
                return false;
            }
        }
        return true;            
    }

    for(int i=0; i<this->castable_to_types.size(); i++) {
        if(this->castable_to_types[i] == type) return true;
    }

    return false;
}

bool ASTType::acceptConstructor(AST* l, Parser* parser) {
    if(l->ast_type == NodeType::AST_LITERAL) {
        ASTLiteral* list = static_cast<ASTLiteral*>(l);

        if(list->is_initialization_list) {

            // Cant initialize array whithout all members
            if(list->list_values.size() != this->members.size()) return false;

            // Se if all dimensions of the vector are initialized
            for(int j=0; j<this->members.size(); j++)
                if(!this->members[j]->acceptTree(list->list_values[j], parser)) return false;


            return true;
        } else {

            return this->acceptLiteral(static_cast<ASTLiteral*>(l), parser);
        }
        
    }

    if(l->ast_type == NodeType::AST_FUNCTION_CALL) {
        ASTFunctionCall* call = static_cast<ASTFunctionCall*>(l);
        ASTSymbol* symbol = static_cast<ASTSymbol*>(call->func_call_symbol);

        if(strcmp(symbol->symbol_name, this->type_name) != 0) {
            return false;
        }

        for(int  i=0; i< this->constructors.size(); i++) {
            if(this->constructors[i]->arguments.size() != call->func_call_arguments.size()) continue;

            bool accept = true;
            for(int  j=0; j< this->constructors[i]->arguments.size(); j++) {
                if(!this->constructors[i]->arguments[j]->acceptTree(call->func_call_arguments[i], parser)) accept = false;
            }

            if(accept) return true;
        }
    }

    return true;            
}

bool ASTType::acceptTree(AST* t, Parser* parser) {

    switch (t->ast_type) {
        case NodeType::AST_LITERAL:
            return this->acceptConstructor(static_cast<ASTLiteral*>(t), parser);
        case NodeType::AST_SYMBOL:
            return this->acceptSymbol(t,parser);
        case NodeType::AST_FUNCTION_CALL:
            return this->acceptFunction(static_cast<ASTFunctionCall*>(t), parser);
        case NodeType::AST_TYPE_DECL:
            return this->isCastableTo(static_cast<ASTType*>(t));
        case NodeType::AST_EXPRESSION_BINARY:
            return this->acceptTree(static_cast<ASTBinaryExpression*>(t)->bin_exp_left_operand, parser)
                && this->acceptTree(static_cast<ASTBinaryExpression*>(t)->bin_exp_left_operand, parser);
        case NodeType::AST_EXPRESSION_UNARY:
            return this->acceptTree(static_cast<ASTUnaryExpression*>(t)->un_exp_operand, parser);
        case NodeType::AST_ASSIGNMENT:
            return this->acceptTree(static_cast<ASTAssignment*>(t)->assignment_right_operand, parser);
    }

    return true;
}

AST* ASTType::getMember(int id) {
    if(this->members.size() >= id) return nullptr;
    return this->members[id];
}

AST* ASTType::getMemberFunDecl(char* id) {
    for(int i=0; i<this->functions.size(); i++) {
        ASTFunctionDeclaration* decl = static_cast<ASTFunctionDeclaration*>(this->functions[i]);
        if(strcmp(decl->func_decl_name, id) == 0) {
            return decl;
        }
    }

    return nullptr;
}

bool ASTType::canAcccessIndex(int i, int j) {
    if(this->members.size() <= i) return false;
    else if(j > 0) return j < this->members[i]->members.size();
    else return true;
}


ASTLiteral* _parseLiteral(Parser* parser) {

    ASTLiteral* literal = new ASTLiteral();

    switch (parser->currentToken()->type) {
        case Token::TOKEN_INT_LITERAL:
            literal->type = ASTLiteral::Type::LITERAL_INT;
            literal->int_val = atoi(parser->currentToken()->value);
            parser->readNumeric();
            break;
        case Token::TOKEN_FLOAT_LITERAL:
            literal->type = ASTLiteral::Type::LITERAL_FLOAT;
            literal->float_val = atof(parser->currentToken()->value);
            parser->readNumeric();
        case Token::TOKEN_TRUE:
            literal->type = ASTLiteral::Type::LITERAL_BOOL;
            literal->bool_val = true;
            parser->readToken(Token::TOKEN_TRUE);
            break;
        case Token::TOKEN_FALSE:
            literal->type = ASTLiteral::Type::LITERAL_BOOL;
            parser->readToken(Token::TOKEN_FALSE);
            literal->bool_val = false;
            break;
        case Token::TOKEN_STRING_LITERAL:
            literal->type = ASTLiteral::Type::LITERAL_BOOL;
            literal->string_val = parser->currentToken()->value;
            parser->readToken(Token::TOKEN_STRING_LITERAL);
            break;
    }

    return literal;

}

ASTLiteral* parseLiteral(Parser* parser, ASTType* type) {
    ASTLiteral* literal = new ASTLiteral();
    literal->is_initialization_list = false;
    AST* ast = parser->scope->getTypeDefinition(parser->currentToken()->value);
    
    if(ast) {
        // Type constructor
        parser->readToken(parser->currentToken()->type);
        parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
        literal->is_initialization_list = true;
        literal->list_values.push_back(parseExpression(parser));
        while(parser->currentToken()->type == Token::TOKEN_COMMA) {
            parser->readToken(Token::TOKEN_COMMA);
            literal->list_values.push_back(parseExpression(parser));
        }
        parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
    }else if(parser->currentToken()->type == Token::TOKEN_OPEN_CURLY_BRACKETS) {
        parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);

        if(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
            literal->is_initialization_list = true;
            literal->list_values.push_back(parseExpression(parser));
            while(parser->currentToken()->type == Token::TOKEN_COMMA) {
                parser->readToken(Token::TOKEN_COMMA);
                literal->list_values.push_back(parseExpression(parser));
            }
        }
        parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);
    } else {
        switch (parser->currentToken()->type) {
            case Token::TOKEN_INT_LITERAL:
                literal->type = ASTLiteral::Type::LITERAL_INT;
                literal->int_val = atoi(parser->currentToken()->value);
                parser->readNumeric();
                break;
            case Token::TOKEN_FLOAT_LITERAL:
                literal->type = ASTLiteral::Type::LITERAL_FLOAT;
                literal->float_val = atof(parser->currentToken()->value);
                parser->readNumeric();
                break;
            case Token::TOKEN_TRUE:
                literal->type = ASTLiteral::Type::LITERAL_BOOL;
                literal->bool_val = true;
                parser->readToken(Token::TOKEN_TRUE);
                break;
            case Token::TOKEN_FALSE:
                literal->type = ASTLiteral::Type::LITERAL_BOOL;
                parser->readToken(Token::TOKEN_FALSE);
                literal->bool_val = false;
                break;
            case Token::TOKEN_STRING_LITERAL:
                literal->type = ASTLiteral::Type::LITERAL_BOOL;
                literal->string_val = parser->currentToken()->value;
                parser->readToken(Token::TOKEN_STRING_LITERAL);
                break;
            default:
                printf("Error: Undefined initilizer at line '%i'!\n", parser->currentToken()->line);
                exit(-1);
        }
    }

    return literal;
}



ASTType* parseType(Parser* parser) {
    AST* type = parser->scope->getTypeDefinition(parser->currentToken()->value);
    if(!type) {
        printf("Undefined Type '%s' at line '%i'\n", parser->currentToken()->value, parser->currentToken()->line);
        exit(-1);
    }

    parser->readToken(parser->currentToken()->type);

    return static_cast<ASTType*>(type);
}


}