#pragma once
#include <yw-buffer.hpp>

namespace yw {

/// class to represent vertex shaders
class vertex_shader {
protected:
  comptr<::ID3D11VertexShader> d3d_vs{};
  /// compiles a vertex shader
  static void compile(strview Source, const char* Entry, const source& _, ::ID3D11VertexShader** Out) {
    comptr<::ID3D10Blob> blob, error;
    auto hr = ::D3DCompile(Source.data(), Source.size(), nullptr, nullptr, nullptr, Entry, "vs_5_0", 1 << 11, 0, &blob.get(), &error.get());
    if (hr != 0) throw std::runtime_error(format("error {:x}: {} <- {}\n{}", hr, Source, _, (char*)error->GetBufferPointer()));
    hr = main::sys::d3d_device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, Out);
    if (hr != 0) throw std::runtime_error(format("error {:x}: {} <- {}", hr, Source, _));
  }
public:
  /// checks if the shader is compiled
  explicit operator bool() const noexcept { return d3d_vs != nullptr; }
  ::ID3D11VertexShader* operator->() const noexcept { return d3d_vs.get(); }
  /// compiles a vertex shader
  template<stringable S> explicit vertex_shader(S&& Source, const char* Entry = "vsmain", const source& _ = {}) {
    auto source = unicode<char>(static_cast<S&&>(Source));
    compile(source, Entry, _, &d3d_vs.get());
  }
};

namespace main::vs {

/// sets a vertex shader
inline void shader(const vertex_shader& shader) { sys::d3d_context->VSSetShader(shader.operator->(), nullptr, 0); }

/// sets constant buffers
template<typename... Ts> requires(specialization_of<remove_cvref<Ts>, constant_buffer> && ...)
void constant_buffers(Ts&&... Buffers) {
  array<::ID3D11Buffer*, sizeof...(Ts)> buffers{Buffers.operator->()...};
  sys::d3d_context->VSSetConstantBuffers(0, sizeof...(Ts), buffers.data());
}

/// sets shader resources
template<typename... Ts> requires(requires(Ts&& ts) { { ts.operator->() } -> convertible_to<::ID3D11ShaderResourceView*>; } && ...)
void shader_resources(Ts&&... Resources) {
  array<::ID3D11ShaderResourceView*, sizeof...(Resources)> views{Resources.operator->()...};
  sys::d3d_context->VSSetShaderResources(0, sizeof...(Resources), views.data());
}
}

/// class to represent pixel shaders
class pixel_shader {
protected:
  comptr<::ID3D11PixelShader> d3d_ps{};
  /// compiles a pixel shader
  static void compile(strview Source, const char* Entry, const source& _, ::ID3D11PixelShader** Out) {
    comptr<::ID3D10Blob> blob, error;
    auto hr = ::D3DCompile(Source.data(), Source.size(), nullptr, nullptr, nullptr, Entry, "ps_5_0", 1 << 11, 0, &blob.get(), &error.get());
    if (hr != 0) throw std::runtime_error(format("error {:x}: {} <- {}\n{}", hr, Source, _, (char*)error->GetBufferPointer()));
    hr = main::sys::d3d_device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, Out);
    if (hr != 0) throw std::runtime_error(format("error {:x}: {} <- {}", hr, Source, _));
  }
public:
  /// checks if the shader is compiled
  explicit operator bool() const noexcept { return d3d_ps != nullptr; }
  ::ID3D11PixelShader* operator->() const noexcept { return d3d_ps.get(); }
  /// compiles a pixel shader
  template<stringable S> explicit pixel_shader(S&& Source, const char* Entry = "psmain", const source& _ = {}) {
    auto source = unicode<char>(static_cast<S&&>(Source));
    compile(source, Entry, _, &d3d_ps.get());
  }
};

namespace main::ps {

/// sets a pixel shader
inline void shader(const pixel_shader& shader) { sys::d3d_context->PSSetShader(shader.operator->(), nullptr, 0); }

/// sets constant buffers
template<typename... Ts> requires(specialization_of<remove_cvref<Ts>, constant_buffer> && ...)
void constant_buffers(Ts&&... Buffers) {
  array<::ID3D11Buffer*, sizeof...(Ts)> buffers{Buffers...};
  sys::d3d_context->PSSetConstantBuffers(0, sizeof...(Ts), buffers.data());
}

/// sets shader resources
template<typename... Ts> requires(requires(Ts&& ts) { { ts.operator->() } -> convertible_to<::ID3D11ShaderResourceView*>; } && ...)
void shader_resources(Ts&&... Resources) {
  array<::ID3D11ShaderResourceView*, sizeof...(Resources)> views{Resources...};
  sys::d3d_context->PSSetShaderResources(0, sizeof...(Resources), views.data());
}
}

/// class to represent geometry shaders
class geometry_shader {
protected:
  comptr<::ID3D11GeometryShader> d3d_gs{};
  /// compiles a geometry shader
  static void compile(strview Source, const char* Entry, const source& _, ::ID3D11GeometryShader** Out) {
    comptr<::ID3D10Blob> blob, error;
    auto hr = ::D3DCompile(Source.data(), Source.size(), nullptr, nullptr, nullptr, Entry, "gs_5_0", 1 << 11, 0, &blob.get(), &error.get());
    if (hr != 0) throw std::runtime_error(format("error {:x}: {} <- {}\n{}", hr, Source, _, (char*)error->GetBufferPointer()));
    hr = main::sys::d3d_device->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, Out);
    if (hr != 0) throw std::runtime_error(format("error {:x}: {} <- {}", hr, Source, _));
  }
public:
  /// checks if the shader is compiled
  explicit operator bool() const noexcept { return d3d_gs != nullptr; }
  ::ID3D11GeometryShader* operator->() const noexcept { return d3d_gs.get(); }
  /// compiles a geometry shader
  template<stringable S> explicit geometry_shader(S&& Source, const char* Entry = "gsmain", const source& _ = {}) {
    auto source = unicode<char>(static_cast<S&&>(Source));
    compile(source, Entry, _, &d3d_gs.get());
  }
};

namespace main::gs {

/// sets a geometry shader
inline void shader(const geometry_shader& shader) { sys::d3d_context->GSSetShader(shader.operator->(), nullptr, 0); }

/// sets constant buffers
template<typename... Ts> requires(specialization_of<remove_cvref<Ts>, constant_buffer> && ...)
void constant_buffers(Ts&&... Buffers) {
  array<::ID3D11Buffer*, sizeof...(Ts)> buffers{Buffers...};
  sys::d3d_context->GSSetConstantBuffers(0, sizeof...(Ts), buffers.data());
}

/// sets shader resources
template<typename... Ts> requires(requires(Ts&& ts) { { ts.operator->() } -> convertible_to<::ID3D11ShaderResourceView*>; } && ...)
void shader_resources(Ts&&... Resources) {
  array<::ID3D11ShaderResourceView*, sizeof...(Resources)> views{Resources...};
  sys::d3d_context->GSSetShaderResources(0, sizeof...(Resources), views.data());
}
}

/// class to represent compute shaders
class compute_shader {
protected:
  comptr<::ID3D11ComputeShader> d3d_cs{};
  /// compiles a compute shader
  static void compile(strview Source, const char* Entry, const source& _, ::ID3D11ComputeShader** Out) {
    comptr<::ID3D10Blob> blob, error;
    auto hr = ::D3DCompile(Source.data(), Source.size(), nullptr, nullptr, nullptr, Entry, "cs_5_0", 1 << 11, 0, &blob.get(), &error.get());
    if (hr != 0) throw std::runtime_error(format("error {:x}: {} <- {}\n{}", hr, Source, _, (char*)error->GetBufferPointer()));
    hr = main::sys::d3d_device->CreateComputeShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, Out);
    if (hr != 0) throw std::runtime_error(format("error {:x}: {} <- {}", hr, Source, _));
  }
public:
  /// checks if the shader is compiled
  explicit operator bool() const noexcept { return d3d_cs != nullptr; }
  ::ID3D11ComputeShader* operator->() const noexcept { return d3d_cs.get(); }
  /// compiles a compute shader
  template<stringable S> explicit compute_shader(S&& Source, const char* Entry = "csmain", const source& _ = {}) {
    auto source = unicode<char>(static_cast<S&&>(Source));
    compile(source, Entry, _, &d3d_cs.get());
  }
  /// sets shader resources
  template<typename... Ts> requires(requires(Ts&& ts) { { ts.operator->() } -> convertible_to<::ID3D11ShaderResourceView*>; } && ...)
  static void set_resource(Ts&&... Resources) {
    array<::ID3D11ShaderResourceView*, sizeof...(Resources)> views{Resources.operator->()...};
    main::sys::d3d_context->CSSetShaderResources(0, sizeof...(Resources), views.data());
  }
  /// sets read-write structured buffers
  template<typename... Ts> requires(requires(Ts&& ts) { { ts.operator->() } -> convertible_to<::ID3D11UnorderedAccessView*>; } && ...)
  static void set_readwrite(Ts&&... Resources) {
    array<::ID3D11UnorderedAccessView*, sizeof...(Resources)> views{Resources.operator->()...};
    main::sys::d3d_context->CSSetUnorderedAccessViews(0, sizeof...(Resources), views.data(), nullptr);
  }
  /// dispatches the compute shader
  void dispatch(castable_to<uint32_t> auto Parallel, const uint32_t NumThread = 1024) {
    main::sys::d3d_context->CSSetShader(d3d_cs.get(), nullptr, 0);
    main::sys::d3d_context->Dispatch((uint32_t(Parallel) + NumThread - 1) / NumThread, 1, 1);
  }
};
}
