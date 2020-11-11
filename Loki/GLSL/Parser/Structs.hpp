#include "AST.hpp"
#include "Parser.hpp"
#include "Declarations.hpp"
#include "Types.hpp"
#include "StorageQualifiers.hpp"

#include <vector>

namespace GLSL {

ASTTypeDecl* parseStruct(Parser* parser);

}