float4 lightWood; // xyz == Light Wood Color
float4 darkWood; // xyz == Dark Wood Color
float ringFreq; // ring frequency

sampler PulseTrainSampler;

float4 hlsl_rings (float4 Pshade : TEXCOORD0) : COLOR {
 float scaledDistFromZAxis = sqrt(dot(Pshade.xy, Pshade.xy)) * ringFreq;
 float blendFactor = tex1D (PulseTrainSampler, scaledDistFromZAxis);

 return lerp (darkWood, lightWood, blendFactor);
} 