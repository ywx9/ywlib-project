#pragma once
#include <yw-wmessage.hpp>
#include <ywlib>

namespace yw {

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

/// class to represent a bitmap for 2D drawing
class bitmap {
protected:
  static constexpr auto pixel_format      = D2D1_PIXEL_FORMAT{DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED};
  static constexpr auto bitmap_properties = D2D1_BITMAP_PROPERTIES1{pixel_format, 96.f, 96.f, D2D1_BITMAP_OPTIONS_TARGET, nullptr};
  comptr<::ID2D1Bitmap1> d2d_bitmap;
public:
  class drawing {
    inline static ::ID2D1Bitmap1* _bitmap = nullptr;
    drawing(const drawing&)               = delete;
    drawing& operator=(const drawing&)    = delete;
  public:
    explicit operator bool() const noexcept { return bool(_bitmap); }
    ~drawing() { _bitmap ? void((_bitmap = nullptr, main::sys::d2d_context->EndDraw())) : void(); }
    /// begins drawing on the bitmap
    drawing(::ID2D1Bitmap1* b, const source& _ = {}) {
      if (_bitmap) throw std::logic_error(format("{}: already drawing", _));
      if (!b) throw std::logic_error(format("{}: bitmap is null", _));
      _bitmap = b, main::sys::d2d_context->SetTarget(b), main::sys::d2d_context->BeginDraw();
    }
    /// fills the bitmap with a color and begins drawing
    drawing(::ID2D1Bitmap1* b, const color& c, const source& _ = {}) : drawing(b, _) { main::sys::d2d_context->Clear(&c); }
    /// ends drawing
    void close(const source& _ = {}) {
      if (!_bitmap) throw std::logic_error(format("{}: not drawing", _));
      _bitmap = nullptr, main::sys::d2d_context->EndDraw(), main::sys::d2d_context->SetTarget(nullptr);
    }
    /// clears the bitmap with a color
    void clear(const color& c) { main::sys::d2d_context->Clear(&c); }
    /// draws a bitmap; fill the target
    void bitmap(::ID2D1Bitmap1* Bitmap, float Opacity = 1.0f) {
      main::sys::d2d_context->DrawBitmap(Bitmap, nullptr, Opacity, D2D1_INTERPOLATION_MODE_LINEAR, nullptr);
    }
    /// draws a bitmap; with destination and clipping rectangle
    void bitmap(::ID2D1Bitmap1* b, const vector4<float>& dest_xywh, const vector4<float>& clip_xywh, float opacity = 1.0f) {
      main::sys::d2d_context->DrawBitmap(b, &dest_xywh, opacity, D2D1_INTERPOLATION_MODE_LINEAR, &clip_xywh);
    }
    /// draws a bitmap; with destination rectangle
    void bitmap(::ID2D1Bitmap1* b, const vector4<float>& dest_xywh, float opacity = 1.0f) {
      main::sys::d2d_context->DrawBitmap(b, &dest_xywh, opacity, D2D1_INTERPOLATION_MODE_LINEAR, nullptr);
    }
    /// draws text
    template<stringable S> void text(
      S&& Str, const vector4<float>& rect, //
      const text_format& Format = text_format::default_, const brush& Brush = brush::black) {
      auto str = unicode<wchar_t>(static_cast<S&&>(Str));
      main::sys::d2d_context->DrawText(str.data(), int(str.size()), Format.operator->(), &rect, Brush.operator->(), 2, 0);
    }
    /// draws text
    template<stringable S> void text(
      S&& Str, const vector2<float>& xy, const vector2<float>& wh, //
      const text_format& Format = text_format::default_, const brush& Brush = brush::black) {
      auto str  = unicode<wchar_t>(static_cast<S&&>(Str));
      auto rect = vector4<float>(xy.x, xy.y, xy.x + wh.x, xy.y + wh.y);
      main::sys::d2d_context->DrawText(str.data(), int(str.size()), Format.operator->(), &rect, Brush.operator->(), 2, 0);
    }
    /// draws a line
    void line(const vector2<float>& p1, const vector2<float>& p2, const brush& Brush = brush::black, float Width = 1.0f) {
      main::sys::d2d_context->DrawLine({p1.x, p1.y}, {p2.x, p2.y}, Brush.operator->(), Width);
    }
  };
  explicit operator bool() const noexcept { return d2d_bitmap.operator bool(); }
  ::ID2D1Bitmap1* operator->() const noexcept { return d2d_bitmap.get(); }
  bitmap() noexcept = default;
  bitmap(const vector2<int>& wh, const source& _ = {}) {
    auto hr = main::sys::d2d_context->CreateBitmap({wh.x, wh.y}, nullptr, 0, &bitmap_properties, &d2d_bitmap.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
  }
  bitmap(const path& File, const source& _ = {}) {
    comptr<::IWICBitmapDecoder> decoder{};
    auto hr = main::sys::wic_factory->CreateDecoderFromFilename(File.c_str(), nullptr, 0x80000000, {}, &decoder.get());
    if (hr != 0) throw std::runtime_error(format("{}: CreateDecoderFromFilename failed: {:x}", _, hr));
    comptr<::IWICBitmapFrameDecode> frame{};
    hr = decoder->GetFrame(0, &frame.get());
    if (hr != 0) throw std::runtime_error(format("{}: IWICBitmapDecoder::GetFrame failed: {:x}", _, hr));
    vector2<int> wh;
    hr = frame->GetSize(&wh.x, &wh.y);
    if (hr != 0) throw std::runtime_error(format("{}: IWICBitmapFrameDecode::GetSize failed: {:x}", _, hr)); // clang-format off
    GUID pformat, guid = GUID{0x3cc4a650, 0xa527, 0x4d37, {0xa9, 0x16, 0x31, 0x42, 0xc7, 0xeb, 0xed, 0xba}}; // clang-format on
    hr = frame->GetPixelFormat(&pformat);
    if (hr != 0) throw std::runtime_error(format("{}: IWICBitmapFrameDecode::GetPixelFormat failed: {:x}", _, hr));
    comptr<::IWICFormatConverter> fc;
    hr = main::sys::wic_factory->CreateFormatConverter(&fc.get());
    if (hr != 0) throw std::runtime_error(format("{}: CreateFormatConverter failed: {:x}", _, hr));
    int can_convert{0};
    hr = fc->CanConvert(pformat, guid, &can_convert);
    if (hr != 0) throw std::runtime_error(format("{}: IWICFormatConverter::CanConvert failed: {:x}", _, hr));
    if (!can_convert) throw std::runtime_error(format("{}: IWICFormatConverter::CanConvert returns false", _));
    hr = fc->Initialize(frame, guid, WICBitmapDitherTypeErrorDiffusion, nullptr, 0, WICBitmapPaletteTypeMedianCut);
    if (hr != 0) throw std::runtime_error(format("{}: IWICFormatConverter::Initialize failed: {:x}", _, hr));
    main::sys::d2d_context->CreateBitmapFromWicBitmap(fc, nullptr, &d2d_bitmap.get());
  }
  /// creates a bitmap from swap-chain
  bitmap(::IDXGISwapChain1* sc, const source& _ = {}) {
    comptr<::ID3D11Texture2D> tex;
    auto hr = sc->GetBuffer(0, __uuidof(::ID3D11Texture2D), (void**)&tex.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
    comptr<::IDXGISurface> surface;
    hr = tex->QueryInterface(&surface.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
    D2D1_BITMAP_PROPERTIES1 bp{
      D2D1_PIXEL_FORMAT{{}, D2D1_ALPHA_MODE_PREMULTIPLIED},
      96.0f, 96.0f, D2D1_BITMAP_OPTIONS(3), nullptr
    };
    hr = main::sys::d2d_context->CreateBitmapFromDxgiSurface(surface, &bp, &d2d_bitmap.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
  }
  /// gets the size
  vector2<int> size() const noexcept {
    if (!d2d_bitmap) return {};
    return bitcast<vector2<int>>(d2d_bitmap->GetSize());
  }
  /// gets the width
  int width() const noexcept { return size().x; }
  /// gets the height
  int height() const noexcept { return size().y; }
  /// starts drawing
  drawing draw(const source& _ = {}) { return drawing(d2d_bitmap.get(), _); }
  /// starts drawing with clear color
  drawing draw(const color& Clear, const source& _ = {}) { return drawing(d2d_bitmap.get(), Clear, _); }
  /// saves bitmap as a png or jpg
  void to_file(const path& File, const source& _ = {}) {
    if (!d2d_bitmap) throw std::logic_error(format("{}: bitmap is null", _));
    comptr<::IWICStream> stream;
    auto hr = main::sys::wic_factory->CreateStream(&stream.get());
    if (hr != 0) throw std::runtime_error(format("{}: CreateStream failed: {:x}", _, hr));
    hr = stream->InitializeFromFilename(File.c_str(), 0x40000000);
    comptr<::IWICBitmapEncoder> encoder{};
    auto extension = File.extension();
    if (extension == L".png" || extension == L".PNG") { // clang-format off
      hr = main::sys::wic_factory->CreateEncoder(GUID{0x1b7cfaf4, 0x713f, 0x473c, {0xbb, 0xcd, 0x61, 0x37, 0x42, 0x5f, 0xae, 0xaf}}, nullptr, &encoder.get());
    } else if (extension == L".jpg" || extension == L".jpeg" || extension == L".JPG" || extension == L".JPEG") {
      hr = main::sys::wic_factory->CreateEncoder(GUID{0x19e4a5aa, 0x5662, 0x4fc5, {0xa0, 0xc0, 0x17, 0x58, 0x02, 0x8e, 0x10, 0x57}}, nullptr, &encoder.get());
    } else throw std::runtime_error(format("{}: unsupported file format", _)); // clang-format on
    if (hr != 0) throw std::runtime_error(format("{}: CreateEncoder failed: {:x}", _, hr));
    hr = encoder->Initialize(stream, WICBitmapEncoderNoCache);
    if (hr != 0) throw std::runtime_error(format("{}: IWICBitmapEncoder::Initialize failed: {:x}", _, hr));
    comptr<::IWICBitmapFrameEncode> frame{};
    hr = encoder->CreateNewFrame(&frame.get(), nullptr);
    if (hr != 0) throw std::runtime_error(format("{}: CreateNewFrame failed: {:x}", _, hr));
    hr = frame->Initialize(nullptr);
    if (hr != 0) throw std::runtime_error(format("{}: IWICBitmapFrameEncode::Initialize failed: {:x}", _, hr));
    comptr<::IWICImageEncoder> image_encoder{};
    hr = main::sys::wic_factory->CreateImageEncoder(main::sys::d2d_device, &image_encoder.get());
    if (hr != 0) throw std::runtime_error(format("{}: CreateImageEncoder failed: {:x}", _, hr));
    hr = image_encoder->WriteFrame(d2d_bitmap.get(), frame, nullptr);
    if (hr != 0) throw std::runtime_error(format("{}: IWICImageEncoder::WriteFrame failed: {:x}", _, hr));
    if ((hr = frame->Commit()) != 0) throw std::runtime_error(format("{}: IWICBitmapFrameEncode::Commit failed: {:x}", _, hr));
    if ((hr = encoder->Commit()) != 0) throw std::runtime_error(format("{}: IWICBitmapEncoder::Commit failed: {:x}", _, hr));
    if ((hr = stream->Commit(0)) != 0) throw std::runtime_error(format("{}: IWICStream::Commit failed: {:x}", _, hr));
  }
};

namespace main {

/// user-defined window procedure
inline bool (*userproc)(wmessage msg, size_t wp, size_t lp) = nullptr;

/// path to the dropped files into main-window
inline array<path> dropped_files{};

namespace sys {

/// flag to check if the main-window is active
inline bool is_active = false;

/// main-window procedure
size_t __stdcall window_proc(HANDLE hw, int msg, size_t wp, size_t lp) {
  if (userproc && userproc(wmessage(msg), wp, lp)) return 0;
  else if (msg == WM_DROPFILES) {
    auto drop = (HANDLE)wp;
    POINT pt;
    ::DragQueryPoint(drop, &pt);
    auto n = ::DragQueryFileW(drop, 0xffffffff, nullptr, 0);
    dropped_files.reserve(n), dropped_files.resize(n);
    wchar_t s[FILENAME_MAX];
    for (int i{}; i < n; ++i) dropped_files[i] = path(wstr(s, ::DragQueryFileW(drop, i, s, FILENAME_MAX)));
    ::DragFinish(drop);
  } else if (msg == WM_DESTROY) is_active = false, ::PostQuitMessage(0);
  return ::DefWindowProcW(hw, msg, wp, lp);
}

/// instance handle
inline const HANDLE instance = ::GetModuleHandleW(nullptr);

/// windows username
inline const wstr username = [](int n) -> wstr {
  ::GetUserNameW(nullptr, &n);
  wstr s(n - 1, L'\0');
  ::GetUserNameW(s.data(), &n);
  return s;
}({});

/// primary desktop window size
inline const vector2<int> desktop_size = []() -> vector2<int> {
  RECT rc;
  ::GetClientRect(::GetDesktopWindow(), &rc);
  return {rc.right, rc.bottom};
}();

/// main-window class name
inline constexpr const wchar_t* class_name = L"ywlib-main-window";

/// main-window class atom
inline const uint16_t class_atom = [](WNDCLASSEXW wc) {
  wc.hInstance     = instance;
  wc.hCursor       = ::LoadCursorW(nullptr, IDC_ARROW);
  wc.hbrBackground = (HANDLE)(COLOR_WINDOW + 1);
  wc.lpszClassName = class_name;
  auto a           = ::RegisterClassExW(&wc);
  if (!a) yw::ok(L"Failed to register window class", L"Fatal Error");
  return a;
}({sizeof(WNDCLASSEXW), 0, window_proc});

/// main-window padding
inline vector4<int> padding{};

/// main-window handle
inline const HANDLE hwnd = []() -> HANDLE {
  constexpr int sz{400};
  auto hw = ::CreateWindowExW(WS_EX_ACCEPTFILES, class_name, 0, WS_SYSMENU, 0, 0, sz, sz, 0, 0, instance, 0);
  if (!hw) return yw::ok(L"Failed to create main-window", L"Fatal Error"), nullptr;
  is_active = true;
  ::GetClientRect(hw, (RECT*)&padding);
  padding.x = (sz - padding.z) / 2, padding.z = 2 * padding.x;
  padding.y = sz - padding.w - padding.x, padding.w = padding.x + padding.y;
  int init_x = int(stoi(main::argv.option("--main-x", "-1")));
  int init_y = int(stoi(main::argv.option("--main-y", "-1")));
  int init_w = int(abs(stoi(main::argv.option("--main-width", "800"))));
  int init_h = int(abs(stoi(main::argv.option("--main-height", "600"))));
  init_w += padding.z, init_h += padding.w;
  if (init_x < 0) init_x = (desktop_size.x - init_w) / 2;
  if (init_y < 0) init_y = (desktop_size.y - init_h) / 2;
  ::SetWindowPos(hw, nullptr, init_x, init_y, init_w, init_h, SWP_NOZORDER);
  if (main::argv.option("--main-show")) ::ShowWindow(hw, SW_SHOW), ::SetForegroundWindow(hw), ::SetActiveWindow(hw);
  return hw;
}();

/// main-window message
inline MSG message{};

/// swap-chain for the main-window
inline comptr<::IDXGISwapChain1> swapchain = [](comptr<::IDXGISwapChain1> p) -> comptr<::IDXGISwapChain1> {
  RECT r;
  ::GetClientRect(sys::hwnd, &r); // clang-format off
  DXGI_SWAP_CHAIN_DESC1 desc{uint32_t(r.right), uint32_t(r.bottom), DXGI_FORMAT_R8G8B8A8_UNORM, false, {1, 0}, {}, 2}; // clang-format on
  desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  desc.SwapEffect  = DXGI_SWAP_EFFECT_DISCARD;
  auto hr          = dxgi_factory->CreateSwapChainForHwnd(d3d_device.get(), hwnd, &desc, nullptr, nullptr, &p.get());
  if (hr != 0) yw::ok(L"Failed to create swapchain", L"Fatal Error");
  return p;
}({});

/// render-target for the main-window
inline bitmap rendertarget = bitmap(swapchain.get());
}

/// shows, activates and brings the main-window to the foreground
inline void show() noexcept {
  ::ShowWindow(sys::hwnd, SW_SHOW);
  ::SetForegroundWindow(sys::hwnd);
  ::SetActiveWindow(sys::hwnd);
}

/// hides the main-window
inline void hide() noexcept {
  ::ShowWindow(sys::hwnd, SW_HIDE);
}

/// functor for `yw::main::title`
struct Title {
  /// gets the title of the main-window
  wstr operator()() const {
    int n = ::GetWindowTextLengthW(sys::hwnd);
    if (n <= 0) return wstr{};
    wstr buf(n, L'\0');
    ::GetWindowTextW(sys::hwnd, buf.data(), n + 1);
    return buf;
  }
  /// gets the title of the main-window
  operator wstr() const { return operator()(); }
  /// sets the title of the main-window
  template<stringable S> void operator()(S&& s) const {
    auto ss = unicode<wchar_t>(static_cast<S&&>(s));
    ::SetWindowTextW(sys::hwnd, ss.c_str());
  }
};
inline constexpr caster<Title> title{};

/// functor for `yw::main::size`
struct Size {
  /// gets the size of the main-window
  vector2<int> operator()() const {
    RECT r;
    ::GetClientRect(sys::hwnd, &r);
    return {r.right, r.bottom};
  }
  /// gets the size of the main-window
  operator vector2<int>() const { return operator()(); }
  /// sets the size of the main-window
  void operator()(const vector2<int>& size) const = delete;
};
/// gets/sets the size of the main-window
inline constexpr caster<Size> size{};
/// gets the width of the main-window
inline constexpr caster width{[]() -> int { return size().x; }};
/// gets the height of the main-window
inline constexpr caster height{[]() -> int { return size().y; }};

/// functor for `yw::main::update`
struct Update {
  /// updates the main-window
  bool operator()() const {
    sys::swapchain->Present(1, 0);
    while (true) {
      if (::PeekMessageW(&sys::message, nullptr, 0, 0, 1)) {
        ::TranslateMessage(&sys::message), ::DispatchMessageW(&sys::message);
        continue;
      }
      return sys::is_active;
    }
    return false;
  }
  /// updates the main-window
  operator bool() const { return operator()(); }
};
/// updates the main-window
inline constexpr caster<Update> update{};
}

/// begins drawing on the main-window
inline bitmap::drawing draw() { return main::sys::rendertarget.draw(); }

/// begins drawing on the main-window with a clear color
inline bitmap::drawing draw(const yw::color& Clear) { return main::sys::rendertarget.draw(Clear); }

/// class to represent a texture for 3D rendering
class texture : public bitmap {
protected:
  // comptr<::ID3D11Texture2D> d3d_texture;
  comptr<::ID3D11ShaderResourceView> d3d_srv;
  void init(const source& _) {
    comptr<::IDXGISurface> surface;
    auto hr = bitmap::d2d_bitmap->GetSurface(&surface.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
    comptr<::ID3D11Texture2D> texture_;
    hr = surface->QueryInterface(&texture_.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
    D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc{DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_SRV_DIMENSION_TEXTURE2D};
    assign(srv_desc.Texture2D.MipLevels, 1);
    hr = main::sys::d3d_device->CreateShaderResourceView(texture_.get(), &srv_desc, &d3d_srv.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
  }
public:
  explicit operator bool() const noexcept { return bitmap::operator bool() && bool(d3d_srv); }
  ::ID3D11ShaderResourceView* operator->() const noexcept { return d3d_srv.get(); }
  texture() noexcept = default;
  explicit texture(bitmap&& b, const source& _ = {}) : bitmap(mv(b)) { init(_); }
  explicit texture(vector2<int> size, const source& _ = {}) : bitmap(size, _) { init(_); }
  texture(arithmetic auto Width, arithmetic auto Height, const source& _ = {}) : texture({Width, Height}, _) {}
  explicit texture(const path& p, const source& _ = {}) : bitmap(p, _) { init(_); }
};

/// class to represent a canvas for being 3D rendered
class canvas : public texture {
protected:
  comptr<::ID3D11RenderTargetView> d3d_rtv;
  comptr<::ID3D11DepthStencilView> d3d_dsv;
  void init(int msaa, const source& _) {
    msaa = msaa < 2 ? 1 : (msaa < 4 ? 2 : (msaa < 8 ? 4 : 8));
    comptr<::ID3D11Texture2D> temp; // clang-format off
    D3D11_TEXTURE2D_DESC tex_desc{bitmap::width(), bitmap::height(), 1, 1, DXGI_FORMAT_D24_UNORM_S8_UINT, {msaa, 0}, {}, D3D11_BIND_DEPTH_STENCIL, {}, {}}; // clang-format on
    auto hr = main::sys::d3d_device->CreateTexture2D(&tex_desc, nullptr, &temp.get());
    if (hr != 0) throw std::runtime_error(format("error {:x}: {} <- {}", hr, source{}, _));
    hr = main::sys::d3d_device->CreateDepthStencilView(temp, nullptr, &d3d_dsv.get());
    if (hr != 0) throw std::runtime_error(format("error {:x}: {} <- {}", hr, source{}, _));
    temp.release(), tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM, tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET;
    hr = main::sys::d3d_device->CreateTexture2D(&tex_desc, nullptr, &temp.get());
    if (hr != 0) throw std::runtime_error(format("error {:x}: {} <- {}", hr, source{}, _));
    D3D11_RENDER_TARGET_VIEW_DESC rtv_desc{DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_RTV_DIMENSION_TEXTURE2DMS};
    hr = main::sys::d3d_device->CreateRenderTargetView(temp, &rtv_desc, &d3d_rtv.get());
    if (hr != 0) throw std::runtime_error(format("error {:x}: {} <- {}", hr, source{}, _));
  }
public:
  /// class to manage 3D rendering
  class rendering;
  friend class rendering;
  explicit operator bool() const noexcept { return texture::operator bool() && bool(d3d_rtv) && bool(d3d_dsv); }
  ::ID3D11RenderTargetView* operator->() const noexcept { return d3d_rtv.get(); }
  canvas() noexcept = default;
  explicit canvas(texture&& t, arithmetic auto msaa = 8, const source& _ = {}) : texture(mv(t)) { init(int(msaa), _); }
  explicit canvas(texture&& t, const source& _) : texture(mv(t)) { init(8, _); }
  explicit canvas(arithmetic auto Width, arithmetic auto Height, arithmetic auto msaa = 8, const source& _ = {}) : texture(Width, Height, _) { init(int(msaa), _); }
  explicit canvas(arithmetic auto Width, arithmetic auto Height, const source& _) : texture(Width, Height, _) { init(8, _); }
  rendering render(const source& _ = {});
  rendering render(const color& Clear, const source& _ = {});
};

class canvas::rendering {
  inline static canvas* target = nullptr;
public:
  explicit operator bool() const noexcept { return bool(target); }
  ~rendering() {
    if (!target) return;
    comptr<::ID3D11Resource> src, dst;
    target->d3d_rtv->GetResource(&src.get());
    target->d3d_srv->GetResource(&dst.get());
    main::sys::d3d_context->ResolveSubresource(src, 0, dst, 0, DXGI_FORMAT_R8G8B8A8_UNORM);
    main::sys::d3d_context->OMSetRenderTargets(0, nullptr, nullptr);
    target = nullptr;
  }
  rendering(canvas& Canvas, const source& _ = {}) {
    if (target) throw std::logic_error(format("already rendering: {} <- {}", source{}, _));
    if (!Canvas) throw std::runtime_error(format("invalid render target: {} <- {}", source{}, _));
    target = &Canvas;
    D3D11_VIEWPORT vp{0.0f, 0.0f, Canvas.width(), Canvas.height(), 0.0f, 1.0f};
    main::sys::d3d_context->RSSetViewports(1, &vp);
    main::sys::d3d_context->OMSetRenderTargets(1, &target->d3d_rtv.get(), target->d3d_dsv.get());
  }
  rendering(canvas& Canvas, const color& Clear, const source& _ = {}) : rendering(Canvas, _) {
    main::sys::d3d_context->ClearRenderTargetView(target->d3d_rtv.get(), &Clear.r);
    main::sys::d3d_context->ClearDepthStencilView(target->d3d_dsv.get(), 3, 1.0f, 0);
  }
  void run(int Vertices) { main::sys::d3d_context->Draw(Vertices, 0); }
  /// sets rendering shaders
  void set_shaders(::ID3D11VertexShader* vs, ::ID3D11PixelShader* ps, ::ID3D11GeometryShader* gs = nullptr) {
    main::sys::d3d_context->VSSetShader(vs, nullptr, 0);
    main::sys::d3d_context->PSSetShader(ps, nullptr, 0);
    main::sys::d3d_context->GSSetShader(gs, nullptr, 0);
  }
  void as_pointlist() noexcept { main::sys::d3d_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST); }
  void as_linelist() noexcept { main::sys::d3d_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST); }
  void as_linestrip() noexcept { main::sys::d3d_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP); }
  void as_trianglelist() noexcept { main::sys::d3d_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); }
  void as_trianglestip() noexcept { main::sys::d3d_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); }
};
}
