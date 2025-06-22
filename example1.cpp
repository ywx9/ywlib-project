#include <ywlibx>
using namespace yw;

int yw::main::main() {
  texture tex(R"(D:\OneDrive\sd-images\202506\22\172220-921829271487325.png)");
  print(source{});
  main::title("show image as texture");
  main::size(vector2<int>{tex.size.x / 2, tex.size.y / 2});
  main::show();

  /// two triangles to show the image
  tuple<vector4<float>, vector2<float>> vertices[] = {
    {vector4<float>{-1.0f, -1.0f, 0.1f, 1.0f}, vector2<float>{0.0f, 1.0f}}, // bottom left
    { vector4<float>{1.0f, -1.0f, 0.1f, 1.0f}, vector2<float>{1.0f, 1.0f}}, // bottom right
    { vector4<float>{-1.0f, 1.0f, 0.1f, 1.0f}, vector2<float>{0.0f, 0.0f}}, // top left
    {  vector4<float>{1.0f, 1.0f, 0.1f, 1.0f}, vector2<float>{1.0f, 0.0f}}  // top right
  };

  array indices{
    vector3<int>{0, 1, 2},
    vector3<int>{1, 3, 2}
  };

  strview hlsl = R"(#pragma pack_matrix(row_major)
Texture2D<float4> tex : register(t0);
struct SB1 { // vertices
  float4 v;
  float2 uv;
};
StructuredBuffer<SB1> sb1 : register(t1);
struct SB2 { // indices
  uint3 i;
};
StructuredBuffer<SB2> sb2 : register(t2);
SamplerState sampler0 : register(s0);
struct PSIN { // pixel shader input
  float4 pos : SV_POSITION;
  float2 tex : TEXCOORD0;
};
void vsmain(uint i : SV_VertexID, out PSIN psin) {
  SB1 vertex = sb1[sb2[i / 3].i[i % 3]]; // get vertex from structured buffer
  psin.pos = vertex.v; // get vertex position
  psin.tex = vertex.uv;
}
float4 psmain(PSIN psin) : SV_TARGET {
  // float4 temp = tex.Sample(sampler0, psin.tex);
  // return temp;
  return float4(1.0f, 0.0f, 0.0f, 0.5f);
}
)";

  main::sys::d2d_context->SetPrimitiveBlend(D2D1_PRIMITIVE_BLEND_SOURCE_OVER);

  structured_buffer sb1(vertices);
  structured_buffer sb2(indices);

  vertex_shader vs(hlsl);
  main::vs::shader(vs);
  main::vs::shader_resources(tex, sb1, sb2);
  pixel_shader ps(hlsl);
  main::ps::shader(ps);

  canvas cv(main::size);
  static_assert(constructible<canvas, decltype(main::size)>);
  {
    auto r = cv.render(color::transparent);
    r.as_trianglelist();
    r.run(6);
  }
  cv.to_file("example1.png");

  while (main::update()) {
    auto d = main::draw(color::black);
    d.bitmap(cv);
    // [&](vector2<int> Size) { d.bitmap(tex, vector4<float>{0.0f, 0.0f, float(Size.x), float(Size.y)}); }(main::size);
  }

  return 0;
}
