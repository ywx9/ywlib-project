#pragma once
#include <inc/d2d1.h>

#ifndef __ywlib_import
__ywlib_exportc;
extern "C++" {

enum class D2D1_BITMAP_OPTIONS {
  D2D1_BITMAP_OPTIONS_NONE = 0x0,
  D2D1_BITMAP_OPTIONS_TARGET = 0x1,
  D2D1_BITMAP_OPTIONS_CANNOT_DRAW = 0x2,
  D2D1_BITMAP_OPTIONS_CPU_READ = 0x4,
  D2D1_BITMAP_OPTIONS_GDI_COMPATIBLE = 0x8,
};
using enum D2D1_BITMAP_OPTIONS;

enum class D2D1_BUFFER_PRECISION {
  D2D1_BUFFER_PRECISION_UNKNOWN,
  D2D1_BUFFER_PRECISION_8BPC_UNORM,
  D2D1_BUFFER_PRECISION_8BPC_UNORM_SRGB,
  D2D1_BUFFER_PRECISION_16BPC_UNORM,
  D2D1_BUFFER_PRECISION_16BPC_FLOAT,
  D2D1_BUFFER_PRECISION_32BPC_FLOAT,
};
using enum D2D1_BUFFER_PRECISION;

enum class D2D1_COLOR_INTERPOLATION_MODE {
  D2D1_COLOR_INTERPOLATION_MODE_STRAIGHT,
  D2D1_COLOR_INTERPOLATION_MODE_PREMULTIPLIED,
};
using enum D2D1_COLOR_INTERPOLATION_MODE;

enum class D2D1_COLOR_SPACE {
  D2D1_COLOR_SPACE_CUSTOM,
  D2D1_COLOR_SPACE_SRGB,
  D2D1_COLOR_SPACE_SCRGB,
};
using enum D2D1_COLOR_SPACE;

enum class D2D1_COMPOSITE_MODE {
  D2D1_COMPOSITE_MODE_SOURCE_OVER,
  D2D1_COMPOSITE_MODE_DESTINATION_OVER,
  D2D1_COMPOSITE_MODE_SOURCE_IN,
  D2D1_COMPOSITE_MODE_DESTINATION_IN,
  D2D1_COMPOSITE_MODE_SOURCE_OUT,
  D2D1_COMPOSITE_MODE_DESTINATION_OUT,
  D2D1_COMPOSITE_MODE_SOURCE_ATOP,
  D2D1_COMPOSITE_MODE_DESTINATION_ATOP,
  D2D1_COMPOSITE_MODE_XOR,
  D2D1_COMPOSITE_MODE_PLUS,
  D2D1_COMPOSITE_MODE_SOURCE_COPY,
  D2D1_COMPOSITE_MODE_BOUNDED_SOURCE_COPY,
  D2D1_COMPOSITE_MODE_MASK_INVERT,
};
using enum D2D1_COMPOSITE_MODE;

enum class D2D1_DEVICE_CONTEXT_OPTIONS {
  D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
  D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS,
};
using enum D2D1_DEVICE_CONTEXT_OPTIONS;

enum class D2D1_INTERPOLATION_MODE {
  D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
  D2D1_INTERPOLATION_MODE_LINEAR,
  D2D1_INTERPOLATION_MODE_CUBIC,
  D2D1_INTERPOLATION_MODE_MULTI_SAMPLE_LINEAR,
  D2D1_INTERPOLATION_MODE_ANISOTROPIC,
  D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC,
};
using enum D2D1_INTERPOLATION_MODE;

enum class D2D1_LAYER_OPTIONS1 {
  D2D1_LAYER_OPTIONS1_NONE,
  D2D1_LAYER_OPTIONS1_INITIALIZE_FROM_BACKGROUND,
  D2D1_LAYER_OPTIONS1_IGNORE_ALPHA,
};
using enum D2D1_LAYER_OPTIONS1;

enum class D2D1_MAP_OPTIONS {
  D2D1_MAP_OPTIONS_NONE,
  D2D1_MAP_OPTIONS_READ,
  D2D1_MAP_OPTIONS_WRITE,
  D2D1_MAP_OPTIONS_DISCARD,
};
using enum D2D1_MAP_OPTIONS;

enum class D2D1_PRIMITIVE_BLEND {
  D2D1_PRIMITIVE_BLEND_SOURCE_OVER,
  D2D1_PRIMITIVE_BLEND_COPY,
  D2D1_PRIMITIVE_BLEND_MIN,
  D2D1_PRIMITIVE_BLEND_ADD,
  D2D1_PRIMITIVE_BLEND_MAX,
};
using enum D2D1_PRIMITIVE_BLEND;

enum class D2D1_PRINT_FONT_SUBSET_MODE {
  D2D1_PRINT_FONT_SUBSET_MODE_DEFAULT,
  D2D1_PRINT_FONT_SUBSET_MODE_EACHPAGE,
  D2D1_PRINT_FONT_SUBSET_MODE_NONE,
};
using enum D2D1_PRINT_FONT_SUBSET_MODE;

enum class D2D1_PROPERTY_TYPE {
  D2D1_PROPERTY_TYPE_UNKNOWN,
  D2D1_PROPERTY_TYPE_STRING,
  D2D1_PROPERTY_TYPE_BOOL,
  D2D1_PROPERTY_TYPE_UINT32,
  D2D1_PROPERTY_TYPE_INT32,
  D2D1_PROPERTY_TYPE_FLOAT,
  D2D1_PROPERTY_TYPE_VECTOR2,
  D2D1_PROPERTY_TYPE_VECTOR3,
  D2D1_PROPERTY_TYPE_VECTOR4,
  D2D1_PROPERTY_TYPE_BLOB,
  D2D1_PROPERTY_TYPE_IUNKNOWN,
  D2D1_PROPERTY_TYPE_ENUM,
  D2D1_PROPERTY_TYPE_ARRAY,
  D2D1_PROPERTY_TYPE_CLSID,
  D2D1_PROPERTY_TYPE_MATRIX_3X2,
  D2D1_PROPERTY_TYPE_MATRIX_4X3,
  D2D1_PROPERTY_TYPE_MATRIX_4X4,
  D2D1_PROPERTY_TYPE_MATRIX_5X4,
  D2D1_PROPERTY_TYPE_COLOR_CONTEXT,
};
using enum D2D1_PROPERTY_TYPE;

enum class D2D1_STROKE_TRANSFORM_TYPE {
  D2D1_STROKE_TRANSFORM_TYPE_NORMAL,
  D2D1_STROKE_TRANSFORM_TYPE_FIXED,
  D2D1_STROKE_TRANSFORM_TYPE_HAIRLINE,
};
using enum D2D1_STROKE_TRANSFORM_TYPE;

enum D2D1_UNIT_MODE {
  D2D1_UNIT_MODE_DIPS,
  D2D1_UNIT_MODE_PIXELS,
};
using enum D2D1_UNIT_MODE;

struct D2D1_MATRIX_4X4_F {
  float m[4][4];
};

cominterface("82237326-8111-4f7c-bcf4-b5c1175564fe") ID2D1GdiMetafileSink : IUnknown {
  virtual HRESULT __stdcall ProcessRecord(int, const void*, int) noexcept = 0;
};

cominterface("2f543dc3-cfc1-4211-864f-cfd91c6f3395") ID2D1GdiMetafile : ID2D1Resource {
  virtual HRESULT __stdcall Stream(ID2D1GdiMetafileSink*) noexcept = 0;
  virtual HRESULT __stdcall GetBounds(D2D1_RECT_F*) noexcept = 0;
};

struct D2D1_LAYER_PARAMETERS1 {
  D2D1_RECT_F contentBounds;
  ID2D1Geometry* geometricMask;
  D2D1_ANTIALIAS_MODE maskAntialiasMode;
  D2D1_MATRIX_3X2_F maskTransform;
  float opacity;
  ID2D1Brush* opacityBrush;
  D2D1_LAYER_OPTIONS1 layerOptions;
};

struct DWRITE_GLYPH_RUN_DESCRIPTION;
cominterface("54d7898a-a061-40a7-bec7-e465bcba2c4f") ID2D1CommandSink : IUnknown {
  virtual HRESULT __stdcall BeginDraw() noexcept = 0;
  virtual HRESULT __stdcall EndDraw() noexcept = 0;
  virtual HRESULT __stdcall SetAntialiasMode(D2D1_ANTIALIAS_MODE) noexcept = 0;
  virtual HRESULT __stdcall SetTags(size_t, size_t) noexcept = 0;
  virtual HRESULT __stdcall SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE) noexcept = 0;
  virtual HRESULT __stdcall SetTextRenderingParams(IDWriteRenderingParams*) noexcept = 0;
  virtual HRESULT __stdcall SetTransform(const D2D1_MATRIX_3X2_F*) noexcept = 0;
  virtual HRESULT __stdcall SetPrimitiveBlend(D2D1_PRIMITIVE_BLEND) noexcept = 0;
  virtual HRESULT __stdcall SetUnitMode(D2D1_UNIT_MODE) noexcept = 0;
  virtual HRESULT __stdcall Clear(const D2D1_COLOR_F*) noexcept = 0;
  virtual HRESULT __stdcall DrawGlyphRun(D2D1_POINT_2F, const DWRITE_GLYPH_RUN*, const DWRITE_GLYPH_RUN_DESCRIPTION*, ID2D1Brush*, DWRITE_MEASURING_MODE) noexcept = 0;
  virtual HRESULT __stdcall DrawLine(D2D1_POINT_2F, D2D1_POINT_2F, ID2D1Brush*, float, ID2D1StrokeStyle*) noexcept = 0;
  virtual HRESULT __stdcall DrawGeometry(ID2D1Geometry*, ID2D1Brush*, float, ID2D1StrokeStyle*) noexcept = 0;
  virtual HRESULT __stdcall DrawRectangle(const D2D1_RECT_F*, ID2D1Brush*, float, ID2D1StrokeStyle*) noexcept = 0;
  virtual HRESULT __stdcall DrawBitmap(ID2D1Bitmap*, const D2D1_RECT_F*, float, D2D1_INTERPOLATION_MODE, const D2D1_RECT_F*, const D2D1_MATRIX_4X4_F*) noexcept = 0;
  virtual HRESULT __stdcall DrawImage(ID2D1Image*, const D2D1_POINT_2F*, const D2D1_RECT_F*, D2D1_INTERPOLATION_MODE, D2D1_COMPOSITE_MODE) noexcept = 0;
  virtual HRESULT __stdcall DrawGdiMetafile(ID2D1GdiMetafile*, const D2D1_POINT_2F*) noexcept = 0;
  virtual HRESULT __stdcall FillMesh(ID2D1Mesh*, ID2D1Brush*) noexcept = 0;
  virtual HRESULT __stdcall FillOpacityMask(ID2D1Bitmap*, ID2D1Brush*, const D2D1_RECT_F*, const D2D1_RECT_F*) noexcept = 0;
  virtual HRESULT __stdcall FillGeometry(ID2D1Geometry*, ID2D1Brush*, ID2D1Brush*) noexcept = 0;
  virtual HRESULT __stdcall FillRectangle(const D2D1_RECT_F*, ID2D1Brush*) noexcept = 0;
  virtual HRESULT __stdcall PushAxisAlignedClip(const D2D1_RECT_F*, D2D1_ANTIALIAS_MODE) noexcept = 0;
  virtual HRESULT __stdcall PushLayer(const D2D1_LAYER_PARAMETERS1*, ID2D1Layer*) noexcept = 0;
  virtual HRESULT __stdcall PopAxisAlignedClip() noexcept = 0;
  virtual HRESULT __stdcall PopLayer() noexcept = 0;
};

cominterface("b4f34a19-2383-4d76-94f6-ec343657c3dc") ID2D1CommandList : ID2D1Image {
  virtual HRESULT __stdcall Stream(ID2D1CommandSink*) noexcept = 0;
  virtual HRESULT __stdcall Close() noexcept = 0;
};

cominterface("2c1d867d-c290-41c8-ae7e-34a98702e9a5") ID2D1PrintControl : IUnknown {
  virtual HRESULT __stdcall AddPage(ID2D1CommandList*, D2D1_SIZE_F, IStream*, size_t* = nullptr, size_t* = nullptr) noexcept = 0;
  virtual HRESULT __stdcall Close() noexcept = 0;
};

cominterface("fe9e984d-3f95-407c-b5db-cb94d4e8f87c") ID2D1ImageBrush : ID2D1Brush {
  virtual void __stdcall SetImage(ID2D1Image*) noexcept = 0;
  virtual void __stdcall SetExtendModeX(D2D1_EXTEND_MODE) noexcept = 0;
  virtual void __stdcall SetExtendModeY(D2D1_EXTEND_MODE) noexcept = 0;
  virtual void __stdcall SetInterpolationMode(D2D1_INTERPOLATION_MODE) noexcept = 0;
  virtual void __stdcall SetSourceRectangle(const D2D1_RECT_F*) noexcept = 0;
  virtual void __stdcall GetImage(ID2D1Image**) const noexcept = 0;
  virtual D2D1_EXTEND_MODE __stdcall GetExtendModeX() const noexcept = 0;
  virtual D2D1_EXTEND_MODE __stdcall GetExtendModeY() const noexcept = 0;
  virtual D2D1_INTERPOLATION_MODE __stdcall GetInterpolationMode() const noexcept = 0;
  virtual void __stdcall GetSourceRectangle(D2D1_RECT_F*) const noexcept = 0;
};

cominterface("41343a53-e41a-49a2-91cd-21793bbb62e5") ID2D1BitmapBrush1 : ID2D1BitmapBrush {
  virtual void __stdcall SetInterpolationMode1(D2D1_INTERPOLATION_MODE) noexcept = 0;
  virtual D2D1_INTERPOLATION_MODE __stdcall GetInterpolationMode1() const noexcept = 0;
};

cominterface("10a72a66-e91c-43f4-993f-ddf4b82b0b4a") ID2D1StrokeStyle1 : ID2D1StrokeStyle {
  virtual D2D1_STROKE_TRANSFORM_TYPE __stdcall GetStrokeTransformType() const noexcept = 0;
};

struct D2D1_POINT_DESCRIPTION {
  D2D1_POINT_2F point, unitTangentVector;
  int endSegment, endFigure;
  float lengthToEndSegment;
};

cominterface("62baa2d2-ab54-41b7-b872-787e0106a421") ID2D1PathGeometry1 : ID2D1PathGeometry {
  virtual HRESULT __stdcall ComputePointAndSegmentAtLength(float, int, const D2D1_MATRIX_3X2_F*, float, D2D1_POINT_DESCRIPTION*) const noexcept = 0;
  HRESULT ComputePointAndSegmentAtLength(float length, int startSegment, const D2D1_MATRIX_3X2_F& worldTransform, float flatteningTolerance, D2D1_POINT_DESCRIPTION* pointDescription) const noexcept { return ComputePointAndSegmentAtLength(length, startSegment, &worldTransform, flatteningTolerance, pointDescription); }
  HRESULT ComputePointAndSegmentAtLength(float length, int startSegment, const D2D1_MATRIX_3X2_F* worldTransform, D2D1_POINT_DESCRIPTION* pointDescription) const noexcept { return ComputePointAndSegmentAtLength(length, startSegment, worldTransform, 0.25f, pointDescription); }
  HRESULT ComputePointAndSegmentAtLength(float length, int startSegment, const D2D1_MATRIX_3X2_F& worldTransform, D2D1_POINT_DESCRIPTION* pointDescription) const noexcept { return ComputePointAndSegmentAtLength(length, startSegment, &worldTransform, 0.25f, pointDescription); }
};

cominterface("483473d7-cd46-4f9d-9d3a-3112aa80159d") ID2D1Properties : IUnknown {
  virtual int __stdcall GetPropertyCount() const noexcept = 0;
  virtual HRESULT __stdcall GetPropertyName(int, wchar_t*, int) const noexcept = 0;
  virtual int __stdcall GetPropertyNameLength(int) const noexcept = 0;
  virtual D2D1_PROPERTY_TYPE __stdcall GetType(int) const noexcept = 0;
  virtual int __stdcall GetPropertyIndex(const wchar_t*) const noexcept = 0;
  virtual HRESULT __stdcall SetValueByName(const wchar_t*, D2D1_PROPERTY_TYPE, const void*, int) noexcept = 0;
  virtual HRESULT __stdcall SetValue(int, D2D1_PROPERTY_TYPE, const void*, int) noexcept = 0;
  virtual HRESULT __stdcall GetValueByName(const wchar_t*, D2D1_PROPERTY_TYPE, void*, int) const noexcept = 0;
  virtual HRESULT __stdcall GetValue(int, D2D1_PROPERTY_TYPE, void*, int) const noexcept = 0;
  virtual int __stdcall GetValueSize(int) const noexcept = 0;
  virtual HRESULT __stdcall GetSubProperties(int, ID2D1Properties**) const noexcept = 0;
  HRESULT SetValueByName(const wchar_t* name, const void* data, int dataSize) noexcept { return SetValueByName(name, D2D1_PROPERTY_TYPE_UNKNOWN, data, dataSize); }
  HRESULT SetValue(int index, const void* data, int dataSize) noexcept { return SetValue(index, D2D1_PROPERTY_TYPE_UNKNOWN, data, dataSize); }
  HRESULT GetValueByName(const wchar_t* name, void* data, int dataSize) const noexcept { return GetValueByName(name, D2D1_PROPERTY_TYPE_UNKNOWN, data, dataSize); }
  HRESULT GetValue(int index, void* data, int dataSize) const noexcept { return GetValue(index, D2D1_PROPERTY_TYPE_UNKNOWN, data, dataSize); }
  template<typename T> HRESULT GetValueByName(const wchar_t* propertyName, T* value) const noexcept { return GetValueByName(propertyName, reinterpret_cast<void*>(value), sizeof(*value)); }
  template<typename T> T GetValueByName(const wchar_t* propertyName) const noexcept {
    return [&](T value) { return (void)(GetValueByName(propertyName, reinterpret_cast<void*>(&value), sizeof(value))), value; }({});
  }
  template<typename T> HRESULT SetValueByName(const wchar_t* propertyName, const T& value) noexcept { return SetValueByName(propertyName, &value, sizeof(value)); }
  template<typename U> HRESULT GetValue(U index, void* data, int dataSize) const noexcept { return GetValue(static_cast<int>(index), data, dataSize); }
  template<typename T, typename U> HRESULT GetValue(U index, T * value) const noexcept { return GetValue(static_cast<int>(index), reinterpret_cast<void*>(value), sizeof(*value)); }
  template<typename T, typename U> T GetValue(U index) const noexcept {
    return [&](T value) { return (void)(GetValue(static_cast<int>(index), reinterpret_cast<void*>(&value), sizeof(value))), value; }({});
  }
  template<typename U> HRESULT SetValue(U index, const void* data, int dataSize) noexcept { return SetValue(static_cast<int>(index), data, dataSize); }
  template<typename T, typename U> HRESULT SetValue(U index, const T& value) noexcept { return SetValue(static_cast<int>(index), &value, sizeof(value)); }
  template<typename U> HRESULT GetPropertyName(U index, wchar_t * name, int nameCount) const noexcept { return GetPropertyName(static_cast<int>(index), name, nameCount); }
  template<typename U> int GetPropertyNameLength(U index) const noexcept { return GetPropertyNameLength(static_cast<int>(index)); }
  template<typename U> D2D1_PROPERTY_TYPE GetType(U index) const noexcept { return GetType(static_cast<int>(index)); }
  template<typename U> int GetValueSize(U index) const noexcept { return GetValueSize(static_cast<int>(index)); }
  template<typename U> HRESULT GetSubProperties(U index, ID2D1Properties * *subProperties) const noexcept { return GetSubProperties(static_cast<int>(index), subProperties); }
};

cominterface("28211a43-7d89-476f-8181-2d6159b220ad") ID2D1Effect : ID2D1Properties {
  virtual void __stdcall SetInput(int, ID2D1Image*, int = true) noexcept = 0;
  virtual HRESULT __stdcall SetInputCount(int) noexcept = 0;
  virtual void __stdcall GetInput(int, ID2D1Image**) const noexcept = 0;
  virtual int __stdcall GetInputCount() const noexcept = 0;
  virtual void __stdcall GetOutput(ID2D1Image**) const noexcept = 0;
  void SetInputEffect(int index, ID2D1Effect* inputEffect, int invalidate = true) noexcept {
    ID2D1Image* output = nullptr;
    if (inputEffect != nullptr) inputEffect->GetOutput(&output);
    SetInput(index, output, invalidate);
    if (output != nullptr) output->Release();
  }
};

struct D2D1_MAPPED_RECT {
  int pitch;
  void* bits;
};

cominterface("1c4820bb-5771-4518-a581-2fe4dd0ec657") ID2D1ColorContext : ID2D1Resource {
  virtual D2D1_COLOR_SPACE __stdcall GetColorSpace() const noexcept = 0;
  virtual int __stdcall GetProfileSize() const noexcept = 0;
  virtual HRESULT __stdcall GetProfile(void*, int) const noexcept = 0;
};

cominterface("a898a84c-3873-4588-b08b-ebbf978df041") ID2D1Bitmap1 : ID2D1Bitmap {
  virtual void __stdcall GetColorContext(ID2D1ColorContext**) const noexcept = 0;
  virtual D2D1_BITMAP_OPTIONS __stdcall GetOptions() const noexcept = 0;
  virtual HRESULT __stdcall GetSurface(IDXGISurface**) const noexcept = 0;
  virtual HRESULT __stdcall Map(D2D1_MAP_OPTIONS, D2D1_MAPPED_RECT*) noexcept = 0;

  virtual HRESULT __stdcall Unmap() noexcept = 0;
};

cominterface("ae1572f4-5dd0-4777-998b-9279472ae63b") ID2D1GradientStopCollection1 : ID2D1GradientStopCollection {
  virtual void __stdcall GetGradientStops1(D2D1_GRADIENT_STOP*, int) const noexcept = 0;
  virtual D2D1_COLOR_SPACE __stdcall GetPreInterpolationSpace() const noexcept = 0;
  virtual D2D1_COLOR_SPACE __stdcall GetPostInterpolationSpace() const noexcept = 0;
  virtual D2D1_BUFFER_PRECISION __stdcall GetBufferPrecision() const noexcept = 0;
  virtual D2D1_COLOR_INTERPOLATION_MODE __stdcall GetColorInterpolationMode() const noexcept = 0;
};

struct D2D1_DRAWING_STATE_DESCRIPTION1 {
  D2D1_ANTIALIAS_MODE antialiasMode;
  D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode;
  size_t tag1, tag2;
  D2D1_MATRIX_3X2_F transform;
  D2D1_PRIMITIVE_BLEND primitiveBlend;
  D2D1_UNIT_MODE unitMode;
};

cominterface("689f1f85-c72e-4e33-8f19-85754efd5ace") ID2D1DrawingStateBlock1 : ID2D1DrawingStateBlock {
  virtual void __stdcall GetDescription(D2D1_DRAWING_STATE_DESCRIPTION1*) const noexcept = 0;
  using ID2D1DrawingStateBlock::GetDescription;
  virtual void __stdcall SetDescription(const D2D1_DRAWING_STATE_DESCRIPTION1*) noexcept = 0;
  using ID2D1DrawingStateBlock::SetDescription;
};

struct D2D1_BITMAP_BRUSH_PROPERTIES1 {
  D2D1_EXTEND_MODE extendModeX, extendModeY;
  D2D1_INTERPOLATION_MODE interpolationMode;
};

struct D2D1_EFFECT_INPUT_DESCRIPTION {
  ID2D1Effect* effect;
  int inputIndex;
  D2D1_RECT_F inputRectangle;
};

struct D2D1_BITMAP_PROPERTIES1 {
  D2D1_PIXEL_FORMAT pixelFormat;
  float dpiX, dpiY;
  D2D1_BITMAP_OPTIONS bitmapOptions;
  ID2D1ColorContext* colorContext;
};

struct D2D1_IMAGE_BRUSH_PROPERTIES {
  D2D1_RECT_F sourceRectangle;
  D2D1_EXTEND_MODE extendModeX, extendModeY;
  D2D1_INTERPOLATION_MODE interpolationMode;
};

struct D2D1_RENDERING_CONTROLS {
  D2D1_BUFFER_PRECISION bufferPrecision;
  SIZE tileSize;
};

struct IWICColorContext;
cominterface("47dd575d-ac05-4cdd-8049-9b02cd16f44c") ID2D1Device;
cominterface("e8f7fe7a-191c-466d-ad95-975678bda998") ID2D1DeviceContext : ID2D1RenderTarget {
  virtual HRESULT __stdcall CreateBitmap(SIZE, const void*, int, const D2D1_BITMAP_PROPERTIES1*, ID2D1Bitmap1**) noexcept = 0;
  using ID2D1RenderTarget::CreateBitmap;
  virtual HRESULT __stdcall CreateBitmapFromWicBitmap(IWICBitmapSource*, const D2D1_BITMAP_PROPERTIES1*, ID2D1Bitmap1**) noexcept = 0;
  using ID2D1RenderTarget::CreateBitmapFromWicBitmap;
  virtual HRESULT __stdcall CreateColorContext(D2D1_COLOR_SPACE, const void*, int, ID2D1ColorContext**) noexcept = 0;
  virtual HRESULT __stdcall CreateColorContextFromFilename(const wchar_t*, ID2D1ColorContext**) noexcept = 0;
  virtual HRESULT __stdcall CreateColorContextFromWicColorContext(IWICColorContext*, ID2D1ColorContext**) noexcept = 0;
  virtual HRESULT __stdcall CreateBitmapFromDxgiSurface(IDXGISurface*, const D2D1_BITMAP_PROPERTIES1*, ID2D1Bitmap1**) noexcept = 0;
  virtual HRESULT __stdcall CreateEffect(const GUID&, ID2D1Effect**) noexcept = 0;
  virtual HRESULT __stdcall CreateGradientStopCollection(const D2D1_GRADIENT_STOP*, int, D2D1_COLOR_SPACE, D2D1_COLOR_SPACE, D2D1_BUFFER_PRECISION, D2D1_EXTEND_MODE, D2D1_COLOR_INTERPOLATION_MODE, ID2D1GradientStopCollection1**) noexcept = 0;
  using ID2D1RenderTarget::CreateGradientStopCollection;
  virtual HRESULT __stdcall CreateImageBrush(ID2D1Image*, const D2D1_IMAGE_BRUSH_PROPERTIES*, const D2D1_BRUSH_PROPERTIES*, ID2D1ImageBrush**) noexcept = 0;
  virtual HRESULT __stdcall CreateBitmapBrush(ID2D1Bitmap*, const D2D1_BITMAP_BRUSH_PROPERTIES1*, const D2D1_BRUSH_PROPERTIES*, ID2D1BitmapBrush1**) noexcept = 0;
  using ID2D1RenderTarget::CreateBitmapBrush;
  virtual HRESULT __stdcall CreateCommandList(ID2D1CommandList**) noexcept = 0;
  virtual int __stdcall IsDxgiFormatSupported(DXGI_FORMAT) const noexcept = 0;
  virtual int __stdcall IsBufferPrecisionSupported(D2D1_BUFFER_PRECISION) const noexcept = 0;
  virtual HRESULT __stdcall GetImageLocalBounds(ID2D1Image*, D2D1_RECT_F*) const noexcept = 0;
  virtual HRESULT __stdcall GetImageWorldBounds(ID2D1Image*, D2D1_RECT_F*) const noexcept = 0;
  virtual HRESULT __stdcall GetGlyphRunWorldBounds(D2D1_POINT_2F, const DWRITE_GLYPH_RUN*, DWRITE_MEASURING_MODE, D2D1_RECT_F*) const noexcept = 0;
  virtual void __stdcall GetDevice(ID2D1Device**) const noexcept = 0;
  virtual void __stdcall SetTarget(ID2D1Image*) noexcept = 0;
  virtual void __stdcall GetTarget(ID2D1Image**) const noexcept = 0;
  virtual void __stdcall SetRenderingControls(const D2D1_RENDERING_CONTROLS*) noexcept = 0;
  virtual void __stdcall GetRenderingControls(D2D1_RENDERING_CONTROLS*) const noexcept = 0;
  virtual void __stdcall SetPrimitiveBlend(D2D1_PRIMITIVE_BLEND) noexcept = 0;
  virtual D2D1_PRIMITIVE_BLEND __stdcall GetPrimitiveBlend() const noexcept = 0;
  virtual void __stdcall SetUnitMode(D2D1_UNIT_MODE) noexcept = 0;
  virtual D2D1_UNIT_MODE __stdcall GetUnitMode() const noexcept = 0;
  virtual void __stdcall DrawGlyphRun(D2D1_POINT_2F, const DWRITE_GLYPH_RUN*, const DWRITE_GLYPH_RUN_DESCRIPTION*, ID2D1Brush*, DWRITE_MEASURING_MODE = DWRITE_MEASURING_MODE_NATURAL) noexcept = 0;
  using ID2D1RenderTarget::DrawGlyphRun;
  virtual void __stdcall DrawImage(ID2D1Image*, const void* = nullptr, const void* = nullptr, D2D1_INTERPOLATION_MODE = D2D1_INTERPOLATION_MODE_LINEAR, D2D1_COMPOSITE_MODE = D2D1_COMPOSITE_MODE_SOURCE_OVER) noexcept = 0;
  virtual void __stdcall DrawGdiMetafile(ID2D1GdiMetafile*, const void* = nullptr) noexcept = 0;
  virtual void __stdcall DrawBitmap(ID2D1Bitmap*, const void*, float, D2D1_INTERPOLATION_MODE, const void* = nullptr, const D2D1_MATRIX_4X4_F* = nullptr) noexcept = 0;
  using ID2D1RenderTarget::DrawBitmap;
  virtual void __stdcall PushLayer(const D2D1_LAYER_PARAMETERS1*, ID2D1Layer*) noexcept = 0;
  using ID2D1RenderTarget::PushLayer;
  virtual HRESULT __stdcall InvalidateEffectInputRectangle(ID2D1Effect*, int, const void*) noexcept = 0;
  virtual HRESULT __stdcall GetEffectInvalidRectangleCount(ID2D1Effect*, int*) noexcept = 0;
  virtual HRESULT __stdcall GetEffectInvalidRectangles(ID2D1Effect*, void*, int) noexcept = 0;
  virtual HRESULT __stdcall GetEffectRequiredInputRectangles(ID2D1Effect*, const void*, const D2D1_EFFECT_INPUT_DESCRIPTION*, void*, int) noexcept = 0;
  virtual void __stdcall FillOpacityMask(ID2D1Bitmap*, ID2D1Brush*, const void* = nullptr, const void* = nullptr) noexcept = 0;
  using ID2D1RenderTarget::FillOpacityMask;
  HRESULT CreateBitmap(SIZE size, const void* sourceData, int pitch, const D2D1_BITMAP_PROPERTIES1& bitmapProperties, ID2D1Bitmap1** bitmap) noexcept { return CreateBitmap(size, sourceData, pitch, &bitmapProperties, bitmap); }
  HRESULT CreateBitmapFromWicBitmap(IWICBitmapSource * wicBitmapSource, const D2D1_BITMAP_PROPERTIES1& bitmapProperties, ID2D1Bitmap1** bitmap) noexcept { return CreateBitmapFromWicBitmap(wicBitmapSource, &bitmapProperties, bitmap); }
  HRESULT CreateBitmapFromWicBitmap(IWICBitmapSource * wicBitmapSource, ID2D1Bitmap1 * *bitmap) noexcept { return CreateBitmapFromWicBitmap(wicBitmapSource, nullptr, bitmap); }
  HRESULT CreateBitmapFromDxgiSurface(IDXGISurface * surface, const D2D1_BITMAP_PROPERTIES1& bitmapProperties, ID2D1Bitmap1** bitmap) noexcept { return CreateBitmapFromDxgiSurface(surface, &bitmapProperties, bitmap); }
  HRESULT CreateImageBrush(ID2D1Image * image, const D2D1_IMAGE_BRUSH_PROPERTIES& imageBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, ID2D1ImageBrush** imageBrush) noexcept { return CreateImageBrush(image, &imageBrushProperties, &brushProperties, imageBrush); }
  HRESULT CreateImageBrush(ID2D1Image * image, const D2D1_IMAGE_BRUSH_PROPERTIES& imageBrushProperties, ID2D1ImageBrush** imageBrush) noexcept { return CreateImageBrush(image, &imageBrushProperties, nullptr, imageBrush); }
  HRESULT CreateBitmapBrush(ID2D1Bitmap * bitmap, ID2D1BitmapBrush1 * *bitmapBrush) noexcept { return CreateBitmapBrush(bitmap, nullptr, nullptr, bitmapBrush); }
  HRESULT CreateBitmapBrush(ID2D1Bitmap * bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES1& bitmapBrushProperties, ID2D1BitmapBrush1** bitmapBrush) noexcept { return CreateBitmapBrush(bitmap, &bitmapBrushProperties, nullptr, bitmapBrush); }
  HRESULT CreateBitmapBrush(ID2D1Bitmap * bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES1& bitmapBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, ID2D1BitmapBrush1** bitmapBrush) noexcept { return CreateBitmapBrush(bitmap, &bitmapBrushProperties, &brushProperties, bitmapBrush); }
  void DrawImage(ID2D1Effect * effect, const D2D1_POINT_2F* targetOffset = nullptr, const D2D1_RECT_F* imageRectangle = nullptr, D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR, D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER) noexcept {
    [&](ID2D1Image* output) { effect->GetOutput(&output), DrawImage(output, targetOffset, imageRectangle, interpolationMode, compositeMode), output->Release(); }({});
  }
  void DrawImage(ID2D1Image * image, D2D1_INTERPOLATION_MODE interpolationMode, D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER) noexcept { DrawImage(image, nullptr, nullptr, interpolationMode, compositeMode); }
  void DrawImage(ID2D1Effect * effect, D2D1_INTERPOLATION_MODE interpolationMode, D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER) noexcept { DrawImage(effect, nullptr, nullptr, interpolationMode, compositeMode); }
  void DrawImage(ID2D1Image * image, D2D1_POINT_2F targetOffset, D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR, D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER) noexcept { DrawImage(image, &targetOffset, nullptr, interpolationMode, compositeMode); }
  void DrawImage(ID2D1Effect * effect, D2D1_POINT_2F targetOffset, D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR, D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER) noexcept { DrawImage(effect, &targetOffset, nullptr, interpolationMode, compositeMode); }
  void DrawImage(ID2D1Image * image, D2D1_POINT_2F targetOffset, const D2D1_RECT_F& imageRectangle, D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR, D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER) noexcept { DrawImage(image, &targetOffset, &imageRectangle, interpolationMode, compositeMode); }
  void DrawImage(ID2D1Effect * effect, D2D1_POINT_2F targetOffset, const D2D1_RECT_F& imageRectangle, D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR, D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER) noexcept { DrawImage(effect, &targetOffset, &imageRectangle, interpolationMode, compositeMode); }
  void PushLayer(const D2D1_LAYER_PARAMETERS1& layerParameters, ID2D1Layer* layer) noexcept { PushLayer(&layerParameters, layer); }
  void DrawGdiMetafile(ID2D1GdiMetafile * gdiMetafile, D2D1_POINT_2F targetOffset) noexcept { DrawGdiMetafile(gdiMetafile, &targetOffset); }
  void DrawBitmap(ID2D1Bitmap * bitmap, const D2D1_RECT_F& destinationRectangle, float opacity, D2D1_INTERPOLATION_MODE interpolationMode, const D2D1_RECT_F* sourceRectangle = nullptr, const D2D1_MATRIX_4X4_F* perspectiveTransform = nullptr) noexcept { DrawBitmap(bitmap, &destinationRectangle, opacity, interpolationMode, sourceRectangle, perspectiveTransform); }
  void DrawBitmap(ID2D1Bitmap * bitmap, const D2D1_RECT_F& destinationRectangle, float opacity, D2D1_INTERPOLATION_MODE interpolationMode, const D2D1_RECT_F& sourceRectangle, const D2D1_MATRIX_4X4_F* perspectiveTransform = nullptr) noexcept { DrawBitmap(bitmap, &destinationRectangle, opacity, interpolationMode, &sourceRectangle, perspectiveTransform); }
  void DrawBitmap(ID2D1Bitmap * bitmap, const D2D1_RECT_F& destinationRectangle, float opacity, D2D1_INTERPOLATION_MODE interpolationMode, const D2D1_RECT_F& sourceRectangle, const D2D1_MATRIX_4X4_F& perspectiveTransform) noexcept { DrawBitmap(bitmap, &destinationRectangle, opacity, interpolationMode, &sourceRectangle, &perspectiveTransform); }
  void FillOpacityMask(ID2D1Bitmap * opacityMask, ID2D1Brush * brush, const D2D1_RECT_F& destinationRectangle, const D2D1_RECT_F* sourceRectangle = nullptr) noexcept { FillOpacityMask(opacityMask, brush, &destinationRectangle, sourceRectangle); }
  void FillOpacityMask(ID2D1Bitmap * opacityMask, ID2D1Brush * brush, const D2D1_RECT_F& destinationRectangle, const D2D1_RECT_F& sourceRectangle) noexcept { FillOpacityMask(opacityMask, brush, &destinationRectangle, &sourceRectangle); }
  void SetRenderingControls(const D2D1_RENDERING_CONTROLS& renderingControls) noexcept { return SetRenderingControls(&renderingControls); }
};

struct D2D1_PRINT_CONTROL_PROPERTIES {
  D2D1_PRINT_FONT_SUBSET_MODE fontSubset;
  float rasterDPI;
  D2D1_COLOR_SPACE colorSpace;
};

struct IPrintDocumentPackageTarget;
struct IWICImagingFactory;
cominterface("47dd575d-ac05-4cdd-8049-9b02cd16f44c") ID2D1Device : ID2D1Resource {
  virtual HRESULT __stdcall CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS options, ID2D1DeviceContext * *deviceContext) noexcept = 0;
  virtual HRESULT __stdcall CreatePrintControl(IWICImagingFactory*, IPrintDocumentPackageTarget*, const D2D1_PRINT_CONTROL_PROPERTIES*, ID2D1PrintControl**) noexcept = 0;
  virtual void __stdcall SetMaximumTextureMemory(size_t) noexcept = 0;
  virtual size_t __stdcall GetMaximumTextureMemory() const noexcept = 0;
  virtual void __stdcall ClearResources(int = 0) noexcept = 0;
  HRESULT CreatePrintControl(IWICImagingFactory * wicFactory, IPrintDocumentPackageTarget * documentTarget, const D2D1_PRINT_CONTROL_PROPERTIES& printControlProperties, ID2D1PrintControl** printControl) noexcept { return CreatePrintControl(wicFactory, documentTarget, &printControlProperties, printControl); }
};

struct D2D1_STROKE_STYLE_PROPERTIES1 {
  D2D1_CAP_STYLE startCap, endCap, dashCap;
  D2D1_LINE_JOIN lineJoin;
  float miterLimit;
  D2D1_DASH_STYLE dashStyle;
  float dashOffset;
  D2D1_STROKE_TRANSFORM_TYPE transformType;
};

struct D2D1_PROPERTY_BINDING;
cominterface("bb12d362-daee-4b9a-aa1d-14ba401cfa1f") ID2D1Factory1 : ID2D1Factory {
  virtual HRESULT __stdcall CreateDevice(IDXGIDevice*, ID2D1Device**) noexcept = 0;
  virtual HRESULT __stdcall CreateStrokeStyle(const D2D1_STROKE_STYLE_PROPERTIES1*, const float*, int, ID2D1StrokeStyle1**) noexcept = 0;
  using ID2D1Factory::CreateStrokeStyle;
  virtual HRESULT __stdcall CreatePathGeometry(ID2D1PathGeometry1**) noexcept = 0;
  using ID2D1Factory::CreatePathGeometry;
  virtual HRESULT __stdcall CreateDrawingStateBlock(const D2D1_DRAWING_STATE_DESCRIPTION1*, IDWriteRenderingParams*, ID2D1DrawingStateBlock1**) noexcept = 0;
  using ID2D1Factory::CreateDrawingStateBlock;
  virtual HRESULT __stdcall CreateGdiMetafile(IStream*, ID2D1GdiMetafile**) noexcept = 0;
  virtual HRESULT __stdcall RegisterEffectFromStream(const GUID&, IStream*, const D2D1_PROPERTY_BINDING*, int, HRESULT(__stdcall* const)(IUnknown**)) noexcept = 0;
  virtual HRESULT __stdcall RegisterEffectFromString(const GUID&, const wchar_t*, const D2D1_PROPERTY_BINDING*, int, HRESULT(__stdcall* const)(IUnknown**)) noexcept = 0;
  virtual HRESULT __stdcall UnregisterEffect(const GUID&) noexcept = 0;
  virtual HRESULT __stdcall GetRegisteredEffects(GUID*, int, int*, int*) const noexcept = 0;
  virtual HRESULT __stdcall GetEffectProperties(const GUID&, ID2D1Properties**) const noexcept = 0;
  HRESULT CreateStrokeStyle(const D2D1_STROKE_STYLE_PROPERTIES1& strokeStyleProperties, const float* dashes, int dashesCount, ID2D1StrokeStyle1** strokeStyle) noexcept { return CreateStrokeStyle(&strokeStyleProperties, dashes, dashesCount, strokeStyle); }
  HRESULT CreateDrawingStateBlock(const D2D1_DRAWING_STATE_DESCRIPTION1& drawingStateDescription, ID2D1DrawingStateBlock1** drawingStateBlock) noexcept { return CreateDrawingStateBlock(&drawingStateDescription, nullptr, drawingStateBlock); }
  HRESULT CreateDrawingStateBlock(ID2D1DrawingStateBlock1 * *drawingStateBlock) noexcept { return CreateDrawingStateBlock(nullptr, nullptr, drawingStateBlock); }
};

cominterface("31e6e7bc-e0ff-4d46-8c64-a0a8c41c15d3") ID2D1Multithread : IUnknown {
  virtual int __stdcall GetMultithreadProtected() const noexcept = 0;
  virtual void __stdcall Enter() noexcept = 0;
  virtual void __stdcall Leave() noexcept = 0;
};
}
__ywlib_exportcend;
#endif
