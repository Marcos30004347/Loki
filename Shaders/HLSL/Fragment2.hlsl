float4 Material;
sampler Outline;

float4 main( float3 View: TEXCOORD0,
    float3 Normal: TEXCOORD1,
    float3 Light1: TEXCOORD2,
    float3 Light2: TEXCOORD3,
    float3 Light3: TEXCOORD4 ) : COLOR
{
    float3 norm = normalize (Normal);

    float4 outline = tex1D(Outline, 1 - dot (norm, normalize(View)));
    float lighting = (dot (normalize (Light1), norm) * 0.5 + 0.5) +
    (dot (normalize (Light2), norm) * 0.5 + 0.5) +
    (dot (normalize (Light3), norm) * 0.5 + 0.5);
    return outline * Material * lighting;
} 