/**
* GLSL Shader Transpiled by Loki(https://github.com/Marcos30004347/Loki).
*/

uniform float time;
uniform vec2 resolution;

float tri(float x)
{
    return ((min(fract(x), (1.000000-fract(x)))*4.000000)-1.000000);
}
bool grid(vec2 p, float l, float h)
{
    return (((fract((p.x*10.000000))<0.100000)||(fract((p.y*10.000000))<0.100000))&&((abs((p.x-0.025000))<1.250000)&&((p.y>l)&&(p.y<h))));
}
void main(void)
{
    vec2 pos = ((((2.000000*gl_FragCoord.xy)-resolution.xy)/min(resolution.x, resolution.y))+vec2(0.000000, 0.300000));
    col = vec4(0.500000);
    float x = (tri((time*0.100000))*1.600000);
    vec2 s = ((2.000000*pos)-vec2(x, (1.500000*abs(sin((time*1.700000))))));
    if((length(s)<0.850000))
    {
        col = vec4(1.000000, 0.000000, 0.000000, 0.000000);
        s = ((s*(mat2(0.960000, (-0.280000), 0.280000, 0.960000)/sin((1.850000-(length(s.xy)*1.400000)))))+vec2((1.000000*x), 0.000000));
        if(((fract((s.x*1.200000))<0.500000)^^(fract((s.y*1.200000))<0.500000)))col += 1.100000;
    }
    else 
    {
        if(grid(pos, (-0.300000), 1.205000))col.g = 0.000000;
        pos = (vec2(pos.x, 1.000000)/(pos.y*(-0.300000)));
        if(grid(pos, 0.700000, 1.000000))col.g = 0.000000;
        if((length((s-vec2(0.400000, 0.100000)))<0.850000))col /= 2.000000;
    }
}