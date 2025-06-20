#include <ywlibx>
using namespace yw;

/// triangle
vector4<float> triangle[] = {
  {-0.5f, -0.5f, 0.f, 1.f},
  {0.5f, -0.5f, 0.f, 1.f},
  {0.f, 0.5f, 0.f, 1.f}
};

/// hlsl source code
strview hlsl = R"(
#pragma matrix(row_major)
struct SR0 {
  float4 pos : SV_Position;
};
StructuredBuffer<SR0> sb0 : register(t0);
struct PSIN {
  float4 pos : SV_Position;
  float4 color : COLOR;
};
void vsmain(uint id : SV_VertexID, out PSIN psin) {
  psin.pos = sb0[id].pos;
  psin.color = float4(1.f, 0.f, 0.f, 1.f);
}
void psmain(PSIN psin, out float4 color : SV_Target) {
  color = psin.color;
}
)";

/// hlsl for compute shader
strview hlsl_compute = R"(
#pragma matrix(row_major)
struct SB0 {
  float r, g, b, a;
};
struct UB0 {
  float value;
};
StructuredBuffer<SB0> sb0 : register(t0);
RWStructuredBuffer<UB0> ub0 : register(u0);
[numthreads(1024, 1, 1)]
void csmain(uint i : SV_DispatchThreadID) {
  UB0 uav;
  ub0[i].value = (sb0[i].r + sb0[i].g + sb0[i].b + sb0[i].a) / 4;
}
)";

int main::main() {
  array<vector4<float>> inputs(1024 * 1024);
  for (auto& i : inputs) for (auto& j : i) {
    // 乱数
    j = std::rand() / (float)RAND_MAX;
  }
  // gpu buffers
  structured_buffer sb0(inputs);
  rw_structured_buffer<float> ub0(sb0.count);
  compute_shader cs(hlsl_compute);
  cs.set_resource(sb0);
  cs.set_readwrite(ub0);
  cs.dispatch(1024, 1024);

  auto result = ub0.to_cpu();
  for (int i{}; i < 20; ++i) {
    auto r = (inputs[i].x + inputs[i].y + inputs[i].z + inputs[i].w) / 4;
    print("average({}, {}, {}, {}) -> {} = {}", inputs[i].x, inputs[i].y, inputs[i].z, inputs[i].w, result[i], r);
  }
  main::show();
  color c;
  while (main::update()) {
    if (key::lbutton.down()) {
      c = color::red;
    } else c = color::green;
    main::draw(c);
  }

  return 0;
}
