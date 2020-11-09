// struct VS_OUTPUT
// {
//     float4 Position   : SV_POSITION; 
//     float4 Diffuse    : COLOR0;
//     float2 TextureUV  : TEXCOORD0;
// };

// VS_OUTPUT RenderSceneVS( float4 vPos : POSITION,
//                          float3 vNormal : NORMAL,
//                          float2 vTexCoord0 : TEXCOORD,
//                          uniform int nNumLights,
//                          uniform bool bTexture,
//                          uniform bool bAnimate )
// {
//     VS_OUTPUT Output;
//     return Output;    
// }

struct PSSceneIn {

}

float4 PSPointSprite(PSSceneIn input) : SV_Target
{   
    return g_txDiffuse.Sample( g_samLinear, input.tex ) * input.color;
}

// [numthreads(16,16,1)]
// void CS(){
//     if(3 > 4) {
//         return 3;
//     } else if(4 > 5) {
//         return 4;
//     } else {
//         return 5;
//     }

//     switch(4) {
//         case 4:
//             return 4;
//             break;
//         case 6:
//             return 9;
//             break;
//         default:
//             return 9;
//     }

//     while(3) {
//         break;
//         return 4;
//     }

//     do {
//         continue;
//     } while(4);

//     for(int i=0; i<3; i++) {
//         discard;
//     }

// }