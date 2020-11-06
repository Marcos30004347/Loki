// https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-struct

#include "AST.hpp"
#include "Parser.hpp"
#include "BaseType.hpp"
#include "InterpolationModifier.hpp"
#include <vector>
namespace HLSL {


struct StructMember {
    InterpolationModifier member_interpolation_modifier;
    BaseType* member_base_type;
    char* member_name;
};

struct ASTStruct : AST {
    explicit ASTStruct();
    char* struct_identifier;
    std::vector<StructMember*> struct_members;
};

// STRUCT -> 'struct' IDENTIFIER '{' (INTERPOLATION_MODIFIER? TYPE IDENTIFIER';')* };
ASTStruct* parseStruct(Parser* parser);

}