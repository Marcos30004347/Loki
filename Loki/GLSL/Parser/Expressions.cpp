#include "Expressions.hpp"
#include "Structs.hpp"

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

namespace GLSL {

ASTSymbol::ASTSymbol(): AST{NodeType::AST_SYMBOL} {}
ASTBinaryExpression::ASTBinaryExpression(): AST{NodeType::AST_EXPRESSION_BINARY} {}
ASTUnaryExpression::ASTUnaryExpression(): AST{NodeType::AST_EXPRESSION_UNARY} {}
ASTFunctionCall::ASTFunctionCall(): AST{NodeType::AST_FUNCTION_CALL} {}
ASTAssignment::ASTAssignment(): AST{NodeType::AST_ASSIGNMENT} {}
ASTMemberAccess::ASTMemberAccess(): AST{ NodeType::AST_MEMBER_ACCESS } {}
ASTArrayAccess::ASTArrayAccess(): AST{ NodeType::AST_ARRAY_ACCESS } {}
ASTTernary::ASTTernary(): AST{ NodeType::AST_TERNARY } {}

// EXPRESSION → IDENTIFIER ('=' | '|=' | '&=' | '+=' | '-=' ) ASSIGNMENT | EQUALITY | EXPRESSION ? EXPRESSION : EXPRESSION
AST* parseExpression(Parser* parser, bool constant) {
    AST* root = parseTernary(parser, constant);
    if(
        parser->currentToken() &&
        (parser->currentToken()->type == Token::TOKEN_EQUAL
        || parser->currentToken()->type == Token::TOKEN_PIPE_EQUAL
        || parser->currentToken()->type == Token::TOKEN_AMPERSAND_EQUAL
        || parser->currentToken()->type == Token::TOKEN_TIMES_EQUAL
        || parser->currentToken()->type == Token::TOKEN_PLUS_EQUAL
        || parser->currentToken()->type == Token::TOKEN_MINUS_EQUAL
        || parser->currentToken()->type == Token::TOKEN_PERCENT_EQUAL
        || parser->currentToken()->type == Token::TOKEN_HAT_EQUAL
        || parser->currentToken()->type == Token::TOKEN_DIVIDE_EQUAL
        || parser->currentToken()->type == Token::TOKEN_GREATER_GREATER_EQUAL
        || parser->currentToken()->type == Token::TOKEN_LESS_LESS_EQUAL)
    ) {
        AST* assignment = new ASTAssignment();
        static_cast<ASTAssignment*>(assignment)->assignment_left_operand = root;
        switch(parser->currentToken()->type) {
            case Token::TOKEN_EQUAL: static_cast<ASTAssignment*>(assignment)->assignment_op = AssignmentOp::ASSIGNMENT_EQUAL; break;
            case Token::TOKEN_PIPE_EQUAL: static_cast<ASTAssignment*>(assignment)->assignment_op = AssignmentOp::ASSIGNMENT_OR_EQUAL; break;
            case Token::TOKEN_AMPERSAND_EQUAL: static_cast<ASTAssignment*>(assignment)->assignment_op = AssignmentOp::ASSIGNMENT_AND_EQUAL; break;
            case Token::TOKEN_TIMES_EQUAL: static_cast<ASTAssignment*>(assignment)->assignment_op = AssignmentOp::ASSIGNMENT_TIMES_EQUAL; break;
            case Token::TOKEN_PLUS_EQUAL: static_cast<ASTAssignment*>(assignment)->assignment_op = AssignmentOp::ASSIGNMENT_PLUS_EQUAL; break;
            case Token::TOKEN_MINUS_EQUAL: static_cast<ASTAssignment*>(assignment)->assignment_op = AssignmentOp::ASSIGNMENT_MINUS_EQUAL; break;
            case Token::TOKEN_PERCENT_EQUAL: static_cast<ASTAssignment*>(assignment)->assignment_op = AssignmentOp::ASSIGNMENT_MOD_EQUAL; break;
            case Token::TOKEN_HAT_EQUAL: static_cast<ASTAssignment*>(assignment)->assignment_op = AssignmentOp::ASSIGNMENT_XOR_EQUAL; break;
            case Token::TOKEN_DIVIDE_EQUAL: static_cast<ASTAssignment*>(assignment)->assignment_op = AssignmentOp::ASSIGNMENT_DIVIDE_EQUAL; break;
            case Token::TOKEN_GREATER_GREATER_EQUAL: static_cast<ASTAssignment*>(assignment)->assignment_op = AssignmentOp::ASSIGNMENT_RIGHT_SHIFT_EQUAL; break;
            case Token::TOKEN_LESS_LESS_EQUAL: static_cast<ASTAssignment*>(assignment)->assignment_op = AssignmentOp::ASSIGNMENT_LEFT_SHIFT_EQUAL; break;
            default: printf("Error parsing equality operation! \n"); exit(-1); break;
        }
        parser->readToken(parser->currentToken()->type);

        static_cast<ASTAssignment*>(assignment)->assignment_right_operand = parseExpression(parser);
        root = assignment;
    }

    return root;
}


AST* parseTernary(Parser* parser, bool constant) {
    // Ternary
    AST* root = parseBooleans(parser, constant);

    if(parser->currentToken() && parser->currentToken()->type == Token::TOKEN_INTERROGATION) {
        parser->readToken(Token::TOKEN_INTERROGATION);
        ASTTernary* ternary = new ASTTernary();
        ternary->ternary_expression = root;
        ternary->ternary_left = parseExpression(parser);
        parser->readToken(Token::TOKEN_TWO_POINTS);
        ternary->ternary_right = parseExpression(parser);
        root = ternary;
    }

    return root;
}


// BOOL → TERM (( '&&' | '^^' | '||') BOOL)*
AST* parseBooleans(Parser* parser, bool constant) {
    AST* root = parseBitwise(parser, constant);

    if(
        parser->currentToken() &&
        (parser->currentToken()->type == Token::TOKEN_PIPE_PIPE
        || parser->currentToken()->type == Token::TOKEN_APERSAND_AMPERSAND
        || parser->currentToken()->type == Token::TOKEN_HAT_HAT)
    ) {
        AST* bn = new ASTBinaryExpression();
        static_cast<ASTBinaryExpression*>(bn)->bin_exp_left_operand = root;
        switch(parser->currentToken()->type) {
            case Token::TOKEN_PIPE_PIPE: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_OR; break;
            case Token::TOKEN_APERSAND_AMPERSAND: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_AND; break;
            case Token::TOKEN_HAT_HAT: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_LOGICAL_EXCLUSIVE_OR; break;
            default: printf("Error parsing Boolean operation! \n"); exit(-1); break;
        }
        parser->readToken(parser->currentToken()->type);
        static_cast<ASTBinaryExpression*>(bn)->bin_exp_right_operand = parseBooleans(parser, constant);
        root = bn;
    }
    return root;
}

// BITWISE → BOOL (( '&' | '|' | '^'  ) BITWISE)*
AST* parseBitwise(Parser* parser, bool constant) {
    AST* root = parseEquality(parser, constant);

    if(
        parser->currentToken() &&
        (parser->currentToken()->type == Token::TOKEN_PIPE
        || parser->currentToken()->type == Token::TOKEN_AMPERSAND
        || parser->currentToken()->type == Token::TOKEN_HAT)
    ) {
        AST* bn = new ASTBinaryExpression();
        static_cast<ASTBinaryExpression*>(bn)->bin_exp_left_operand = root;
        switch(parser->currentToken()->type) {
            case Token::TOKEN_PIPE: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_BITWISE_OR; break;
            case Token::TOKEN_AMPERSAND: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_BITWISE_AND; break;
            case Token::TOKEN_HAT: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_BITWISE_EXLUSIVE_OR; break;
            default: printf("Error parsing Boolean operation! \n"); exit(-1); break;
        }
        parser->readToken(parser->currentToken()->type);
        static_cast<ASTBinaryExpression*>(bn)->bin_exp_right_operand = parseBooleans(parser, constant);
        root = bn;
    }
    return root;
}

// EQUALITY → COMPARISON (('!=' | '==') EQUALITY)*
AST* parseEquality(Parser* parser, bool constant) {
    AST* root = parseComparison(parser, constant);
    if(
        parser->currentToken() &&
        (parser->currentToken()->type == Token::TOKEN_NOT_EQUAL
        || parser->currentToken()->type == Token::TOKEN_EQUAL_EQUAL)
    ) {
        AST* bn = new ASTBinaryExpression();
        static_cast<ASTBinaryExpression*>(bn)->bin_exp_left_operand = root;
        switch(parser->currentToken()->type) {
            case Token::TOKEN_NOT_EQUAL: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_COMPARISON_NOT_EQUAL; break;
            case Token::TOKEN_EQUAL_EQUAL: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_COMPARISON_EQUAL; break;
            default: printf("Error parsing equality operation! \n"); exit(-1); break;
        }
        parser->readToken(parser->currentToken()->type);

        static_cast<ASTBinaryExpression*>(bn)->bin_exp_right_operand = parseEquality(parser);
        root = bn;
    }
    return root;
}


// COMPARISON → SHIFT (( '>' | '>=' | '<' | '<='  ) COMPARISON)*
AST* parseComparison(Parser* parser, bool constant) {
    AST* root = parseBitwiseShift(parser, constant);

    if(
        parser->currentToken() &&
        (parser->currentToken()->type == Token::TOKEN_GREATER_OR_EQUAL
        || parser->currentToken()->type == Token::TOKEN_GREATER
        || parser->currentToken()->type == Token::TOKEN_LESS
        || parser->currentToken()->type == Token::TOKEN_LESS_OR_EQUAL)
    ) {
        AST* bn = new ASTBinaryExpression();
        static_cast<ASTBinaryExpression*>(bn)->bin_exp_left_operand = root;
        switch(parser->currentToken()->type) {
            case Token::TOKEN_GREATER_OR_EQUAL: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_GREATER_OR_EQUAL; break;
            case Token::TOKEN_GREATER: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_GREATER; break;
            case Token::TOKEN_LESS: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_LESS; break;
            case Token::TOKEN_LESS_OR_EQUAL: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_LESS_OR_EQUAL; break;
            default: printf("Error parsing Comparison operation! \n"); exit(-1); break;
        }
        parser->readToken(parser->currentToken()->type);
        static_cast<ASTBinaryExpression*>(bn)->bin_exp_right_operand = parseComparison(parser, constant);
        root = bn;
    }
    return root;
}

// SHIFT → TERM (( '>>' | '<<'  ) COMPARISON)*
AST* parseBitwiseShift(Parser* parser, bool constant) {
    AST* root = parseTerm(parser, constant);

    if(
        parser->currentToken() &&
        (parser->currentToken()->type == Token::TOKEN_GREATER_GREATER
        || parser->currentToken()->type == Token::TOKEN_LESS_LESS)
    ) {
        AST* bn = new ASTBinaryExpression();
        static_cast<ASTBinaryExpression*>(bn)->bin_exp_left_operand = root;
        switch(parser->currentToken()->type) {
            case Token::TOKEN_GREATER_GREATER: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_BITWISE_SHIFT_RIGHT; break;
            case Token::TOKEN_LESS_LESS: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_BITWISE_SHIFT_LEFT; break;
            default: printf("Error parsing shift operation! \n"); exit(-1); break;
        }
        parser->readToken(parser->currentToken()->type);
        static_cast<ASTBinaryExpression*>(bn)->bin_exp_right_operand = parseBitwiseShift(parser, constant);
        root = bn;
    }

    return root;
}


// TERM → FACTOR (('+' | '-') TERM)*
AST* parseTerm(Parser* parser, bool constant) {

    AST* root = parseFactor(parser, constant);

    if(
        parser->currentToken() &&
        (parser->currentToken()->type == Token::TOKEN_PLUS
        || parser->currentToken()->type == Token::TOKEN_MINUS)
    ) {
        AST* bn = new ASTBinaryExpression();
        static_cast<ASTBinaryExpression*>(bn)->bin_exp_left_operand = root;
        switch(parser->currentToken()->type) {
            case Token::TOKEN_PLUS: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_ADD; break;
            case Token::TOKEN_MINUS: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_SUB; break;
            default: printf("Error parsing term operation! \n"); exit(-1); break;
        }
        parser->readToken(parser->currentToken()->type);
        static_cast<ASTBinaryExpression*>(bn)->bin_exp_right_operand = parseTerm(parser, constant);
        root = bn;
    }

    return root;
}

// FACTOR → UNARY (('/' | '*' | '%' ) FACTOR)*
AST* parseFactor(Parser* parser, bool constant) {

    AST* root = parseUnary(parser, constant);

    if(
        parser->currentToken() &&
        (parser->currentToken()->type == Token::TOKEN_SLASH
        || parser->currentToken()->type == Token::TOKEN_ASTERISK
        || parser->currentToken()->type == Token::TOKEN_PERCENT)
    ) {
        AST* bn = new ASTBinaryExpression();
        static_cast<ASTBinaryExpression*>(bn)->bin_exp_left_operand = root;
        switch(parser->currentToken()->type) {
            case Token::TOKEN_SLASH: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_DIV; break;
            case Token::TOKEN_ASTERISK: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_MUL; break;
            case Token::TOKEN_PERCENT: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_MOD; break;
            default: printf("Error parsing factor operation! \n"); exit(-1); break;
        }
        parser->readToken(parser->currentToken()->type);

        static_cast<ASTBinaryExpression*>(bn)->bin_exp_right_operand = parseFactor(parser, constant);
        root = bn;
    }

    return root;
}

// UNARY → ('!' | '-' | '+' | '++' | '--' | '~' )UNARY | UNARY('++' | '--') | CALL
AST* parseUnary(Parser* parser, bool constant) {
    AST* root = nullptr;
    if(
        parser->currentToken() &&
        (parser->currentToken()->type == Token::TOKEN_EXCLAMATION
        || parser->currentToken()->type == Token::TOKEN_MINUS
        || parser->currentToken()->type == Token::TOKEN_PLUS
        || parser->currentToken()->type == Token::TOKEN_PLUS_PLUS
        || parser->currentToken()->type == Token::TOKEN_MINUS_MINUS
        || parser->currentToken()->type == Token::TOKEN_TIL)
    ) {
        switch (parser->currentToken()->type) {
        case Token::TOKEN_EXCLAMATION:
            parser->readToken(Token::TOKEN_EXCLAMATION);
            root = new ASTUnaryExpression();
            static_cast<ASTUnaryExpression*>(root)->un_exp_operator = UnaryOp::UNARY_OP_NOT;
            static_cast<ASTUnaryExpression*>(root)->un_exp_operand = parseUnary(parser, constant);
            
            break;
        case Token::TOKEN_PLUS: parser->readToken(Token::TOKEN_PLUS); break; // does nothing
        case Token::TOKEN_MINUS:
            parser->readToken(Token::TOKEN_MINUS);
            root = new ASTUnaryExpression();
            static_cast<ASTUnaryExpression*>(root)->un_exp_operator = UnaryOp::UNARY_OP_NEGATIVE;
            static_cast<ASTUnaryExpression*>(root)->un_exp_operand = parseUnary(parser, constant);
            break;
        case Token::TOKEN_PLUS_PLUS:
            parser->readToken(Token::TOKEN_PLUS_PLUS);
            root = new ASTUnaryExpression();
            static_cast<ASTUnaryExpression*>(root)->un_exp_operator = UnaryOp::UNARY_OP_PRE_INCREMENT;
            static_cast<ASTUnaryExpression*>(root)->un_exp_operand = parseUnary(parser, constant);
            break;
        case Token::TOKEN_MINUS_MINUS:
            parser->readToken(Token::TOKEN_MINUS_MINUS);
            root = new ASTUnaryExpression();
            static_cast<ASTUnaryExpression*>(root)->un_exp_operator = UnaryOp::UNARY_OP_PRE_DECREMENT;
            static_cast<ASTUnaryExpression*>(root)->un_exp_operand = parseUnary(parser, constant);
            break;
        case Token::TOKEN_TIL:
            parser->readToken(Token::TOKEN_TIL);
            root = new ASTUnaryExpression();
            static_cast<ASTUnaryExpression*>(root)->un_exp_operator = UnaryOp::UNARY_OP_LOGICAL_NOT;
            static_cast<ASTUnaryExpression*>(root)->un_exp_operand = parseUnary(parser, constant);
            break;
        }

        return root;
    }

    return parseMemberAccess(parser, constant);
}


AST* parseMemberAccess(Parser* parser, bool constant) {
    AST* root = parseArrayAccess(parser, constant);
    while(parser->currentToken() && parser->currentToken()->type == Token::TOKEN_POINT) {
        parser->readToken(Token::TOKEN_POINT);
        ASTMemberAccess* access = new ASTMemberAccess();
        access->member_left = root;
        access->member_right = parseMemberAccess(parser, constant);

        root = access;
    }

    return root;
}

AST* parseArrayAccess(Parser* parser, bool constant) {
    AST* root = parseCall(parser, constant);
    
    while(parser->currentToken() && parser->currentToken()->type == Token::TOKEN_OPEN_SQUARE_BRACKETS) {
        ASTArrayAccess* access = new ASTArrayAccess();
        parser->readToken(Token::TOKEN_OPEN_SQUARE_BRACKETS);
        access->member_left = root;
        access->arra_index = parseExpression(parser, constant);
        access->member_right = parseMemberAccess(parser, constant);
        parser->readToken(Token::TOKEN_CLOSE_SQUARE_BRACKETS);
        root = access;
    }

    return root;
}






// UNARY → ('!' | '-' | '+' | '++' | '--' | '~' )UNARY | UNARY('++' | '--') | CALL
AST* parsePostfixSuffixUnary(Parser* parser, bool constant) {
    AST* root = parsePrimary(parser, constant);

    AST* un = nullptr;
    
    if(
        parser->currentToken() &&
        (parser->currentToken()->type == Token::TOKEN_PLUS_PLUS
        || parser->currentToken()->type == Token::TOKEN_MINUS_MINUS)
    ) {
        switch (parser->currentToken()->type) {
        case Token::TOKEN_PLUS_PLUS:
            parser->readToken(Token::TOKEN_PLUS_PLUS);
            un = new ASTUnaryExpression();
            static_cast<ASTUnaryExpression*>(un)->un_exp_operator = UnaryOp::UNARY_OP_POST_INCREMENT;
            static_cast<ASTUnaryExpression*>(un)->un_exp_operand = root;
            root = un;
            break;
        case Token::TOKEN_MINUS_MINUS:
            parser->readToken(Token::TOKEN_MINUS_MINUS);
            un = new ASTUnaryExpression();
            static_cast<ASTUnaryExpression*>(un)->un_exp_operator = UnaryOp::UNARY_OP_POST_DECREMENT;
            static_cast<ASTUnaryExpression*>(un)->un_exp_operand = root;
            root = un;
            break;
        }
    }

    return root;
}



// PRIMARY → LITERAL | SYMBOL | '('EXPRESSION')'
AST* parsePrimary(Parser* parser, bool constant) {
    if(parser->currentToken() && parser->currentToken()->type == Token::TOKEN_OPEN_PARENTESIS) {
        parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
        AST* expression = parseExpression(parser, constant);
        parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);

        return expression;
    }

    if(parser->currentToken() && parser->currentToken()->type == Token::TOKEN_IDENTIFIER) {
        char* identifier = parser->currentToken()->value;
        parser->readToken(Token::TOKEN_IDENTIFIER);
        ASTSymbol* symbol = new ASTSymbol();
        symbol->symbol_name = identifier;
        return symbol;
    }

    return parseLiteral(parser);
}



}

