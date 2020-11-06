#ifndef EVALUATOR
#define EVALUATOR

#include "AST.hpp"

struct Context {
    char* name;
    AST* declarations;
};
Context* initContext(AST* context_node);

struct Export {
    enum Type {
        EXPORT_NONE,
        VERTEX_SHADER,
        PIXEL_SHADER,
    };

    // EXPORT
    Type type;
    char* main;
    char* context;
};

Export* initExport(AST* export_node);


struct Evaluation {
    // EXPORTS
    Export** exports;
    unsigned int exports_count;
    
    // CONTEXTS
    Context** contexts;
    unsigned int contexts_count;
};

Evaluation* initEvaluator();

Context* findExportContext(Evaluation* eval, Export* exp);
void evaluate(Evaluation* eval, AST* tree);


#endif
