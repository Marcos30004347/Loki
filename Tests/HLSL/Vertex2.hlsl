float4x4 view_proj_matrix;
float4 view_position;
float4 light0;
float4 light1;
float4 light2;
struct VS_OUTPUT
{
 float4 Pos : POSITION;
 float3 View : TEXCOORD0;
 float3 Normal: TEXCOORD1;
 float3 Light1: TEXCOORD2;
 float3 Light2: TEXCOORD3;
 float3 Light3: TEXCOORD4;
};
VS_OUTPUT main( float4 inPos : POSITION,
 float3 inNorm : NORMAL )
{
 VS_OUTPUT Out = (VS_OUTPUT) 0;
 // Output transformed vertex position:
 Out.Pos = mul( view_proj_matrix, inPos );
 Out.Normal = inNorm;
 // Compute the view vector:
 Out.View = normalize( view_position - inPos );
 // Compute vectors to three lights from the current vertex position:
 Out.Light1 = normalize (light0 - inPos); // Light 1
 Out.Light2 = normalize (light1 - inPos); // Light 2
 Out.Light3 = normalize (light2 - inPos); // Light 3
 return Out;
} 