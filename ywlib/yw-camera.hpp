#pragma once
#include <yw-buffer.hpp>

namespace yw {

class camera : public canvas {
protected:
  constant_buffer<tuple<xmatrix, xmatrix>> cb;
public:
  vector4<float> position{}, rotation{}, offset{};
  float factor      = 1.0f;
  bool orthographic = false;
  camera() noexcept = default;
  explicit camera(canvas&& c) : canvas(mv(c)) {}
  explicit camera(arithmetic auto Width, arithmetic auto Height, arithmetic auto Msaa = 8, const source& _ = {})
    : canvas(Width, Height, Msaa, _) {}
  const constant_buffer<tuple<xmatrix, xmatrix>>& update(const source& _ = {}) {
    if (!cb) cb = constant_buffer<tuple<xmatrix, xmatrix>>();
    constexpr float f = 1048576.0f, n = 0.25f;
    D3D11_MAPPED_SUBRESOURCE mapped;
    auto hr = main::sys::d3d_context->Map(cb.operator->(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
    if (hr != 0) throw std::runtime_error(format("error {:x}: {} <- {}", hr, source{}, _));
    auto& [v, vp] = *(tuple<xmatrix, xmatrix>*)mapped.pData;
    xvview(position, rotation, offset, v);
    if (orthographic) {
      auto a = xvset(2.0f * factor / bitmap::width, 2.0f * factor / bitmap::height, 1.0f / (f - n), n / (f - n));
      vp[0] = v[0] * xvpermute<0, 0, 0, 0>(a), vp[1] = v[1] * xvpermute<1, 1, 1, 1>(a);
      vp[2] = v[2] * xvpermute<2, 2, 2, 2>(a) - xvsetzero<1, 1, 1, 0>(a), vp[3] = v[3];
    } else {
      auto a = xvset((-factor * height) / width, factor, f / (f - n), -f * n / (f - n));
      vp[0] = v[0] * xvpermute<0, 0, 0, 0>(a), vp[1] = v[1] * xvpermute<1, 1, 1, 1>(a);
      vp[2] = v[2] * xvpermute<2, 2, 2, 2>(a) + xvsetzero<1, 1, 1, 0>(a), vp[3] = v[2];
    }
    main::sys::d3d_context->Unmap(cb.operator->(), 0);
    return cb;
  }
};
}
