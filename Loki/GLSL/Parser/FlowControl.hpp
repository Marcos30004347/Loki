#ifndef FLOW_CONTROL_H
#define FLOW_CONTROL_H

#include "AST.hpp"
#include "Parser.hpp"
#include "Block.hpp"
#include "Expressions.hpp"
#include "Statement.hpp"

#include <vector>

namespace GLSL {

struct ASTIf: AST {
    explicit ASTIf();
    AST* if_expression;
    AST* if_statement;
    AST* if_else;
};

struct ASTWhile: AST {
    explicit ASTWhile();
    AST* while_expression;
    AST* while_statement;
};

struct ASTDoWhile: AST {
    explicit ASTDoWhile();
    AST* do_while_expression;
    AST* do_while_statement;
};

struct ASTBreak: AST {
    explicit ASTBreak();
};
struct ASTContinue: AST {
    explicit ASTContinue();
};
struct ASTDiscard: AST {
    explicit ASTDiscard();
};

struct ASTCase: AST {
    explicit ASTCase();
    AST* case_expression;
    std::vector<AST*> case_statements;
};

struct ASTDefault: AST {
    explicit ASTDefault();
    std::vector<AST*> default_statements;
};


struct ASTSwitch: AST {
    explicit ASTSwitch();
    std::vector<ASTCase*> switch_case_statements;
    AST* switch_expression;
    AST* swtich_default;
};

struct ASTFor: AST {
    explicit ASTFor();
    AST* for_init_statement;
    AST* for_cond_expression;
    AST* for_loop_expression;
    AST* for_body_statement;
};

ASTIf* parseIf(Parser* parser);
ASTWhile* parseWhile(Parser* parser);
ASTDoWhile* parseDoWhile(Parser* parser);
ASTBreak* parseBreak(Parser* parser);
ASTContinue* parseContinue(Parser* parser);
ASTDiscard* parseDiscard(Parser* parser);
ASTFor* parseFor(Parser* parser);
ASTSwitch* parseSwitch(Parser* parser);
ASTCase* parseCase(Parser* parser);
ASTDefault* parseDefault(Parser* parser);

}

#endif