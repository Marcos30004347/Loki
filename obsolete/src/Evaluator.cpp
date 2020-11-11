#include "Evaluator.hpp"
#include "Utils.hpp"

#include <malloc.h>
#include <string.h>

Context* initContext(AST* context_node) {
    Context* ctx = (Context*)malloc(sizeof(Context));
    ctx->name = copyString(context_node->context_identifier->identifier);
    ctx->declarations = context_node->context_declarations;
    return ctx;
}


Export* initExport(AST* export_node){
    Export* exp = (Export*)malloc(sizeof(Export));
    exp->type = Export::Type::EXPORT_NONE;

    for(int i=0; i<export_node->export_pairs_count; i++) {
        if(strcmp("type", export_node->export_keys_identifiers[i]->identifier) == 0) {
            if(strcmp("vertex", export_node->export_values_identifiers[i]->identifier) == 0) 
                exp->type = Export::Type::VERTEX_SHADER;

            if(strcmp("pixel", export_node->export_values_identifiers[i]->identifier) == 0) 
                exp->type = Export::Type::PIXEL_SHADER;
        }
        else if(strcmp("main", export_node->export_keys_identifiers[i]->identifier) == 0) {
            exp->main = copyString(export_node->export_values_identifiers[i]->identifier);
        }
        else if(strcmp("context", export_node->export_keys_identifiers[i]->identifier) == 0) {
            exp->context = export_node->export_values_identifiers[i]->identifier;
        }
    }

    if(!exp->main) {
        printf("ERROR: no main exported!\n");
        exit(-1);
    }
    if(!exp->context) {
        printf("ERROR: no context exported!\n");
        exit(-1);
    }
    if(exp->type == Export::Type::EXPORT_NONE) {
        printf("ERROR: no type exported!\n");
        exit(-1);
    }
    return exp;
}

Evaluation* initEvaluator() {
    Evaluation* eval = (Evaluation*)malloc(sizeof(Evaluation));
    eval->contexts_count = 0;
    eval->contexts = nullptr;
    eval->exports_count = 0;
    eval->exports = nullptr;
    return eval;
}

void evaluate(Evaluation* eval, AST* tree) {
    for(int i=0; i<tree->declarations_list_count; i++) {
        switch(tree->ast_type) {
            case AST::ASTTypeDecl::CONTEXT:
                eval->contexts_count += + 1;
                eval->contexts = (Context**)realloc(
                    eval->contexts,
                    eval->contexts_count
                );
                eval->contexts[eval->contexts_count - 1] = initContext(tree->declarations_list[i]);
                break;
        
            case AST::ASTTypeDecl::EXPORT:
                eval->exports_count += + 1;
                eval->exports = (Export**)realloc(
                    eval->exports,
                    eval->exports_count
                );
                eval->exports[eval->exports_count - 1] = initExport(tree->declarations_list[i]);
                break;
            break;
        }
    }

    for(int i=0; i<eval->exports_count; i++) {
        if(findExportContext(eval, eval->exports[i]) == nullptr) {
            printf("Context exported didn't defined!\n");
        }
    }
}

Context* findExportContext(Evaluation* eval, Export* exp) {
    for(int j=0; j<eval->contexts_count; j++) {
        if(strcmp(exp->context, eval->contexts[j]->name) == 0) {
            return eval->contexts[j];
        }
    }
    return nullptr;
}