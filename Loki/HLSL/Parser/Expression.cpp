#include "Expressions.hpp"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
namespace HLSL {

ASTSymbol::ASTSymbol(): AST{NodeType::NODE_TYPE_SYMBOL} {}
ASTBinaryExpression::ASTBinaryExpression(): AST{NodeType::NODE_TYPE_EXPRESSION_BINARY} {}
ASTUnaryExpression::ASTUnaryExpression(): AST{NodeType::NODE_TYPE_EXPRESSION_UNARY} {}
ASTFunctionCall::ASTFunctionCall(): AST{NodeType::NODE_TYPE_FUNCTION_CALL} {}
ASTAssignment::ASTAssignment(): AST{NodeType::NODE_TYPE_ASSIGNMENT} {}
ASTMemberAccess::ASTMemberAccess(): AST{ NodeType::NODE_TYPE_MEMBER_ACCESS } {}
ASTArrayAccess::ASTArrayAccess(): AST{ NodeType::NODE_TYPE_ARRAY_ACCESS } {}
ASTTernary::ASTTernary(): AST{ NodeType::NODE_TYPE_TERNARY } {}

// EXPRESSION → IDENTIFIER ('=' | '|=' | '&=' | '+=' | '-=' ) ASSIGNMENT | EQUALITY | EXPRESSION ? EXPRESSION : EXPRESSION
AST* parseExpression(Parser* parser, bool constant) {
    printf("EXPRESSION %s\n", parser->currentToken()->value);

    AST* root = parseEquality(parser, constant);
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

    // Ternary
    if(parser->currentToken() && parser->currentToken()->type == Token::TOKEN_INTERROGATION) {
        parser->readToken(Token::TOKEN_INTERROGATION);
        ASTTernary* ternary = new ASTTernary();
        ternary->ternary_expression = root;
        ternary->ternary_left = parseExpression(parser);
        parser->readToken(Token::TOKEN_TWO_POINTS);
        ternary->ternary_right = parseExpression(parser);
        root = ternary;
    }
    printf("~EXPRESSION\n");

    return root;
}

// EQUALITY → COMPARISON (('!=' | '==') EQUALITY)*
AST* parseEquality(Parser* parser, bool constant) {
    printf("EQ %s\n", parser->currentToken()->value);

    AST* root = parseBooleans(parser, constant);
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
    printf("~EQ\n");

    return root;
}


// BOOL → TERM (( '&&' | '||') BOOL)*
AST* parseBooleans(Parser* parser, bool constant) {
    printf("BOOL %s\n", parser->currentToken()->value);

    AST* root = parseBitwise(parser, constant);

    if(
        parser->currentToken() &&
        (parser->currentToken()->type == Token::TOKEN_PIPE_PIPE
        || parser->currentToken()->type == Token::TOKEN_APERSAND_AMPERSAND)
    ) {
        AST* bn = new ASTBinaryExpression();
        static_cast<ASTBinaryExpression*>(bn)->bin_exp_left_operand = root;
        switch(parser->currentToken()->type) {
            case Token::TOKEN_PIPE_PIPE: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_OR; break;
            case Token::TOKEN_APERSAND_AMPERSAND: static_cast<ASTBinaryExpression*>(bn)->bin_exp_op = BinaryOp::BINARY_OP_AND; break;
            default: printf("Error parsing Boolean operation! \n"); exit(-1); break;
        }
        parser->readToken(parser->currentToken()->type);
        static_cast<ASTBinaryExpression*>(bn)->bin_exp_right_operand = parseBooleans(parser, constant);
        root = bn;
    }
    printf("~BOOL\n");

    return root;
}

// BITWISE → BOOL (( '&' | '|' | '^'  ) BITWISE)*
AST* parseBitwise(Parser* parser, bool constant) {
    printf("BITWISE %s\n", parser->currentToken()->value);

    AST* root = parseComparison(parser, constant);

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
    printf("~BITWISE\n");

    return root;
}

// COMPARISON → SHIFT (( '>' | '>=' | '<' | '<='  ) COMPARISON)*
AST* parseComparison(Parser* parser, bool constant) {
    printf("COMPARISON %s\n", parser->currentToken()->value);

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
    printf("~COMPARISON\n");

    return root;
}

// SHIFT → TERM (( '>>' | '<<'  ) COMPARISON)*
AST* parseBitwiseShift(Parser* parser, bool constant) {
    printf("SHIFT %s\n", parser->currentToken()->value);

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
    printf("~SHIFT\n");

    return root;
}


// TERM → FACTOR (('+' | '-') TERM)*
AST* parseTerm(Parser* parser, bool constant) {
    printf("TERM %s\n", parser->currentToken()->value);

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
    printf("~TERM\n");

    return root;
}

// FACTOR → UNARY (('/' | '*' | '%' ) FACTOR)*
AST* parseFactor(Parser* parser, bool constant) {
    printf("FACTOR %s\n", parser->currentToken()->value);

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
    printf("~FACTOR\n");

    return root;
}

// UNARY → ('!' | '-' | '+' | '++' | '--' | '~' )UNARY | UNARY('++' | '--') | CALL
AST* parseUnary(Parser* parser, bool constant) {
    printf("UNARY %s\n", parser->currentToken()->value);

    int a;
    AST* root = nullptr;
    while(
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
            break;
        case Token::TOKEN_PLUS: parser->readToken(Token::TOKEN_PLUS); break; // does nothing
        case Token::TOKEN_MINUS:
            parser->readToken(Token::TOKEN_MINUS);
            root = new ASTUnaryExpression();
            static_cast<ASTUnaryExpression*>(root)->un_exp_operator = UnaryOp::UNARY_OP_NEGATIVE;
            break;
        case Token::TOKEN_PLUS_PLUS:
            parser->readToken(Token::TOKEN_PLUS_PLUS);
            root = new ASTUnaryExpression();
            static_cast<ASTUnaryExpression*>(root)->un_exp_operator = UnaryOp::UNARY_OP_PRE_INCREMENT;
            break;
        case Token::TOKEN_MINUS_MINUS:
            parser->readToken(Token::TOKEN_MINUS_MINUS);
            root = new ASTUnaryExpression();
            static_cast<ASTUnaryExpression*>(root)->un_exp_operator = UnaryOp::UNARY_OP_PRE_DECREMENT;
            break;
        case Token::TOKEN_TIL:
            parser->readToken(Token::TOKEN_TIL);
            root = new ASTUnaryExpression();
            static_cast<ASTUnaryExpression*>(root)->un_exp_operator = UnaryOp::UNARY_OP_LOGICAL_NOT;
            break;
        }
    }

    if(root) {
        static_cast<ASTUnaryExpression*>(root)->un_exp_operand = parseUnary(parser, constant);
        AST* un = nullptr;
        while(
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
    } else {
        root = parseArrayAccess(parser, constant);

    }
    printf("~UNARY\n");

    return root;
}

AST* parseArrayAccess(Parser* parser, bool constant) {
    printf("ARRAY %s\n", parser->currentToken()->value);

    AST* root = parseMemberAccess(parser, constant);

    while(parser->currentToken() && parser->currentToken()->type == Token::TOKEN_POINT) {
        ASTArrayAccess* access = new ASTArrayAccess();
        parser->readToken(Token::TOKEN_OPEN_SQUARE_BRACKETS);
        access->member_left = root;
        access->arra_index = parseExpression(parser, constant);
        access->member_right = parseMemberAccess(parser, constant);
        parser->readToken(Token::TOKEN_CLOSE_SQUARE_BRACKETS);
        root = access;
    }
    printf("~ARRAY\n");

    return root;
}

AST* parseMemberAccess(Parser* parser, bool constant) {
    printf("MEMBER %s\n", parser->currentToken()->value);

    AST* root = parseCall(parser, constant);
    while(parser->currentToken() && parser->currentToken()->type == Token::TOKEN_POINT) {
        parser->readToken(Token::TOKEN_POINT);
        ASTMemberAccess* access = new ASTMemberAccess();
        access->member_left = root;
        access->member_right = parseMemberAccess(parser, constant);
        root = access;
    }
    printf("~ARRAY\n");

    return root;
}

constexpr int func() {
    return 4;
}
// CALL → PRIMARY('('ARGUMENTS?')')?
AST* parseCall(Parser* parser, bool constant) {
    printf("CALL %s\n", parser->currentToken()->value);

    AST* root = parsePrimary(parser, constant);


    if(parser->currentToken() && parser->currentToken()->type == Token::TOKEN_OPEN_PARENTESIS) {
        if(root->ast_type != NodeType::NODE_TYPE_SYMBOL) {
            printf("Unexpected function name at line %i\n", parser->currentToken()->line);
        }


        ASTFunctionCall* func_call = new ASTFunctionCall();
        func_call->func_call_symbol = root;
        func_call->constexp = constant;
    
        parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
        if(parser->currentToken() && parser->currentToken()->type != Token::TOKEN_CLOSE_PARENTESIS) {
            func_call->func_call_arguments.push_back(parseExpression(parser, constant));
            while(parser->currentToken() && parser->currentToken()->type == Token::TOKEN_COMMA) {
                parser->readToken(Token::TOKEN_COMMA);
                func_call->func_call_arguments.push_back(parseExpression(parser, constant));
            }
        }
        parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
        root = func_call;
    } else {
        if(root->ast_type == NodeType::NODE_TYPE_SYMBOL && constant) {
            printf("Cant use variables in constant expression at line '%i'!\n", parser->currentToken()->line);
        }
    }
    printf("~CALL\n");

    return root;
}

// PRIMARY → LITERAL | SYMBOL | '('EXPRESSION')'
AST* parsePrimary(Parser* parser, bool constant) {
    printf("PRIMARY %s\n", parser->currentToken()->value);

    if(parser->currentToken() && parser->currentToken()->type == Token::TOKEN_OPEN_PARENTESIS) {
        parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
        AST* expression = parseExpression(parser, constant);
        parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);

        printf("~PRIMARY\n");
        return expression;
    }

    if(parser->currentToken() && parser->currentToken()->type == Token::TOKEN_IDENTIFIER) {
        char* identifier = parser->currentToken()->value;
        parser->readToken(Token::TOKEN_IDENTIFIER);
        ASTSymbol* symbol = new ASTSymbol();
        symbol->symbol_name = identifier;
        printf("~PRIMARY\n");
        return symbol;
    }

    printf("~PRIMARY\n");
    return parseLiteral(parser);
}

}