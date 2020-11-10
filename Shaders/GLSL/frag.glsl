uniform float time;
uniform vec2 resolution;

float tri(float x) { return min(fract(x), 1. - fract(x)) * 4. - 1.; }
bool grid(vec2 p, float l, float h) {
    return (fract(p.x * 10.) < .1 || fract(p.y * 10.) < .1)
           && abs(p.x - .025) < 1.25 && p.y > l && p.y < h;
}

void main(void) {
    vec2 pos = (2. * gl_FragCoord.xy - resolution.xy )
             / min(resolution.x, resolution.y) + vec2(.0, .3);
    col = vec4(.5);
    float x = tri(time * .1) * 1.6;
    vec2 s = 2. * pos - vec2(x, 1.5 * abs(sin(time * 1.7)));
    if (length(s) < .85) {
        col = vec4(1.0, .0, 0., .0);
        s = s * mat2(.96, -.28, .28, .96) / sin(1.85 - length(s.xy)*1.4) + vec2(1. * x, 0.);
        if (fract(s.x * 1.2) < .5 ^^ fract(s.y * 1.2) < 0.5) col += 1.1;
    } else {
        if (grid(pos, -.3, 1.205)) col.g = 0.;
        pos = vec2(pos.x, 1.) / pos.y * -.3;
        if (grid(pos, .7, 1.)) col.g = 0.;
        if (length(s - vec2(.4, .1)) < .85) col /= 2.;
    }
}