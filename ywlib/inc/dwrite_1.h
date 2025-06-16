#pragma once
#include <inc/dwrite.h>
#ifndef __ywlib_import
__ywlib_exportc;
extern "C++" {

enum class DWRITE_OUTLINE_THRESHOLD {
  DWRITE_OUTLINE_THRESHOLD_ANTIALIASED,
  DWRITE_OUTLINE_THRESHOLD_ALIASED,
};
using enum DWRITE_OUTLINE_THRESHOLD;

enum class DWRITE_BASELINE {
  DWRITE_BASELINE_DEFAULT,
  DWRITE_BASELINE_ROMAN,
  DWRITE_BASELINE_CENTRAL,
  DWRITE_BASELINE_MATH,
  DWRITE_BASELINE_HANGING,
  DWRITE_BASELINE_IDEOGRAPHIC_BOTTOM,
  DWRITE_BASELINE_IDEOGRAPHIC_TOP,
  DWRITE_BASELINE_MINIMUM,
  DWRITE_BASELINE_MAXIMUM,
};
using enum DWRITE_BASELINE;

enum class DWRITE_VERTICAL_GLYPH_ORIENTATION {
  DWRITE_VERTICAL_GLYPH_ORIENTATION_DEFAULT,
  DWRITE_VERTICAL_GLYPH_ORIENTATION_STACKED,
};
using enum DWRITE_VERTICAL_GLYPH_ORIENTATION;

enum class DWRITE_GLYPH_ORIENTATION_ANGLE {
  DWRITE_GLYPH_ORIENTATION_ANGLE_0_DEGREES,
  DWRITE_GLYPH_ORIENTATION_ANGLE_90_DEGREES,
  DWRITE_GLYPH_ORIENTATION_ANGLE_180_DEGREES,
  DWRITE_GLYPH_ORIENTATION_ANGLE_270_DEGREES,
};
using enum DWRITE_GLYPH_ORIENTATION_ANGLE;

enum class DWRITE_TEXT_ANTIALIAS_MODE {
  DWRITE_TEXT_ANTIALIAS_MODE_CLEARTYPE,
  DWRITE_TEXT_ANTIALIAS_MODE_GRAYSCALE,
};
using enum DWRITE_TEXT_ANTIALIAS_MODE;

struct DWRITE_FONT_METRICS1 : DWRITE_FONT_METRICS {
  int16_t glyphBoxLeft, glyphBoxTop, glyphBoxRight, glyphBoxBottom, subscriptPositionX, subscriptPositionY, subscriptSizeX, subscriptSizeY, superscriptPositionX, superscriptPositionY, superscriptSizeX, superscriptSizeY;
  int hasTypographicMetrics;
};

struct DWRITE_CARET_METRICS {
  int16_t slopeRise, slopeRun, offset;
};

struct DWRITE_UNICODE_RANGE {
  uint32_t first, last;
};
struct DWRITE_SCRIPT_PROPERTIES {
  uint32_t isoScriptCode, isoScriptNumber, clusterLookahead, justificationCharacter;
  uint32_t restrictCaretToClusters : 1;
  uint32_t usesWordDividers : 1;
  uint32_t isDiscreteWriting : 1;
  uint32_t isBlockWriting : 1;
  uint32_t isDistributedWithinCluster : 1;
  uint32_t isConnectedWriting : 1;
  uint32_t isCursiveWriting : 1;
  uint32_t reserved : 25;
};
struct DWRITE_JUSTIFICATION_OPPORTUNITY {
  float expansionMinimum, expansionMaximum, compressionMaximum;
  uint32_t expansionPriority : 8;
  uint32_t compressionPriority : 8;
  uint32_t allowResidualExpansion : 1;
  uint32_t allowResidualCompression : 1;
  uint32_t applyToLeadingEdge : 1;
  uint32_t applyToTrailingEdge : 1;
  uint32_t reserved : 12;
};

cominterface("94413cf4-a6fc-4248-8b50-6674348fcad3") IDWriteRenderingParams1 : IDWriteRenderingParams {
  virtual float __stdcall GetGrayscaleEnhancedContrast() noexcept = 0;
};

cominterface("30572f99-dac6-41db-a16e-0486307e606a") IDWriteFactory1 : IDWriteFactory {
  virtual HRESULT __stdcall GetEudcFontCollection(IDWriteFontCollection**, int = false) noexcept = 0;
  virtual HRESULT __stdcall CreateCustomRenderingParams(float, float, float, float, DWRITE_PIXEL_GEOMETRY, DWRITE_RENDERING_MODE, IDWriteRenderingParams1**) noexcept = 0;
  using IDWriteFactory::CreateCustomRenderingParams;
};

cominterface("a71efdb4-9fdb-4838-ad90-cfc3be8c3daf") IDWriteFontFace1 : IDWriteFontFace {
  virtual void __stdcall GetMetrics(DWRITE_FONT_METRICS1*) noexcept = 0;
  virtual HRESULT __stdcall GetGdiCompatibleMetrics(float, float, const DWRITE_MATRIX*, DWRITE_FONT_METRICS1*) noexcept = 0;
  virtual void __stdcall GetCaretMetrics(DWRITE_CARET_METRICS*) noexcept = 0;
  virtual HRESULT __stdcall GetUnicodeRanges(uint32_t, DWRITE_UNICODE_RANGE*, uint32_t*) noexcept = 0;
  virtual int __stdcall IsMonospacedFont() noexcept = 0;
  virtual HRESULT __stdcall GetDesignGlyphAdvances(uint32_t, const uint16_t*, int32_t*, int = false) noexcept = 0;
  virtual HRESULT __stdcall GetGdiCompatibleGlyphAdvances(float, float, const DWRITE_MATRIX*, int, int, uint32_t, const uint16_t*, int32_t*) noexcept = 0;
  virtual HRESULT __stdcall GetKerningPairAdjustments(uint32_t, const uint16_t*, int32_t*) noexcept = 0;
  virtual int __stdcall HasKerningPairs() noexcept = 0;
  virtual HRESULT __stdcall GetRecommendedRenderingMode(float, float, float, const DWRITE_MATRIX*, int, DWRITE_OUTLINE_THRESHOLD, DWRITE_MEASURING_MODE, DWRITE_RENDERING_MODE*) noexcept = 0;
  virtual HRESULT __stdcall GetVerticalGlyphVariants(uint32_t, const uint16_t*, uint16_t*) noexcept = 0;
  virtual int __stdcall HasVerticalGlyphVariants() noexcept = 0;
  using IDWriteFontFace::GetGdiCompatibleMetrics;
  using IDWriteFontFace::GetMetrics;
  using IDWriteFontFace::GetRecommendedRenderingMode;
};

cominterface("acd16696-8c14-4f5d-877e-fe3fc1d32738") IDWriteFont1 : IDWriteFont {
  virtual void __stdcall GetMetrics(DWRITE_FONT_METRICS1*) noexcept = 0;
  using IDWriteFont::GetMetrics;
  virtual void __stdcall GetPanose(void*) noexcept = 0;
  virtual HRESULT __stdcall GetUnicodeRanges(uint32_t, DWRITE_UNICODE_RANGE*, uint32_t*) noexcept = 0;
  virtual int __stdcall IsMonospacedFont() noexcept = 0;
};

cominterface("B0D941A0-85E7-4D8B-9FD3-5CED9934482A") IDWriteTextAnalysisSink1 : IDWriteTextAnalysisSink {
  virtual HRESULT __stdcall SetGlyphOrientation(uint32_t, uint32_t, DWRITE_GLYPH_ORIENTATION_ANGLE, uint8_t, int, int) noexcept = 0;
};

cominterface("639CFAD8-0FB4-4B21-A58A-067920120009") IDWriteTextAnalysisSource1 : IDWriteTextAnalysisSource {
  virtual HRESULT __stdcall GetVerticalGlyphOrientation(uint32_t, uint32_t*, DWRITE_VERTICAL_GLYPH_ORIENTATION*, uint8_t*) noexcept = 0;
};

cominterface("80DAD800-E21F-4E83-96CE-BFCCE500DB7C") IDWriteTextAnalyzer1 : IDWriteTextAnalyzer {
  virtual HRESULT __stdcall ApplyCharacterSpacing(float, float, float, uint32_t, uint32_t, const uint16_t*, const float*, const DWRITE_GLYPH_OFFSET*, const DWRITE_SHAPING_GLYPH_PROPERTIES*, float*, DWRITE_GLYPH_OFFSET*) noexcept = 0;
  virtual HRESULT __stdcall GetBaseline(IDWriteFontFace*, DWRITE_BASELINE, int, int, DWRITE_SCRIPT_ANALYSIS, const wchar_t*, int32_t*, int*) noexcept = 0;
  virtual HRESULT __stdcall AnalyzeVerticalGlyphOrientation(IDWriteTextAnalysisSource1*, uint32_t, uint32_t, IDWriteTextAnalysisSink1*) noexcept = 0;
  virtual HRESULT __stdcall GetGlyphOrientationTransform(DWRITE_GLYPH_ORIENTATION_ANGLE, int, DWRITE_MATRIX*) noexcept = 0;
  virtual HRESULT __stdcall GetScriptProperties(DWRITE_SCRIPT_ANALYSIS, DWRITE_SCRIPT_PROPERTIES*) noexcept = 0;
  virtual HRESULT __stdcall GetTextComplexity(const wchar_t*, uint32_t, IDWriteFontFace*, int*, uint32_t*, uint16_t*) noexcept = 0;
  virtual HRESULT __stdcall GetJustificationOpportunities(IDWriteFontFace*, float, DWRITE_SCRIPT_ANALYSIS, uint32_t, uint32_t, const wchar_t*, const uint16_t*, const DWRITE_SHAPING_GLYPH_PROPERTIES*, DWRITE_JUSTIFICATION_OPPORTUNITY*) noexcept = 0;
  virtual HRESULT __stdcall JustifyGlyphAdvances(float, uint32_t, const DWRITE_JUSTIFICATION_OPPORTUNITY*, const float*, const DWRITE_GLYPH_OFFSET*, float*, DWRITE_GLYPH_OFFSET*) noexcept = 0;
  virtual HRESULT __stdcall GetJustifiedGlyphs(IDWriteFontFace*, float, DWRITE_SCRIPT_ANALYSIS, uint32_t, uint32_t, uint32_t, const uint16_t*, const uint16_t*, const float*, const float*, const DWRITE_GLYPH_OFFSET*, const DWRITE_SHAPING_GLYPH_PROPERTIES*, uint32_t*, uint16_t*, uint16_t*, float*, DWRITE_GLYPH_OFFSET*) noexcept = 0;
};

cominterface("9064D822-80A7-465C-A986-DF65F78B8FEB") IDWriteTextLayout1 : IDWriteTextLayout {
  virtual HRESULT __stdcall SetPairKerning(int, DWRITE_TEXT_RANGE) noexcept = 0;
  virtual HRESULT __stdcall GetPairKerning(uint32_t, int*, DWRITE_TEXT_RANGE* = nullptr) noexcept = 0;
  virtual HRESULT __stdcall SetCharacterSpacing(float, float, float, DWRITE_TEXT_RANGE) noexcept = 0;
  virtual HRESULT __stdcall GetCharacterSpacing(uint32_t, float*, float*, float*, DWRITE_TEXT_RANGE* = nullptr) noexcept = 0;
};

cominterface("791e8298-3ef3-4230-9880-c9bdecc42064") IDWriteBitmapRenderTarget1 : IDWriteBitmapRenderTarget {
  virtual DWRITE_TEXT_ANTIALIAS_MODE __stdcall GetTextAntialiasMode() noexcept = 0;
  virtual HRESULT __stdcall SetTextAntialiasMode(DWRITE_TEXT_ANTIALIAS_MODE) noexcept = 0;
};
}

__ywlib_exportcend;
#endif
