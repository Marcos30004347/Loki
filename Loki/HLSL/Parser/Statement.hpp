#ifndef STATEMENT_H
#define STATEMENT_H

#include "AST.hpp"
#include "Parser.hpp"

namespace HLSL {

AST* parseStatement(Parser* parser);

}

#endif