/**
layout-qualifier :
    layout ( layout-qualifier-id-list )
layout-qualifier-id-list :
    layout-qualifier-id
    layout-qualifier-id , layout-qualifier-id-list
layout-qualifier-id :
    layout-qualifier-name
    layout-qualifier-name = layout-qualifier-value
    shared
**/

#include "AST.hpp"
#include "Parser.hpp"

namespace GLSL {

enum QualifierName {
    SHARED,
    PACKED,
    STD140,
    STD430,
    ROW_MAJOR,
    COLUMN_MAJOR,
    BINDING,
    OFFSET,
    ALLIGN,
    LOCATION,
    LOCATION,
    COMPONENT,
    INDEX,
    TRIANGLES,
    QUADS,
    ISOLINES,
    EQUAL_SPACING,
    FRACTIONAL_EVEN_SPACING,
    FRACTIONAL_ODD_SPACING,
    CW,
    CCW,
    POINT_MODE,
    POINTS,
    LINES,
    LINES_ADJACENCY,
    TRIANGLES,
    TRIANGLES_ADJACENCY,
    INVOCATIONS,
    ORIGIN_UPPER_LEFT,
    PIXEL_CENTER_INTEGER,
    EARLY_FRAGMENT_TESTS,
    LOCAL_SIZE_X,
    LOCAL_SIZE_Y,
    LOCAL_SIZE_Z,
    XFB_BUFFER,
    XFB_STRIDE,
    XFB_OFFSET,
    VERTICES,
    LINE_STRIP,
    TRIANGLE_STRIP,
    MAX_VERTICES,
    STREAM,
    DEPH_ANY,
    DEPH_GREATER,
    DEPH_LESS,
    DEPH_UNCHANGED,
};
 
struct LayoutQualifier {
    char* qualifier;
    AST* qualifier_contant_expression;
};

struct ASTLayout: AST {
    explicit ASTLayout();
    std::vector<LayoutQualifier*> qualifiers;
};

ASTLayout* parseLayoutQualifier(Parser* parser);

}