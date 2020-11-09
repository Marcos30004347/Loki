// https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-struct

#include "AST.hpp"
#include "Parser.hpp"
#include "BaseType.hpp"
#include "Variables.hpp"
#include "InterpolationModifier.hpp"
#include <vector>
namespace HLSL {


struct StructMember {
    InterpolationModifier member_interpolation_modifier;
    ASTVarDecl* struct_member_variable;
};

struct ASTStruct : AST {
    explicit ASTStruct();
    char* struct_identifier;
    char* struct_declarator;
    std::vector<StructMember*> struct_members;
    void assertInitializationList(ASTLiteral* literal);
};

// STRUCT -> 'struct' IDENTIFIER '{' (INTERPOLATION_MODIFIER? TYPE IDENTIFIER';')* };
ASTStruct* parseStruct(Parser* parser);


}