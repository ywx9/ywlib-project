#pragma once
#include <inc/d3d11.h>

#ifndef __ywlib_import
__ywlib_exportc;
extern "C++" {

enum class D2D1_ALPHA_MODE {
  D2D1_ALPHA_MODE_UNKNOWN,
  D2D1_ALPHA_MODE_PREMULTIPLIED,
  D2D1_ALPHA_MODE_STRAIGHT,
  D2D1_ALPHA_MODE_IGNORE,
};
using enum D2D1_ALPHA_MODE;

enum D2D1_ANTIALIAS_MODE {
  D2D1_ANTIALIAS_MODE_PER_PRIMITIVE,
  D2D1_ANTIALIAS_MODE_ALIASED,
};
using enum D2D1_ANTIALIAS_MODE;

enum class D2D1_ARC_SIZE {
  D2D1_ARC_SIZE_SMALL,
  D2D1_ARC_SIZE_LARGE,
};
using enum D2D1_ARC_SIZE;

enum class D2D1_BITMAP_INTERPOLATION_MODE {
  D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
  D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
};
using enum D2D1_BITMAP_INTERPOLATION_MODE;

enum class D2D1_CAP_STYLE {
  D2D1_CAP_STYLE_FLAT,
  D2D1_CAP_STYLE_SQUARE,
  D2D1_CAP_STYLE_ROUND,
  D2D1_CAP_STYLE_TRIANGLE,
};
using enum D2D1_CAP_STYLE;

enum class D2D1_COMBINE_MODE {
  D2D1_COMBINE_MODE_UNION,
  D2D1_COMBINE_MODE_INTERSECT,
  D2D1_COMBINE_MODE_XOR,
  D2D1_COMBINE_MODE_EXCLUDE,
};
using enum D2D1_COMBINE_MODE;

enum class D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS {
  D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE,
  D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_GDI_COMPATIBLE,
};
using enum D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS;

enum class D2D1_DASH_STYLE {
  D2D1_DASH_STYLE_SOLID,
  D2D1_DASH_STYLE_DASH,
  D2D1_DASH_STYLE_DOT,
  D2D1_DASH_STYLE_DASH_DOT,
  D2D1_DASH_STYLE_DASH_DOT_DOT,
  D2D1_DASH_STYLE_CUSTOM,
};
using enum D2D1_DASH_STYLE;

enum class D2D1_DC_INITIALIZE_MODE {
  D2D1_DC_INITIALIZE_MODE_COPY,
  D2D1_DC_INITIALIZE_MODE_CLEAR,
};
using enum D2D1_DC_INITIALIZE_MODE;

enum class D2D1_DRAW_TEXT_OPTIONS {
  D2D1_DRAW_TEXT_OPTIONS_NONE = 0x0,
  D2D1_DRAW_TEXT_OPTIONS_NO_SNAP = 0x1,
  D2D1_DRAW_TEXT_OPTIONS_CLIP = 0x2,
  D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT = 0x4,
  D2D1_DRAW_TEXT_OPTIONS_DISABLE_COLOR_BITMAP_SNAPPING = 0x8,
};
using enum D2D1_DRAW_TEXT_OPTIONS;

enum class D2D1_EXTEND_MODE {
  D2D1_EXTEND_MODE_CLAMP,
  D2D1_EXTEND_MODE_WRAP,
  D2D1_EXTEND_MODE_MIRROR,
};
using enum D2D1_EXTEND_MODE;

enum class D2D1_FACTORY_TYPE {
  D2D1_FACTORY_TYPE_SINGLE_THREADED,
  D2D1_FACTORY_TYPE_MULTI_THREADED,
};
using enum D2D1_FACTORY_TYPE;

enum D2D1_FEATURE_LEVEL {
  D2D1_FEATURE_LEVEL_DEFAULT = 0,
  D2D1_FEATURE_LEVEL_9 = int(D3D_FEATURE_LEVEL_9_1),
  D2D1_FEATURE_LEVEL_10 = int(D3D_FEATURE_LEVEL_10_0),
};
using enum D2D1_FEATURE_LEVEL;

enum class D2D1_FIGURE_BEGIN {
  D2D1_FIGURE_BEGIN_FILLED,
  D2D1_FIGURE_BEGIN_HOLLOW,
};
using enum D2D1_FIGURE_BEGIN;

enum class D2D1_FIGURE_END {
  D2D1_FIGURE_END_OPEN,
  D2D1_FIGURE_END_CLOSED,
};
using enum D2D1_FIGURE_END;

enum class D2D1_FILL_MODE {
  D2D1_FILL_MODE_ALTERNATE,
  D2D1_FILL_MODE_WINDING,
};
using enum D2D1_FILL_MODE;

enum class D2D1_GAMMA {
  D2D1_GAMMA_2_2,
  D2D1_GAMMA_1_0,
};
using enum D2D1_GAMMA;

enum class D2D1_GEOMETRY_RELATION {
  D2D1_GEOMETRY_RELATION_UNKNOWN,
  D2D1_GEOMETRY_RELATION_DISJOINT,
  D2D1_GEOMETRY_RELATION_IS_CONTAINED,
  D2D1_GEOMETRY_RELATION_CONTAINS,
  D2D1_GEOMETRY_RELATION_OVERLAP,
};
using enum D2D1_GEOMETRY_RELATION;

enum D2D1_GEOMETRY_SIMPLIFICATION_OPTION {
  D2D1_GEOMETRY_SIMPLIFICATION_OPTION_CUBICS_AND_LINES,
  D2D1_GEOMETRY_SIMPLIFICATION_OPTION_LINES,
};
using enum D2D1_GEOMETRY_SIMPLIFICATION_OPTION;

enum class D2D1_LAYER_OPTIONS {
  D2D1_LAYER_OPTIONS_NONE,
  D2D1_LAYER_OPTIONS_INITIALIZE_FOR_CLEARTYPE,
};
using enum D2D1_LAYER_OPTIONS;

enum class D2D1_LINE_JOIN {
  D2D1_LINE_JOIN_MITER,
  D2D1_LINE_JOIN_BEVEL,
  D2D1_LINE_JOIN_ROUND,
  D2D1_LINE_JOIN_MITER_OR_BEVEL,
};
using enum D2D1_LINE_JOIN;

enum class DWRITE_MEASURING_MODE {
  DWRITE_MEASURING_MODE_NATURAL,
  DWRITE_MEASURING_MODE_GDI_CLASSIC,
  DWRITE_MEASURING_MODE_GDI_NATURAL
};
using enum DWRITE_MEASURING_MODE;

enum class D2D1_OPACITY_MASK_CONTENT {
  D2D1_OPACITY_MASK_CONTENT_GRAPHICS,
  D2D1_OPACITY_MASK_CONTENT_TEXT_NATURAL,
  D2D1_OPACITY_MASK_CONTENT_TEXT_GDI_COMPATIBLE,
};
using enum D2D1_OPACITY_MASK_CONTENT;

enum class D2D1_PATH_SEGMENT {
  D2D1_PATH_SEGMENT_NONE,
  D2D1_PATH_SEGMENT_FORCE_UNSTROKED,
  D2D1_PATH_SEGMENT_FORCE_ROUND_LINE_JOIN,
};
using enum D2D1_PATH_SEGMENT;

enum class D2D1_PRESENT_OPTIONS {
  D2D1_PRESENT_OPTIONS_NONE,
  D2D1_PRESENT_OPTIONS_RETAIN_CONTENTS,
  D2D1_PRESENT_OPTIONS_IMMEDIATELY,
};
using enum D2D1_PRESENT_OPTIONS;

enum class D2D1_RENDER_TARGET_TYPE {
  D2D1_RENDER_TARGET_TYPE_DEFAULT,
  D2D1_RENDER_TARGET_TYPE_SOFTWARE,
  D2D1_RENDER_TARGET_TYPE_HARDWARE,
};
using enum D2D1_RENDER_TARGET_TYPE;

enum class D2D1_RENDER_TARGET_USAGE {
  D2D1_RENDER_TARGET_USAGE_NONE,
  D2D1_RENDER_TARGET_USAGE_FORCE_BITMAP_REMOTING,
  D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE,
};
using enum D2D1_RENDER_TARGET_USAGE;

enum class D2D1_SWEEP_DIRECTION {
  D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE,
  D2D1_SWEEP_DIRECTION_CLOCKWISE,
};
using enum D2D1_SWEEP_DIRECTION;

enum class D2D1_TEXT_ANTIALIAS_MODE {
  D2D1_TEXT_ANTIALIAS_MODE_DEFAULT,
  D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE,
  D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE,
  D2D1_TEXT_ANTIALIAS_MODE_ALIASED,
};
using enum D2D1_TEXT_ANTIALIAS_MODE;

enum class D2D1_WINDOW_STATE {
  D2D1_WINDOW_STATE_NONE,
  D2D1_WINDOW_STATE_OCCLUDED,
};
using enum D2D1_WINDOW_STATE;

struct D2D1_POINT_2F {
  float x, y;
};

struct D2D1_RECT_F {
  float left, top, right, bottom;
};

struct D2D1_SIZE_F {
  float width, height;
};

struct D2D1_COLOR_F {
  float r, g, b, a;
};

struct D2D1_MATRIX_3X2_F {
  float m[3][2];
};

cominterface("06152247-6f50-465a-9245-118bfd3b6007") ID2D1Factory;
cominterface("2cd90691-12e2-11dc-9fed-001143a055f9") ID2D1Resource : IUnknown {
  virtual void __stdcall GetFactory(ID2D1Factory**) const noexcept = 0;
};

cominterface("65019f75-8da2-497c-b32c-dfa34e48ede6") ID2D1Image : ID2D1Resource{};

struct D2D1_PIXEL_FORMAT {
  DXGI_FORMAT format;
  D2D1_ALPHA_MODE alphaMode;
};

cominterface("2cd90694-12e2-11dc-9fed-001143a055f9") ID2D1RenderTarget;
cominterface("a2296057-ea42-4099-983b-539fb6505426") ID2D1Bitmap : ID2D1Image {
  virtual D2D1_SIZE_F __stdcall GetSize() const noexcept = 0;
  virtual SIZE __stdcall GetPixelSize() const noexcept = 0;
  virtual D2D1_PIXEL_FORMAT __stdcall GetPixelFormat() const noexcept = 0;
  virtual void __stdcall GetDpi(float*, float*) const noexcept = 0;
  virtual HRESULT __stdcall CopyFromBitmap(const POINT*, ID2D1Bitmap*, const RECT*) noexcept = 0;
  virtual HRESULT __stdcall CopyFromRenderTarget(const POINT*, ID2D1RenderTarget*, const RECT*) noexcept = 0;
  virtual HRESULT __stdcall CopyFromMemory(const RECT*, const void*, int) noexcept = 0;
};

struct D2D1_GRADIENT_STOP {
  float position;
  D2D1_COLOR_F color;
};

cominterface("2cd906a7-12e2-11dc-9fed-001143a055f9") ID2D1GradientStopCollection : ID2D1Resource {
  virtual int __stdcall GetGradientStopCount() const noexcept = 0;
  virtual void __stdcall GetGradientStops(D2D1_GRADIENT_STOP*, int) const noexcept = 0;
  virtual D2D1_GAMMA __stdcall GetColorInterpolationGamma() const noexcept = 0;
  virtual D2D1_EXTEND_MODE __stdcall GetExtendMode() const noexcept = 0;
};

cominterface("2cd906a8-12e2-11dc-9fed-001143a055f9") ID2D1Brush : ID2D1Resource {
  virtual void __stdcall SetOpacity(float) noexcept = 0;
  virtual void __stdcall SetTransform(const D2D1_MATRIX_3X2_F*) noexcept = 0;
  virtual float __stdcall GetOpacity() const noexcept = 0;
  virtual void __stdcall GetTransform(D2D1_MATRIX_3X2_F*) const noexcept = 0;
  void SetTransform(const D2D1_MATRIX_3X2_F& transform) noexcept { SetTransform(&transform); }
};

cominterface("2cd906aa-12e2-11dc-9fed-001143a055f9") ID2D1BitmapBrush : ID2D1Brush {
  virtual void __stdcall SetExtendModeX(D2D1_EXTEND_MODE) noexcept = 0;
  virtual void __stdcall SetExtendModeY(D2D1_EXTEND_MODE) noexcept = 0;
  virtual void __stdcall SetInterpolationMode(D2D1_BITMAP_INTERPOLATION_MODE) noexcept = 0;
  virtual void __stdcall SetBitmap(ID2D1Bitmap*) noexcept = 0;
  virtual D2D1_EXTEND_MODE __stdcall GetExtendModeX() const noexcept = 0;
  virtual D2D1_EXTEND_MODE __stdcall GetExtendModeY() const noexcept = 0;
  virtual D2D1_BITMAP_INTERPOLATION_MODE __stdcall GetInterpolationMode() const noexcept = 0;
  virtual void __stdcall GetBitmap(ID2D1Bitmap**) const noexcept = 0;
};

cominterface("2cd906a9-12e2-11dc-9fed-001143a055f9") ID2D1SolidColorBrush : ID2D1Brush {
  virtual void __stdcall SetColor(const void*) noexcept = 0;
  virtual D2D1_COLOR_F __stdcall GetColor() const noexcept = 0;
  void SetColor(const D2D1_COLOR_F& color) noexcept { SetColor(&color); }
};

cominterface("2cd906ab-12e2-11dc-9fed-001143a055f9") ID2D1LinearGradientBrush : ID2D1Brush {
  virtual void __stdcall SetStartPoint(D2D1_POINT_2F) noexcept = 0;
  virtual void __stdcall SetEndPoint(D2D1_POINT_2F) noexcept = 0;
  virtual D2D1_POINT_2F __stdcall GetStartPoint() const noexcept = 0;
  virtual D2D1_POINT_2F __stdcall GetEndPoint() const noexcept = 0;
  virtual void __stdcall GetGradientStopCollection(ID2D1GradientStopCollection**) const noexcept = 0;
};

cominterface("2cd906ac-12e2-11dc-9fed-001143a055f9") ID2D1RadialGradientBrush : ID2D1Brush {
  virtual void __stdcall SetCenter(D2D1_POINT_2F) noexcept = 0;
  virtual void __stdcall SetGradientOriginOffset(D2D1_POINT_2F) noexcept = 0;
  virtual void __stdcall SetRadiusX(float) noexcept = 0;
  virtual void __stdcall SetRadiusY(float) noexcept = 0;
  virtual D2D1_POINT_2F __stdcall GetCenter() const noexcept = 0;
  virtual D2D1_POINT_2F __stdcall GetGradientOriginOffset() const noexcept = 0;
  virtual float __stdcall GetRadiusX() const noexcept = 0;
  virtual float __stdcall GetRadiusY() const noexcept = 0;
  virtual void __stdcall GetGradientStopCollection(ID2D1GradientStopCollection**) const noexcept = 0;
};

cominterface("2cd9069d-12e2-11dc-9fed-001143a055f9") ID2D1StrokeStyle : ID2D1Resource {
  virtual D2D1_CAP_STYLE __stdcall GetStartCap() const noexcept = 0;
  virtual D2D1_CAP_STYLE __stdcall GetEndCap() const noexcept = 0;
  virtual D2D1_CAP_STYLE __stdcall GetDashCap() const noexcept = 0;
  virtual float __stdcall GetMiterLimit() const noexcept = 0;
  virtual D2D1_LINE_JOIN __stdcall GetLineJoin() const noexcept = 0;
  virtual float __stdcall GetDashOffset() const noexcept = 0;
  virtual D2D1_DASH_STYLE __stdcall GetDashStyle() const noexcept = 0;
  virtual int __stdcall GetDashesCount() const noexcept = 0;
  virtual void __stdcall GetDashes(float*, int) const noexcept = 0;
};

struct D2D1_BEZIER_SEGMENT {
  D2D1_POINT_2F point1, point2, point3;
};

cominterface("2cd9069e-12e2-11dc-9fed-001143a055f9") ID2D1SimplifiedGeometrySink : IUnknown {
  virtual void __stdcall SetFillMode(D2D1_FILL_MODE) noexcept = 0;
  virtual void __stdcall SetSegmentFlags(D2D1_PATH_SEGMENT) noexcept = 0;
  virtual void __stdcall BeginFigure(D2D1_POINT_2F, D2D1_FIGURE_BEGIN) noexcept = 0;
  virtual void __stdcall AddLines(const D2D1_POINT_2F*, int) noexcept = 0;
  virtual void __stdcall AddBeziers(const D2D1_BEZIER_SEGMENT*, int) noexcept = 0;
  virtual void __stdcall EndFigure(D2D1_FIGURE_END) noexcept = 0;
  virtual HRESULT __stdcall Close() noexcept = 0;
};

struct D2D1_ARC_SEGMENT {
  D2D1_POINT_2F point;
  D2D1_SIZE_F size;
  float rotationAngle;
  D2D1_SWEEP_DIRECTION sweepDirection;
  D2D1_ARC_SIZE arcSize;
};

struct D2D1_QUADRATIC_BEZIER_SEGMENT {
  D2D1_POINT_2F point1, point2;
};

cominterface("2cd9069f-12e2-11dc-9fed-001143a055f9") ID2D1GeometrySink : ID2D1SimplifiedGeometrySink {
  virtual void __stdcall AddLine(D2D1_POINT_2F) noexcept = 0;
  virtual void __stdcall AddBezier(const D2D1_BEZIER_SEGMENT*) noexcept = 0;
  virtual void __stdcall AddQuadraticBezier(const D2D1_QUADRATIC_BEZIER_SEGMENT*) noexcept = 0;
  virtual void __stdcall AddQuadraticBeziers(const D2D1_QUADRATIC_BEZIER_SEGMENT*, int) noexcept = 0;
  virtual void __stdcall AddArc(const D2D1_ARC_SEGMENT*) noexcept = 0;
  void AddBezier(const D2D1_BEZIER_SEGMENT& bezier) noexcept { AddBezier(&bezier); }
  void AddQuadraticBezier(const D2D1_QUADRATIC_BEZIER_SEGMENT& bezier) noexcept { AddQuadraticBezier(&bezier); }
  void AddArc(const D2D1_ARC_SEGMENT& arc) noexcept { AddArc(&arc); }
};

struct D2D1_TRIANGLE {
  D2D1_POINT_2F point1, point2, point3;
};

cominterface("2cd906c1-12e2-11dc-9fed-001143a055f9") ID2D1TessellationSink : IUnknown {
  virtual void __stdcall AddTriangles(const D2D1_TRIANGLE*, int) noexcept = 0;
  virtual HRESULT __stdcall Close() noexcept = 0;
};

cominterface("2cd906a1-12e2-11dc-9fed-001143a055f9") ID2D1Geometry : ID2D1Resource {
  virtual HRESULT __stdcall GetBounds(const D2D1_MATRIX_3X2_F*, D2D1_RECT_F*) const noexcept = 0;
  virtual HRESULT __stdcall GetWidenedBounds(float, ID2D1StrokeStyle*, const D2D1_MATRIX_3X2_F*, float, D2D1_RECT_F*) const noexcept = 0;
  virtual HRESULT __stdcall StrokeContainsPoint(D2D1_POINT_2F, float, ID2D1StrokeStyle*, const D2D1_MATRIX_3X2_F*, float, int*) const noexcept = 0;
  virtual HRESULT __stdcall FillContainsPoint(D2D1_POINT_2F, const D2D1_MATRIX_3X2_F*, float, int*) const noexcept = 0;
  virtual HRESULT __stdcall CompareWithGeometry(ID2D1Geometry*, const D2D1_MATRIX_3X2_F*, float, D2D1_GEOMETRY_RELATION*) const noexcept = 0;
  virtual HRESULT __stdcall Simplify(D2D1_GEOMETRY_SIMPLIFICATION_OPTION, const D2D1_MATRIX_3X2_F*, float, ID2D1SimplifiedGeometrySink*) const noexcept = 0;
  virtual HRESULT __stdcall Tessellate(const D2D1_MATRIX_3X2_F*, float, ID2D1TessellationSink*) const noexcept = 0;
  virtual HRESULT __stdcall CombineWithGeometry(ID2D1Geometry*, D2D1_COMBINE_MODE, const D2D1_MATRIX_3X2_F*, float, ID2D1SimplifiedGeometrySink*) const noexcept = 0;
  virtual HRESULT __stdcall Outline(const D2D1_MATRIX_3X2_F*, float, ID2D1SimplifiedGeometrySink*) const noexcept = 0;
  virtual HRESULT __stdcall ComputeArea(const D2D1_MATRIX_3X2_F*, float, float*) const noexcept = 0;
  virtual HRESULT __stdcall ComputeLength(const D2D1_MATRIX_3X2_F*, float, float*) const noexcept = 0;
  virtual HRESULT __stdcall ComputePointAtLength(float, const D2D1_MATRIX_3X2_F*, float, D2D1_POINT_2F*, D2D1_POINT_2F*) const noexcept = 0;
  virtual HRESULT __stdcall Widen(float, ID2D1StrokeStyle*, const D2D1_MATRIX_3X2_F*, float, ID2D1SimplifiedGeometrySink*) const noexcept = 0;
  HRESULT GetBounds(const D2D1_MATRIX_3X2_F& worldTransform, D2D1_RECT_F* bounds) const noexcept { return GetBounds(&worldTransform, bounds); }
  HRESULT GetWidenedBounds(float strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F& worldTransform, float flatteningTolerance, D2D1_RECT_F* bounds) const noexcept { return GetWidenedBounds(strokeWidth, strokeStyle, &worldTransform, flatteningTolerance, bounds); }
  HRESULT GetWidenedBounds(float strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F* worldTransform, D2D1_RECT_F* bounds) const noexcept { return GetWidenedBounds(strokeWidth, strokeStyle, worldTransform, 0.25f, bounds); }
  HRESULT GetWidenedBounds(float strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F& worldTransform, D2D1_RECT_F* bounds) const noexcept { return GetWidenedBounds(strokeWidth, strokeStyle, &worldTransform, 0.25f, bounds); }
  HRESULT StrokeContainsPoint(D2D1_POINT_2F point, float strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F& worldTransform, float flatteningTolerance, int* contains) const { return StrokeContainsPoint(point, strokeWidth, strokeStyle, &worldTransform, flatteningTolerance, contains); }
  HRESULT StrokeContainsPoint(D2D1_POINT_2F point, float strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F* worldTransform, int* contains) const noexcept { return StrokeContainsPoint(point, strokeWidth, strokeStyle, worldTransform, 0.25f, contains); }
  HRESULT StrokeContainsPoint(D2D1_POINT_2F point, float strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F& worldTransform, int* contains) const noexcept { return StrokeContainsPoint(point, strokeWidth, strokeStyle, &worldTransform, 0.25f, contains); }
  HRESULT FillContainsPoint(D2D1_POINT_2F point, const D2D1_MATRIX_3X2_F& worldTransform, float flatteningTolerance, int* contains) const noexcept { return FillContainsPoint(point, &worldTransform, flatteningTolerance, contains); }
  HRESULT FillContainsPoint(D2D1_POINT_2F point, const D2D1_MATRIX_3X2_F* worldTransform, int* contains) const noexcept { return FillContainsPoint(point, worldTransform, 0.25f, contains); }
  HRESULT FillContainsPoint(D2D1_POINT_2F point, const D2D1_MATRIX_3X2_F& worldTransform, int* contains) const noexcept { return FillContainsPoint(point, &worldTransform, 0.25f, contains); }
  HRESULT CompareWithGeometry(ID2D1Geometry * inputGeometry, const D2D1_MATRIX_3X2_F& inputGeometryTransform, float flatteningTolerance, D2D1_GEOMETRY_RELATION* relation) const noexcept { return CompareWithGeometry(inputGeometry, &inputGeometryTransform, flatteningTolerance, relation); }
  HRESULT CompareWithGeometry(ID2D1Geometry * inputGeometry, const D2D1_MATRIX_3X2_F* inputGeometryTransform, D2D1_GEOMETRY_RELATION* relation) const noexcept { return CompareWithGeometry(inputGeometry, inputGeometryTransform, 0.25f, relation); }
  HRESULT CompareWithGeometry(ID2D1Geometry * inputGeometry, const D2D1_MATRIX_3X2_F& inputGeometryTransform, D2D1_GEOMETRY_RELATION* relation) const noexcept { return CompareWithGeometry(inputGeometry, &inputGeometryTransform, 0.25f, relation); }
  HRESULT Simplify(D2D1_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption, const D2D1_MATRIX_3X2_F& worldTransform, float flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink) const noexcept { return Simplify(simplificationOption, &worldTransform, flatteningTolerance, geometrySink); }
  HRESULT Simplify(D2D1_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption, const D2D1_MATRIX_3X2_F* worldTransform, ID2D1SimplifiedGeometrySink* geometrySink) const noexcept { return Simplify(simplificationOption, worldTransform, 0.25f, geometrySink); }
  HRESULT Simplify(D2D1_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption, const D2D1_MATRIX_3X2_F& worldTransform, ID2D1SimplifiedGeometrySink* geometrySink) const noexcept { return Simplify(simplificationOption, &worldTransform, 0.25f, geometrySink); }
  HRESULT Tessellate(const D2D1_MATRIX_3X2_F& worldTransform, float flatteningTolerance, ID2D1TessellationSink* tessellationSink) const noexcept { return Tessellate(&worldTransform, flatteningTolerance, tessellationSink); }
  HRESULT Tessellate(const D2D1_MATRIX_3X2_F* worldTransform, ID2D1TessellationSink* tessellationSink) const noexcept { return Tessellate(worldTransform, 0.25f, tessellationSink); }
  HRESULT Tessellate(const D2D1_MATRIX_3X2_F& worldTransform, ID2D1TessellationSink* tessellationSink) const noexcept { return Tessellate(&worldTransform, 0.25f, tessellationSink); }
  HRESULT CombineWithGeometry(ID2D1Geometry * inputGeometry, D2D1_COMBINE_MODE combineMode, const D2D1_MATRIX_3X2_F& inputGeometryTransform, float flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink) const noexcept { return CombineWithGeometry(inputGeometry, combineMode, &inputGeometryTransform, flatteningTolerance, geometrySink); }
  HRESULT CombineWithGeometry(ID2D1Geometry * inputGeometry, D2D1_COMBINE_MODE combineMode, const D2D1_MATRIX_3X2_F* inputGeometryTransform, ID2D1SimplifiedGeometrySink* geometrySink) const noexcept { return CombineWithGeometry(inputGeometry, combineMode, inputGeometryTransform, 0.25f, geometrySink); }
  HRESULT CombineWithGeometry(ID2D1Geometry * inputGeometry, D2D1_COMBINE_MODE combineMode, const D2D1_MATRIX_3X2_F& inputGeometryTransform, ID2D1SimplifiedGeometrySink* geometrySink) const noexcept { return CombineWithGeometry(inputGeometry, combineMode, &inputGeometryTransform, 0.25f, geometrySink); }
  HRESULT Outline(const D2D1_MATRIX_3X2_F& worldTransform, float flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink) const noexcept { return Outline(&worldTransform, flatteningTolerance, geometrySink); }
  HRESULT Outline(const D2D1_MATRIX_3X2_F* worldTransform, ID2D1SimplifiedGeometrySink* geometrySink) const noexcept { return Outline(worldTransform, 0.25f, geometrySink); }
  HRESULT Outline(const D2D1_MATRIX_3X2_F& worldTransform, ID2D1SimplifiedGeometrySink* geometrySink) const noexcept { return Outline(&worldTransform, 0.25f, geometrySink); }
  HRESULT ComputeArea(const D2D1_MATRIX_3X2_F& worldTransform, float flatteningTolerance, float* area) const noexcept { return ComputeArea(&worldTransform, flatteningTolerance, area); }
  HRESULT ComputeArea(const D2D1_MATRIX_3X2_F* worldTransform, float* area) const noexcept { return ComputeArea(worldTransform, 0.25f, area); }
  HRESULT ComputeArea(const D2D1_MATRIX_3X2_F& worldTransform, float* area) const noexcept { return ComputeArea(&worldTransform, 0.25f, area); }
  HRESULT ComputeLength(const D2D1_MATRIX_3X2_F& worldTransform, float flatteningTolerance, float* length) const noexcept { return ComputeLength(&worldTransform, flatteningTolerance, length); }
  HRESULT ComputeLength(const D2D1_MATRIX_3X2_F* worldTransform, float* length) const noexcept { return ComputeLength(worldTransform, 0.25f, length); }
  HRESULT ComputeLength(const D2D1_MATRIX_3X2_F& worldTransform, float* length) const noexcept { return ComputeLength(&worldTransform, 0.25f, length); }
  HRESULT ComputePointAtLength(float length, const D2D1_MATRIX_3X2_F& worldTransform, float flatteningTolerance, D2D1_POINT_2F* point, D2D1_POINT_2F* unitTangentVector) const noexcept { return ComputePointAtLength(length, &worldTransform, flatteningTolerance, point, unitTangentVector); }
  HRESULT ComputePointAtLength(float length, const D2D1_MATRIX_3X2_F* worldTransform, D2D1_POINT_2F* point, D2D1_POINT_2F* unitTangentVector) const noexcept { return ComputePointAtLength(length, worldTransform, 0.25f, point, unitTangentVector); }
  HRESULT ComputePointAtLength(float length, const D2D1_MATRIX_3X2_F& worldTransform, D2D1_POINT_2F* point, D2D1_POINT_2F* unitTangentVector) const noexcept { return ComputePointAtLength(length, &worldTransform, 0.25f, point, unitTangentVector); }
  HRESULT Widen(float strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F& worldTransform, float flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink) const noexcept { return Widen(strokeWidth, strokeStyle, &worldTransform, flatteningTolerance, geometrySink); }
  HRESULT Widen(float strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F* worldTransform, ID2D1SimplifiedGeometrySink* geometrySink) const noexcept { return Widen(strokeWidth, strokeStyle, worldTransform, 0.25f, geometrySink); }
  HRESULT Widen(float strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F& worldTransform, ID2D1SimplifiedGeometrySink* geometrySink) const noexcept { return Widen(strokeWidth, strokeStyle, &worldTransform, 0.25f, geometrySink); }
};

cominterface("2cd906a2-12e2-11dc-9fed-001143a055f9") ID2D1RectangleGeometry : ID2D1Geometry {
  virtual void __stdcall GetRect(D2D1_RECT_F*) const noexcept = 0;
};

struct D2D1_ROUNDED_RECT {
  D2D1_RECT_F rect;
  float radiusX, radiusY;
};

cominterface("2cd906a3-12e2-11dc-9fed-001143a055f9") ID2D1RoundedRectangleGeometry : ID2D1Geometry {
  virtual void __stdcall GetRoundedRect(D2D1_ROUNDED_RECT*) const noexcept = 0;
};

struct D2D1_ELLIPSE {
  D2D1_POINT_2F point;
  float radiusX, radiusY;
};

cominterface("2cd906a4-12e2-11dc-9fed-001143a055f9") ID2D1EllipseGeometry : ID2D1Geometry {
  virtual void __stdcall GetEllipse(D2D1_ELLIPSE*) const noexcept = 0;
};

cominterface("2cd906a6-12e2-11dc-9fed-001143a055f9") ID2D1GeometryGroup : ID2D1Geometry {
  virtual D2D1_FILL_MODE __stdcall GetFillMode() const noexcept = 0;
  virtual int __stdcall GetSourceGeometryCount() const noexcept = 0;
  virtual void __stdcall GetSourceGeometries(ID2D1Geometry**, int) const noexcept = 0;
};

cominterface("2cd906bb-12e2-11dc-9fed-001143a055f9") ID2D1TransformedGeometry : ID2D1Geometry {
  virtual void __stdcall GetSourceGeometry(ID2D1Geometry**) const noexcept = 0;
  virtual void __stdcall GetTransform(D2D1_MATRIX_3X2_F*) const noexcept = 0;
};

cominterface("2cd906a5-12e2-11dc-9fed-001143a055f9") ID2D1PathGeometry : ID2D1Geometry {
  virtual HRESULT __stdcall Open(ID2D1GeometrySink**) noexcept = 0;
  virtual HRESULT __stdcall Stream(ID2D1GeometrySink*) const noexcept = 0;
  virtual HRESULT __stdcall GetSegmentCount(int*) const noexcept = 0;
  virtual HRESULT __stdcall GetFigureCount(int*) const noexcept = 0;
};

cominterface("2cd906c2-12e2-11dc-9fed-001143a055f9") ID2D1Mesh : ID2D1Resource {
  virtual HRESULT __stdcall Open(ID2D1TessellationSink**) noexcept = 0;
};

cominterface("2cd9069b-12e2-11dc-9fed-001143a055f9") ID2D1Layer : ID2D1Resource {
  virtual D2D1_SIZE_F __stdcall GetSize() const noexcept = 0;
};

struct D2D1_DRAWING_STATE_DESCRIPTION {
  D2D1_ANTIALIAS_MODE antialiasMode;
  D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode;
  size_t tag1, tag2;
  D2D1_MATRIX_3X2_F transform;
};

struct IDWriteRenderingParams;
cominterface("28506e39-ebf6-46a1-bb47-fd85565ab957") ID2D1DrawingStateBlock : ID2D1Resource {
  virtual void __stdcall GetDescription(D2D1_DRAWING_STATE_DESCRIPTION*) const noexcept = 0;
  virtual void __stdcall SetDescription(const D2D1_DRAWING_STATE_DESCRIPTION*) noexcept = 0;
  virtual void __stdcall SetTextRenderingParams(IDWriteRenderingParams* = nullptr) noexcept = 0;
  virtual void __stdcall GetTextRenderingParams(IDWriteRenderingParams**) const noexcept = 0;
  void SetDescription(const D2D1_DRAWING_STATE_DESCRIPTION& stateDescription) noexcept { SetDescription(&stateDescription); }
};

struct D2D1_BITMAP_BRUSH_PROPERTIES {
  D2D1_EXTEND_MODE extendModeX, extendModeY;
  D2D1_BITMAP_INTERPOLATION_MODE interpolationMode;
};

struct D2D1_BITMAP_PROPERTIES {
  D2D1_PIXEL_FORMAT pixelFormat;
  float dpiX, dpiY;
};

struct D2D1_BRUSH_PROPERTIES {
  float opacity;
  D2D1_MATRIX_3X2_F transform;
};

struct DWRITE_GLYPH_OFFSET;
struct IDWriteFontFace;
struct DWRITE_GLYPH_RUN {
  IDWriteFontFace* fontFace;
  float fontEmSize;
  int glyphCount;
  const uint16_t* glyphIndices;
  const float* glyphAdvances;
  const DWRITE_GLYPH_OFFSET* glyphOffsets;
  int isSideways;
  int bidiLevel;
};

struct D2D1_LAYER_PARAMETERS {
  D2D1_RECT_F contentBounds;
  ID2D1Geometry* geometricMask;
  D2D1_ANTIALIAS_MODE maskAntialiasMode;
  D2D1_MATRIX_3X2_F maskTransform;
  float opacity;
  ID2D1Brush* opacityBrush;
  D2D1_LAYER_OPTIONS layerOptions;
};

struct D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES {
  D2D1_POINT_2F startPoint, endPoint;
};

struct D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES {
  D2D1_POINT_2F center, gradientOriginOffset;
  float radiusX, radiusY;
};

struct D2D1_RENDER_TARGET_PROPERTIES {
  D2D1_RENDER_TARGET_TYPE type;
  D2D1_PIXEL_FORMAT pixelFormat;
  float dpiX, dpiY;
  D2D1_RENDER_TARGET_USAGE usage;
  D2D1_FEATURE_LEVEL minLevel;
};

struct DWRITE_GLYPH_RUN;
struct IDWriteTextFormat;
struct IDWriteTextLayout;
struct IWICBitmapSource;
cominterface("2cd90695-12e2-11dc-9fed-001143a055f9") ID2D1BitmapRenderTarget;
cominterface("2cd90694-12e2-11dc-9fed-001143a055f9") ID2D1RenderTarget : ID2D1Resource {
  virtual HRESULT __stdcall CreateBitmap(SIZE, const void*, int, const D2D1_BITMAP_PROPERTIES*, ID2D1Bitmap**) noexcept = 0;
  virtual HRESULT __stdcall CreateBitmapFromWicBitmap(IWICBitmapSource*, const D2D1_BITMAP_PROPERTIES*, ID2D1Bitmap**) noexcept = 0;
  virtual HRESULT __stdcall CreateSharedBitmap(const GUID&, void*, const D2D1_BITMAP_PROPERTIES*, ID2D1Bitmap**) noexcept = 0;
  virtual HRESULT __stdcall CreateBitmapBrush(ID2D1Bitmap*, const D2D1_BITMAP_BRUSH_PROPERTIES*, const D2D1_BRUSH_PROPERTIES*, ID2D1BitmapBrush**) noexcept = 0;
  virtual HRESULT __stdcall CreateSolidColorBrush(const void*, const D2D1_BRUSH_PROPERTIES*, ID2D1SolidColorBrush**) noexcept = 0;
  virtual HRESULT __stdcall CreateGradientStopCollection(const D2D1_GRADIENT_STOP*, int, D2D1_GAMMA, D2D1_EXTEND_MODE, ID2D1GradientStopCollection**) noexcept = 0;
  virtual HRESULT __stdcall CreateLinearGradientBrush(const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES*, const D2D1_BRUSH_PROPERTIES*, ID2D1GradientStopCollection*, ID2D1LinearGradientBrush**) noexcept = 0;
  virtual HRESULT __stdcall CreateRadialGradientBrush(const D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES*, const D2D1_BRUSH_PROPERTIES*, ID2D1GradientStopCollection*, ID2D1RadialGradientBrush**) noexcept = 0;
  virtual HRESULT __stdcall CreateCompatibleRenderTarget(const D2D1_SIZE_F*, const SIZE*, const D2D1_PIXEL_FORMAT*, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS, ID2D1BitmapRenderTarget**) noexcept = 0;
  virtual HRESULT __stdcall CreateLayer(const D2D1_SIZE_F*, ID2D1Layer**) noexcept = 0;
  virtual HRESULT __stdcall CreateMesh(ID2D1Mesh**) noexcept = 0;
  virtual void __stdcall DrawLine(D2D1_POINT_2F, D2D1_POINT_2F, ID2D1Brush*, float = 1.0f, ID2D1StrokeStyle* = nullptr) noexcept = 0;
  virtual void __stdcall DrawRectangle(const D2D1_RECT_F*, ID2D1Brush*, float = 1.0f, ID2D1StrokeStyle* = nullptr) noexcept = 0;
  virtual void __stdcall FillRectangle(const D2D1_RECT_F*, ID2D1Brush*) noexcept = 0;
  virtual void __stdcall DrawRoundedRectangle(const D2D1_ROUNDED_RECT*, ID2D1Brush*, float = 1.0f, ID2D1StrokeStyle* = nullptr) noexcept = 0;
  virtual void __stdcall FillRoundedRectangle(const D2D1_ROUNDED_RECT*, ID2D1Brush*) noexcept = 0;
  virtual void __stdcall DrawEllipse(const D2D1_ELLIPSE*, ID2D1Brush*, float = 1.0f, ID2D1StrokeStyle* = nullptr) noexcept = 0;
  virtual void __stdcall FillEllipse(const D2D1_ELLIPSE*, ID2D1Brush*) noexcept = 0;
  virtual void __stdcall DrawGeometry(ID2D1Geometry*, ID2D1Brush*, float = 1.0f, ID2D1StrokeStyle* = nullptr) noexcept = 0;
  virtual void __stdcall FillGeometry(ID2D1Geometry*, ID2D1Brush*, ID2D1Brush* = nullptr) noexcept = 0;
  virtual void __stdcall FillMesh(ID2D1Mesh*, ID2D1Brush*) noexcept = 0;
  virtual void __stdcall FillOpacityMask(ID2D1Bitmap*, ID2D1Brush*, D2D1_OPACITY_MASK_CONTENT, const void* = nullptr, const void* = nullptr) noexcept = 0;
  virtual void __stdcall DrawBitmap(ID2D1Bitmap*, const void* = nullptr, float = 1.0f, D2D1_BITMAP_INTERPOLATION_MODE = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, const void* = nullptr) noexcept = 0;
  virtual void __stdcall DrawText(const wchar_t*, int, IDWriteTextFormat*, const void*, ID2D1Brush*, D2D1_DRAW_TEXT_OPTIONS = D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE = DWRITE_MEASURING_MODE_NATURAL) noexcept = 0;
  virtual void __stdcall DrawTextLayout(D2D1_POINT_2F, IDWriteTextLayout*, ID2D1Brush*, D2D1_DRAW_TEXT_OPTIONS = D2D1_DRAW_TEXT_OPTIONS_NONE) noexcept = 0;
  virtual void __stdcall DrawGlyphRun(D2D1_POINT_2F, const DWRITE_GLYPH_RUN*, ID2D1Brush*, DWRITE_MEASURING_MODE = DWRITE_MEASURING_MODE_NATURAL) noexcept = 0;
  virtual void __stdcall SetTransform(const D2D1_MATRIX_3X2_F*) noexcept = 0;
  virtual void __stdcall GetTransform(D2D1_MATRIX_3X2_F*) const noexcept = 0;
  virtual void __stdcall SetAntialiasMode(D2D1_ANTIALIAS_MODE) noexcept = 0;
  virtual D2D1_ANTIALIAS_MODE __stdcall GetAntialiasMode() const noexcept = 0;
  virtual void __stdcall SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE) noexcept = 0;
  virtual D2D1_TEXT_ANTIALIAS_MODE __stdcall GetTextAntialiasMode() const noexcept = 0;
  virtual void __stdcall SetTextRenderingParams(IDWriteRenderingParams* = nullptr) noexcept = 0;
  virtual void __stdcall GetTextRenderingParams(IDWriteRenderingParams**) const noexcept = 0;
  virtual void __stdcall SetTags(size_t, size_t) noexcept = 0;
  virtual void __stdcall GetTags(size_t* = nullptr, size_t* = nullptr) const noexcept = 0;
  virtual void __stdcall PushLayer(const D2D1_LAYER_PARAMETERS*, ID2D1Layer*) noexcept = 0;
  virtual void __stdcall PopLayer() noexcept = 0;
  virtual HRESULT __stdcall Flush(size_t* = nullptr, size_t* = nullptr) noexcept = 0;
  virtual void __stdcall SaveDrawingState(ID2D1DrawingStateBlock*) const noexcept = 0;
  virtual void __stdcall RestoreDrawingState(ID2D1DrawingStateBlock*) noexcept = 0;
  virtual void __stdcall PushAxisAlignedClip(const D2D1_RECT_F*, D2D1_ANTIALIAS_MODE) noexcept = 0;
  virtual void __stdcall PopAxisAlignedClip() noexcept = 0;
  virtual void __stdcall Clear(const void* = nullptr) noexcept = 0;
  virtual void __stdcall BeginDraw() noexcept = 0;
  virtual HRESULT __stdcall EndDraw(size_t* = nullptr, size_t* = nullptr) noexcept = 0;
  virtual D2D1_PIXEL_FORMAT __stdcall GetPixelFormat() const noexcept = 0;
  virtual void __stdcall SetDpi(float, float) noexcept = 0;
  virtual void __stdcall GetDpi(float*, float*) const noexcept = 0;
  virtual D2D1_SIZE_F __stdcall GetSize() const noexcept = 0;
  virtual SIZE __stdcall GetPixelSize() const noexcept = 0;
  virtual int __stdcall GetMaximumBitmapSize() const noexcept = 0;
  virtual int __stdcall IsSupported(const D2D1_RENDER_TARGET_PROPERTIES*) const noexcept = 0;
  HRESULT CreateBitmap(SIZE size, const void* srcData, int pitch, const D2D1_BITMAP_PROPERTIES& bitmapProperties, ID2D1Bitmap** bitmap) { return CreateBitmap(size, srcData, pitch, &bitmapProperties, bitmap); }
  HRESULT CreateBitmap(SIZE size, const D2D1_BITMAP_PROPERTIES& bitmapProperties, ID2D1Bitmap** bitmap) { return CreateBitmap(size, nullptr, 0, &bitmapProperties, bitmap); }
  HRESULT CreateBitmapFromWicBitmap(IWICBitmapSource * wicBitmapSource, const D2D1_BITMAP_PROPERTIES& bitmapProperties, ID2D1Bitmap** bitmap) { return CreateBitmapFromWicBitmap(wicBitmapSource, &bitmapProperties, bitmap); }
  HRESULT CreateBitmapFromWicBitmap(IWICBitmapSource * wicBitmapSource, ID2D1Bitmap * *bitmap) { return CreateBitmapFromWicBitmap(wicBitmapSource, nullptr, bitmap); }
  HRESULT CreateBitmapBrush(ID2D1Bitmap * bitmap, ID2D1BitmapBrush * *bitmapBrush) { return CreateBitmapBrush(bitmap, nullptr, nullptr, bitmapBrush); }
  HRESULT CreateBitmapBrush(ID2D1Bitmap * bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES& bitmapBrushProperties, ID2D1BitmapBrush** bitmapBrush) { return CreateBitmapBrush(bitmap, &bitmapBrushProperties, nullptr, bitmapBrush); }
  HRESULT CreateBitmapBrush(ID2D1Bitmap * bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES& bitmapBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, ID2D1BitmapBrush** bitmapBrush) { return CreateBitmapBrush(bitmap, &bitmapBrushProperties, &brushProperties, bitmapBrush); }
  HRESULT CreateSolidColorBrush(const D2D1_COLOR_F& color, ID2D1SolidColorBrush** solidColorBrush) { return CreateSolidColorBrush(&color, nullptr, solidColorBrush); }
  HRESULT CreateSolidColorBrush(const D2D1_COLOR_F& color, const D2D1_BRUSH_PROPERTIES& brushProperties, ID2D1SolidColorBrush** solidColorBrush) { return CreateSolidColorBrush(&color, &brushProperties, solidColorBrush); }
  HRESULT CreateGradientStopCollection(_In_reads_(gradientStopsCount) const D2D1_GRADIENT_STOP* gradientStops, int gradientStopsCount, ID2D1GradientStopCollection** gradientStopCollection) { return CreateGradientStopCollection(gradientStops, gradientStopsCount, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, gradientStopCollection); }
  HRESULT CreateLinearGradientBrush(const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES& linearGradientBrushProperties, ID2D1GradientStopCollection* gradientStopCollection, ID2D1LinearGradientBrush** linearGradientBrush) { return CreateLinearGradientBrush(&linearGradientBrushProperties, nullptr, gradientStopCollection, linearGradientBrush); }
  HRESULT CreateLinearGradientBrush(const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES& linearGradientBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, ID2D1GradientStopCollection* gradientStopCollection, ID2D1LinearGradientBrush** linearGradientBrush) { return CreateLinearGradientBrush(&linearGradientBrushProperties, &brushProperties, gradientStopCollection, linearGradientBrush); }
  HRESULT CreateRadialGradientBrush(const D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES& radialGradientBrushProperties, ID2D1GradientStopCollection* gradientStopCollection, ID2D1RadialGradientBrush** radialGradientBrush) { return CreateRadialGradientBrush(&radialGradientBrushProperties, nullptr, gradientStopCollection, radialGradientBrush); }
  HRESULT CreateRadialGradientBrush(const D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES& radialGradientBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, ID2D1GradientStopCollection* gradientStopCollection, ID2D1RadialGradientBrush** radialGradientBrush) { return CreateRadialGradientBrush(&radialGradientBrushProperties, &brushProperties, gradientStopCollection, radialGradientBrush); }
  HRESULT CreateCompatibleRenderTarget(ID2D1BitmapRenderTarget * *bitmapRenderTarget) { return CreateCompatibleRenderTarget(nullptr, nullptr, nullptr, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE, bitmapRenderTarget); }
  HRESULT CreateCompatibleRenderTarget(D2D1_SIZE_F desiredSize, ID2D1BitmapRenderTarget * *bitmapRenderTarget) { return CreateCompatibleRenderTarget(&desiredSize, nullptr, nullptr, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE, bitmapRenderTarget); }
  HRESULT CreateCompatibleRenderTarget(D2D1_SIZE_F desiredSize, SIZE desiredPixelSize, ID2D1BitmapRenderTarget * *bitmapRenderTarget) { return CreateCompatibleRenderTarget(&desiredSize, &desiredPixelSize, nullptr, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE, bitmapRenderTarget); }
  HRESULT CreateCompatibleRenderTarget(D2D1_SIZE_F desiredSize, SIZE desiredPixelSize, D2D1_PIXEL_FORMAT desiredFormat, ID2D1BitmapRenderTarget * *bitmapRenderTarget) { return CreateCompatibleRenderTarget(&desiredSize, &desiredPixelSize, &desiredFormat, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE, bitmapRenderTarget); }
  HRESULT CreateCompatibleRenderTarget(D2D1_SIZE_F desiredSize, SIZE desiredPixelSize, D2D1_PIXEL_FORMAT desiredFormat, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options, ID2D1BitmapRenderTarget * *bitmapRenderTarget) { return CreateCompatibleRenderTarget(&desiredSize, &desiredPixelSize, &desiredFormat, options, bitmapRenderTarget); }
  HRESULT CreateLayer(D2D1_SIZE_F size, ID2D1Layer * *layer) { return CreateLayer(&size, layer); }
  HRESULT CreateLayer(ID2D1Layer * *layer) { return CreateLayer(nullptr, layer); }
  void DrawRectangle(const D2D1_RECT_F& rect, ID2D1Brush* brush, float strokeWidth = 1.0f, ID2D1StrokeStyle* strokeStyle = nullptr) noexcept { DrawRectangle(&rect, brush, strokeWidth, strokeStyle); }
  void FillRectangle(const D2D1_RECT_F& rect, ID2D1Brush* brush) noexcept { FillRectangle(&rect, brush); }
  void DrawRoundedRectangle(const D2D1_ROUNDED_RECT& roundedRect, ID2D1Brush* brush, float strokeWidth = 1.0f, ID2D1StrokeStyle* strokeStyle = nullptr) noexcept { DrawRoundedRectangle(&roundedRect, brush, strokeWidth, strokeStyle); }
  void FillRoundedRectangle(const D2D1_ROUNDED_RECT& roundedRect, ID2D1Brush* brush) noexcept { FillRoundedRectangle(&roundedRect, brush); }
  void DrawEllipse(const D2D1_ELLIPSE& ellipse, ID2D1Brush* brush, float strokeWidth = 1.0f, ID2D1StrokeStyle* strokeStyle = nullptr) noexcept { DrawEllipse(&ellipse, brush, strokeWidth, strokeStyle); }
  void FillEllipse(const D2D1_ELLIPSE& ellipse, ID2D1Brush* brush) noexcept { FillEllipse(&ellipse, brush); }
  void FillOpacityMask(ID2D1Bitmap * opacityMask, ID2D1Brush * brush, D2D1_OPACITY_MASK_CONTENT content, const D2D1_RECT_F& destinationRectangle, const D2D1_RECT_F& sourceRectangle) noexcept { FillOpacityMask(opacityMask, brush, content, &destinationRectangle, &sourceRectangle); }
  void DrawBitmap(ID2D1Bitmap * bitmap, const D2D1_RECT_F& destinationRectangle, float opacity = 1.0f, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, const D2D1_RECT_F* sourceRectangle = nullptr) noexcept { DrawBitmap(bitmap, &destinationRectangle, opacity, interpolationMode, sourceRectangle); }
  void DrawBitmap(ID2D1Bitmap * bitmap, const D2D1_RECT_F& destinationRectangle, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode, const D2D1_RECT_F& sourceRectangle) noexcept { DrawBitmap(bitmap, &destinationRectangle, opacity, interpolationMode, &sourceRectangle); }
  void SetTransform(const D2D1_MATRIX_3X2_F& transform) noexcept { SetTransform(&transform); }
  void PushLayer(const D2D1_LAYER_PARAMETERS& layerParameters, ID2D1Layer* layer) noexcept { PushLayer(&layerParameters, layer); }
  void PushAxisAlignedClip(const D2D1_RECT_F& clipRect, D2D1_ANTIALIAS_MODE antialiasMode) noexcept { return PushAxisAlignedClip(&clipRect, antialiasMode); }
  void Clear(const D2D1_COLOR_F& clearColor) noexcept { return Clear(&clearColor); }
  void DrawText(const wchar_t* string, int stringLength, IDWriteTextFormat* textFormat, const D2D1_RECT_F& layoutRect, ID2D1Brush* defaultFillBrush, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL) noexcept { return DrawText(string, stringLength, textFormat, &layoutRect, defaultFillBrush, options, measuringMode); }
  int IsSupported(const D2D1_RENDER_TARGET_PROPERTIES& renderTargetProperties) const noexcept { return IsSupported(&renderTargetProperties); }
};

cominterface("2cd90695-12e2-11dc-9fed-001143a055f9") ID2D1BitmapRenderTarget : ID2D1RenderTarget {
  virtual HRESULT __stdcall GetBitmap(ID2D1Bitmap**) noexcept = 0;
};

cominterface("2cd90698-12e2-11dc-9fed-001143a055f9") ID2D1HwndRenderTarget : ID2D1RenderTarget {
  virtual D2D1_WINDOW_STATE __stdcall CheckWindowState() noexcept = 0;
  virtual HRESULT __stdcall Resize(const SIZE*) noexcept = 0;
  virtual HANDLE __stdcall GetHwnd() const noexcept = 0;
  HRESULT Resize(const SIZE& pixelSize) noexcept { return Resize(&pixelSize); }
};

cominterface("e0db51c3-6f77-4bae-b3d5-e47509b35838") ID2D1GdiInteropRenderTarget : IUnknown {
  virtual HRESULT __stdcall GetDC(D2D1_DC_INITIALIZE_MODE mode, HANDLE*) noexcept = 0;
  virtual HRESULT __stdcall ReleaseDC(const RECT*) noexcept = 0;
};

cominterface("1c51bc64-de61-46fd-9899-63a5d8f03950") ID2D1DCRenderTarget : ID2D1RenderTarget {
  virtual HRESULT __stdcall BindDC(const HANDLE, const RECT*) noexcept = 0;
};

struct D2D1_HWND_RENDER_TARGET_PROPERTIES {
  HANDLE hwnd;
  SIZE pixelSize;
  D2D1_PRESENT_OPTIONS presentOptions;
};

struct D2D1_STROKE_STYLE_PROPERTIES {
  D2D1_CAP_STYLE startCap, endCap, dashCap;
  D2D1_LINE_JOIN lineJoin;
  float miterLimit;
  D2D1_DASH_STYLE dashStyle;
  float dashOffset;
};

struct IWICBitmap;
cominterface("06152247-6f50-465a-9245-118bfd3b6007") ID2D1Factory : IUnknown {
  virtual HRESULT __stdcall ReloadSystemMetrics() noexcept = 0;
  virtual void __stdcall GetDesktopDpi(float*, float*) noexcept = 0;
  virtual HRESULT __stdcall CreateRectangleGeometry(const D2D1_RECT_F*, ID2D1RectangleGeometry**) noexcept = 0;
  virtual HRESULT __stdcall CreateRoundedRectangleGeometry(const D2D1_ROUNDED_RECT*, ID2D1RoundedRectangleGeometry**) noexcept = 0;
  virtual HRESULT __stdcall CreateEllipseGeometry(const D2D1_ELLIPSE*, ID2D1EllipseGeometry**) noexcept = 0;
  virtual HRESULT __stdcall CreateGeometryGroup(D2D1_FILL_MODE, ID2D1Geometry**, int, ID2D1GeometryGroup**) noexcept = 0;
  virtual HRESULT __stdcall CreateTransformedGeometry(ID2D1Geometry*, const D2D1_MATRIX_3X2_F*, ID2D1TransformedGeometry**) noexcept = 0;
  virtual HRESULT __stdcall CreatePathGeometry(ID2D1PathGeometry**) noexcept = 0;
  virtual HRESULT __stdcall CreateStrokeStyle(const D2D1_STROKE_STYLE_PROPERTIES*, const float*, int, ID2D1StrokeStyle**) noexcept = 0;
  virtual HRESULT __stdcall CreateDrawingStateBlock(const D2D1_DRAWING_STATE_DESCRIPTION*, IDWriteRenderingParams*, ID2D1DrawingStateBlock**) noexcept = 0;
  virtual HRESULT __stdcall CreateWicBitmapRenderTarget(IWICBitmap*, const D2D1_RENDER_TARGET_PROPERTIES*, ID2D1RenderTarget**) noexcept = 0;
  virtual HRESULT __stdcall CreateHwndRenderTarget(const D2D1_RENDER_TARGET_PROPERTIES*, const D2D1_HWND_RENDER_TARGET_PROPERTIES*, ID2D1HwndRenderTarget**) noexcept = 0;
  virtual HRESULT __stdcall CreateDxgiSurfaceRenderTarget(IDXGISurface*, const D2D1_RENDER_TARGET_PROPERTIES*, ID2D1RenderTarget**) noexcept = 0;
  virtual HRESULT __stdcall CreateDCRenderTarget(const D2D1_RENDER_TARGET_PROPERTIES*, ID2D1DCRenderTarget**) noexcept = 0;
  HRESULT CreateRectangleGeometry(const D2D1_RECT_F& rectangle, ID2D1RectangleGeometry** rectangleGeometry) { return CreateRectangleGeometry(&rectangle, rectangleGeometry); }
  HRESULT CreateRoundedRectangleGeometry(const D2D1_ROUNDED_RECT& roundedRectangle, ID2D1RoundedRectangleGeometry** roundedRectangleGeometry) { return CreateRoundedRectangleGeometry(&roundedRectangle, roundedRectangleGeometry); }
  HRESULT CreateEllipseGeometry(const D2D1_ELLIPSE& ellipse, ID2D1EllipseGeometry** ellipseGeometry) { return CreateEllipseGeometry(&ellipse, ellipseGeometry); }
  HRESULT CreateTransformedGeometry(ID2D1Geometry * sourceGeometry, const D2D1_MATRIX_3X2_F& transform, ID2D1TransformedGeometry** transformedGeometry) { return CreateTransformedGeometry(sourceGeometry, &transform, transformedGeometry); }
  HRESULT CreateStrokeStyle(const D2D1_STROKE_STYLE_PROPERTIES& strokeStyleProperties, const float* dashes, int dashesCount, ID2D1StrokeStyle** strokeStyle) { return CreateStrokeStyle(&strokeStyleProperties, dashes, dashesCount, strokeStyle); }
  HRESULT CreateDrawingStateBlock(const D2D1_DRAWING_STATE_DESCRIPTION& drawingStateDescription, ID2D1DrawingStateBlock** drawingStateBlock) { return CreateDrawingStateBlock(&drawingStateDescription, nullptr, drawingStateBlock); }
  HRESULT CreateDrawingStateBlock(ID2D1DrawingStateBlock * *drawingStateBlock) { return CreateDrawingStateBlock(nullptr, nullptr, drawingStateBlock); }
  HRESULT CreateWicBitmapRenderTarget(IWICBitmap * target, const D2D1_RENDER_TARGET_PROPERTIES& renderTargetProperties, ID2D1RenderTarget** renderTarget) { return CreateWicBitmapRenderTarget(target, &renderTargetProperties, renderTarget); }
  HRESULT CreateHwndRenderTarget(const D2D1_RENDER_TARGET_PROPERTIES& renderTargetProperties, const D2D1_HWND_RENDER_TARGET_PROPERTIES& hwndRenderTargetProperties, ID2D1HwndRenderTarget** hwndRenderTarget) { return CreateHwndRenderTarget(&renderTargetProperties, &hwndRenderTargetProperties, hwndRenderTarget); }
  HRESULT CreateDxgiSurfaceRenderTarget(IDXGISurface * dxgiSurface, const D2D1_RENDER_TARGET_PROPERTIES& renderTargetProperties, ID2D1RenderTarget** renderTarget) { return CreateDxgiSurfaceRenderTarget(dxgiSurface, &renderTargetProperties, renderTarget); }
};
}

HRESULT __stdcall D2D1CreateFactory(D2D1_FACTORY_TYPE, const GUID&, const void*, void**);

__ywlib_exportcend;
#endif
