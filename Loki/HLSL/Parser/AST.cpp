#include<stdio.h>

#include "AST.hpp"

#include "Buffer.hpp"
#include "Struct.hpp"
#include "Block.hpp"
#include "Expressions.hpp"
#include "Functions.hpp"
#include "Variables.hpp"
#include "Statement.hpp"
#include "FlowControl.hpp"

#define TABS 3

namespace HLSL {

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
};

const char* unary_op_names[] = {
    "-x",       // -x
    "+x",       // +x
    "!x",            // !x
    "++x",   // ++x
    "--x",   // --x
    "x++",  // x++
    "x--",  // x--
    "~x" // ~x
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

void AST::print(int tabs) {
    ASTProgram* program;
    ASTVarDecl* var_decl;
    ASTFunctionDeclaration* func_decl;
    ASTFunctionCall* func_call;
    ASTStruct* struct_decl;
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

    switch(this->ast_type) {
    case AST_PROGRAM:
        program = static_cast<ASTProgram*>(this);
        printf("%*cPROGRAM\n", tabs, ' ');
        printf("%*cSTATEMENTS COUNT %lu\n", tabs, ' ', program->program_declarations.size());
        printf("%*cMAIN %s\n", tabs, ' ', program->program_main);
        printf("%*cTYPE %s\n", tabs, ' ', program_names[program->program_type]);
        for(int i=0; i<program->program_declarations.size(); i++) {program->program_declarations[i]->print(tabs+TABS);}
        break;
    case AST_VARIABLE_DECLARATION:
        var_decl = static_cast<ASTVarDecl*>(this);
        printf("%*cVARIABLE DECLARATION\n", tabs, ' ');
        printf("%*cNAME %s\n", tabs, ' ', var_decl->var_decl_name);
        printf("%*cTYPE %s\n", tabs, ' ', var_decl->var_decl_type->type_name);
        if(var_decl->var_decl_is_array)
        printf("%*cIS_ARRAY %i\n", tabs, ' ', var_decl->var_decl_is_array);
        if(var_decl->var_decl_register) {
            printf("%*cREGISTER TYPE %c\n", tabs, ' ', var_decl->var_decl_register->register_type);
            printf("%*cREGISTER NAME %i\n", tabs, ' ', var_decl->var_decl_register->register_number);
            if(var_decl->var_decl_register->register_has_subcomponent)
            printf("%*cREGISTER SUBCOMPONENT %i\n", tabs, ' ', var_decl->var_decl_register->register_subcomponent);
            printf("%*cREGISTER PROFILE %i\n", tabs, ' ', var_decl->var_decl_register->register_profile);
        }
        if(var_decl->var_decl_storage_class)
        printf("%*cSTORAGE CLASS %i\n", tabs, ' ', var_decl->var_decl_storage_class);
        if(var_decl->var_decl_type_modifier)
        printf("%*cTYPE MODIFIER %i\n", tabs, ' ', var_decl->var_decl_type_modifier);
        if(var_decl->var_decl_is_array) {
            printf("%*cARRAY SIZE:\n", tabs, ' ');
            var_decl->var_decl_array_size->print(tabs+TABS);
        }
        if(var_decl->var_decl_pack_offset) {
            printf("%*cPACK OFFSET COMPONENT %i\n", tabs, ' ', var_decl->var_decl_pack_offset->pack_ofsset_component);
            printf("%*cPACK OFFSET SUBCOMPONENT %i\n", tabs, ' ', var_decl->var_decl_pack_offset->pack_offset_sumcomponent);
        }
        if(var_decl->var_decl_semantic) {
            printf("%*cSEMANTIC %s\n", tabs, ' ', var_decl->var_decl_semantic->name);
        }
        if(var_decl->var_decl_default_value) {
            printf("%*cVALUE:\n", tabs, ' ');
            var_decl->var_decl_default_value->print(tabs+TABS);
        }
        break;
    case AST_FUNCTION_DECLARATION: 
        func_decl = static_cast<ASTFunctionDeclaration*>(this);
        printf("%*cFUNCTION DECLARATION\n", tabs, ' ');
        printf("%*cNAME '%s'\n", tabs, ' ', func_decl->func_decl_name);
        printf("%*cTYPE '%s'\n", tabs, ' ', func_decl->func_decl_return_type->type_name);
        if(func_decl->func_decl_semantic)
            printf("%*cSEMANTIC %s\n", tabs, ' ', func_decl->func_decl_semantic->name);

        printf("%*cSTORAGE CLASS %i\n", tabs, ' ', func_decl->func_decl_storage_class);
        for(int i=0; i<func_decl->func_decl_attributes.size(); i++) {
            printf("%*cATTRIBUTE%i NAME = '%s'\n", tabs, ' ', i, func_decl->func_decl_attributes[i]->name);
            for(int j=0; j<func_decl->func_decl_attributes[i]->paramenters.size(); j++) {
                printf("%*cATTRIBUTE%i ARGUMENT%i:\n", tabs, ' ', i, j);
                func_decl->func_decl_attributes[i]->paramenters[j]->print(tabs+TABS);
            }
        }
        
        for(int i=0; i<func_decl->func_decl_arguments.size(); i++) {
            printf("%*cARGUMENT%i TYPE = '%s'\n", tabs, ' ', i, func_decl->func_decl_arguments[i]->argument_type->type_name);
            printf("%*cARGUMENT%i NAME = '%s'\n", tabs, ' ', i, func_decl->func_decl_arguments[i]->argument_name);
            if(func_decl->func_decl_arguments[i]->argument_semantic)
                printf("%*cARGUMENT%i SEMANTIC = '%s'\n", tabs, ' ', i, func_decl->func_decl_arguments[i]->argument_semantic->name);

            printf("%*cARGUMENT%i INTERPOLATION MODIFIER = '%i'\n", tabs, ' ', i, func_decl->func_decl_arguments[i]->argument_interpolation_modifier);
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
    case AST_STRUCT_DECLARATION: 
        struct_decl = static_cast<ASTStruct*>(this);
        printf("%*cSTRUCT DECLARATION\n", tabs, ' ');
        printf("%*cNAME %s\n", tabs, ' ', struct_decl->struct_identifier);
        for(int i=0; i<struct_decl->struct_members.size(); i++) {
            printf("%*cSTRUCT MEMBER%i\n", tabs, ' ', i);
            printf("%*cINTERPOLATION%i  %i\n", tabs, ' ', i, struct_decl->struct_members[i]->member_interpolation_modifier);
            struct_decl->struct_members[i]->struct_member_variable->print(tabs+TABS);
        }
        break;
    case AST_BUFFER_DECLARATION: 
        printf("%*cBUFFER DECLARATION\n", tabs, ' ');
        buffer_decl = static_cast<ASTBuffer*>(this);
        printf("%*cNAME %s\n", tabs, ' ', buffer_decl->buffer_name);
        if(buffer_decl->buffer_register) {
            printf("%*cREGISTER TYPE %c\n", tabs, ' ', buffer_decl->buffer_register->register_type);
            printf("%*cREGISTER NAME %i\n", tabs, ' ', buffer_decl->buffer_register->register_number);
            if(buffer_decl->buffer_register->register_has_subcomponent)
            printf("%*cREGISTER SUBCOMPONENT %i\n", tabs, ' ', buffer_decl->buffer_register->register_subcomponent);
            printf("%*cREGISTER PROFILE %i\n", tabs, ' ', buffer_decl->buffer_register->register_profile);
        }
        for(int i=0; i<buffer_decl->buffer_fields.size(); i++) {
            printf("%*cBUFFER MEMBER%i\n", tabs, ' ', i);
            buffer_decl->buffer_fields[i]->print(tabs+TABS);
        }
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
        if(literal->is_initialization_list) {
            printf("%*cCONSTRUCTOR\n", tabs, ' ');
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

}