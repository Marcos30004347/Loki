#include "Types.hpp"
#include "Expressions.hpp"
#include "Declarations.hpp"
#include "Structs.hpp"
#include "Lib/String.hpp"

#include <stdio.h>
#include <stdlib.h>

namespace GLSL {

const char* literal_names[] = {
    "int",
    "float",
    "string",
    "bool"
};

ASTTypeDecl::ASTTypeDecl(const char* id, bool builtIn):
    AST{AST_TYPE_DECL},
    type_name{copyStr(id)},
    build_in{builtIn},
    is_struct{false}
    {}

ASTTypeDecl::ASTTypeDecl(char* id, bool builtIn):
    AST{AST_TYPE_DECL},
    type_name{id},
    build_in{builtIn},
    is_struct{false}
    {}

ASTTypeDecl::ASTTypeDecl(bool builtIn):
    AST{AST_TYPE_DECL},
    type_name{nullptr},
    build_in{builtIn},
    is_struct{false}
    {}

ASTLiteral::ASTLiteral(): AST{AST_LITERAL} {}
ASTConstructor::ASTConstructor(): AST{AST_TYPE_CONSTRUCTOR} {}
ASTType::ASTType(ASTTypeDecl* type): AST{NodeType::AST_TYPE}, type{type} {};

bool ASTTypeDecl::isCastableToLiteral(ASTLiteral* type) {
    for(int i=0; i<this->castable_to_literals.size(); i++) {
        if(type->type == this->castable_to_literals[i]) return true;
    }
    return false;
}

bool ASTTypeDecl::acceptLiteral(ASTLiteral* t, Parser* parser) {
    for(int i=0; i<this->accept_literals.size(); i++) {
        if(this->accept_literals[i] == t->type || this->isCastableToLiteral(t)) return true;
    }

    return false;
}

bool ASTTypeDecl::acceptSymbol(AST* symbol, Parser* parser) {
    AST* decl = parser->scope->getVariableDefinition(
        static_cast<ASTSymbol*>(symbol)->symbol_name
    );

    ASTVarDecl* var_decl = static_cast<ASTVarDecl*>(decl);
    return var_decl->var_decl_type->type == this || this->isCastableTo(var_decl->var_decl_type->type);
}

bool ASTTypeDecl::acceptFunction(AST* func, Parser* parser) {
    ASTSymbol* symbol = static_cast<ASTSymbol*>(static_cast<ASTFunctionCall*>(func)->func_call_symbol);

    if(strcmp(symbol->symbol_name, this->type_name) == 0) {
        return this->acceptConstructor(func, parser);
    }
    // std::vector<ASTTypeDecl*> arguments_types;
    // ASTFunctionCall* call = static_cast<ASTFunctionCall*>(func);
    // for(int i=0; i<call->func_call_arguments.size(); i++) {
        // arguments_types.push_back(static_cast<AST>call->func_call_arguments[i]);
    // }
    AST* tmp = parser->scope->getFunctionDefinition(symbol->symbol_name);
    ASTFunctionDeclaration* call = static_cast<ASTFunctionDeclaration*>(tmp);
    return this->isCastableTo(static_cast<ASTTypeDecl*>(call->func_decl_return_type->type));
}


bool ASTTypeDecl::isCastableTo(ASTTypeDecl* type) {
    std::vector<AST*> data_members = this->getTypeMembers();

    if(type->getTypeMembers().size() != data_members.size()) {
        return false;
    }

    if(type->members.size()) {
        for(int i=0; i<data_members.size(); i++) {
            ASTType* data_type = static_cast<ASTType*>(data_members[i]);
            if(!this->isCastableTo(data_type->type)) {
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

bool ASTTypeDecl::acceptConstructor(AST* l, Parser* parser) {
    if(l->ast_type == NodeType::AST_LITERAL) {
        ASTLiteral* list = static_cast<ASTLiteral*>(l);

        if(list->is_initialization_list) {
            std::vector<AST*> data_members = this->getTypeMembers();

            // Cant initialize array whithout all members
            if(list->list_values.size() != data_members.size()) return false;

            // Se if all dimensions of the vector are initialized
            for(int j=0; j<data_members.size(); j++) {
                ASTType* data_type;
                data_type = static_cast<ASTType*>(data_members[j]);
                if(!data_type->acceptTree(list->list_values[j], parser)) return false;
            }


            return true;
        }

        return this->acceptLiteral(static_cast<ASTLiteral*>(l), parser);
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

bool ASTTypeDecl::acceptTree(AST* t, Parser* parser) {

    switch (t->ast_type) {
        case NodeType::AST_LITERAL:
            return this->acceptConstructor(static_cast<ASTLiteral*>(t), parser);
        case NodeType::AST_SYMBOL:
            return this->acceptSymbol(t,parser);
        case NodeType::AST_FUNCTION_CALL:
            return this->acceptFunction(static_cast<ASTFunctionCall*>(t), parser);
        case NodeType::AST_TYPE_DECL:
            return this->isCastableTo(static_cast<ASTTypeDecl*>(t));
        case NodeType::AST_EXPRESSION_BINARY:
            return this->acceptTree(static_cast<ASTBinaryExpression*>(t)->bin_exp_left_operand, parser)
                && this->acceptTree(static_cast<ASTBinaryExpression*>(t)->bin_exp_right_operand, parser);
        case NodeType::AST_EXPRESSION_UNARY:
            return this->acceptTree(static_cast<ASTUnaryExpression*>(t)->un_exp_operand, parser);
        case NodeType::AST_ASSIGNMENT:
            return this->acceptTree(static_cast<ASTAssignment*>(t)->assignment_right_operand, parser);
    }

    return true;
}

std::vector<AST*> ASTTypeDecl::getTypeMembers() {
    std::vector<AST*> result;

    for(int i=0; i<this->members.size(); i++) {
        if(this->members[i]->ast_type == AST_TYPE) {
            result.push_back(static_cast<ASTType*>(this->members[i]));
        }
    }

    return result;
}

std::vector<AST*> ASTTypeDecl::getFunctionMembers() {
    std::vector<AST*> result;

    for(int i=0; i<this->members.size(); i++) {
        if(this->members[i]->ast_type == AST_FUNCTION_DECLARATION) {
            result.push_back(static_cast<ASTFunctionDeclaration*>(this->members[i]));
        } 
    }

    return result;
}

ASTLiteral* parseLiteral(Parser* parser, ASTTypeDecl* type) {
    ASTLiteral* literal = new ASTLiteral();
    literal->is_initialization_list = false;
    literal->is_constructor = false;

    AST* ast = parser->scope->getTypeDefinition(parser->currentToken()->value);
    if(ast) {
        // Type constructor
        literal->constructor_name = static_cast<ASTTypeDecl*>(ast)->type_name;
        parser->readToken(parser->currentToken()->type);
        
        if(parser->currentToken()->type == Token::TOKEN_OPEN_PARENTESIS)
            parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
        else 
            parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);

        literal->is_constructor = true;
        literal->is_initialization_list = false;
        literal->list_values.push_back(parseExpression(parser));
        while(parser->currentToken()->type == Token::TOKEN_COMMA) {
            parser->readToken(Token::TOKEN_COMMA);
            literal->list_values.push_back(parseExpression(parser));
        }
    
        if(parser->currentToken()->type == Token::TOKEN_CLOSE_PARENTESIS)
            parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
        else 
            parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);

    }else if(parser->currentToken()->type == Token::TOKEN_OPEN_CURLY_BRACKETS) {
        parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);

        if(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
            literal->is_initialization_list = true;
            literal->is_constructor = false;
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
    AST* type_decl;
    ASTType* type;

    if(parser->currentToken()->type == Token::TOKEN_STRUCT) {
        // type_decl = parseStruct(parser);

        parser->scope->addStructDefinition(type_decl);
        parser->scope->addTypeDeclaration(type_decl);
    
        type = new ASTType(static_cast<ASTTypeDecl*>(type_decl));

        while(parser->currentToken()->type == Token::TOKEN_LESS) {
            parser->readToken(Token::TOKEN_LESS);
            switch(parser->currentToken()->type) {
                case Token::TOKEN_INT_LITERAL:
                case Token::TOKEN_TRUE:
                case Token::TOKEN_FALSE:
                case Token::TOKEN_FLOAT_LITERAL:
                case Token::TOKEN_STRING_LITERAL:
                    type->template_arguments.push_back(parseLiteral(parser));
                    break;
                default:
                    type->template_arguments.push_back(parseType(parser));
                    break;
            }
            parser->readToken(Token::TOKEN_GREATER);
        }
    

        while(parser->currentToken()->type == Token::TOKEN_OPEN_SQUARE_BRACKETS) {
            parser->readToken(Token::TOKEN_OPEN_SQUARE_BRACKETS);
            type->dimensions.push_back(parseExpression(parser));
            parser->readToken(Token::TOKEN_CLOSE_SQUARE_BRACKETS);
        }
    
        return type;
    }

    type_decl = parser->scope->getTypeDefinition(parser->currentToken()->value);
    
    if(!type_decl) {
        printf("Undefined Type '%s' at line '%i'\n", parser->currentToken()->value, parser->currentToken()->line);
        exit(-1);
    }

    parser->readToken(parser->currentToken()->type); // Read type token

    type = new ASTType(static_cast<ASTTypeDecl*>(type_decl));
    
    while(parser->currentToken()->type == Token::TOKEN_OPEN_SQUARE_BRACKETS) {
        parser->readToken(Token::TOKEN_OPEN_SQUARE_BRACKETS);
        type->dimensions.push_back(parseExpression(parser));
        parser->readToken(Token::TOKEN_CLOSE_SQUARE_BRACKETS);
    }

    return type;
}

bool ASTType::isCastableTo(ASTType* other) {
    return other->dimensions.size() == this->dimensions.size() && this->type->isCastableTo(other->type);
}

bool ASTType::acceptTree(AST* tree, Parser* parser) {
    if(this->isArray()) {
        if(tree->ast_type != AST_LITERAL) {
            printf("ERROR: Array type cant accept non list initializer!\n");
            exit(-1);
        }
        ASTLiteral* literal = static_cast<ASTLiteral*>(tree);
        for(int i=0; i<literal->list_values.size(); i++) {
            if(!this->type->acceptTree(literal->list_values[i], parser)) return false;
        }

        return true;
    }

    return this->type->acceptTree(tree, parser);
    
}


}