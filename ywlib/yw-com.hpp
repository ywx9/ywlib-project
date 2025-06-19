#pragma once
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
}

namespace yw::main::sys {

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

namespace yw {

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
  virtual ~bitmap() noexcept {}
  explicit operator bool() const noexcept { return d2d_bitmap.operator bool(); }
  ::ID2D1Bitmap1* operator->() const noexcept { return d2d_bitmap.get(); }
  bitmap() noexcept = default;
  bitmap(const vector2<int>& wh, const source& _ = {}) {
    auto hr = main::sys::d2d_context->CreateBitmap({wh.x, wh.y}, nullptr, 0, &bitmap_properties, &d2d_bitmap.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
  }
  bitmap(const path& File, const source& _ = {}) {
    comptr<IWICBitmapDecoder> decoder{};
    auto hr = main::sys::wic_factory->CreateDecoderFromFilename(File.c_str(), nullptr, 0x80000000, {}, &decoder.get());
    if (hr != 0) throw std::runtime_error(format("{}: CreateDecoderFromFilename failed: {:x}", _, hr));
    comptr<IWICBitmapFrameDecode> frame{};
    hr = decoder->GetFrame(0, &frame.get());
    if (hr != 0) throw std::runtime_error(format("{}: IWICBitmapDecoder::GetFrame failed: {:x}", _, hr));
    vector2<int> wh;
    hr = frame->GetSize(&wh.x, &wh.y);
    if (hr != 0) throw std::runtime_error(format("{}: IWICBitmapFrameDecode::GetSize failed: {:x}", _, hr)); // clang-format off
    GUID pixel_format, guid = GUID{0x3cc4a650, 0xa527, 0x4d37, {0xa9, 0x16, 0x31, 0x42, 0xc7, 0xeb, 0xed, 0xba}}; // clang-format on
    hr = frame->GetPixelFormat(&pixel_format);
    if (hr != 0) throw std::runtime_error(format("{}: IWICBitmapFrameDecode::GetPixelFormat failed: {:x}", _, hr));
    comptr<IWICFormatConverter> fc;
    hr = main::sys::wic_factory->CreateFormatConverter(&fc.get());
    if (hr != 0) throw std::runtime_error(format("{}: CreateFormatConverter failed: {:x}", _, hr));
    int can_convert{0};
    hr = fc->CanConvert(pixel_format, guid, &can_convert);
    if (hr != 0) throw std::runtime_error(format("{}: IWICFormatConverter::CanConvert failed: {:x}", _, hr));
    if (!can_convert) throw std::runtime_error(format("{}: IWICFormatConverter::CanConvert returns false", _));
    hr = fc->Initialize(frame, guid, WICBitmapDitherTypeErrorDiffusion, nullptr, 0, WICBitmapPaletteTypeMedianCut);
    if (hr != 0) throw std::runtime_error(format("{}: IWICFormatConverter::Initialize failed: {:x}", _, hr));
    main::sys::d2d_context->CreateBitmapFromWicBitmap(fc, nullptr, &d2d_bitmap.get());
  }
  /// starts drawing
  drawing draw(const source& _ = {}) { return drawing(d2d_bitmap.get(), _); }
  /// starts drawing with clear color
  drawing draw(const color& Clear, const source& _ = {}) { return drawing(d2d_bitmap.get(), Clear, _); }
  /// saves bitmap as a png or jpg
  void to_file(const path& File, const source& _ = {}) {
    if (!d2d_bitmap) throw std::logic_error(format("{}: bitmap is null", _));
    comptr<IWICStream> stream;
    auto hr = main::sys::wic_factory->CreateStream(&stream.get());
    if (hr != 0) throw std::runtime_error(format("{}: CreateStream failed: {:x}", _, hr));
    hr = stream->InitializeFromFilename(File.c_str(), 0x40000000);
    comptr<IWICBitmapEncoder> encoder{};
    auto extension = File.extension();
    if (extension == L".png" || extension == L".PNG") { // clang-format off
      hr = main::sys::wic_factory->CreateEncoder(GUID{0x1b7cfaf4, 0x713f, 0x473c, {0xbb, 0xcd, 0x61, 0x37, 0x42, 0x5f, 0xae, 0xaf}}, nullptr, &encoder.get());
    } else if (extension == L".jpg" || extension == L".jpeg" || extension == L".JPG" || extension == L".JPEG") {
      hr = main::sys::wic_factory->CreateEncoder(GUID{0x19e4a5aa, 0x5662, 0x4fc5, {0xa0, 0xc0, 0x17, 0x58, 0x02, 0x8e, 0x10, 0x57}}, nullptr, &encoder.get());
    } else throw std::runtime_error(format("{}: unsupported file format", _)); // clang-format on
    if (hr != 0) throw std::runtime_error(format("{}: CreateEncoder failed: {:x}", _, hr));
    hr = encoder->Initialize(stream, WICBitmapEncoderNoCache);
    if (hr != 0) throw std::runtime_error(format("{}: IWICBitmapEncoder::Initialize failed: {:x}", _, hr));
    comptr<IWICBitmapFrameEncode> frame{};
    hr = encoder->CreateNewFrame(&frame.get(), nullptr);
    if (hr != 0) throw std::runtime_error(format("{}: CreateNewFrame failed: {:x}", _, hr));
    hr = frame->Initialize(nullptr);
    if (hr != 0) throw std::runtime_error(format("{}: IWICBitmapFrameEncode::Initialize failed: {:x}", _, hr));
    comptr<IWICImageEncoder> image_encoder{};
    hr = main::sys::wic_factory->CreateImageEncoder(main::sys::d2d_device, &image_encoder.get());
    if (hr != 0) throw std::runtime_error(format("{}: CreateImageEncoder failed: {:x}", _, hr));
    hr = image_encoder->WriteFrame(d2d_bitmap.get(), frame, nullptr);
    if (hr != 0) throw std::runtime_error(format("{}: IWICImageEncoder::WriteFrame failed: {:x}", _, hr));
    if ((hr = frame->Commit()) != 0) throw std::runtime_error(format("{}: IWICBitmapFrameEncode::Commit failed: {:x}", _, hr));
    if ((hr = encoder->Commit()) != 0) throw std::runtime_error(format("{}: IWICBitmapEncoder::Commit failed: {:x}", _, hr));
    if ((hr = stream->Commit(0)) != 0) throw std::runtime_error(format("{}: IWICStream::Commit failed: {:x}", _, hr));
  }
};
}
