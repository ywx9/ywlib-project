#pragma once
#include <inc/d2d1.h>
#ifndef __ywlib_import
__ywlib_exportc;
extern "C++" {

enum class DWRITE_BREAK_CONDITION {
  DWRITE_BREAK_CONDITION_NEUTRAL,
  DWRITE_BREAK_CONDITION_CAN_BREAK,
  DWRITE_BREAK_CONDITION_MAY_NOT_BREAK,
  DWRITE_BREAK_CONDITION_MUST_BREAK,
};
using enum DWRITE_BREAK_CONDITION;

enum class DWRITE_FACTORY_TYPE {
  DWRITE_FACTORY_TYPE_SHARED,
  DWRITE_FACTORY_TYPE_ISOLATED,
};
using enum DWRITE_FACTORY_TYPE;

enum class DWRITE_FLOW_DIRECTION {
  DWRITE_FLOW_DIRECTION_TOP_TO_BOTTOM,
  DWRITE_FLOW_DIRECTION_BOTTOM_TO_TOP,
  DWRITE_FLOW_DIRECTION_LEFT_TO_RIGHT,
  DWRITE_FLOW_DIRECTION_RIGHT_TO_LEFT,
};
using enum DWRITE_FLOW_DIRECTION;

enum class DWRITE_FONT_FACE_TYPE {
  DWRITE_FONT_FACE_TYPE_CFF,
  DWRITE_FONT_FACE_TYPE_TRUETYPE,
  DWRITE_FONT_FACE_TYPE_OPENTYPE_COLLECTION,
  DWRITE_FONT_FACE_TYPE_TYPE1,
  DWRITE_FONT_FACE_TYPE_VECTOR,
  DWRITE_FONT_FACE_TYPE_BITMAP,
  DWRITE_FONT_FACE_TYPE_UNKNOWN,
  DWRITE_FONT_FACE_TYPE_RAW_CFF,
  DWRITE_FONT_FACE_TYPE_TRUETYPE_COLLECTION = DWRITE_FONT_FACE_TYPE_OPENTYPE_COLLECTION,
};
using enum DWRITE_FONT_FACE_TYPE;

#define __ywlib_opentypetag(a, b, c, d) (int(a) << 24 | int(b) << 16 | int(c) << 8 | int(d))
enum class DWRITE_FONT_FEATURE_TAG {
  DWRITE_FONT_FEATURE_TAG_ALTERNATIVE_FRACTIONS = __ywlib_opentypetag('a', 'f', 'r', 'c'),
  DWRITE_FONT_FEATURE_TAG_PETITE_CAPITALS_FROM_CAPITALS = __ywlib_opentypetag('c', '2', 'p', 'c'),
  DWRITE_FONT_FEATURE_TAG_SMALL_CAPITALS_FROM_CAPITALS = __ywlib_opentypetag('c', '2', 's', 'c'),
  DWRITE_FONT_FEATURE_TAG_CONTEXTUAL_ALTERNATES = __ywlib_opentypetag('c', 'a', 'l', 't'),
  DWRITE_FONT_FEATURE_TAG_CASE_SENSITIVE_FORMS = __ywlib_opentypetag('c', 'a', 's', 'e'),
  DWRITE_FONT_FEATURE_TAG_GLYPH_COMPOSITION_DECOMPOSITION = __ywlib_opentypetag('c', 'c', 'm', 'p'),
  DWRITE_FONT_FEATURE_TAG_CONTEXTUAL_LIGATURES = __ywlib_opentypetag('c', 'l', 'i', 'g'),
  DWRITE_FONT_FEATURE_TAG_CAPITAL_SPACING = __ywlib_opentypetag('c', 'p', 's', 'p'),
  DWRITE_FONT_FEATURE_TAG_CONTEXTUAL_SWASH = __ywlib_opentypetag('c', 's', 'w', 'h'),
  DWRITE_FONT_FEATURE_TAG_CURSIVE_POSITIONING = __ywlib_opentypetag('c', 'u', 'r', 's'),
  DWRITE_FONT_FEATURE_TAG_DEFAULT = __ywlib_opentypetag('d', 'f', 'l', 't'),
  DWRITE_FONT_FEATURE_TAG_DISCRETIONARY_LIGATURES = __ywlib_opentypetag('d', 'l', 'i', 'g'),
  DWRITE_FONT_FEATURE_TAG_EXPERT_FORMS = __ywlib_opentypetag('e', 'x', 'p', 't'),
  DWRITE_FONT_FEATURE_TAG_FRACTIONS = __ywlib_opentypetag('f', 'r', 'a', 'c'),
  DWRITE_FONT_FEATURE_TAG_FULL_WIDTH = __ywlib_opentypetag('f', 'w', 'i', 'd'),
  DWRITE_FONT_FEATURE_TAG_HALF_FORMS = __ywlib_opentypetag('h', 'a', 'l', 'f'),
  DWRITE_FONT_FEATURE_TAG_HALANT_FORMS = __ywlib_opentypetag('h', 'a', 'l', 'n'),
  DWRITE_FONT_FEATURE_TAG_ALTERNATE_HALF_WIDTH = __ywlib_opentypetag('h', 'a', 'l', 't'),
  DWRITE_FONT_FEATURE_TAG_HISTORICAL_FORMS = __ywlib_opentypetag('h', 'i', 's', 't'),
  DWRITE_FONT_FEATURE_TAG_HORIZONTAL_KANA_ALTERNATES = __ywlib_opentypetag('h', 'k', 'n', 'a'),
  DWRITE_FONT_FEATURE_TAG_HISTORICAL_LIGATURES = __ywlib_opentypetag('h', 'l', 'i', 'g'),
  DWRITE_FONT_FEATURE_TAG_HALF_WIDTH = __ywlib_opentypetag('h', 'w', 'i', 'd'),
  DWRITE_FONT_FEATURE_TAG_HOJO_KANJI_FORMS = __ywlib_opentypetag('h', 'o', 'j', 'o'),
  DWRITE_FONT_FEATURE_TAG_JIS04_FORMS = __ywlib_opentypetag('j', 'p', '0', '4'),
  DWRITE_FONT_FEATURE_TAG_JIS78_FORMS = __ywlib_opentypetag('j', 'p', '7', '8'),
  DWRITE_FONT_FEATURE_TAG_JIS83_FORMS = __ywlib_opentypetag('j', 'p', '8', '3'),
  DWRITE_FONT_FEATURE_TAG_JIS90_FORMS = __ywlib_opentypetag('j', 'p', '9', '0'),
  DWRITE_FONT_FEATURE_TAG_KERNING = __ywlib_opentypetag('k', 'e', 'r', 'n'),
  DWRITE_FONT_FEATURE_TAG_STANDARD_LIGATURES = __ywlib_opentypetag('l', 'i', 'g', 'a'),
  DWRITE_FONT_FEATURE_TAG_LINING_FIGURES = __ywlib_opentypetag('l', 'n', 'u', 'm'),
  DWRITE_FONT_FEATURE_TAG_LOCALIZED_FORMS = __ywlib_opentypetag('l', 'o', 'c', 'l'),
  DWRITE_FONT_FEATURE_TAG_MARK_POSITIONING = __ywlib_opentypetag('m', 'a', 'r', 'k'),
  DWRITE_FONT_FEATURE_TAG_MATHEMATICAL_GREEK = __ywlib_opentypetag('m', 'g', 'r', 'k'),
  DWRITE_FONT_FEATURE_TAG_MARK_TO_MARK_POSITIONING = __ywlib_opentypetag('m', 'k', 'm', 'k'),
  DWRITE_FONT_FEATURE_TAG_ALTERNATE_ANNOTATION_FORMS = __ywlib_opentypetag('n', 'a', 'l', 't'),
  DWRITE_FONT_FEATURE_TAG_NLC_KANJI_FORMS = __ywlib_opentypetag('n', 'l', 'c', 'k'),
  DWRITE_FONT_FEATURE_TAG_OLD_STYLE_FIGURES = __ywlib_opentypetag('o', 'n', 'u', 'm'),
  DWRITE_FONT_FEATURE_TAG_ORDINALS = __ywlib_opentypetag('o', 'r', 'd', 'n'),
  DWRITE_FONT_FEATURE_TAG_PROPORTIONAL_ALTERNATE_WIDTH = __ywlib_opentypetag('p', 'a', 'l', 't'),
  DWRITE_FONT_FEATURE_TAG_PETITE_CAPITALS = __ywlib_opentypetag('p', 'c', 'a', 'p'),
  DWRITE_FONT_FEATURE_TAG_PROPORTIONAL_FIGURES = __ywlib_opentypetag('p', 'n', 'u', 'm'),
  DWRITE_FONT_FEATURE_TAG_PROPORTIONAL_WIDTHS = __ywlib_opentypetag('p', 'w', 'i', 'd'),
  DWRITE_FONT_FEATURE_TAG_QUARTER_WIDTHS = __ywlib_opentypetag('q', 'w', 'i', 'd'),
  DWRITE_FONT_FEATURE_TAG_REQUIRED_LIGATURES = __ywlib_opentypetag('r', 'l', 'i', 'g'),
  DWRITE_FONT_FEATURE_TAG_RUBY_NOTATION_FORMS = __ywlib_opentypetag('r', 'u', 'b', 'y'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_ALTERNATES = __ywlib_opentypetag('s', 'a', 'l', 't'),
  DWRITE_FONT_FEATURE_TAG_SCIENTIFIC_INFERIORS = __ywlib_opentypetag('s', 'i', 'n', 'f'),
  DWRITE_FONT_FEATURE_TAG_SMALL_CAPITALS = __ywlib_opentypetag('s', 'm', 'c', 'p'),
  DWRITE_FONT_FEATURE_TAG_SIMPLIFIED_FORMS = __ywlib_opentypetag('s', 'm', 'p', 'l'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_1 = __ywlib_opentypetag('s', 's', '0', '1'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_2 = __ywlib_opentypetag('s', 's', '0', '2'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_3 = __ywlib_opentypetag('s', 's', '0', '3'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_4 = __ywlib_opentypetag('s', 's', '0', '4'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_5 = __ywlib_opentypetag('s', 's', '0', '5'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_6 = __ywlib_opentypetag('s', 's', '0', '6'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_7 = __ywlib_opentypetag('s', 's', '0', '7'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_8 = __ywlib_opentypetag('s', 's', '0', '8'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_9 = __ywlib_opentypetag('s', 's', '0', '9'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_10 = __ywlib_opentypetag('s', 's', '1', '0'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_11 = __ywlib_opentypetag('s', 's', '1', '1'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_12 = __ywlib_opentypetag('s', 's', '1', '2'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_13 = __ywlib_opentypetag('s', 's', '1', '3'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_14 = __ywlib_opentypetag('s', 's', '1', '4'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_15 = __ywlib_opentypetag('s', 's', '1', '5'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_16 = __ywlib_opentypetag('s', 's', '1', '6'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_17 = __ywlib_opentypetag('s', 's', '1', '7'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_18 = __ywlib_opentypetag('s', 's', '1', '8'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_19 = __ywlib_opentypetag('s', 's', '1', '9'),
  DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_20 = __ywlib_opentypetag('s', 's', '2', '0'),
  DWRITE_FONT_FEATURE_TAG_SUBSCRIPT = __ywlib_opentypetag('s', 'u', 'b', 's'),
  DWRITE_FONT_FEATURE_TAG_SUPERSCRIPT = __ywlib_opentypetag('s', 'u', 'p', 's'),
  DWRITE_FONT_FEATURE_TAG_SWASH = __ywlib_opentypetag('s', 'w', 's', 'h'),
  DWRITE_FONT_FEATURE_TAG_TITLING = __ywlib_opentypetag('t', 'i', 't', 'l'),
  DWRITE_FONT_FEATURE_TAG_TRADITIONAL_NAME_FORMS = __ywlib_opentypetag('t', 'n', 'a', 'm'),
  DWRITE_FONT_FEATURE_TAG_TABULAR_FIGURES = __ywlib_opentypetag('t', 'n', 'u', 'm'),
  DWRITE_FONT_FEATURE_TAG_TRADITIONAL_FORMS = __ywlib_opentypetag('t', 'r', 'a', 'd'),
  DWRITE_FONT_FEATURE_TAG_THIRD_WIDTHS = __ywlib_opentypetag('t', 'w', 'i', 'd'),
  DWRITE_FONT_FEATURE_TAG_UNICASE = __ywlib_opentypetag('u', 'n', 'i', 'c'),
  DWRITE_FONT_FEATURE_TAG_VERTICAL_WRITING = __ywlib_opentypetag('v', 'e', 'r', 't'),
  DWRITE_FONT_FEATURE_TAG_VERTICAL_ALTERNATES_AND_ROTATION = __ywlib_opentypetag('v', 'r', 't', '2'),
  DWRITE_FONT_FEATURE_TAG_SLASHED_ZERO = __ywlib_opentypetag('z', 'e', 'r', 'o'),
};
using enum DWRITE_FONT_FEATURE_TAG;

enum class DWRITE_FONT_FILE_TYPE {
  DWRITE_FONT_FILE_TYPE_UNKNOWN,
  DWRITE_FONT_FILE_TYPE_CFF,
  DWRITE_FONT_FILE_TYPE_TRUETYPE,
  DWRITE_FONT_FILE_TYPE_OPENTYPE_COLLECTION,
  DWRITE_FONT_FILE_TYPE_TYPE1_PFM,
  DWRITE_FONT_FILE_TYPE_TYPE1_PFB,
  DWRITE_FONT_FILE_TYPE_VECTOR,
  DWRITE_FONT_FILE_TYPE_BITMAP,
  DWRITE_FONT_FILE_TYPE_TRUETYPE_COLLECTION = DWRITE_FONT_FILE_TYPE_OPENTYPE_COLLECTION,
};
using enum DWRITE_FONT_FILE_TYPE;

enum class DWRITE_FONT_SIMULATIONS {
  DWRITE_FONT_SIMULATIONS_NONE = 0x0,
  DWRITE_FONT_SIMULATIONS_BOLD = 0x1,
  DWRITE_FONT_SIMULATIONS_OBLIQUE = 0x2,
};
using enum DWRITE_FONT_SIMULATIONS;
constexpr DWRITE_FONT_SIMULATIONS operator~(DWRITE_FONT_SIMULATIONS a) noexcept { return DWRITE_FONT_SIMULATIONS(~static_cast<size_t>(a)); }
constexpr DWRITE_FONT_SIMULATIONS operator|(DWRITE_FONT_SIMULATIONS a, DWRITE_FONT_SIMULATIONS b) noexcept { return DWRITE_FONT_SIMULATIONS(static_cast<size_t>(a) | static_cast<size_t>(b)); }
constexpr DWRITE_FONT_SIMULATIONS operator&(DWRITE_FONT_SIMULATIONS a, DWRITE_FONT_SIMULATIONS b) noexcept { return DWRITE_FONT_SIMULATIONS(static_cast<size_t>(a) & static_cast<size_t>(b)); }
constexpr DWRITE_FONT_SIMULATIONS operator^(DWRITE_FONT_SIMULATIONS a, DWRITE_FONT_SIMULATIONS b) noexcept { return DWRITE_FONT_SIMULATIONS(static_cast<size_t>(a) ^ static_cast<size_t>(b)); }

enum class DWRITE_FONT_WEIGHT {
  DWRITE_FONT_WEIGHT_THIN = 100,
  DWRITE_FONT_WEIGHT_EXTRA_LIGHT = 200,
  DWRITE_FONT_WEIGHT_ULTRA_LIGHT = 200,
  DWRITE_FONT_WEIGHT_LIGHT = 300,
  DWRITE_FONT_WEIGHT_SEMI_LIGHT = 350,
  DWRITE_FONT_WEIGHT_NORMAL = 400,
  DWRITE_FONT_WEIGHT_REGULAR = 400,
  DWRITE_FONT_WEIGHT_MEDIUM = 500,
  DWRITE_FONT_WEIGHT_DEMI_BOLD = 600,
  DWRITE_FONT_WEIGHT_SEMI_BOLD = 600,
  DWRITE_FONT_WEIGHT_BOLD = 700,
  DWRITE_FONT_WEIGHT_EXTRA_BOLD = 800,
  DWRITE_FONT_WEIGHT_ULTRA_BOLD = 800,
  DWRITE_FONT_WEIGHT_BLACK = 900,
  DWRITE_FONT_WEIGHT_HEAVY = 900,
  DWRITE_FONT_WEIGHT_EXTRA_BLACK = 950,
  DWRITE_FONT_WEIGHT_ULTRA_BLACK = 950,
};
using enum DWRITE_FONT_WEIGHT;

enum class DWRITE_FONT_STRETCH {
  DWRITE_FONT_STRETCH_UNDEFINED,
  DWRITE_FONT_STRETCH_ULTRA_CONDENSED,
  DWRITE_FONT_STRETCH_EXTRA_CONDENSED,
  DWRITE_FONT_STRETCH_CONDENSED,
  DWRITE_FONT_STRETCH_SEMI_CONDENSED,
  DWRITE_FONT_STRETCH_NORMAL,
  DWRITE_FONT_STRETCH_MEDIUM,
  DWRITE_FONT_STRETCH_SEMI_EXPANDED,
  DWRITE_FONT_STRETCH_EXPANDED,
  DWRITE_FONT_STRETCH_EXTRA_EXPANDED,
  DWRITE_FONT_STRETCH_ULTRA_EXPANDED,
};
using enum DWRITE_FONT_STRETCH;

enum class DWRITE_FONT_STYLE {
  DWRITE_FONT_STYLE_NORMAL,
  DWRITE_FONT_STYLE_OBLIQUE,
  DWRITE_FONT_STYLE_ITALIC,
};
using enum DWRITE_FONT_STYLE;

enum class DWRITE_INFORMATIONAL_STRING_ID {
  DWRITE_INFORMATIONAL_STRING_NONE,
  DWRITE_INFORMATIONAL_STRING_COPYRIGHT_NOTICE,
  DWRITE_INFORMATIONAL_STRING_VERSION_STRINGS,
  DWRITE_INFORMATIONAL_STRING_TRADEMARK,
  DWRITE_INFORMATIONAL_STRING_MANUFACTURER,
  DWRITE_INFORMATIONAL_STRING_DESIGNER,
  DWRITE_INFORMATIONAL_STRING_DESIGNER_URL,
  DWRITE_INFORMATIONAL_STRING_DESCRIPTION,
  DWRITE_INFORMATIONAL_STRING_FONT_VENDOR_URL,
  DWRITE_INFORMATIONAL_STRING_LICENSE_DESCRIPTION,
  DWRITE_INFORMATIONAL_STRING_LICENSE_INFO_URL,
  DWRITE_INFORMATIONAL_STRING_WIN32_FAMILY_NAMES,
  DWRITE_INFORMATIONAL_STRING_WIN32_SUBFAMILY_NAMES,
  DWRITE_INFORMATIONAL_STRING_TYPOGRAPHIC_FAMILY_NAMES,
  DWRITE_INFORMATIONAL_STRING_TYPOGRAPHIC_SUBFAMILY_NAMES,
  DWRITE_INFORMATIONAL_STRING_SAMPLE_TEXT,
  DWRITE_INFORMATIONAL_STRING_FULL_NAME,
  DWRITE_INFORMATIONAL_STRING_POSTSCRIPT_NAME,
  DWRITE_INFORMATIONAL_STRING_POSTSCRIPT_CID_NAME,
  DWRITE_INFORMATIONAL_STRING_WEIGHT_STRETCH_STYLE_FAMILY_NAME,
  DWRITE_INFORMATIONAL_STRING_DESIGN_SCRIPT_LANGUAGE_TAG,
  DWRITE_INFORMATIONAL_STRING_SUPPORTED_SCRIPT_LANGUAGE_TAG,
  DWRITE_INFORMATIONAL_STRING_PREFERRED_FAMILY_NAMES = DWRITE_INFORMATIONAL_STRING_TYPOGRAPHIC_FAMILY_NAMES,
  DWRITE_INFORMATIONAL_STRING_PREFERRED_SUBFAMILY_NAMES = DWRITE_INFORMATIONAL_STRING_TYPOGRAPHIC_SUBFAMILY_NAMES,
  DWRITE_INFORMATIONAL_STRING_WWS_FAMILY_NAME = DWRITE_INFORMATIONAL_STRING_WEIGHT_STRETCH_STYLE_FAMILY_NAME,
};
using enum DWRITE_INFORMATIONAL_STRING_ID;

enum class DWRITE_LINE_SPACING_METHOD {
  DWRITE_LINE_SPACING_METHOD_DEFAULT,
  DWRITE_LINE_SPACING_METHOD_UNIFORM,
  DWRITE_LINE_SPACING_METHOD_PROPORTIONAL
};
using enum DWRITE_LINE_SPACING_METHOD;

enum class DWRITE_NUMBER_SUBSTITUTION_METHOD {
  DWRITE_NUMBER_SUBSTITUTION_METHOD_FROM_CULTURE,
  DWRITE_NUMBER_SUBSTITUTION_METHOD_CONTEXTUAL,
  DWRITE_NUMBER_SUBSTITUTION_METHOD_NONE,
  DWRITE_NUMBER_SUBSTITUTION_METHOD_NATIONAL,
  DWRITE_NUMBER_SUBSTITUTION_METHOD_TRADITIONAL,
};
using enum DWRITE_NUMBER_SUBSTITUTION_METHOD;

enum class DWRITE_PARAGRAPH_ALIGNMENT {
  DWRITE_PARAGRAPH_ALIGNMENT_NEAR,
  DWRITE_PARAGRAPH_ALIGNMENT_FAR,
  DWRITE_PARAGRAPH_ALIGNMENT_CENTER,
};
using enum DWRITE_PARAGRAPH_ALIGNMENT;

enum class DWRITE_PIXEL_GEOMETRY {
  DWRITE_PIXEL_GEOMETRY_FLAT,
  DWRITE_PIXEL_GEOMETRY_RGB,
  DWRITE_PIXEL_GEOMETRY_BGR,
};
using enum DWRITE_PIXEL_GEOMETRY;

enum class DWRITE_READING_DIRECTION {
  DWRITE_READING_DIRECTION_LEFT_TO_RIGHT,
  DWRITE_READING_DIRECTION_RIGHT_TO_LEFT,
  DWRITE_READING_DIRECTION_TOP_TO_BOTTOM,
  DWRITE_READING_DIRECTION_BOTTOM_TO_TOP,
};
using enum DWRITE_READING_DIRECTION;

enum class DWRITE_RENDERING_MODE {
  DWRITE_RENDERING_MODE_DEFAULT,
  DWRITE_RENDERING_MODE_ALIASED,
  DWRITE_RENDERING_MODE_GDI_CLASSIC,
  DWRITE_RENDERING_MODE_GDI_NATURAL,
  DWRITE_RENDERING_MODE_NATURAL,
  DWRITE_RENDERING_MODE_NATURAL_SYMMETRIC,
  DWRITE_RENDERING_MODE_OUTLINE,
  DWRITE_RENDERING_MODE_CLEARTYPE_GDI_CLASSIC = DWRITE_RENDERING_MODE_GDI_CLASSIC,
  DWRITE_RENDERING_MODE_CLEARTYPE_GDI_NATURAL = DWRITE_RENDERING_MODE_GDI_NATURAL,
  DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL = DWRITE_RENDERING_MODE_NATURAL,
  DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL_SYMMETRIC = DWRITE_RENDERING_MODE_NATURAL_SYMMETRIC
};
using enum DWRITE_RENDERING_MODE;

enum class DWRITE_SCRIPT_SHAPES {
  DWRITE_SCRIPT_SHAPES_DEFAULT,
  DWRITE_SCRIPT_SHAPES_NO_VISUAL,
};
using enum DWRITE_SCRIPT_SHAPES;

enum class DWRITE_TEXT_ALIGNMENT {
  DWRITE_TEXT_ALIGNMENT_LEADING,
  DWRITE_TEXT_ALIGNMENT_TRAILING,
  DWRITE_TEXT_ALIGNMENT_CENTER,
  DWRITE_TEXT_ALIGNMENT_JUSTIFIED,
};
using enum DWRITE_TEXT_ALIGNMENT;

enum class DWRITE_TEXTURE_TYPE {
  DWRITE_TEXTURE_ALIASED_1x1,
  DWRITE_TEXTURE_CLEARTYPE_3x1,
};
using enum DWRITE_TEXTURE_TYPE;

enum class DWRITE_TRIMMING_GRANULARITY {
  DWRITE_TRIMMING_GRANULARITY_NONE,
  DWRITE_TRIMMING_GRANULARITY_CHARACTER,
  DWRITE_TRIMMING_GRANULARITY_WORD
};
using enum DWRITE_TRIMMING_GRANULARITY;

enum class DWRITE_WORD_WRAPPING {
  DWRITE_WORD_WRAPPING_WRAP,
  DWRITE_WORD_WRAPPING_NO_WRAP,
  DWRITE_WORD_WRAPPING_EMERGENCY_BREAK,
  DWRITE_WORD_WRAPPING_WHOLE_WORD,
  DWRITE_WORD_WRAPPING_CHARACTER,
};
using enum DWRITE_WORD_WRAPPING;

struct IDWriteFontFileStream;
cominterface("727cad4e-d6af-4c9e-8a08-d695b11caa49") IDWriteFontFileLoader : IUnknown { virtual HRESULT __stdcall CreateStreamFromKey(const void*, uint32_t, IDWriteFontFileStream**) noexcept = 0; };

cominterface("b2d9f3ec-c9fe-4a11-a2ec-d86208f7c0a2") IDWriteLocalFontFileLoader : IDWriteFontFileLoader {
  virtual HRESULT __stdcall GetFilePathLengthFromKey(const void*, uint32_t, uint32_t*) noexcept = 0;
  virtual HRESULT __stdcall GetFilePathFromKey(const void*, uint32_t, wchar_t*, uint32_t) noexcept = 0;
  virtual HRESULT __stdcall GetLastWriteTimeFromKey(const void*, uint32_t, FILETIME*) noexcept = 0;
};

cominterface("6d4865fe-0ab8-4d91-8f62-5dd6be34a3e0") IDWriteFontFileStream : IUnknown {
  virtual HRESULT __stdcall ReadFileFragment(const void**, uint64_t, uint64_t, void**) noexcept = 0;
  virtual void __stdcall ReleaseFileFragment(void*) noexcept = 0;
  virtual HRESULT __stdcall GetFileSize(uint64_t*) noexcept = 0;
  virtual HRESULT __stdcall GetLastWriteTime(uint64_t*) noexcept = 0;
};

cominterface("739d886a-cef5-47dc-8769-1a8b41bebbb0") IDWriteFontFile : IUnknown {
  virtual HRESULT __stdcall GetReferenceKey(const void**, uint32_t*) noexcept = 0;
  virtual HRESULT __stdcall GetLoader(IDWriteFontFileLoader**) noexcept = 0;
  virtual HRESULT __stdcall Analyze(int*, DWRITE_FONT_FILE_TYPE*, DWRITE_FONT_FACE_TYPE*, uint32_t*) noexcept = 0;
};
cominterface("2f0da53a-2add-47cd-82ee-d9ec34688e75") IDWriteRenderingParams : IUnknown {
  virtual float __stdcall GetGamma() noexcept = 0;
  virtual float __stdcall GetEnhancedContrast() noexcept = 0;
  virtual float __stdcall GetClearTypeLevel() noexcept = 0;
  virtual DWRITE_PIXEL_GEOMETRY __stdcall GetPixelGeometry() noexcept = 0;
  virtual DWRITE_RENDERING_MODE __stdcall GetRenderingMode() noexcept = 0;
};

struct DWRITE_FONT_METRICS {
  uint16_t designUnitsPerEm, ascent, descent;
  int16_t lineGap;
  uint16_t capHeight, xHeight;
  int16_t underlinePosition;
  uint16_t underlineThickness;
  int16_t strikethroughPosition;
  uint16_t strikethroughThickness;
};

struct DWRITE_GLYPH_METRICS {
  int32_t leftSideBearing;
  uint32_t advanceWidth;
  int32_t rightSideBearing, topSideBearing;
  uint32_t advanceHeight;
  int32_t bottomSideBearing, verticalOriginY;
};

struct DWRITE_MATRIX {
  float m11, m12, m21, m22, dx, dy;
};

struct DWRITE_GLYPH_OFFSET {
  float advanceOffset, ascenderOffset;
};

cominterface("5f49804d-7024-4d43-bfa9-d25984f53849") IDWriteFontFace : IUnknown {
  virtual DWRITE_FONT_FACE_TYPE __stdcall GetType() noexcept = 0;
  virtual HRESULT __stdcall GetFiles(uint32_t*, IDWriteFontFile**) noexcept = 0;
  virtual uint32_t __stdcall GetIndex() noexcept = 0;
  virtual DWRITE_FONT_SIMULATIONS __stdcall GetSimulations() noexcept = 0;
  virtual int __stdcall IsSymbolFont() noexcept = 0;
  virtual void __stdcall GetMetrics(DWRITE_FONT_METRICS*) noexcept = 0;
  virtual uint16_t __stdcall GetGlyphCount() noexcept = 0;
  virtual HRESULT __stdcall GetDesignGlyphMetrics(const uint16_t*, uint32_t, DWRITE_GLYPH_METRICS*, int = false) noexcept = 0;
  virtual HRESULT __stdcall GetGlyphIndices(const uint32_t*, uint32_t, uint16_t*) noexcept = 0;
  virtual HRESULT __stdcall TryGetFontTable(uint32_t, const void**, uint32_t*, void**, int*) noexcept = 0;
  virtual void __stdcall ReleaseFontTable(void*) noexcept = 0;
  virtual HRESULT __stdcall GetGlyphRunOutline(float, const uint16_t*, const float*, const DWRITE_GLYPH_OFFSET*, uint32_t, int, int, ID2D1SimplifiedGeometrySink*) noexcept = 0;
  virtual HRESULT __stdcall GetRecommendedRenderingMode(float, float, DWRITE_MEASURING_MODE, IDWriteRenderingParams*, DWRITE_RENDERING_MODE*) noexcept = 0;
  virtual HRESULT __stdcall GetGdiCompatibleMetrics(float, float, const DWRITE_MATRIX*, DWRITE_FONT_METRICS*) noexcept = 0;
  virtual HRESULT __stdcall GetGdiCompatibleGlyphMetrics(float, float, const DWRITE_MATRIX*, int, const uint16_t*, uint32_t, DWRITE_GLYPH_METRICS*, int = false) noexcept = 0;
};

cominterface("72755049-5ff7-435d-8348-4be97cfa6c7c") IDWriteFontFileEnumerator : IUnknown {
  virtual HRESULT __stdcall MoveNext(int*) noexcept = 0;
  virtual HRESULT __stdcall GetCurrentFontFile(IDWriteFontFile**) noexcept = 0;
};

cominterface("b859ee5a-d838-4b5b-a2e8-1adc7d93db48") IDWriteFactory;
cominterface("cca920e4-52f0-492b-bfa8-29c72ee0a468") IDWriteFontCollectionLoader : IUnknown {
  virtual HRESULT __stdcall CreateEnumeratorFromKey(IDWriteFactory*, const void*, uint32_t, IDWriteFontFileEnumerator**) noexcept = 0;
};

cominterface("08256209-099a-4b34-b86d-c22b110e7771") IDWriteLocalizedStrings : IUnknown {
  virtual uint32_t __stdcall GetCount() noexcept = 0;
  virtual HRESULT __stdcall FindLocaleName(const wchar_t*, uint32_t*, int*) noexcept = 0;
  virtual HRESULT __stdcall GetLocaleNameLength(uint32_t, uint32_t*) noexcept = 0;
  virtual HRESULT __stdcall GetLocaleName(uint32_t, wchar_t*, uint32_t) noexcept = 0;
  virtual HRESULT __stdcall GetStringLength(uint32_t, uint32_t*) noexcept = 0;
  virtual HRESULT __stdcall GetString(uint32_t, wchar_t*, uint32_t) noexcept = 0;
};

cominterface("acd16696-8c14-4f5d-877e-fe3fc1d32737") IDWriteFont;
cominterface("da20d8ef-812a-4c43-9802-62ec4abd7add") IDWriteFontFamily;
cominterface("a84cee02-3eea-4eee-a827-87c1a02a0fcc") IDWriteFontCollection : IUnknown {
  virtual uint32_t __stdcall GetFontFamilyCount() noexcept = 0;
  virtual HRESULT __stdcall GetFontFamily(uint32_t, IDWriteFontFamily**) noexcept = 0;
  virtual HRESULT __stdcall FindFamilyName(const wchar_t*, uint32_t*, int*) noexcept = 0;
  virtual HRESULT __stdcall GetFontFromFontFace(IDWriteFontFace*, IDWriteFont**) noexcept = 0;
};

cominterface("1a0d8438-1d97-4ec1-aef9-a2fb86ed6acb") IDWriteFontList : IUnknown {
  virtual HRESULT __stdcall GetFontCollection(IDWriteFontCollection**) noexcept = 0;
  virtual uint32_t __stdcall GetFontCount() noexcept = 0;
  virtual HRESULT __stdcall GetFont(uint32_t, IDWriteFont**) noexcept = 0;
};

cominterface("da20d8ef-812a-4c43-9802-62ec4abd7add") IDWriteFontFamily : IDWriteFontList {
  virtual HRESULT __stdcall GetFamilyNames(IDWriteLocalizedStrings**) noexcept = 0;
  virtual HRESULT __stdcall GetFirstMatchingFont(DWRITE_FONT_WEIGHT, DWRITE_FONT_STRETCH, DWRITE_FONT_STYLE, IDWriteFont**) noexcept = 0;
  virtual HRESULT __stdcall GetMatchingFonts(DWRITE_FONT_WEIGHT, DWRITE_FONT_STRETCH, DWRITE_FONT_STYLE, IDWriteFontList**) noexcept = 0;
};

cominterface("acd16696-8c14-4f5d-877e-fe3fc1d32737") IDWriteFont : IUnknown {
  virtual HRESULT __stdcall GetFontFamily(IDWriteFontFamily**) noexcept = 0;
  virtual DWRITE_FONT_WEIGHT __stdcall GetWeight() noexcept = 0;
  virtual DWRITE_FONT_STRETCH __stdcall GetStretch() noexcept = 0;
  virtual DWRITE_FONT_STYLE __stdcall GetStyle() noexcept = 0;
  virtual int __stdcall IsSymbolFont() noexcept = 0;
  virtual HRESULT __stdcall GetFaceNames(IDWriteLocalizedStrings**) noexcept = 0;
  virtual HRESULT __stdcall GetInformationalStrings(DWRITE_INFORMATIONAL_STRING_ID, IDWriteLocalizedStrings**, int*) noexcept = 0;
  virtual DWRITE_FONT_SIMULATIONS __stdcall GetSimulations() noexcept = 0;
  virtual void __stdcall GetMetrics(DWRITE_FONT_METRICS*) noexcept = 0;
  virtual HRESULT __stdcall HasCharacter(uint32_t, int*) noexcept = 0;
  virtual HRESULT __stdcall CreateFontFace(IDWriteFontFace**) noexcept = 0;
};

struct DWRITE_TRIMMING {
  DWRITE_TRIMMING_GRANULARITY granularity;
  uint32_t delimiter;
  uint32_t delimiterCount;
};

cominterface("8339FDE3-106F-47ab-8373-1C6295EB10B3") IDWriteInlineObject;
cominterface("9c906818-31d7-4fd3-a151-7c5e225db55a") IDWriteTextFormat : IUnknown {
  virtual HRESULT __stdcall SetTextAlignment(DWRITE_TEXT_ALIGNMENT) noexcept = 0;
  virtual HRESULT __stdcall SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT) noexcept = 0;
  virtual HRESULT __stdcall SetWordWrapping(DWRITE_WORD_WRAPPING) noexcept = 0;
  virtual HRESULT __stdcall SetReadingDirection(DWRITE_READING_DIRECTION) noexcept = 0;
  virtual HRESULT __stdcall SetFlowDirection(DWRITE_FLOW_DIRECTION) noexcept = 0;
  virtual HRESULT __stdcall SetIncrementalTabStop(float) noexcept = 0;
  virtual HRESULT __stdcall SetTrimming(const DWRITE_TRIMMING*, IDWriteInlineObject*) noexcept = 0;
  virtual HRESULT __stdcall SetLineSpacing(DWRITE_LINE_SPACING_METHOD, float, float) noexcept = 0;
  virtual DWRITE_TEXT_ALIGNMENT __stdcall GetTextAlignment() noexcept = 0;
  virtual DWRITE_PARAGRAPH_ALIGNMENT __stdcall GetParagraphAlignment() noexcept = 0;
  virtual DWRITE_WORD_WRAPPING __stdcall GetWordWrapping() noexcept = 0;
  virtual DWRITE_READING_DIRECTION __stdcall GetReadingDirection() noexcept = 0;
  virtual DWRITE_FLOW_DIRECTION __stdcall GetFlowDirection() noexcept = 0;
  virtual float __stdcall GetIncrementalTabStop() noexcept = 0;
  virtual HRESULT __stdcall GetTrimming(DWRITE_TRIMMING*, IDWriteInlineObject**) noexcept = 0;
  virtual HRESULT __stdcall GetLineSpacing(DWRITE_LINE_SPACING_METHOD*, float*, float*) noexcept = 0;
  virtual HRESULT __stdcall GetFontCollection(IDWriteFontCollection**) noexcept = 0;
  virtual uint32_t __stdcall GetFontFamilyNameLength() noexcept = 0;
  virtual HRESULT __stdcall GetFontFamilyName(wchar_t*, uint32_t) noexcept = 0;
  virtual DWRITE_FONT_WEIGHT __stdcall GetFontWeight() noexcept = 0;
  virtual DWRITE_FONT_STYLE __stdcall GetFontStyle() noexcept = 0;
  virtual DWRITE_FONT_STRETCH __stdcall GetFontStretch() noexcept = 0;
  virtual float __stdcall GetFontSize() noexcept = 0;
  virtual uint32_t __stdcall GetLocaleNameLength() noexcept = 0;
  virtual HRESULT __stdcall GetLocaleName(wchar_t*, uint32_t) noexcept = 0;
};

struct DWRITE_FONT_FEATURE {
  DWRITE_FONT_FEATURE_TAG nameTag;
  uint32_t parameter;
};

cominterface("55f1112b-1dc2-4b3c-9541-f46894ed85b6") IDWriteTypography : IUnknown {
  virtual HRESULT __stdcall AddFontFeature(DWRITE_FONT_FEATURE) noexcept = 0;
  virtual uint32_t __stdcall GetFontFeatureCount() noexcept = 0;
  virtual HRESULT __stdcall GetFontFeature(uint32_t, DWRITE_FONT_FEATURE*) noexcept = 0;
};

cominterface("14885CC9-BAB0-4f90-B6ED-5C366A2CD03D") IDWriteNumberSubstitution : IUnknown{};

cominterface("688e1a58-5094-47c8-adc8-fbcea60ae92b") IDWriteTextAnalysisSource : IUnknown {
  virtual HRESULT __stdcall GetTextAtPosition(uint32_t, const wchar_t**, uint32_t*) noexcept = 0;
  virtual HRESULT __stdcall GetTextBeforePosition(uint32_t, const wchar_t**, uint32_t*) noexcept = 0;
  virtual DWRITE_READING_DIRECTION __stdcall GetParagraphReadingDirection() noexcept = 0;
  virtual HRESULT __stdcall GetLocaleName(uint32_t, uint32_t*, const wchar_t**) noexcept = 0;
  virtual HRESULT __stdcall GetNumberSubstitution(uint32_t, uint32_t*, IDWriteNumberSubstitution**) noexcept = 0;
};

struct DWRITE_LINE_BREAKPOINT {
  uint8_t breakConditionBefore : 2;
  uint8_t breakConditionAfter : 2;
  uint8_t isWhitespace : 1;
  uint8_t isSoftHyphen : 1;
  uint8_t padding : 2;
};

struct DWRITE_SCRIPT_ANALYSIS {
  uint16_t script;
  DWRITE_SCRIPT_SHAPES shapes;
};

cominterface("5810cd44-0ca0-4701-b3fa-bec5182ae4f6") IDWriteTextAnalysisSink : IUnknown {
  virtual HRESULT __stdcall SetScriptAnalysis(uint32_t, uint32_t, const DWRITE_SCRIPT_ANALYSIS*) noexcept = 0;
  virtual HRESULT __stdcall SetLineBreakpoints(uint32_t, uint32_t, const DWRITE_LINE_BREAKPOINT*) noexcept = 0;
  virtual HRESULT __stdcall SetBidiLevel(uint32_t, uint32_t, uint8_t, uint8_t) noexcept = 0;
  virtual HRESULT __stdcall SetNumberSubstitution(uint32_t, uint32_t, IDWriteNumberSubstitution*) noexcept = 0;
};

struct DWRITE_TYPOGRAPHIC_FEATURES {
  DWRITE_FONT_FEATURE* features;
  uint32_t featureCount;
};
struct DWRITE_SHAPING_TEXT_PROPERTIES {
  uint16_t isShapedAlone : 1;
  uint16_t reserved1 : 1;
  uint16_t canBreakShapingAfter : 1;
  uint16_t reserved : 13;
};
struct DWRITE_SHAPING_GLYPH_PROPERTIES {
  uint16_t justification : 4;
  uint16_t isClusterStart : 1;
  uint16_t isDiacritic : 1;
  uint16_t isZeroWidthSpace : 1;
  uint16_t reserved : 9;
};

cominterface("b7e6163e-7f46-43b4-84b3-e4e6249c365d") IDWriteTextAnalyzer : IUnknown {
  virtual HRESULT __stdcall AnalyzeScript(IDWriteTextAnalysisSource*, uint32_t, uint32_t, IDWriteTextAnalysisSink*) noexcept = 0;
  virtual HRESULT __stdcall AnalyzeBidi(IDWriteTextAnalysisSource*, uint32_t, uint32_t, IDWriteTextAnalysisSink*) noexcept = 0;
  virtual HRESULT __stdcall AnalyzeNumberSubstitution(IDWriteTextAnalysisSource*, uint32_t, uint32_t, IDWriteTextAnalysisSink*) noexcept = 0;
  virtual HRESULT __stdcall AnalyzeLineBreakpoints(IDWriteTextAnalysisSource*, uint32_t, uint32_t, IDWriteTextAnalysisSink*) noexcept = 0;
  virtual HRESULT __stdcall GetGlyphs(const wchar_t*, uint32_t, IDWriteFontFace*, int, int, const DWRITE_SCRIPT_ANALYSIS*, const wchar_t*, IDWriteNumberSubstitution*, const DWRITE_TYPOGRAPHIC_FEATURES**, const uint32_t*, uint32_t, uint32_t, uint16_t*, DWRITE_SHAPING_TEXT_PROPERTIES*, uint16_t*, DWRITE_SHAPING_GLYPH_PROPERTIES*, uint32_t*) noexcept = 0;
  virtual HRESULT __stdcall GetGlyphPlacements(const wchar_t*, const uint16_t*, DWRITE_SHAPING_TEXT_PROPERTIES*, uint32_t, const uint16_t*, const DWRITE_SHAPING_GLYPH_PROPERTIES*, uint32_t, IDWriteFontFace*, float, int, int, const DWRITE_SCRIPT_ANALYSIS*, const wchar_t*, const DWRITE_TYPOGRAPHIC_FEATURES**, const uint32_t*, uint32_t, float*, DWRITE_GLYPH_OFFSET*) noexcept = 0;
  virtual HRESULT __stdcall GetGdiCompatibleGlyphPlacements(const wchar_t*, const uint16_t*, DWRITE_SHAPING_TEXT_PROPERTIES*, uint32_t, const uint16_t*, const DWRITE_SHAPING_GLYPH_PROPERTIES*, uint32_t, IDWriteFontFace*, float, float, const DWRITE_MATRIX*, int, int, int, const DWRITE_SCRIPT_ANALYSIS*, const wchar_t*, const DWRITE_TYPOGRAPHIC_FEATURES**, const uint32_t*, uint32_t, float*, DWRITE_GLYPH_OFFSET*) noexcept = 0;
};

struct DWRITE_INLINE_OBJECT_METRICS {
  float width, height, baseline;
  int supportsSideways;
};

struct DWRITE_OVERHANG_METRICS {
  float left, top, right, bottom;
};

cominterface("ef8a8135-5cc6-45fe-8825-c5a0724eb819") IDWriteTextRenderer;
cominterface("8339FDE3-106F-47ab-8373-1C6295EB10B3") IDWriteInlineObject : IUnknown {
  virtual HRESULT __stdcall Draw(void*, IDWriteTextRenderer*, float, float, int, int, IUnknown*) noexcept = 0;
  virtual HRESULT __stdcall GetMetrics(DWRITE_INLINE_OBJECT_METRICS*) noexcept = 0;
  virtual HRESULT __stdcall GetOverhangMetrics(DWRITE_OVERHANG_METRICS*) noexcept = 0;
  virtual HRESULT __stdcall GetBreakConditions(DWRITE_BREAK_CONDITION*, DWRITE_BREAK_CONDITION*) noexcept = 0;
};

cominterface("eaf3a2da-ecf4-4d24-b644-b34f6842024b") IDWritePixelSnapping : IUnknown {
  virtual HRESULT __stdcall IsPixelSnappingDisabled(void*, int*) noexcept = 0;
  virtual HRESULT __stdcall GetCurrentTransform(void*, DWRITE_MATRIX*) noexcept = 0;
  virtual HRESULT __stdcall GetPixelsPerDip(void*, float*) noexcept = 0;
};

struct DWRITE_STRIKETHROUGH {
  float width, thickness, offset;
  DWRITE_READING_DIRECTION readingDirection;
  DWRITE_FLOW_DIRECTION flowDirection;
  const wchar_t* localeName;
  DWRITE_MEASURING_MODE measuringMode;
};

struct DWRITE_UNDERLINE {
  float width, thickness, offset, runHeight;
  DWRITE_READING_DIRECTION readingDirection;
  DWRITE_FLOW_DIRECTION flowDirection;
  const wchar_t* localeName;
  DWRITE_MEASURING_MODE measuringMode;
};

cominterface("ef8a8135-5cc6-45fe-8825-c5a0724eb819") IDWriteTextRenderer : IDWritePixelSnapping {
  virtual HRESULT __stdcall DrawGlyphRun(void*, float, float, DWRITE_MEASURING_MODE, const DWRITE_GLYPH_RUN*, const DWRITE_GLYPH_RUN_DESCRIPTION*, IUnknown*) noexcept = 0;
  virtual HRESULT __stdcall DrawUnderline(void*, float, float, const DWRITE_UNDERLINE*, IUnknown*) noexcept = 0;
  virtual HRESULT __stdcall DrawStrikethrough(void*, float, float, const DWRITE_STRIKETHROUGH*, IUnknown*) noexcept = 0;
  virtual HRESULT __stdcall DrawInlineObject(void*, float, float, IDWriteInlineObject*, int, int, IUnknown*) noexcept = 0;
};

struct DWRITE_CLUSTER_METRICS {
  float width;
  uint16_t length;
  uint16_t canWrapLineAfter : 1;
  uint16_t isWhitespace : 1;
  uint16_t isNewline : 1;
  uint16_t isSoftHyphen : 1;
  uint16_t isRightToLeft : 1;
  uint16_t padding : 11;
};

struct DWRITE_HIT_TEST_METRICS {
  uint32_t textPosition, length;
  float left, top, width, height;
  uint32_t bidiLevel;
  int isText, isTrimmed;
};

struct DWRITE_LINE_METRICS {
  uint32_t length, trailingWhitespaceLength, newlineLength;
  float height, baseline;
  int isTrimmed;
};

struct DWRITE_TEXT_METRICS {
  float left, top, width, widthIncludingTrailingWhitespace, height, layoutWidth, layoutHeight;
  uint32_t maxBidiReorderingDepth, lineCount;
};

struct DWRITE_TEXT_RANGE {
  uint32_t startPosition;
  uint32_t length;
};

cominterface("53737037-6d14-410b-9bfe-0b182bb70961") IDWriteTextLayout : IDWriteTextFormat {
  virtual HRESULT __stdcall SetMaxWidth(float) noexcept = 0;
  virtual HRESULT __stdcall SetMaxHeight(float) noexcept = 0;
  virtual HRESULT __stdcall SetFontCollection(IDWriteFontCollection*, DWRITE_TEXT_RANGE) noexcept = 0;
  virtual HRESULT __stdcall SetFontFamilyName(const wchar_t*, DWRITE_TEXT_RANGE) noexcept = 0;
  virtual HRESULT __stdcall SetFontWeight(DWRITE_FONT_WEIGHT, DWRITE_TEXT_RANGE) noexcept = 0;
  virtual HRESULT __stdcall SetFontStyle(DWRITE_FONT_STYLE, DWRITE_TEXT_RANGE) noexcept = 0;
  virtual HRESULT __stdcall SetFontStretch(DWRITE_FONT_STRETCH, DWRITE_TEXT_RANGE) noexcept = 0;
  virtual HRESULT __stdcall SetFontSize(float, DWRITE_TEXT_RANGE) noexcept = 0;
  virtual HRESULT __stdcall SetUnderline(int, DWRITE_TEXT_RANGE) noexcept = 0;
  virtual HRESULT __stdcall SetStrikethrough(int, DWRITE_TEXT_RANGE) noexcept = 0;
  virtual HRESULT __stdcall SetDrawingEffect(IUnknown*, DWRITE_TEXT_RANGE) noexcept = 0;
  virtual HRESULT __stdcall SetInlineObject(IDWriteInlineObject*, DWRITE_TEXT_RANGE) noexcept = 0;
  virtual HRESULT __stdcall SetTypography(IDWriteTypography*, DWRITE_TEXT_RANGE) noexcept = 0;
  virtual HRESULT __stdcall SetLocaleName(const wchar_t*, DWRITE_TEXT_RANGE) noexcept = 0;
  virtual float __stdcall GetMaxWidth() noexcept = 0;
  virtual float __stdcall GetMaxHeight() noexcept = 0;
  virtual HRESULT __stdcall GetFontCollection(uint32_t, IDWriteFontCollection**, DWRITE_TEXT_RANGE* = nullptr) noexcept = 0;
  virtual HRESULT __stdcall GetFontFamilyNameLength(uint32_t, uint32_t*, DWRITE_TEXT_RANGE* = nullptr) noexcept = 0;
  virtual HRESULT __stdcall GetFontFamilyName(uint32_t, wchar_t*, uint32_t, DWRITE_TEXT_RANGE* = nullptr) noexcept = 0;
  virtual HRESULT __stdcall GetFontWeight(uint32_t, DWRITE_FONT_WEIGHT*, DWRITE_TEXT_RANGE* = nullptr) noexcept = 0;
  virtual HRESULT __stdcall GetFontStyle(uint32_t, DWRITE_FONT_STYLE*, DWRITE_TEXT_RANGE* = nullptr) noexcept = 0;
  virtual HRESULT __stdcall GetFontStretch(uint32_t, DWRITE_FONT_STRETCH*, DWRITE_TEXT_RANGE* = nullptr) noexcept = 0;
  virtual HRESULT __stdcall GetFontSize(uint32_t, float*, DWRITE_TEXT_RANGE* = nullptr) noexcept = 0;
  virtual HRESULT __stdcall GetUnderline(uint32_t, int*, DWRITE_TEXT_RANGE* = nullptr) noexcept = 0;
  virtual HRESULT __stdcall GetStrikethrough(uint32_t, int*, DWRITE_TEXT_RANGE* = nullptr) noexcept = 0;
  virtual HRESULT __stdcall GetDrawingEffect(uint32_t, IUnknown**, DWRITE_TEXT_RANGE* = nullptr) noexcept = 0;
  virtual HRESULT __stdcall GetInlineObject(uint32_t, IDWriteInlineObject**, DWRITE_TEXT_RANGE* = nullptr) noexcept = 0;
  virtual HRESULT __stdcall GetTypography(uint32_t, IDWriteTypography**, DWRITE_TEXT_RANGE* = nullptr) noexcept = 0;
  virtual HRESULT __stdcall GetLocaleNameLength(uint32_t, uint32_t*, DWRITE_TEXT_RANGE* = nullptr) noexcept = 0;
  virtual HRESULT __stdcall GetLocaleName(uint32_t, wchar_t*, uint32_t, DWRITE_TEXT_RANGE* = nullptr) noexcept = 0;
  virtual HRESULT __stdcall Draw(void*, IDWriteTextRenderer*, float, float) noexcept = 0;
  virtual HRESULT __stdcall GetLineMetrics(DWRITE_LINE_METRICS*, uint32_t, uint32_t*) noexcept = 0;
  virtual HRESULT __stdcall GetMetrics(DWRITE_TEXT_METRICS*) noexcept = 0;
  virtual HRESULT __stdcall GetOverhangMetrics(DWRITE_OVERHANG_METRICS*) noexcept = 0;
  virtual HRESULT __stdcall GetClusterMetrics(DWRITE_CLUSTER_METRICS*, uint32_t, uint32_t*) noexcept = 0;
  virtual HRESULT __stdcall DetermineMinWidth(float*) noexcept = 0;
  virtual HRESULT __stdcall HitTestPoint(float, float, int*, int*, DWRITE_HIT_TEST_METRICS*) noexcept = 0;
  virtual HRESULT __stdcall HitTestTextPosition(uint32_t, int, float*, float*, DWRITE_HIT_TEST_METRICS*) noexcept = 0;
  virtual HRESULT __stdcall HitTestTextRange(uint32_t, uint32_t, float, float, DWRITE_HIT_TEST_METRICS*, uint32_t, uint32_t*) noexcept = 0;
  using IDWriteTextFormat::GetFontCollection;
  using IDWriteTextFormat::GetFontFamilyName;
  using IDWriteTextFormat::GetFontFamilyNameLength;
  using IDWriteTextFormat::GetFontSize;
  using IDWriteTextFormat::GetFontStretch;
  using IDWriteTextFormat::GetFontStyle;
  using IDWriteTextFormat::GetFontWeight;
  using IDWriteTextFormat::GetLocaleName;
  using IDWriteTextFormat::GetLocaleNameLength;
};

cominterface("5e5a32a3-8dff-4773-9ff6-0696eab77267") IDWriteBitmapRenderTarget : IUnknown {
  virtual HRESULT __stdcall DrawGlyphRun(float, float, DWRITE_MEASURING_MODE, const DWRITE_GLYPH_RUN*, IDWriteRenderingParams*, uint32_t, RECT* = nullptr) noexcept = 0;
  virtual HANDLE __stdcall GetMemoryDC() noexcept = 0;
  virtual float __stdcall GetPixelsPerDip() noexcept = 0;
  virtual HRESULT __stdcall SetPixelsPerDip(float) noexcept = 0;
  virtual HRESULT __stdcall GetCurrentTransform(DWRITE_MATRIX*) noexcept = 0;
  virtual HRESULT __stdcall SetCurrentTransform(const DWRITE_MATRIX*) noexcept = 0;
  virtual HRESULT __stdcall GetSize(SIZE*) noexcept = 0;
  virtual HRESULT __stdcall Resize(uint32_t, uint32_t) noexcept = 0;
};

cominterface("1edd9491-9853-4299-898f-6432983b6f3a") IDWriteGdiInterop : IUnknown {
  virtual HRESULT __stdcall CreateFontFromLOGFONT(const LOGFONTW*, IDWriteFont**) noexcept = 0;
  virtual HRESULT __stdcall ConvertFontToLOGFONT(IDWriteFont*, LOGFONTW*, int*) noexcept = 0;
  virtual HRESULT __stdcall ConvertFontFaceToLOGFONT(IDWriteFontFace*, LOGFONTW*) noexcept = 0;
  virtual HRESULT __stdcall CreateFontFaceFromHdc(HANDLE, IDWriteFontFace**) noexcept = 0;
  virtual HRESULT __stdcall CreateBitmapRenderTarget(HANDLE, uint32_t, uint32_t, IDWriteBitmapRenderTarget**) noexcept = 0;
};

cominterface("7d97dbf7-e085-42d4-81e3-6a883bded118") IDWriteGlyphRunAnalysis : IUnknown {
  virtual HRESULT __stdcall GetAlphaTextureBounds(DWRITE_TEXTURE_TYPE, RECT*) noexcept = 0;
  virtual HRESULT __stdcall CreateAlphaTexture(DWRITE_TEXTURE_TYPE, const RECT*, void*, uint32_t) noexcept = 0;
  virtual HRESULT __stdcall GetAlphaBlendParams(IDWriteRenderingParams*, float*, float*, float*) noexcept = 0;
};

cominterface("b859ee5a-d838-4b5b-a2e8-1adc7d93db48") IDWriteFactory : IUnknown {
  virtual HRESULT __stdcall GetSystemFontCollection(IDWriteFontCollection**, int = false) noexcept = 0;
  virtual HRESULT __stdcall CreateCustomFontCollection(IDWriteFontCollectionLoader*, const void*, uint32_t, IDWriteFontCollection**) noexcept = 0;
  virtual HRESULT __stdcall RegisterFontCollectionLoader(IDWriteFontCollectionLoader*) noexcept = 0;
  virtual HRESULT __stdcall UnregisterFontCollectionLoader(IDWriteFontCollectionLoader*) noexcept = 0;
  virtual HRESULT __stdcall CreateFontFileReference(const wchar_t*, const FILETIME*, IDWriteFontFile**) noexcept = 0;
  virtual HRESULT __stdcall CreateCustomFontFileReference(const void*, uint32_t, IDWriteFontFileLoader*, IDWriteFontFile**) noexcept = 0;
  virtual HRESULT __stdcall CreateFontFace(DWRITE_FONT_FACE_TYPE, uint32_t, IDWriteFontFile* const*, uint32_t, DWRITE_FONT_SIMULATIONS, IDWriteFontFace**) noexcept = 0;
  virtual HRESULT __stdcall CreateRenderingParams(IDWriteRenderingParams**) noexcept = 0;
  virtual HRESULT __stdcall CreateMonitorRenderingParams(HANDLE, IDWriteRenderingParams**) noexcept = 0;
  virtual HRESULT __stdcall CreateCustomRenderingParams(float, float, float, DWRITE_PIXEL_GEOMETRY, DWRITE_RENDERING_MODE, IDWriteRenderingParams**) noexcept = 0;
  virtual HRESULT __stdcall RegisterFontFileLoader(IDWriteFontFileLoader*) noexcept = 0;
  virtual HRESULT __stdcall UnregisterFontFileLoader(IDWriteFontFileLoader*) noexcept = 0;
  virtual HRESULT __stdcall CreateTextFormat(const wchar_t*, IDWriteFontCollection*, DWRITE_FONT_WEIGHT, DWRITE_FONT_STYLE, DWRITE_FONT_STRETCH, float, const wchar_t*, IDWriteTextFormat**) noexcept = 0;
  virtual HRESULT __stdcall CreateTypography(IDWriteTypography**) noexcept = 0;
  virtual HRESULT __stdcall GetGdiInterop(IDWriteGdiInterop**) noexcept = 0;
  virtual HRESULT __stdcall CreateTextLayout(const wchar_t*, uint32_t, IDWriteTextFormat*, float, float, IDWriteTextLayout**) noexcept = 0;
  virtual HRESULT __stdcall CreateGdiCompatibleTextLayout(const wchar_t*, uint32_t, IDWriteTextFormat*, float, float, float, const DWRITE_MATRIX*, int, IDWriteTextLayout**) noexcept = 0;
  virtual HRESULT __stdcall CreateEllipsisTrimmingSign(IDWriteTextFormat*, IDWriteInlineObject**) noexcept = 0;
  virtual HRESULT __stdcall CreateTextAnalyzer(IDWriteTextAnalyzer**) noexcept = 0;
  virtual HRESULT __stdcall CreateNumberSubstitution(DWRITE_NUMBER_SUBSTITUTION_METHOD, const wchar_t*, int, IDWriteNumberSubstitution**) noexcept = 0;
  virtual HRESULT __stdcall CreateGlyphRunAnalysis(const DWRITE_GLYPH_RUN*, float, const DWRITE_MATRIX*, DWRITE_RENDERING_MODE, DWRITE_MEASURING_MODE, float, float, IDWriteGlyphRunAnalysis**) noexcept = 0;
};

// struct DWRITE_GLYPH_RUN {
//   IDWriteFontFace* fontFace;
//   float fontEmSize;
//   uint32_t glyphCount;
//   const uint16_t* glyphIndices;
//   const float* glyphAdvances;
//   const DWRITE_GLYPH_OFFSET* glyphOffsets;
//   int isSideways;
//   uint32_t bidiLevel;
// };

// struct DWRITE_GLYPH_RUN_DESCRIPTION {
//   const wchar_t* localeName;
//   const wchar_t* string;
//   uint32_t stringLength;
//   const uint16_t* clusterMap;
//   uint32_t textPosition;
// };
}

HRESULT __stdcall DWriteCreateFactory(DWRITE_FACTORY_TYPE, const GUID&, IUnknown**) noexcept;

__ywlib_exportcend;
#endif
