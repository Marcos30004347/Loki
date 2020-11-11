// https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-struct

#include "AST.hpp"
#include "Parser.hpp"
#include "Declarations.hpp"
#include "InterpolationModifier.hpp"
#include <vector>
namespace HLSL {


// struct StructMember {
//     InterpolationModifier member_interpolation_modifier;
//     ASTVarDecl* struct_member_variable;
// };

// struct ASTStruct : AST {
//     explicit ASTStruct();

//     char* struct_identifier;
//     char* struct_declarator;

//     ASTTypeDecl* struct_type;

//     std::vector<AST*> struct_members;
// };

// STRUCT -> 'struct' IDENTIFIER '{' (INTERPOLATION_MODIFIER? TYPE IDENTIFIER';')* };
ASTTypeDecl* parseStruct(Parser* parser);


}