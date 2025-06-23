#pragma once
#include <yw-wmessage.hpp>
#include <ywlib>

namespace yw {

inline constexpr auto default_dxgi_format = DXGI_FORMAT_R8G8B8A8_UNORM;
inline constexpr GUID default_dxgi_format_guid = []() -> GUID { // clang-format off
  if constexpr (default_dxgi_format == DXGI_FORMAT_B8G8R8A8_UNORM) return WICPixelFormat32bppPBGRA;
  else if constexpr (default_dxgi_format == DXGI_FORMAT_R8G8B8A8_UNORM) return WICPixelFormat32bppPRGBA;
  else throw std::runtime_error("Unsupported default format");
}();

/// smart pointer for COM objects
template<typename Com> class comptr {
  operator Com*() &&               = delete;
  operator Com*() const&&          = delete;
  comptr(const comptr&)            = delete;
  comptr& operator=(const comptr&) = delete;
  Com* p{nullptr};
public:
  operator Com*() & { return p; }
  operator Com*() const& { return p; }
  explicit operator bool() const { return p != nullptr; }
  Com* operator->() const { return p; }
  bool operator==(Com* other) { return p == other; }
  ~comptr() { p ? p->Release(), p = nullptr : nullptr; }
  comptr() = default;
  comptr(comptr&& other) : p(exchange(other.p, nullptr)) {}
  comptr& operator=(comptr&& other) {
    if (this == &other) return *this;
    if (p) p->Release();
    p = exchange(other.p, nullptr);
    return *this;
  }
  Com*& get() { return p; }
  Com* const& get() const { return p; }
  void release() { p ? p->Release(), p = nullptr : nullptr; }
};

namespace main {

namespace sys {

/// class for `yw::main::cominit`
class ComInit {
  bool _bool{};
public:
  explicit operator bool() const { return _bool; }
  ~ComInit() noexcept { _bool ? ::CoUninitialize(), _bool = false : false; }
  ComInit() noexcept : _bool(0 == ::CoInitializeEx(nullptr, 2)) {}
};

/// object for initializing and uninitializing COM
inline const ComInit cominit{};

/// smart pointer for D3D11 device
inline comptr<::ID3D11Device> d3d_device{};

/// smart pointer for D3D11 device context
inline comptr<::ID3D11DeviceContext> d3d_context = [](comptr<::ID3D11DeviceContext> p) -> comptr<::ID3D11DeviceContext> {
  const D3D_FEATURE_LEVEL levels[]{D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_11_1};
  auto hr = ::D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0x20, levels, 2, 7, &d3d_device.get(), 0, &p.get());
  if (hr != 0) yw::ok(L"Failed to create D3D11 device and context", L"Fatal Error");
  else if (debug) print("Created D3D11 device and context");
  return p;
}({});

/// default blend state
inline auto d3d_blend_state = [](comptr<::ID3D11BlendState> p) -> comptr<::ID3D11BlendState> {
  D3D11_BLEND_DESC desc{};
  desc.AlphaToCoverageEnable = false;
  desc.IndependentBlendEnable = false;
  desc.RenderTarget[0].BlendEnable = true;
  desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
  desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
  desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
  desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
  desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
  desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
  desc.RenderTarget[0].RenderTargetWriteMask = 0xf;
  auto hr = d3d_device->CreateBlendState(&desc, &p.get());
  if (hr != 0) yw::ok(L"Failed to create D3D11 blend state", L"Fatal Error");
  d3d_context->OMSetBlendState(p.get(), nullptr, 0xffffffff);
  return p;
}({});

/// default rasterizer state
inline auto d3d_rasterizer_state = [](comptr<::ID3D11RasterizerState> p) -> comptr<::ID3D11RasterizerState> {
  D3D11_RASTERIZER_DESC desc{};
  desc.FillMode = D3D11_FILL_SOLID;
  desc.CullMode = D3D11_CULL_NONE;
  desc.FrontCounterClockwise = true;
  desc.DepthBias = 0;
  desc.DepthBiasClamp = 0.0f;
  desc.SlopeScaledDepthBias = 0.0f;
  desc.DepthClipEnable = true;
  desc.ScissorEnable = false;
  desc.MultisampleEnable = true;
  desc.AntialiasedLineEnable = true;
  auto hr = d3d_device->CreateRasterizerState(&desc, &p.get());
  if (hr != 0) yw::ok(L"Failed to create D3D11 rasterizer state", L"Fatal Error");
  d3d_context->RSSetState(p.get());
  return p;
}({});

/// default sampler state
inline auto d3d_sampler_state = [](comptr<::ID3D11SamplerState> p) -> comptr<::ID3D11SamplerState> {
  D3D11_SAMPLER_DESC desc{};
  desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
  desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
  desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
  desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
  desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
  desc.MaxLOD = FLT_MAX;
  auto hr = d3d_device->CreateSamplerState(&desc, &p.get());
  if (hr != 0) yw::ok(L"Failed to create D3D11 sampler state", L"Fatal Error");
  d3d_context->PSSetSamplers(0, 1, &p.get());
  return p;
}({});

/// smart pointer for DXGI factory
inline comptr<::IDXGIFactory2> dxgi_factory = [](comptr<::IDXGIFactory2> p) {
  auto hr = ::CreateDXGIFactory2(0, __uuidof(IDXGIFactory2), (void**)&p.get());
  if (hr != 0) ::MessageBoxW(nullptr, L"failed to create DXGI factory", L"Fatal Error", 0);
  return p;
}({});

/// smart pointer for DXGI device
inline comptr<::IDXGIDevice2> dxgi_device = [](comptr<::IDXGIDevice2> p) -> comptr<::IDXGIDevice2> {
  auto hr = d3d_device->QueryInterface(&p.get());
  if (hr != 0) yw::ok(L"Failed to create DXGI device", L"Fatal Error");
  return p;
}({});

/// smart pointer for D2D1 factory
inline comptr<::ID2D1Factory1> d2d_factory = [](comptr<::ID2D1Factory1> p) -> comptr<::ID2D1Factory1> {
  auto hr = ::D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory1), nullptr, (void**)&p.get());
  if (hr != 0) yw::ok(L"Failed to create D2D1 factory", L"Fatal Error");
  return p;
}({});

/// smart pointer for D2D1 device
inline comptr<::ID2D1Device> d2d_device = [](comptr<::ID2D1Device> p) -> comptr<::ID2D1Device> {
  auto hr = d2d_factory->CreateDevice(dxgi_device.get(), &p.get());
  if (hr != 0) yw::ok(L"Failed to create D2D1 device", L"Fatal Error");
  return p;
}({});

/// smart pointer for D2D1 device context
inline comptr<::ID2D1DeviceContext> d2d_context = [](comptr<::ID2D1DeviceContext> p) -> comptr<::ID2D1DeviceContext> {
  auto hr = d2d_device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &p.get());
  if (hr != 0) yw::ok(L"Failed to create D2D1 device context", L"Fatal Error");
  return p;
}({});

/// smart pointer for DWrite factory
inline comptr<::IDWriteFactory1> dw_factory = [](comptr<::IDWriteFactory1> p) -> comptr<::IDWriteFactory1> {
  auto hr = ::DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory1), (IUnknown**)&p.get());
  if (hr != 0) yw::ok(L"Failed to create DWrite factory", L"Fatal Error");
  return p;
}({});

/// smart pointer for WIC imaging factory
inline comptr<::IWICImagingFactory2> wic_factory = [](comptr<::IWICImagingFactory2> p) -> comptr<::IWICImagingFactory2> {
  constexpr GUID wic_factory_guid{
    0x317d06e8, 0x5f24, 0x433d, {0xbd, 0xf7, 0x79, 0xce, 0x68, 0xd8, 0xab, 0xc2}
  };
  auto hr = ::CoCreateInstance(wic_factory_guid, nullptr, 1, __uuidof(IWICImagingFactory2), (void**)&p.get());
  if (hr != 0) yw::ok(L"Failed to create WIC imaging factory", L"Fatal Error");
  return p;
}({});
}
}

/// class to represent a solid color brush
class brush {
  comptr<::ID2D1SolidColorBrush> d2d_blush;
public:
  static const brush black, white, red, yellow, green, blue;
  explicit operator bool() const noexcept { return d2d_blush.operator bool(); }
  ::ID2D1SolidColorBrush* operator->() const noexcept { return d2d_blush.get(); }
  brush() noexcept = default;
  /// initializes a brush with a color
  explicit brush(const yw::color& c, const source& _ = {}) {
    auto hr = main::sys::d2d_context->CreateSolidColorBrush(&c, nullptr, &d2d_blush.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
  }
  /// sets the brush color; or initializes with the color.
  void color(const yw::color& c) { operator bool() ? void(d2d_blush->SetColor(&c)) : void(*this = brush(c)); }
  /// gets the brush color
  yw::color color() const { return operator bool() ? bitcast<yw::color>(d2d_blush->GetColor()) : yw::color{}; }
};

inline const brush brush::black{color::black};
inline const brush brush::white{color::white};
inline const brush brush::red{color::red};
inline const brush brush::yellow{color::yellow};
inline const brush brush::green{color::green};
inline const brush brush::blue{color::blue};

/// class to represent a text format
class text_format {
  comptr<::IDWriteTextFormat> dw_text_format;
public:
  explicit operator bool() const noexcept { return dw_text_format.operator bool(); }
  ::IDWriteTextFormat* operator->() const noexcept { return dw_text_format.get(); }
  text_format() noexcept = default;
  template<stringable S> text_format(S&& Name, arithmetic auto Size, const source& _ = {}) {
    auto name = unicode<wchar_t>(static_cast<S&&>(Name));
    auto hr   = main::sys::dw_factory->CreateTextFormat(name.data(), nullptr, 400, 0, 5, float(Size), L"", &dw_text_format.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
    dw_text_format->SetTextAlignment(0);
  }
  /// sets the alignment of the text
  void set_alignment(int MinusZeroPlus) const noexcept {
    int alignment = int(MinusZeroPlus == 0) * 2 + int(MinusZeroPlus > 0);
    dw_text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT(alignment));
  }
};
}
