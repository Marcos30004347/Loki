#include "LayoutQualifier.hpp"
#include "Expressions.hpp"

namespace GLSL {

ASTLayout::ASTLayout(): AST {AST_LAYOUT_QUALIFIER } {}

// LayoutQualifier* parseLayoutQualifier(Parser* parser) {
//     switch(parser->currentToken()->type) {

//     // case Token::TOKEN_SHARED:
//     // case Token::TOKEN_PACKED:
//     // case Token::TOKEN_STD140:
//     // case Token::TOKEN_STD430:
//     // case Token::TOKEN_ROW_MAJOR:
//     // case Token::TOKEN_COLUMN_MAJOR:
//     // case Token::TOKEN_BINDING:
//     // case Token::TOKEN_OFFSET:
//     // case Token::TOKEN_ALLIGN:
//     // case Token::TOKEN_LOCATION:
//     // case Token::TOKEN_LOCATION:
//     // case Token::TOKEN_COMPONENT:
//     // case Token::TOKEN_INDEX:
//     // case Token::TOKEN_TRIANGLES:
//     // case Token::TOKEN_QUADS:
//     // case Token::TOKEN_ISOLINES:
//     // case Token::TOKEN_EQUAL_SPACING:
//     // case Token::TOKEN_FRACTIONAL_EVEN_SPACING:
//     // case Token::TOKEN_FRACTIONAL_ODD_SPACING:
//     // case Token::TOKEN_CW:
//     // case Token::TOKEN_CCW:
//     // case Token::TOKEN_POINT_MODE:
//     // case Token::TOKEN_POINTS:
//     // case Token::TOKEN_LINES:
//     // case Token::TOKEN_LINES_ADJACENCY:
//     // case Token::TOKEN_TRIANGLES:
//     // case Token::TOKEN_TRIANGLES_ADJACENCY:
//     // case Token::TOKEN_INVOCATIONS:
//     // case Token::TOKEN_ORIGIN_UPPER_LEFT:
//     // case Token::TOKEN_PIXEL_CENTER_INTEGER:
//     // case Token::TOKEN_EARLY_FRAGMENT_TESTS:
//     // case Token::TOKEN_LOCAL_SIZE_X:
//     // case Token::TOKEN_LOCAL_SIZE_Y:
//     // case Token::TOKEN_LOCAL_SIZE_Z:
//     // case Token::TOKEN_XFB_BUFFER:
//     // case Token::TOKEN_XFB_STRIDE:
//     // case Token::TOKEN_XFB_OFFSET:
//     // case Token::TOKEN_VERTICES:
//     // case Token::TOKEN_LINE_STRIP:
//     // case Token::TOKEN_TRIANGLE_STRIP:
//     // case Token::TOKEN_MAX_VERTICES:
//     // case Token::TOKEN_STREAM:
//     // case Token::TOKEN_DEPH_ANY:
//     // case Token::TOKEN_DEPH_GREATER:
//     // case Token::TOKEN_DEPH_LESS:
//     // case Token::TOKEN_DEPH_UNCHANGED:

//     }
// }

ASTLayout* parseLayoutQualifier(Parser* parser) {
    ASTLayout* lay = new ASTLayout();
    if(parser->currentToken()->type != Token::TOKEN_LAYOUT) return nullptr;
    
    parser->readToken(Token::TOKEN_LAYOUT);
    parser->readToken(Token::TOKEN_OPEN_PARENTESIS);

    if(parser->currentToken()->type != Token::TOKEN_CLOSE_PARENTESIS) {
        LayoutQualifier* qualifier = new LayoutQualifier();
        qualifier->qualifier = parser->currentToken()->value;
        parser->readToken(parser->currentToken()->type);
        if(parser->currentToken()->type == Token::TOKEN_EQUAL) {
            parser->readToken(Token::TOKEN_EQUAL);
            qualifier->qualifier_contant_expression = parseExpression(parser, true);
        }
    
        lay->qualifiers.push_back(qualifier);
    
        while(parser->currentToken()->type == Token::TOKEN_COMMA) {
            parser->readToken(Token::TOKEN_COMMA);
            LayoutQualifier* qualifier = new LayoutQualifier();
            qualifier->qualifier = parser->currentToken()->value;
            parser->readToken(parser->currentToken()->type);
            if(parser->currentToken()->type == Token::TOKEN_EQUAL) {
                parser->readToken(Token::TOKEN_EQUAL);
                qualifier->qualifier_contant_expression = parseExpression(parser, true);
            }
            lay->qualifiers.push_back(qualifier);
        }
    }
    parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
    
    return lay;
}

}