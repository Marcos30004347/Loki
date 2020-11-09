vec2 someVec;
vec4 otherVec = someVec.xyxx;
vec3 thirdVec = otherVec.zyy;
mat3 theMatrix;
uniform float myValues[12];
uniform sampler images[10];
uniform int imageCount;
uniform vec3 multidim[5][2];
uniform vec3[5][2] multidim;
layout(std430) buffer Buffer1
{
    vec3[][2] multidim; // legal
};

layout(std430) buffer Buffer2
{
    vec3[5][] multidim; // not legal
};

struct Light
{
  vec3 eyePosOrDir;
  bool isDirectional;
  vec3 intensity;
  float attenuation;
} variableName;