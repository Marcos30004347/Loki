#ifndef HLSL_TYPES_H
#define HLSL_TYPES_H

#include "AST.hpp"
#include "Parser.hpp"

#include <vector>

namespace HLSL {

struct ASTLiteral: AST {
    explicit ASTLiteral();
    enum Type {
        LITERAL_INT,
        LITERAL_FLOAT,
        LITERAL_STRING,
        LITERAL_BOOL,
        LITERAL_EXPRESSION,
    };


    Type type;

    int int_val;
    bool bool_val;
    float float_val;
    char* string_val;
    std::vector<AST*> list_values;
    
    bool is_template;
    bool is_initialization_list;
    bool is_constructor;
    
    char* constructor_name;
};

struct ASTType;

struct ASTConstructor: AST {
    explicit ASTConstructor();
    std::vector<ASTType*> arguments;
    std::vector<AST*> constructor_statemetns;
};


struct ASTType: AST {
    explicit ASTType(const char* id, bool builtIn = true);
    explicit ASTType(char* id, bool builtIn = true);

    char* type_name;

    bool build_in = true;

    AST* type_struct = nullptr;

    std::vector<AST*> functions;

    std::vector<ASTType*> members;

    std::vector<AST*> castable_to_types; 

    std::vector<ASTLiteral::Type> castable_to_literals;

    std::vector<ASTLiteral::Type> accept_literals;

    std::vector<ASTConstructor*> constructors;

    bool is_vector_type;

    bool acceptLiteral(ASTLiteral* t, Parser*);
    bool acceptSymbol(AST*, Parser*);
    bool acceptFunction(AST*, Parser*);
    bool acceptTree(AST*, Parser*);
    bool acceptConstructor(AST*, Parser*);
    bool isCastableTo(ASTType*);
    bool isCastableToLiteral(ASTLiteral*);
    bool canAcccessIndex(int i, int j);

    AST* getMember(int id);
    AST* getMemberFunDecl(char*);
};

ASTLiteral* parseLiteral(Parser* parser, ASTType* type  = nullptr);
ASTType* parseType(Parser* parser);

}

#endif