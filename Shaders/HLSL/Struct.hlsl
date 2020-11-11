struct struct1 {
  int    a;
};

struct struct2 {
  int    a;
  float  b;
  int4x4 iMatrix;
};

struct In {
  centroid float2 Texcoord;
};

struct {int a; int b;} teste(int a) {
  return a;
}

struct Teste {
  float2 Texcoord;
} oi = { 3.4f };

struct {
  float2 Texcoord;
} teste = { 3.4f };

struct {
  float2 Texcoord;
}[10] teste;
