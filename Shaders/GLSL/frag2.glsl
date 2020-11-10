#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

const vec3 BG_COLOR = vec3(.2, .2, .2);
const vec3 BOX_COLOR = vec3(.3, .6, .2);

vec3 forward = vec3(0., -0.5, 1.);
vec3 up = vec3(0., 1., 0.);
vec3 pos = vec3(0.0, 1.5, -5.);
vec3 side = cross(forward, up);
vec3 L = normalize(vec3(0, 5, -0.3));

vec3 mul(vec3 v, vec4 q) {
  return v + 2.0 * cross(q.xyz, cross(q.xyz, v) + q.w * v);
}
void rotate(out vec3 v, vec3 axis, float angle) {
  vec4 q = vec4(axis.x * sin(angle / 2.0), axis.y * sin(angle / 2.0),
                axis.z * sin(angle / 2.0), cos(angle / 2.0));
  v = mul(v, q);
}

float sdBox(vec3 p) {
  rotate(p, normalize(vec3(0.0, sin(time * .3), cos(time * .3))),
         radians(time * 30.));
  vec3 box_size = vec3(1.8, 1.8, 1.8);
  vec3 q = abs(p) - box_size;
  return length(max(q, 0.0)) + min(max(q.x, max(q.y, q.z)), 0.0) - .3;
}

vec3 normal(vec3 p) {
  float d = 0.001;
  vec3 dx = vec3(d, .0, .0);
  vec3 dy = vec3(.0, d, .0);
  vec3 dz = vec3(.0, .0, d);
  return normalize(vec3(sdBox(p + dx) - sdBox(p - dx),
                        sdBox(p + dy) - sdBox(p - dy),
                        sdBox(p + dz) - sdBox(p - dz)));
}

float mandelbrot(vec2 p) {
  float cnt = 0.0;
  vec2 z = vec2(.0, .0);
  p.x -= 0.7;

  for (int i = 0; i < 100; ++i) {
    cnt += 1.0;
    if (length(z) > 2.0)
      return 0.0;
    z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + p * .6;
  }
  return cnt / 100.0;
}

void check(in vec3 pos, in vec3 ray, out float min_dist, out float len,
           out vec3 now) {
  now = pos;
  min_dist = sdBox(now);
  len = 0.0;
  for (int i = 0; i < 50; ++i) {
    now = pos + ray * len;
    min_dist = sdBox(now);
    if (min_dist < 0.01)
      break;
    len += min_dist;
  }
}

float tex3D(vec3 p, vec3 n) {
  vec3 blending = abs(n);
  float b = (blending.x + blending.y + blending.z);
  blending /= b;

  float xaxis = mandelbrot(p.yz);
  float yaxis = mandelbrot(p.xz);
  float zaxis = mandelbrot(p.xy);

  return xaxis * blending.x + yaxis * blending.y + zaxis * blending.z;
}

void main() {
  vec2 p = (gl_FragCoord.xy * 2. - resolution) / resolution.y;
  vec3 ray = normalize(p.x * side + p.y * up + forward);

  float d, len;
  vec3 now;
  check(pos, ray, d, len, now);

  vec3 N = normal(now);
  rotate(now, normalize(vec3(0.0, sin(time * .3), cos(time * .3))),
         radians(time * 30.));
  vec3 V = -ray;
  vec3 H = normalize(V + L);
  vec3 ambient = BG_COLOR * 0.7;
  float diffuse = 1.5 * dot(N, L);
  float specular = 0.3 * pow(clamp(dot(N, H), 0.0, 1.0), 80.);

  if (d < 0.01)
    gl_FragColor = vec4(vec3(ambient + BOX_COLOR * diffuse + specular) *
                            (1.0 - tex3D(now, N)),
                        1.0);
  else
    gl_FragColor = vec4(BG_COLOR, 1.0);
}