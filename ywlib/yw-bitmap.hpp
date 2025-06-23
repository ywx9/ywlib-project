#pragma once
#include <yw-shader.hpp>

namespace yw {

/// class to represent a bitmap for 2D drawing
class bitmap {
protected:
  static constexpr auto pixel_format      = D2D1_PIXEL_FORMAT{default_dxgi_format, D2D1_ALPHA_MODE_PREMULTIPLIED};
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
    template<derived_from<yw::bitmap> T> void bitmap(const T& Bitmap, float Opacity = 1.0f) {
      main::sys::d2d_context->DrawBitmap(static_cast<const yw::bitmap&>(Bitmap).operator->(), nullptr, Opacity, D2D1_INTERPOLATION_MODE_LINEAR, nullptr);
    }
    /// draws a bitmap; with destination and clipping rectangle
    template<derived_from<yw::bitmap> T> void bitmap(const T& Bitmap, const vector4<float>& dest_xywh, const vector4<float>& clip_xywh, float opacity = 1.0f) {
      main::sys::d2d_context->DrawBitmap(static_cast<const yw::bitmap&>(Bitmap).operator->(), &dest_xywh, opacity, D2D1_INTERPOLATION_MODE_LINEAR, &clip_xywh);
    }
    /// draws a bitmap; with destination rectangle
    template<derived_from<yw::bitmap> T> void bitmap(const T& Bitmap, const vector4<float>& dest_xywh, float opacity = 1.0f) {
      main::sys::d2d_context->DrawBitmap(static_cast<const yw::bitmap&>(Bitmap).operator->(), &dest_xywh, opacity, D2D1_INTERPOLATION_MODE_LINEAR, nullptr);
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
  const vector2<int> size{};
  explicit operator bool() const noexcept { return d2d_bitmap.operator bool(); }
  ::ID2D1Bitmap1* operator->() const noexcept { return d2d_bitmap.get(); }
  /// default constructor
  bitmap() noexcept = default;
  /// move constructor
  bitmap(bitmap&& b) noexcept : d2d_bitmap(mv(b.d2d_bitmap)), size(b.size) {}
  /// move assignment
  bitmap& operator=(bitmap&& b) noexcept {
    if (this != &b) d2d_bitmap = mv(b.d2d_bitmap), const_cast<vector2<int>&>(size) = b.size;
    return *this;
  }
  /// creates a bitmap with the given size
  explicit bitmap(const vector2<int>& wh, const source& _ = {}) : size(wh) {
    auto hr = main::sys::d2d_context->CreateBitmap({wh.x, wh.y}, nullptr, 0, &bitmap_properties, &d2d_bitmap.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
  }
  /// creates a bitmap from a file
  explicit bitmap(const path& File, const source& _ = {}) {
    comptr<::IWICBitmapDecoder> decoder{};
    auto hr = main::sys::wic_factory->CreateDecoderFromFilename(File.c_str(), nullptr, 0x80000000, {}, &decoder.get());
    if (hr != 0) throw std::runtime_error(format("CreateDecoderFromFilename failed ({:x}): {} <- {}", hr, source{}, _));
    comptr<::IWICBitmapFrameDecode> frame{};
    hr = decoder->GetFrame(0, &frame.get());
    if (hr != 0) throw std::runtime_error(format("IWICBitmapDecoder::GetFrame failed ({:x}): {} <- {}", hr, source{}, _));
    hr = frame->GetSize((int*)&size.x, (int*)&size.y);
    if (hr != 0) throw std::runtime_error(format("IWICBitmapFrameDecode::GetSize failed ({:x}): {} <- {}", hr, source{}, _)); // clang-format off
    GUID pformat;
    hr = frame->GetPixelFormat(&pformat);
    if (hr != 0) throw std::runtime_error(format("IWICBitmapFrameDecode::GetPixelFormat failed ({:x}): {} <- {}", hr, source{}, _));
    comptr<::IWICFormatConverter> fc;
    hr = main::sys::wic_factory->CreateFormatConverter(&fc.get());
    if (hr != 0) throw std::runtime_error(format("CreateFormatConverter failed ({:x}): {} <- {}", hr, source{}, _));
    int can_convert{0};
    hr = fc->CanConvert(pformat, default_dxgi_format_guid, &can_convert);
    if (hr != 0) throw std::runtime_error(format("IWICFormatConverter::CanConvert failed ({:x}): {} <- {}", hr, source{}, _));
    if (!can_convert) throw std::runtime_error(format("IWICFormatConverter::CanConvert returns false: {} <- {}", source{}, _));
    hr = fc->Initialize(frame, default_dxgi_format_guid, WICBitmapDitherTypeErrorDiffusion, nullptr, 0, WICBitmapPaletteTypeMedianCut);
    if (hr != 0) throw std::runtime_error(format("IWICFormatConverter::Initialize failed ({:x}): {} <- {}", hr, source{}, _));
    main::sys::d2d_context->CreateBitmapFromWicBitmap(fc, nullptr, &d2d_bitmap.get());
  }
  /// creates a bitmap from swap-chain
  bitmap(::IDXGISwapChain1* sc, const source& _ = {}) {
    DXGI_SWAP_CHAIN_DESC1 scdesc;
    sc->GetDesc1(&scdesc);
    const_cast<int&>(size.x) = int(scdesc.Width);
    const_cast<int&>(size.y) = int(scdesc.Height);
    comptr<::ID3D11Texture2D> tex{};
    auto hr = sc->GetBuffer(0, __uuidof(::ID3D11Texture2D), (void**)&tex.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
    comptr<::IDXGISurface> surface;
    hr = tex->QueryInterface(&surface.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _)); // clang-format off
    D2D1_BITMAP_PROPERTIES1 bp{D2D1_PIXEL_FORMAT{{}, D2D1_ALPHA_MODE_PREMULTIPLIED}, 96.0f, 96.0f, D2D1_BITMAP_OPTIONS(3), nullptr}; // clang-format on
    hr = main::sys::d2d_context->CreateBitmapFromDxgiSurface(surface, &bp, &d2d_bitmap.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
  }
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

/// class to represent a texture for 3D rendering
class texture : public bitmap {
  friend class staging_texture;
protected:
  comptr<::ID3D11Texture2D> d3d_tex;
  comptr<::ID3D11ShaderResourceView> d3d_srv;
  void init(const source& _) {
    comptr<::IDXGISurface> surface;
    auto hr = bitmap::d2d_bitmap->GetSurface(&surface.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
    hr = surface->QueryInterface(&d3d_tex.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
    D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc{default_dxgi_format, D3D11_SRV_DIMENSION_TEXTURE2D};
    srv_desc.Texture2D.MipLevels = 1;
    hr = main::sys::d3d_device->CreateShaderResourceView(d3d_tex.get(), &srv_desc, &d3d_srv.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
  }
public:
  explicit operator bool() const noexcept { return bitmap::operator bool() && bool(d3d_tex) && bool(d3d_srv); }
  ::ID3D11ShaderResourceView* operator->() const noexcept { return d3d_srv.get(); }
  texture() noexcept = default;
  explicit texture(bitmap&& b, const source& _ = {}) : bitmap(mv(b)) { init(_); }
  explicit texture(vector2<int> wh, const source& _ = {}) : bitmap(wh, _) { init(_); }
  explicit texture(const path& p, const source& _ = {}) : bitmap(p, _) { init(_); }
};

/// class to represent a canvas for 3D rendering
class canvas : public texture {
protected:
  comptr<::ID3D11RenderTargetView> d3d_rtv;
  comptr<::ID3D11DepthStencilView> d3d_dsv;
  void init(int msaa, const source& _) {
    msaa = msaa < 2 ? 1 : (msaa < 4 ? 2 : (msaa < 8 ? 4 : 8));
    comptr<::ID3D11Texture2D> temp; // clang-format off
    D3D11_TEXTURE2D_DESC desc{bitmap::size.x, bitmap::size.y, 1, 1};
    desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    desc.SampleDesc = {uint32_t(msaa), 0};
    desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    auto hr = main::sys::d3d_device->CreateTexture2D(&desc, nullptr, &temp.get());
    if (hr != 0) throw std::runtime_error(format("error {:x}: {} <- {}", hr, source{}, _));
    hr = main::sys::d3d_device->CreateDepthStencilView(temp, nullptr, &d3d_dsv.get());
    if (hr != 0) throw std::runtime_error(format("error {:x}: {} <- {}", hr, source{}, _));
    temp.release();
    desc.Format = default_dxgi_format, desc.BindFlags = D3D11_BIND_RENDER_TARGET;
    hr = main::sys::d3d_device->CreateTexture2D(&desc, nullptr, &temp.get());
    if (hr != 0) throw std::runtime_error(format("error {:x}: {} <- {}", hr, source{}, _));
    D3D11_RENDER_TARGET_VIEW_DESC rtv_desc{default_dxgi_format, D3D11_RTV_DIMENSION_TEXTURE2DMS};
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
  explicit canvas(texture&& t, arithmetic auto msaa, const source& _ = {}) : texture(mv(t)) { init(int(msaa), _); }
  explicit canvas(texture&& t, const source& _ = {}) : texture(mv(t)) { init(8, _); }
  explicit canvas(vector2<int> wh, arithmetic auto msaa, const source& _ = {}) : texture(wh, _) { init(int(msaa), _); }
  explicit canvas(vector2<int> wh, const source& _ = {}) : texture(wh, _) { init(8, _); }
  rendering render(const source& _ = {});
  rendering render(const color& Clear, const source& _ = {});
};

class canvas::rendering {
  inline static canvas* target = nullptr;
public:
  explicit operator bool() const noexcept { return bool(target); }
  ~rendering() {
    if (!target) return;
    comptr<::ID3D11Resource> src;
    target->d3d_rtv->GetResource(&src.get());
    main::sys::d3d_context->ResolveSubresource(target->d3d_tex, 0, src, 0, default_dxgi_format);
    main::sys::d3d_context->OMSetRenderTargets(0, nullptr, nullptr);
    target = nullptr;
  }
  rendering(canvas& Canvas, const source& _ = {}) {
    if (target) throw std::logic_error(format("already rendering: {} <- {}", source{}, _));
    if (!Canvas) throw std::runtime_error(format("invalid render target: {} <- {}", source{}, _));
    target = &Canvas;
    D3D11_VIEWPORT vp{0.0f, 0.0f, float(Canvas.size.x), float(Canvas.size.y), 0.0f, 1.0f};
    main::sys::d3d_context->RSSetViewports(1, &vp);
    main::sys::d3d_context->OMSetRenderTargets(1, &target->d3d_rtv.get(), target->d3d_dsv.get());
  }
  rendering(canvas& Canvas, const color& Clear, const source& _ = {}) : rendering(Canvas, _) {
    main::sys::d3d_context->ClearRenderTargetView(target->d3d_rtv.get(), &Clear.r);
    main::sys::d3d_context->ClearDepthStencilView(target->d3d_dsv.get(), 3, 1.0f, 0);
  }
  void run(int Vertices) { main::sys::d3d_context->Draw(Vertices, 0); }
  void as_pointlist() noexcept { main::sys::d3d_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST); }
  void as_linelist() noexcept { main::sys::d3d_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST); }
  void as_linestrip() noexcept { main::sys::d3d_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP); }
  void as_trianglelist() noexcept { main::sys::d3d_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); }
  void as_trianglestip() noexcept { main::sys::d3d_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); }
};

inline canvas::rendering canvas::render(const source& _) { return rendering(*this, _); }
inline canvas::rendering canvas::render(const color& Clear, const source& _) { return rendering(*this, Clear, _); }

// /// class to represent a read/write texture for compute shaders
// class rw_texture {
// protected:
//   comptr<::ID3D11Texture2D> d3d_tex;
//   comptr<::ID3D11UnorderedAccessView> d3d_uav;
//   void init(const source& _) {
//     D3D11_TEXTURE2D_DESC desc{size.x, size.y, 1, 1};
//     desc.Format         = DXGI_FORMAT_R32G32B32A32_FLOAT;
//     desc.SampleDesc     = {1, 0};
//     desc.Usage          = D3D11_USAGE_DEFAULT;
//     desc.BindFlags      = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
//     auto hr = main::sys::d3d_device->CreateTexture2D(&desc, nullptr, &d3d_tex.get());
//     if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
//     D3D11_UNORDERED_ACCESS_VIEW_DESC uav_desc{DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_UAV_DIMENSION_TEXTURE2D};
//     assign(uav_desc.Texture2D.MipSlice, 0);
//     hr = main::sys::d3d_device->CreateUnorderedAccessView(d3d_tex.get(), &uav_desc, &d3d_uav.get());
//     if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
//   }
// public:
//   const vector2<int> size{};
//   explicit operator bool() const noexcept { return d3d_tex != nullptr && d3d_uav != nullptr; }
//   ::ID3D11UnorderedAccessView* operator->() const noexcept { return d3d_uav.get(); }
//   /// default constructor
//   rw_texture() = default;
//   /// move constructor
//   rw_texture(rw_texture&& t) noexcept : d3d_tex(mv(t.d3d_tex)), d3d_uav(mv(t.d3d_uav)), size(t.size) {}
//   /// move assignment
//   rw_texture& operator=(rw_texture&& t) noexcept {
//     if (this != &t) d3d_tex = mv(t.d3d_tex), d3d_uav = mv(t.d3d_uav), const_cast<vector2<int>&>(size) = t.size;
//     return *this;
//   }
//   /// creates a read/write texture with given width and height
//   explicit rw_texture(vector2<int> wh, const source& _ = {}) : size(wh) { init(_); }
// };


// /// class to represent a staging texture for CPU access
// class staging_texture {
// protected:
//   static constexpr strview converter_hlsl = R"(#pragma pack_matrix(row_major)

// )";
//   inline static compute_shader converter{converter_hlsl};
//   comptr<::ID3D11Texture2D> d3d_tex;
//   void init(const source& _) {
//     D3D11_TEXTURE2D_DESC desc{size.x, size.y, 1, 1};
//     desc.Format         = DXGI_FORMAT_R32G32B32A32_FLOAT;
//     desc.SampleDesc     = {1, 0};
//     desc.Usage          = D3D11_USAGE_STAGING;
//     desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
//     auto hr = main::sys::d3d_device->CreateTexture2D(&desc, nullptr, &d3d_tex.get());
//     if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
//   }
// public:
//   const vector2<int> size{};
//   explicit operator bool() const noexcept { return d3d_tex != nullptr; }
//   ::ID3D11Texture2D* operator->() const noexcept { return d3d_tex.get(); }
//   /// default constructor
//   staging_texture() = default;
//   /// move constructor
//   staging_texture(staging_texture&& t) noexcept : d3d_tex(mv(t.d3d_tex)), size(t.size) {}
//   /// move assignment
//   staging_texture& operator=(staging_texture&& t) noexcept {
//     if (this != &t) d3d_tex = mv(t.d3d_tex), const_cast<vector2<int>&>(size) = t.size;
//     return *this;
//   }
//   /// creates a staging texture with given width and height
//   explicit staging_texture(vector2<int> wh, const source& _ = {}) : size(wh) { init(_); }
//   /// creates a staging texture from cpu memory
//   explicit staging_texture(const vector2<int>& wh, const color* data, const source& _ = {}) : size(wh) {
//     init(_);
//     D3D11_MAPPED_SUBRESOURCE mapped;
//     auto hr = main::sys::d3d_context->Map(d3d_tex.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
//     if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
//     std::memcpy(mapped.pData, data, wh.x * wh.y * sizeof(color));
//     main::sys::d3d_context->Unmap(d3d_tex.get(), 0);
//   }
//   /// creates a staging texture from given texture
//   explicit staging_texture(const derived_from<texture_base> auto& t, const source& _ = {}) : size(t.size) {
//     init(_), main::sys::d3d_context->CopyResource(d3d_tex.get(), t.operator->());
//   }
//   /// creates a staging texture from cpu memory
//   // explicit staging_texture(const
// };
}
