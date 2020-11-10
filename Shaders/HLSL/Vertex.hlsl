float4x4 view_proj_matrix;
float4x4 texture_matrix0;

struct VS_OUTPUT {
    float4 Pos : POSITION;
    float3 Pshade : TEXCOORD0;
};

VS_OUTPUT main (float4 vPosition : POSITION) {
    VS_OUTPUT Out = (VS_OUTPUT) 0;
    Out.Pos = mul (view_proj_matrix, vPosition);
    Out.Pshade = mul (texture_matrix0, vPosition);
    return Out;
} 