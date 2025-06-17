#pragma once
#include <ywlib>

namespace yw::main {

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

/// smart pointer for COM objects
template<typename Com> class comptr {
  comptr(const comptr&)            = delete;
  comptr& operator=(const comptr&) = delete;
  Com* p                           = nullptr;
public:
  operator Com*() const { return p; }
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

/// smart pointer for D3D11 device
inline comptr<ID3D11Device> d3d_device{};
/// smart pointer for D3D11 device context
inline comptr<ID3D11DeviceContext> d3d_context = [](comptr<ID3D11DeviceContext> p) -> comptr<ID3D11DeviceContext> {
  const D3D_FEATURE_LEVEL levels[]{D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_11_1};
  auto hr = ::D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0x20, levels, 2, 7, &d3d_device.get(), 0, &p.get());
  if (hr != 0) ::MessageBoxW(nullptr, L"Failed to create D3D11 device and context", L"Fatal Error", 0);
  return p;
}({});

/// smart pointer for DXGI device
inline comptr<IDXGIDevice2> dxgi_device = [](comptr<IDXGIDevice2> p) -> comptr<IDXGIDevice2> {
  auto hr = d3d_device->QueryInterface(&p.get());
  if (hr != 0) ::MessageBoxW(nullptr, L"Failed to create DXGI device", L"Fatal Error", 0);
  return p;
}({});

/// smart pointer for D2D1 factory
inline comptr<ID2D1Factory1> d2d_factory = [](comptr<ID2D1Factory1> p) -> comptr<ID2D1Factory1> {
  auto hr = ::D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory1), nullptr, (void**)&p.get());
  if (hr != 0) ::MessageBoxW(nullptr, L"Failed to create D2D1 factory", L"Fatal Error", 0);
  return p;
}({});

/// smart pointer for D2D1 device
inline comptr<ID2D1Device> d2d_device = [](comptr<ID2D1Device> p) -> comptr<ID2D1Device> {
  auto hr = d2d_factory->CreateDevice(dxgi_device.get(), &p.get());
  if (hr != 0) ::MessageBoxW(nullptr, L"Failed to create D2D1 device", L"Fatal Error", 0);
  return p;
}({});

/// smart pointer for D2D1 device context
inline comptr<ID2D1DeviceContext> d2d_context = [](comptr<ID2D1DeviceContext> p) -> comptr<ID2D1DeviceContext> {
  auto hr = d2d_device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &p.get());
  if (hr != 0) ::MessageBoxW(nullptr, L"Failed to create D2D1 device context", L"Fatal Error", 0);
  return p;
}({});

/// smart pointer for DWrite factory
inline comptr<IDWriteFactory1> dw_factory = [](comptr<IDWriteFactory1> p) -> comptr<IDWriteFactory1> {
  auto hr = ::DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory1), (IUnknown**)&p.get());
  if (hr != 0) ::MessageBoxW(nullptr, L"Failed to create DWrite factory", L"Fatal Error", 0);
  return p;
}({});

/// smart pointer for WIC imaging factory
inline comptr<IWICImagingFactory2> wic_factory = [](comptr<IWICImagingFactory2> p) -> comptr<IWICImagingFactory2> {
  constexpr GUID wic_factory_guid{
    0x317d06e8, 0x5f24, 0x433d, {0xbd, 0xf7, 0x79, 0xce, 0x68, 0xd8, 0xab, 0xc2}
  };
  auto hr = ::CoCreateInstance(wic_factory_guid, nullptr, 1, __uuidof(IWICImagingFactory2), (void**)&p.get());
  if (hr != 0) ::MessageBoxW(nullptr, L"Failed to create WIC imaging factory", L"Fatal Error", 0);
  return p;
}({});
}
