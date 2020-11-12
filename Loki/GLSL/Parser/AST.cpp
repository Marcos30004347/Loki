#include<stdio.h>

#include "AST.hpp"

#include "Buffer.hpp"
#include "Structs.hpp"
#include "Block.hpp"
#include "Expressions.hpp"
#include "Declarations.hpp"
#include "Statement.hpp"
#include "FlowControl.hpp"

#define TABS 3

namespace GLSL {

const char* program_names[] {
    "mesh shader",
    "vertex shader",
    "geometry shader",
    "tesselation shader",
    "compute shader",
    "pixel shader"
};




const char* binary_op_names[] {
    "&&",
    "||",
    "+",
    "-",
    "*",
    "/",
    "<",
    ">",
    "<=",
    ">=",
    "==",
    "!=",
    "%",
    "&",
    "|",
    "^",
    "<<",
    ">>",
    "^^",
};

const char* unary_op_names[] = {
    "-",       // -x
    "+",       // +x
    "!",            // !x
    "++",   // ++x
    "--",   // --x
    "++",  // x++
    "--",  // x--
    "~" // ~x
};

const char* assignment_op_names[] = {
    "=", // =
    "*=", // *=
    "+=", // +=
    "-=", // -=
    "/=", // /=
    "^=", // ^/
    "|=", // |=
    "&=", // &=
    "<<=", // <<=
    ">>=", // >>=
    "%=", // %=
};


const char* storage_qualifiers_names[] = {
    "",
    "in",
    "path in",
    "const",
    "inout",
    "out",
    "uniform",
    "path",
    "path out",
    "buffer",
    "shared",
    "coherent",
    "volatile",
    "restrict",
    "readonly",
    "attribute",
    "varying",
    "writeonly",
    "subroutine",
};


const char* precision_qualifier_names[] = {
    "",
    "lowp",
    "mediump",
    "highp",
};

const char* interpolation_modifier_names[] = {
    " ",
    "linear",
    "centroid",
    "nointerpolation",
    "sample",
};
const char* type_modifier_names[] = {
    " ",
    "const",
    "row_major",
    "column_major",
};

const char* function_modifier_names[] = {
    " ",
    "in",
    "inout",
    "out",
    "uniform",
};


void AST::print(int tabs) {
    ASTProgram* program;
    ASTVarDecl* var_decl;
    ASTFunctionDeclaration* func_decl;
    ASTFunctionCall* func_call;
    // ASTStruct* struct_decl;
    ASTBuffer* buffer_decl;
    ASTAssignment* assignment;
    ASTBinaryExpression* exp;
    ASTUnaryExpression* uexp;
    ASTBlock* block;
    ASTReturn* return_sttmnt;
    ASTSymbol* symbol;
    ASTLiteral* literal;
    ASTCase* case_sttmnt;
    ASTSwitch* switch_sttmnt;
    ASTFor* for_sttmnt;
    ASTWhile* while_sttmnt;
    ASTDoWhile* do_while_sttmnt;
    ASTDefault* default_sttmnt;
    ASTIf* if_sttmnt;
    ASTMemberAccess* member_access;
    ASTArrayAccess* array_access;
    ASTType* type;
    ASTTypeDecl* type_decl;

    switch(this->ast_type) {
    case AST_PROGRAM:
        program = static_cast<ASTProgram*>(this);
        printf("%*cPROGRAM\n", tabs, ' ');
        printf("%*cSTATEMENTS COUNT %lu\n", tabs, ' ', program->program_declarations.size());
        printf("%*cMAIN %s\n", tabs, ' ', program->program_main);
        printf("%*cTYPE %s\n", tabs, ' ', program_names[program->program_type]);
        for(int i=0; i<program->program_declarations.size(); i++) {program->program_declarations[i]->print(tabs+TABS);}
        break;
    case AST_TYPE_DECL:
        type_decl = static_cast<ASTTypeDecl*>(this);
        printf("%*cTYPE '%s'\n", tabs, ' ', type_decl->type_name);
        break;
    case AST_TYPE:
        type = static_cast<ASTType*>(this);
        type->type->print(tabs+TABS);
        printf("%*cTYPE DIMENSIONS%li\n", tabs, ' ',type->dimensions.size());
        printf("%*cTYPE %s\n", tabs, ' ',type->type->type_name);
        for(int i=0; i<type->dimensions.size(); i++) {
            type->dimensions[i]->print(tabs+TABS);
        }
        break;
    case AST_VARIABLE_DECLARATION:
        var_decl = static_cast<ASTVarDecl*>(this);
        printf("%*cVARIABLE DECLARATION\n", tabs, ' ');
        printf("%*cNAME %s\n", tabs, ' ', var_decl->name);
        var_decl->var_decl_type->print(tabs+TABS);

        break;
    case AST_FUNCTION_DECLARATION: 
        func_decl = static_cast<ASTFunctionDeclaration*>(this);
        printf("%*cFUNCTION DECLARATION\n", tabs, ' ');
        printf("%*cNAME '%s'\n", tabs, ' ', func_decl->func_decl_name);
        func_decl->func_decl_return_type->print(tabs+TABS);

        
        for(int i=0; i<func_decl->func_decl_arguments.size(); i++) {
            func_decl->func_decl_arguments[i]->argument_type->print(tabs+TABS);
            if(func_decl->func_decl_arguments[i]->argument_name)
            printf("%*cARGUMENT%i NAME = '%s'\n", tabs, ' ', i, func_decl->func_decl_arguments[i]->argument_name);

          
            if(func_decl->func_decl_arguments[i]->argument_initializer)
                func_decl->func_decl_arguments[i]->argument_initializer->print(tabs+TABS);
        }
        printf("%*cBODY\n", tabs, ' ');

        func_decl->func_decl_body->print(tabs+TABS);
        break;

    case AST_FUNCTION_CALL: 
        printf("%*cFUNCTION CALL\n", tabs, ' ');
        func_call = static_cast<ASTFunctionCall*>(this);
        printf("%*cSYMBOL:\n", tabs, ' ');
        printf("%*cIS BUILT IN: '%i'\n", tabs, ' ', func_call->func_call_is_build_in);
        func_call->func_call_symbol->print(tabs+TABS);
        for(int i=0; i<func_call->func_call_arguments.size(); i++) {
            printf("%*cARGUMENT%i\n", tabs, ' ', i);
            func_call->func_call_arguments[i]->print(tabs+TABS);
        }
        break;
    // case AST_STRUCT_DECLARATION: 
    //     struct_decl = static_cast<ASTStruct*>(this);
    //     printf("%*cSTRUCT DECLARATION\n", tabs, ' ');
    //     printf("%*cNAME %s\n", tabs, ' ', struct_decl->struct_identifier);
    //     for(int i=0; i<struct_decl->struct_members.size(); i++) {
    //         // printf("%*cSTRUCT MEMBER%i\n", tabs, ' ', i);
    //         // printf("%*cINTERPOLATION%i  %i\n", tabs, ' ', i, struct_decl->struct_members[i]->member_interpolation_modifier);
    //         struct_decl->struct_members[i]->print(tabs+TABS);
    //     }
    //     break;
    case AST_BUFFER_DECLARATION: 
        printf("%*cBUFFER DECLARATION\n", tabs, ' ');
        buffer_decl = static_cast<ASTBuffer*>(this);

        break;
    case AST_ASSIGNMENT: 
        printf("%*cASSIGNMENT\n", tabs, ' ');
        assignment = static_cast<ASTAssignment*>(this);
        printf("%*cOPERATION %s\n",  tabs, ' ', assignment_op_names[assignment->assignment_op]);
        printf("%*cLEFT\n", tabs, ' ');
        assignment->assignment_left_operand->print(tabs+TABS);
        printf("%*cRIGHT\n", tabs, ' ');
        assignment->assignment_right_operand->print(tabs+TABS);
        break;
    case AST_EXPRESSION_BINARY: 
        printf("%*cBINARY EXPRESSION\n", tabs, ' ');
        exp = static_cast<ASTBinaryExpression*>(this);
        printf("%*cOPERATION %s\n", tabs, ' ', binary_op_names[exp->bin_exp_op]);
        printf("%*cLEFT\n",tabs, ' ');
        exp->bin_exp_left_operand->print(tabs+TABS);
        printf("%*cRIGHT\n",tabs, ' ');
        exp->bin_exp_right_operand->print(tabs+TABS);
        break;
    case AST_EXPRESSION_UNARY: 
        printf("%*cUNARY EXPRESSION\n", tabs, ' ');
        uexp = static_cast<ASTUnaryExpression*>(this);
        printf("%*cOPERATION %s\n", tabs, ' ', unary_op_names[uexp->un_exp_operator]);
        printf("%*cOPERAND\n", tabs, ' ');
        uexp->un_exp_operand->print(tabs+TABS);
        break;
    case AST_BLOCK: 
        printf("%*cBLOCK\n", tabs, ' ');
        block = static_cast<ASTBlock*>(this);
        printf("%*cSTETEMENTS:\n", tabs, ' ');
        for(int i=0; i<block->block_statements.size(); i++) block->block_statements[i]->print(tabs+TABS);
        break;
    case AST_RETURN_STATEMENT: 
        printf("%*cRETURN\n", tabs, ' ');
        return_sttmnt = static_cast<ASTReturn*>(this);
        if(return_sttmnt->return_expression){
            printf("%*cVALUE\n", tabs, ' ');
            return_sttmnt->return_expression->print(tabs+TABS);
        }
        break;
    case AST_SYMBOL: 
        symbol = static_cast<ASTSymbol*>(this);
        printf("%*cSYMBOL: '%s'\n", tabs, ' ', symbol->symbol_name);
        break;
    case AST_LITERAL: 
        literal = static_cast<ASTLiteral*>(this);
        if(literal->is_constructor) {
            printf("%*cCONSTRUCTOR\n", tabs, ' ');
            printf("%*cNAME = '%s'\n", tabs, ' ', literal->constructor_name);
            for(int i=0; i<literal->list_values.size(); i++) {
                literal->list_values[i]->print(tabs+TABS);
            }
        }
        else if(literal->is_initialization_list) {
            printf("%*cLIST\n", tabs, ' ');
            for(int i=0; i<literal->list_values.size(); i++) {
                literal->list_values[i]->print(tabs+TABS);
            }
        } else {
            switch (literal->type) {
            case ASTLiteral::Type::LITERAL_INT:
                printf("%*cINT = %i\n", tabs, ' ', literal->int_val);
                break;
            case ASTLiteral::Type::LITERAL_FLOAT:
                printf("%*cFLOAT = %f\n", tabs, ' ', literal->float_val);
                break;
            case ASTLiteral::Type::LITERAL_STRING:
                printf("%*cSTRING = %s\n", tabs, ' ', literal->string_val);
                break;
            case ASTLiteral::Type::LITERAL_BOOL:
                printf("%*cBOOL = %s\n", tabs, ' ', literal->bool_val ? "true" : "false");
                break;
            default:
                break;
            }
        }
        break;
    case AST_DISCARD_STATEMENT:
        printf("%*cDISCARD\n", tabs, ' ');
        break;
    case AST_CONTINUE_STATEMENT:
        printf("%*cCONTINUE\n", tabs, ' ');
        break;
    case AST_BREAK_STATEMENT:
        printf("%*cBREAK\n", tabs, ' ');
        break;
    case AST_CASE_STATEMENT:
        case_sttmnt = static_cast<ASTCase*>(this);
        printf("%*cCASE\n", tabs, ' ');
        printf("%*cEXPRESSION\n", tabs, ' ');
        case_sttmnt->case_expression->print(tabs+TABS);
        printf("%*cSTATEMENTS\n", tabs, ' ');
        for(int i=0; i<case_sttmnt->case_statements.size(); i++) {
            case_sttmnt->case_statements[i]->print(tabs+TABS);
        }
        break;
    case AST_SWITCH_STATEMENT:
        printf("%*cSWTICH\n", tabs, ' ');
        switch_sttmnt = static_cast<ASTSwitch*>(this);
        printf("%*cEXPRESSION\n", tabs, ' ');
        switch_sttmnt->switch_expression->print(tabs+TABS);
        for(int i=0; i<switch_sttmnt->switch_case_statements.size(); i++) {
            switch_sttmnt->switch_case_statements[i]->print(tabs+TABS);
        }
        switch_sttmnt->swtich_default->print(tabs+TABS);
        break;
    case AST_FOR_STATEMENT:
        printf("%*cFOR\n", tabs, ' ');
        for_sttmnt = static_cast<ASTFor*>(this);
        printf("%*cFOR INIT\n", tabs, ' ');
        for_sttmnt->for_init_statement->print(tabs+TABS);
        printf("%*cFOR COND\n", tabs, ' ');
        for_sttmnt->for_cond_expression->print(tabs+TABS);
        printf("%*cFOR LOOP\n", tabs, ' ');
        for_sttmnt->for_loop_expression->print(tabs+TABS);
        printf("%*cFOR STATEMENTS\n", tabs, ' ');
        for_sttmnt->for_body_statement->print(tabs+TABS);
        break;
    case AST_WHILE_STATEMENT:
        printf("%*cWHILE\n", tabs, ' ');
        while_sttmnt = static_cast<ASTWhile*>(this);
        printf("%*cEXPRESSION\n", tabs, ' ');
        while_sttmnt->while_expression->print(tabs+TABS);
        printf("%*cSTATEMENTS\n", tabs, ' ');
        while_sttmnt->while_statement->print(tabs+TABS);
        break;
    case AST_DO_WHILE_STATEMENT:
        printf("%*cDO\n", tabs, ' ');
        do_while_sttmnt = static_cast<ASTDoWhile*>(this);
        printf("%*cSTATEMENT\n", tabs, ' ');
        do_while_sttmnt->do_while_statement->print(tabs+TABS);
        printf("%*cDO WHILE EXPRESSION\n", tabs, ' ');
        do_while_sttmnt->do_while_expression->print(tabs+TABS);
        break;
    case AST_DEFAULT_STATEMENT:
        printf("%*cDEFAULT\n", tabs, ' ');
        default_sttmnt = static_cast<ASTDefault*>(this);
        for(int i=0; i<default_sttmnt->default_statements.size(); i++) {
            default_sttmnt->default_statements[i]->print(tabs+TABS);
        }
        break;
    case AST_IF_STATEMENT:
        printf("%*cIF\n", tabs, ' ');
        if_sttmnt = static_cast<ASTIf*>(this);
        printf("%*cEXPRESSION:\n", tabs, ' ');
        if_sttmnt->if_expression->print(tabs+TABS);
        printf("%*cSTATEMENT:\n", tabs, ' ');
        if_sttmnt->if_statement->print(tabs+TABS);
        if(if_sttmnt->if_else) {
            printf("%*cELSE:\n", tabs, ' ');
            if_sttmnt->if_else->print(tabs+TABS);
        }
        break;
    case AST_MEMBER_ACCESS:
        member_access = static_cast<ASTMemberAccess*>(this);
        printf("%*cMEMBER ACCESS\n", tabs, ' ');
        printf("%*cLEFT\n", tabs, ' ');
        member_access->member_left->print(tabs+TABS);
        printf("%*cRIGHT\n", tabs, ' ');
        member_access->member_right->print(tabs+TABS);
    break;
    case AST_ARRAY_ACCESS:
        array_access = static_cast<ASTArrayAccess*>(this);
        printf("%*cARRAY ACCESS\n", tabs, ' ');
        printf("%*cINDEX:\n", tabs, ' ');
        array_access->arra_index->print(tabs+TABS);
    break;
    }
}



const char* hlsl_header = "/**\n"
"* GLSL Shader Transpiled by Loki(https://github.com/Marcos30004347/Loki).\n"
"*/\n";


void writeASTProgram(AST* tree, int tabs = 0) {
    printf("%s\n", hlsl_header);
    ASTProgram* root = static_cast<ASTProgram*>(tree);
    for(int i=0; i<root->program_declarations.size(); i++) {
        switch (root->program_declarations[i]->ast_type) {
        case AST_VARIABLE_DECLARATION:
            root->program_declarations[i]->write(tabs);
            printf(";\n");
            break;
        case AST_TYPE_DECL:
            root->program_declarations[i]->write(tabs);
            printf(";\n");
            break;
        default:
            root->program_declarations[i]->write(tabs);
            break;
        }
    }
}

void writeASTType(AST* tree, int tabs = 0) {
    ASTType* root = static_cast<ASTType*>(tree);
    root->type->write(tabs);
}

void writeLayoutQualifier(AST* tree, int tabs = 0) {
    ASTLayout* root = static_cast<ASTLayout*>(tree);
    printf("layout(");
    for(int i=0; i<root->qualifiers.size(); i++) {
        root->write();
        if(i< root->qualifiers.size() -1) printf(", ");
    }
    printf(")");
}

void writeASTTypeDecl(AST* tree, int tabs = 0) {
    ASTTypeDecl* root = static_cast<ASTTypeDecl*>(tree);
    if(root->is_struct) {
        printf("struct ");
        if(root->type_name) printf("%s", root->type_name);
        printf("\n{\n");

        for(int i=0; i<root->members.size(); i++) {
            root->members[i]->write();
            printf(";");
            if(i < root->members.size() -1 ) printf("\n");
        }

        printf("\n}");
    } else {
        printf("%s", root->type_name);
    }
}



void writeStorageQualifier(AST* tree, int tabs = 0) {
    ASTStorageQualifiers* qualifier = static_cast<ASTStorageQualifiers*>(tree);
    if(!qualifier->type) return;
    printf("%s", storage_qualifiers_names[qualifier->type]);
    if(qualifier->type_name_list.size()) {
        printf("<");
        for(int i = 0; i< qualifier->type_name_list.size(); i++) {
            qualifier->type_name_list[i]->write();
            if(i < qualifier->type_name_list.size() - 1) printf(",");
        }
        printf(">");
    }
    printf(" ");
}

void writeASTVarDecl(AST* tree, int tabs = 0) {
    ASTVarDecl* root = static_cast<ASTVarDecl*>(tree);

    if(root->is_build_in) return;
    if(root->layout) root->layout->write();
    root->storage_qualifier->write();

    if(root->precision_qualifier)
        printf("%s ", precision_qualifier_names[root->precision_qualifier]);

    for(int i = 0; i< root->interpolation_qualifiers.size(); i++) {
        if(root->interpolation_qualifiers[i])
        printf("%s ", interpolation_modifier_names[root->interpolation_qualifiers[i]]);
    }
    
    root->var_decl_type->write(tabs);
    printf(" ");
    printf("%s", root->name);

    if(root->var_decl_type->isArray()) {
        for(int i=0;i<root->var_decl_type->dimensions.size(); i++) {
            printf("[");
            if(root->var_decl_type->dimensions[i])
                root->var_decl_type->dimensions[i]->write(tabs);
            printf("]");
        }
    }

    if(root->default_value) {
        printf(" = ");
        root->default_value->write(tabs);
    }
}

void writeASTFunctionDeclaration(AST* tree, int tabs = 0) {
    ASTFunctionDeclaration* root = static_cast<ASTFunctionDeclaration*>(tree);
    root->func_decl_return_type->write(tabs);
    printf(" %s(", root->func_decl_name);
    for(int j=0; j<root->func_decl_arguments.size(); j++) {
    
        if(root->func_decl_arguments[j]->argument_modifier) {
            root->func_decl_arguments[j]->argument_modifier->write();
        }
    
        root->func_decl_arguments[j]->argument_type->write(tabs);

        if(root->func_decl_arguments[j]->argument_name) {
            printf(" %s", root->func_decl_arguments[j]->argument_name);
        }

        if(root->func_decl_arguments[j]->argument_initializer)
            root->func_decl_arguments[j]->argument_initializer->write(tabs);

        if(j < root->func_decl_arguments.size() - 1) printf(", ");
    }
    printf(")");
    if(root->func_decl_body)
    root->func_decl_body->write(tabs);
    else printf(";");
}

void writeASTBlock(AST* tree, int tabs = 0) {
    ASTBlock* root = static_cast<ASTBlock*>(tree);
    printf("\n{\n");
    for(int i=0; i<root->block_statements.size(); i++) {
        switch(root->block_statements[i]->ast_type) {
            case NodeType::AST_ASSIGNMENT:
            case NodeType::AST_EXPRESSION_BINARY:
            case NodeType::AST_EXPRESSION_UNARY:
            case NodeType::AST_VARIABLE_DECLARATION:
            root->block_statements[i]->write();
            printf(";\n");
            break;
            default:
            root->block_statements[i]->write();
            break;
        }
    }
    printf("}\n");
}

void writeASTFunctionCall(AST* tree, int tabs = 0) {
    ASTFunctionCall* root = static_cast<ASTFunctionCall*>(tree);
    root->func_call_symbol->write(tabs);
    printf("(");
    for(int i=0;i<root->func_call_arguments.size();i++) {
        root->func_call_arguments[i]->write(tabs);
        if(i < root->func_call_arguments.size() - 1) printf(", ");
    }
    printf(")");

}


void writeASTBuffer(AST* tree, int tabs = 0) {
    ASTBuffer* root = static_cast<ASTBuffer*>(tree);
    printf("Not writing buffers yet!\n");
    throw -1;
}
void writeASTAssignment(AST* tree, int tabs = 0) {
    ASTAssignment* root = static_cast<ASTAssignment*>(tree);
    root->assignment_left_operand->write(tabs);
    printf(" %s ", assignment_op_names[root->assignment_op]);
    root->assignment_right_operand->write(tabs);
}

void writeASTBinaryExpression(AST* tree, int tabs = 0) {
    ASTBinaryExpression* root = static_cast<ASTBinaryExpression*>(tree);
    printf("(");
    root->bin_exp_left_operand->write(tabs);
    printf("%s", binary_op_names[root->bin_exp_op]);
    root->bin_exp_right_operand->write(tabs);
    printf(")");
}

void writeASTUnaryExpression(AST* tree, int tabs = 0) {
    ASTUnaryExpression* root = static_cast<ASTUnaryExpression*>(tree);

    printf("(");
    switch (root->un_exp_operator) {
        case UnaryOp::UNARY_OP_POST_INCREMENT:
        case UnaryOp::UNARY_OP_POST_DECREMENT:
            root->un_exp_operand->write(tabs);
            printf("%s", unary_op_names[root->un_exp_operator]);
            break;
        default:
            printf("%s", unary_op_names[root->un_exp_operator]);
            root->un_exp_operand->write(tabs);
    }
    printf(")");
}

void writeASTReturn(AST* tree, int tabs = 0) {
    ASTReturn* root = static_cast<ASTReturn*>(tree);
    printf("return ");
    if(root->return_expression) root->return_expression->write(tabs);
    printf(";\n");
}
void writeASTBreak(AST* tree, int tabs = 0) {
    ASTBreak* root = static_cast<ASTBreak*>(tree);
    printf("break;\n");
}
void writeASTDiscard(AST* tree, int tabs = 0) {
    ASTDiscard* root = static_cast<ASTDiscard*>(tree);
    printf("discard;\n");
}
void writeASTContinue(AST* tree, int tabs = 0) {
    ASTContinue* root = static_cast<ASTContinue*>(tree);
    printf("continue;\n");
}
void writeASTSymbol(AST* tree, int tabs = 0) {
    ASTSymbol* root = static_cast<ASTSymbol*>(tree);
    printf("%s", root->symbol_name);
}
void writeASTLiteral(AST* tree, int tabs = 0) {
    ASTLiteral* root = static_cast<ASTLiteral*>(tree);
    if(root->is_constructor) {
        printf("%s(", root->constructor_name);
        for(int i=0; i<root->list_values.size(); i++) {
            root->list_values[i]->write(tabs);
            if(i<root->list_values.size() - 1) printf(", ");
        }
        printf(")");
    } else
    if(root->is_initialization_list) {
        printf("{");
        for(int i=0; i<root->list_values.size(); i++) {
            root->list_values[i]->write(tabs);
            if(i<root->list_values.size() - 1) printf(", ");
        }
        printf("}");
    } else {
        switch (root->type) {
        case ASTLiteral::Type::LITERAL_INT:
            printf("%i", root->int_val);
            break;
        case ASTLiteral::Type::LITERAL_FLOAT:
            printf("%f", root->float_val);
            break;
        case ASTLiteral::Type::LITERAL_STRING:
            printf("%s\n", root->string_val);
            break;
        case ASTLiteral::Type::LITERAL_BOOL:
            printf("%s", root->bool_val ? "true" : "false");
            break;
        }
    }
}
void writeASTCase(AST* tree, int tabs = 0) {
    ASTCase* root = static_cast<ASTCase*>(tree);
    printf("case ");
    root->case_expression->write(tabs);
    printf(":\n");
    for(int i=0;i<root->case_statements.size(); i++) {
        root->case_statements[i]->write(tabs+TABS);
    }
}

void writeASTSwitch(AST* tree, int tabs = 0) {
    ASTSwitch* root = static_cast<ASTSwitch*>(tree);
    printf("switch(");
    root->switch_expression->write(tabs);
    printf(")\n{\n");
    for(int i=0; i<root->switch_case_statements.size(); i++)
        root->switch_case_statements[i]->write(tabs+TABS);
    root->swtich_default->write(tabs+TABS);
    printf("\n}\n");

}

void writeASTFor(AST* tree, int tabs = 0) {
    ASTFor* root = static_cast<ASTFor*>(tree);
    printf("for(");
    root->for_init_statement->write(false);
    printf("; ");
    root->for_cond_expression->write(false);
    printf("; ");
    root->for_loop_expression->write(false);
    root->for_body_statement->write(tabs+TABS);
}

void writeASTWhile(AST* tree, int tabs = 0) {
    ASTWhile* root = static_cast<ASTWhile*>(tree);
    printf("while(");
    root->while_expression->write(tabs);
    printf(")");
    root->while_statement->write(tabs+TABS);
}

void writeASTDoWhile(AST* tree, int tabs = 0) {
    ASTDoWhile* root = static_cast<ASTDoWhile*>(tree);
    printf("do");
    root->do_while_statement->write(tabs+TABS);
    printf("while(");
    root->do_while_expression->write(tabs);
    printf(");\n");

}
void writeASTDefault(AST* tree, int tabs = 0) {
    ASTDefault* root = static_cast<ASTDefault*>(tree);
    printf("default:\n");
    for(int i=0;i<root->default_statements.size(); i++) {
        root->default_statements[i]->write(tabs+TABS);
    }
}
void writeASTIf(AST* tree, int tabs = 0) {
    ASTIf* root = static_cast<ASTIf*>(tree);
    printf("if(");
    root->if_expression->write(tabs);
    printf(")");
    switch (root->if_statement->ast_type) {
        case AST_BLOCK:
            root->if_statement->write(tabs+TABS);
            break;
        default:
            root->if_statement->write(tabs+TABS);
            printf(";\n");
            break;
    }

    if(root->if_else) {
        printf("else ");
        root->if_else->write(tabs);
    }
}
void writeASTMemberAccess(AST* tree, int tabs = 0) {
    ASTMemberAccess* root = static_cast<ASTMemberAccess*>(tree);
    root->member_left->write(tabs);
    printf(".");
    root->member_right->write(tabs);
}
void writeASTArrayAccess(AST* tree, int tabs = 0) {
    ASTArrayAccess* root = static_cast<ASTArrayAccess*>(tree);
    printf("[");
    root->arra_index->write(tabs);
    printf("]");
}

void AST::write(bool semicollon) {
    switch(this->ast_type) {
    case AST_PROGRAM:
        writeASTProgram(this);
        break;
    case AST_TYPE:
        writeASTType(this);
        break;
    case AST_VARIABLE_DECLARATION:
        writeASTVarDecl(this);
        break;
    case AST_FUNCTION_DECLARATION: 
        writeASTFunctionDeclaration(this);
        break;
    case AST_FUNCTION_CALL: 
        writeASTFunctionCall(this);
        break;
    // case AST_STRUCT_DECLARATION: 
    //     writeASTStruct(this);
    //     break;
    case AST_BUFFER_DECLARATION: 
        writeASTBuffer(this);
        break;
    case AST_ASSIGNMENT: 
        writeASTAssignment(this);
        break;
    case AST_EXPRESSION_BINARY: 
        writeASTBinaryExpression(this);
        break;
    case AST_EXPRESSION_UNARY: 
        writeASTUnaryExpression(this);
        break;
    case AST_BLOCK: 
        writeASTBlock(this);
        break;
    case AST_RETURN_STATEMENT: 
        writeASTReturn(this);
        break;
    case AST_SYMBOL: 
        writeASTSymbol(this);
        break;
    case AST_LITERAL: 
        writeASTLiteral(this);
        break;
    case AST_DISCARD_STATEMENT:
        writeASTDiscard(this);
        break;
    case AST_CONTINUE_STATEMENT:
        writeASTContinue(this);
        break;
    case AST_BREAK_STATEMENT:
        writeASTBreak(this);
        break;
    case AST_CASE_STATEMENT:
        writeASTCase(this);
        break;
    case AST_SWITCH_STATEMENT:
        writeASTSwitch(this);
        break;
    case AST_FOR_STATEMENT:
        writeASTFor(this);
        break;
    case AST_WHILE_STATEMENT:
        writeASTWhile(this);
        break;
    case AST_DO_WHILE_STATEMENT:
        writeASTDoWhile(this);
        break;
    case AST_DEFAULT_STATEMENT:
        writeASTDefault(this);
        break;
    case AST_IF_STATEMENT:
        writeASTIf(this);
        break;
    case AST_MEMBER_ACCESS:
        writeASTMemberAccess(this);
        break;
    case AST_ARRAY_ACCESS:
        writeASTArrayAccess(this);
        break;
    case AST_TYPE_DECL:
        writeASTTypeDecl(this);
        break;
    case AST_STORAGE_QUALIFIER:
        writeStorageQualifier(this);
        break;
    case AST_LAYOUT_QUALIFIER:
        writeLayoutQualifier(this);
        break;
    }
}


}