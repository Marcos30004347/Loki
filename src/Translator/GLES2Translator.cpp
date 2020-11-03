#include "GLES2Translator.hpp"
#include "Utils/Utils.hpp"

#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <cstdio>

const char* BuildInTypesIds[] = {
    "void",
    "int",
    "uint",
    "float",
    "bool",
    "vec2",
    "vec3",
    "vec4",
    "mat2",
    "mat2x2",
    "mat2x3",
    "mat2x4",
    "mat3",
    "mat3x2",
    "mat3x3",
    "mat3x4",
    "mat4",
    "mat4x2",
    "mat4x3",
    "mat4x4",
    "sampler",
    "sampler3d"
};

Shader* initShader(ShaderType type) {
    Shader* shader = (Shader*)malloc(sizeof(Shader));
    shader->attributes = nullptr;
    shader->attributes_count = 0;
    shader->functions = nullptr;
    shader->functions_count = 0;
    shader->uniforms = nullptr;
    shader->uniforms_count = 0;
    shader->shader_type = type;
    return shader;
}

char* append(const char* a, const char* b) {
    return strcat(copyString(a), copyString(b));
}

char* translateDeclarations(Shader* shader, AST* root) {
    char* declarations = copyString("");
    if(root->type == AST::ASTType::DECLARATIONS) {
        for(int i=0; i<root->declarations_list_count; i++) {
            switch(root->declarations_list[i]->type) {
                case AST::ASTType::FUNCTION_DECLARATION:
                    declarations = append(declarations, translateFunctionDeclaration(shader, root->declarations_list[i]));
                    break;
                case AST::ASTType::VARIABLES_DECLARATIONS:
                    declarations = append(declarations, translateVariableDeclarations(shader, root->declarations_list[i]));
                    break;
            }   
        }
    }
    return declarations;
}

char* translateFunctionDeclaration(Shader* shader, AST* root) {
    char* func_def = copyString("");

    func_def = append(func_def, BuildInTypesIds[root->func_dec_return_type]);
    func_def = append(func_def, translateIdentifier(shader, root->func_dec_identifier));
    func_def = append(func_def, "(");
    
    for(int i=0; i<root->func_dec_arguments_count;i++) {
        func_def = append(func_def, translateFunctionArgument(shader, root->func_dec_arguments[i]));
        if(i != root->func_dec_arguments_count - 1) func_def = append(func_def, ",");
    }

    func_def = append(func_def, ")");
    func_def = append(func_def, translateStatement(shader, root));
    return func_def;

}

char* translateFunctionArgument(Shader* shader, AST* root) {
    char* argument_def = copyString("");

    if(root->func_argument_channel->channel_type != ChannelType::CHANNEL_NONE) {
        // attribute qualifier
        if(root->func_argument_channel->channel_type != ChannelType::CHANNEL_IN) {
            if(shader->shader_type == ShaderType::VERTEX_SHADER) {
                argument_def = append(argument_def, "attribute ");
            } else {
                argument_def = append(argument_def, "in ");
            }
        }else if(root->func_argument_channel->channel_type != ChannelType::CHANNEL_OUT) {
            argument_def = append(argument_def, "out ");
        }

        argument_def = append(argument_def, BuildInTypesIds[root->func_argument_type]);
        argument_def = append(argument_def, translateIdentifier(shader, root->func_argument_id));
        argument_def = append(argument_def, ";\n");
        addShaderAttribute(shader, argument_def);
        return copyString("");
    }

    argument_def = append(argument_def, BuildInTypesIds[root->var_def_type]);
    argument_def = append(argument_def, translateIdentifier(shader, root->var_def_identifier));
    return argument_def;
}

char* translateBlock(Shader* shader, AST* root) {
    char* block_declaration = copyString("");
    block_declaration = append(block_declaration, "{\n");

    while (isASTStatement(root)) {
        block_declaration = append(block_declaration, translateStatement(shader, root));
        block_declaration = append(block_declaration, ";");
    }
    
    block_declaration = append(block_declaration, "}\n");
    return block_declaration;
}


char* translateVariableDeclarations(Shader* shader, AST* root) {
    char* variable_declarations = copyString("");

    for(int i=0; i<root->vars_declarations_count; i++) {
        variable_declarations = append(variable_declarations, translateVariableDeclaration(shader, root->vars_declarations[i]));
    }

    return variable_declarations;
}

char* translateVariableDeclaration(Shader* shader, AST* root) {
    char* variable_declaration = copyString("");

    if(root->var_def_channel->channel_type != ChannelType::CHANNEL_NONE) {
        // attribute qualifier
        if(root->var_def_channel->channel_type != ChannelType::CHANNEL_IN) {
            if(shader->shader_type == ShaderType::VERTEX_SHADER) {
                variable_declaration = append(variable_declaration, "attribute ");
            } else {
                variable_declaration = append(variable_declaration, "in ");
            }
        }else if(root->var_def_channel->channel_type != ChannelType::CHANNEL_OUT) {
            variable_declaration = append(variable_declaration, "out ");
        }
    
        variable_declaration = append(variable_declaration, BuildInTypesIds[root->var_def_type]);
        variable_declaration = append(variable_declaration, translateIdentifier(shader, root->var_def_identifier));
        variable_declaration = append(variable_declaration, ";\n");
        addShaderAttribute(shader, variable_declaration);
        return copyString("");
        // TODO: layout qualifier
    }

    variable_declaration = append(variable_declaration, BuildInTypesIds[root->var_def_type]);
    variable_declaration = append(variable_declaration, translateIdentifier(shader, root->var_def_identifier));
    variable_declaration = append(variable_declaration, "= ");
    variable_declaration = append(variable_declaration, translateExpression(shader, root->var_def_value));
    variable_declaration = append(variable_declaration, ";\n");
    return variable_declaration;
}

char* translateIdentifier(Shader* shader, AST* root) {
    return copyString(root->identifier);
}

char* translateExpression(Shader* shader, AST* root) {
    if(root->type == AST::ASTType::BINARY_EXPRESSION) {
        return copyString("BINARY EXPRESSION\n");
    }
    if(root->type == AST::ASTType::UNARY_EXPRESSION) {
        return copyString("UNARY EXPRESSION\n");
    }
    
    return copyString("");
}

char* translateIf(Shader* shader, AST* root){
    return copyString("IF");
}

char* translateFor(Shader* shader, AST* root) {
    return copyString("FOR");
}

char* translateDoWhile(Shader* shader, AST* root) {
    return copyString("DO_WHILE");
}

char* translateWhile(Shader* shader, AST* root) {
    return copyString("WHILE");
}

char* translateSwitch(Shader* shader, AST* root) {
    return copyString("SWITCH");
}

char* translateBreak(Shader* shader, AST* root) {
    return copyString("break");
}

char* translateInteger(Shader* shader, AST* root) {
    char str[10];
    sprintf(str, "%d", root->integer_value);
    return copyString(str);
}

char* translateFloat(Shader* shader, AST* root) {
    char str[10];
    sprintf(str, "%d", root->float_value);
    return copyString(str);
}

char* translateAssignment(Shader* shader, AST* root) {
    return copyString("ASSIGNMENT");
}

char* translateStatement(Shader* shader, AST* root) {
    if(root->type == AST::ASTType::BLOCK)               return translateBlock(shader, root);
    if(root->type == AST::ASTType::INTEGER)             return translateInteger(shader, root);
    if(root->type == AST::ASTType::FLOAT)               return translateFloat(shader, root);
    if(root->type == AST::ASTType::BREAK)               return translateBreak(shader, root);
    if(root->type == AST::ASTType::IF)                  return translateFor(shader, root);
    if(root->type == AST::ASTType::FOR)                 return translateFor(shader, root);
    if(root->type == AST::ASTType::DO_WHILE)            return translateDoWhile(shader, root);
    if(root->type == AST::ASTType::WHILE)               return translateWhile(shader, root);
    if(root->type == AST::ASTType::SWITCH)              return translateSwitch(shader, root);
    if(root->type == AST::ASTType::BINARY_EXPRESSION)   return translateExpression(shader, root);
    if(root->type == AST::ASTType::UNARY_EXPRESSION)    return translateExpression(shader, root);
    if(root->type == AST::ASTType::ASSIGNMENT)          return translateAssignment(shader, root);

    return copyString("UNKNOW STATEMENT");
}