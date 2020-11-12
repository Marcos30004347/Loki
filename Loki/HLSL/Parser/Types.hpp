#ifndef HLSL_TYPES_H
#define HLSL_TYPES_H

#include "AST.hpp"
#include "Parser.hpp"

#include <vector>

namespace HLSL {

struct ASTType;
struct ASTLiteral;
struct ASTTypeDecl;
struct ASTConstructor;

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
    
    bool is_initialization_list;
    bool is_constructor;
    
    char* constructor_name;
};


struct ASTConstructor: AST {
    explicit ASTConstructor();
    std::vector<ASTType*> arguments;
    std::vector<AST*> constructor_statemetns;
};


struct ASTTypeDecl: AST {
    explicit ASTTypeDecl(const char* id, bool builtIn = true);
    explicit ASTTypeDecl(char* id, bool builtIn = true);
    explicit ASTTypeDecl(bool builtIn = true);

    char* type_name;

    bool build_in = true;

    bool is_struct;

    std::vector<AST*> members; // type members 
    std::vector<char*> members_names; // type members 

    std::vector<AST*> castable_to_types; 
    std::vector<ASTLiteral::Type> castable_to_literals;
    std::vector<ASTLiteral::Type> accept_literals;
    std::vector<ASTConstructor*> constructors;

    bool acceptTree(AST*, Parser*); // If type accept an tree as initializer
    bool acceptSymbol(AST*, Parser*); // If type accepts a symbol as initializer
    bool acceptLiteral(ASTLiteral* t, Parser*); // If type accepts a literal as initializer
    bool acceptFunction(AST*, Parser*); // If funtion accepts Function call as initializer
    bool acceptConstructor(AST*, Parser*); //is Type accepts a constructor (both list and funcs).

    bool isCastableTo(ASTTypeDecl*);
    bool isCastableToLiteral(ASTLiteral*);

    std::vector<AST*> getTypeMembers(); // return ASTType* array that contains all members that are type/typedecl data members.
    std::vector<AST*> getFunctionMembers(); // return ASTFuncDecl* array of all members that are functions declarations.
};

struct ASTType: AST {
    explicit ASTType(ASTTypeDecl*);
    ASTTypeDecl* type;

    std::vector<AST*> dimensions;
    std::vector<AST*> template_arguments;

    inline bool isArray() { return dimensions.size(); }
    bool isCastableTo(ASTType*);
    bool acceptTree(AST*, Parser*);
};

ASTLiteral* parseLiteral(Parser* parser, ASTTypeDecl* type  = nullptr);
ASTType* parseType(Parser* parser);

}

#endif