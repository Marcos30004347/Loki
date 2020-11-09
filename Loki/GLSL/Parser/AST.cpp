#include<stdio.h>

#include "AST.hpp"


#define TABS 1

namespace GLSL {

const char* program_names[] {
    "mesh shader",
    "vertex shader",
    "geometry shader",
    "tesselation shader",
    "compute shader",
    "pixel shader"
};


void AST::print(int tabs) {
}

}