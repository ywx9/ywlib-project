#pragma once
#include <inc/d2d1_1.h>
#ifndef __ywlib_import
__ywlib_exportc;

// enums

enum class WICBitmapAlphaChannelOption {
  WICBitmapUseAlpha,
  WICBitmapUsePremultipliedAlpha,
  WICBitmapIgnoreAlpha,
};
using enum WICBitmapAlphaChannelOption;

enum class WICBitmapCreateCacheOption {
  WICBitmapNoCache,
  WICBitmapCacheOnDemand,
  WICBitmapCacheOnLoad,
};
using enum WICBitmapCreateCacheOption;

enum class WICBitmapDitherType {
  WICBitmapDitherTypeNone = 0,
  WICBitmapDitherTypeSolid = 0,
  WICBitmapDitherTypeOrdered4x4 = 0x1,
  WICBitmapDitherTypeOrdered8x8 = 0x2,
  WICBitmapDitherTypeOrdered16x16 = 0x3,
  WICBitmapDitherTypeSpiral4x4 = 0x4,
  WICBitmapDitherTypeSpiral8x8 = 0x5,
  WICBitmapDitherTypeDualSpiral4x4 = 0x6,
  WICBitmapDitherTypeDualSpiral8x8 = 0x7,
  WICBitmapDitherTypeErrorDiffusion = 0x8,
};
using enum WICBitmapDitherType;

enum class WICBitmapEncoderCacheOption {
  WICBitmapEncoderCacheInMemory,
  WICBitmapEncoderCacheTempFile,
  WICBitmapEncoderNoCache,
};
using enum WICBitmapEncoderCacheOption;

enum class WICBitmapInterpolationMode {
  WICBitmapInterpolationModeNearestNeighbor,
  WICBitmapInterpolationModeLinear,
  WICBitmapInterpolationModeCubic,
  WICBitmapInterpolationModeFant,
  WICBitmapInterpolationModeHighQualityCubic,
};
using enum WICBitmapInterpolationMode;

enum class WICBitmapPaletteType {
  WICBitmapPaletteTypeCustom = 0,
  WICBitmapPaletteTypeMedianCut = 0x1,
  WICBitmapPaletteTypeFixedBW = 0x2,
  WICBitmapPaletteTypeFixedHalftone8 = 0x3,
  WICBitmapPaletteTypeFixedHalftone27 = 0x4,
  WICBitmapPaletteTypeFixedHalftone64 = 0x5,
  WICBitmapPaletteTypeFixedHalftone125 = 0x6,
  WICBitmapPaletteTypeFixedHalftone216 = 0x7,
  WICBitmapPaletteTypeFixedWebPalette = WICBitmapPaletteTypeFixedHalftone216,
  WICBitmapPaletteTypeFixedHalftone252 = 0x8,
  WICBitmapPaletteTypeFixedHalftone256 = 0x9,
  WICBitmapPaletteTypeFixedGray4 = 0xa,
  WICBitmapPaletteTypeFixedGray16 = 0xb,
  WICBitmapPaletteTypeFixedGray256 = 0xc,
};
using enum WICBitmapPaletteType;

enum class WICBitmapTransformOptions {
  WICBitmapTransformRotate0 = 0,
  WICBitmapTransformRotate90 = 0x1,
  WICBitmapTransformRotate180 = 0x2,
  WICBitmapTransformRotate270 = 0x3,
  WICBitmapTransformFlipHorizontal = 0x8,
  WICBitmapTransformFlipVertical = 0x10,
};
using enum WICBitmapTransformOptions;

enum class WICColorContextType {
  WICColorContextUninitialized,
  WICColorContextProfile,
  WICColorContextExifColorSpace,
};
using enum WICColorContextType;

enum class WICDecodeOptions {
  WICDecodeMetadataCacheOnDemand,
  WICDecodeMetadataCacheOnLoad,
};
using enum WICDecodeOptions;

enum class WICComponentType {
  WICDecoder = 0x1,
  WICEncoder = 0x2,
  WICPixelFormatConverter = 0x4,
  WICMetadataReader = 0x8,
  WICMetadataWriter = 0x10,
  WICPixelFormat = 0x20,
  WICAllComponents = 0x3f,
};
using enum WICComponentType;

enum class WICPixelFormatNumericRepresentation {
  WICPixelFormatNumericRepresentationUnspecified,
  WICPixelFormatNumericRepresentationIndexed,
  WICPixelFormatNumericRepresentationUnsignedInteger,
  WICPixelFormatNumericRepresentationSignedInteger,
  WICPixelFormatNumericRepresentationFixed,
  WICPixelFormatNumericRepresentationFloat,
};
using enum WICPixelFormatNumericRepresentation;

enum class WICPlanarOptions {
  WICPlanarOptionsDefault,
  WICPlanarOptionsPreserveSubsampling,
};
using enum WICPlanarOptions;

enum class WICProgressOperation {
  WICProgressOperationCopyPixels = 0x1,
  WICProgressOperationWritePixels = 0x2,
  WICProgressOperationAll = 0xffff,
};
using enum WICProgressOperation;

// clang-format off
inline constexpr GUID WICPixelFormat32bppBGRA{ 0x6fddc324, 0x4e03, 0x4bfe, {0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x0f}};
inline constexpr GUID WICPixelFormat32bppPBGRA{0x6fddc324, 0x4e03, 0x4bfe, {0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x10}};
inline constexpr GUID WICPixelFormat32bppRGBA{ 0xf5c7ad2d, 0x6a8d, 0x43dd, {0xa7, 0xa8, 0xa2, 0x99, 0x35, 0x26, 0x1a, 0xe9}};
inline constexpr GUID WICPixelFormat32bppPRGBA{0x3cc4a650, 0xa527, 0x4d37, {0xa9, 0x16, 0x31, 0x42, 0xc7, 0xeb, 0xed, 0xba}}; // clang-format on

cominterface("00000040-a8f2-4877-ba0a-fd2b6645fb94") IWICPalette : IUnknown {
  virtual HRESULT __stdcall InitializePredefined(WICBitmapPaletteType, int) = 0;
  virtual HRESULT __stdcall InitializeCustom(uint32_t*, int) = 0;
  virtual HRESULT __stdcall InitializeFromBitmap(IWICBitmapSource*, int, int) = 0;
  virtual HRESULT __stdcall InitializeFromPalette(IWICPalette*) = 0;
  virtual HRESULT __stdcall GetType(WICBitmapPaletteType*) = 0;
  virtual HRESULT __stdcall GetColorCount(int*) = 0;
  virtual HRESULT __stdcall GetColors(int, uint32_t*, int*) = 0;
  virtual HRESULT __stdcall IsBlackWhite(int*) = 0;
  virtual HRESULT __stdcall IsGrayscale(int*) = 0;
  virtual HRESULT __stdcall HasAlpha(int*) = 0;
};

cominterface("00000120-a8f2-4877-ba0a-fd2b6645fb94") IWICBitmapSource : IUnknown {
  virtual HRESULT __stdcall GetSize(int*, int*) = 0;
  virtual HRESULT __stdcall GetPixelFormat(GUID*) = 0;
  virtual HRESULT __stdcall GetResolution(double*, double*) = 0;
  virtual HRESULT __stdcall CopyPalette(IWICPalette*) = 0;
  virtual HRESULT __stdcall CopyPixels(const RECT*, int, int, void*) = 0;
};

cominterface("00000301-a8f2-4877-ba0a-fd2b6645fb94") IWICFormatConverter : IWICBitmapSource {
  virtual HRESULT __stdcall Initialize(IWICBitmapSource*, const GUID&, WICBitmapDitherType, IWICPalette*, double, WICBitmapPaletteType) = 0;
  virtual HRESULT __stdcall CanConvert(const GUID&, const GUID&, int*) = 0;
};

cominterface("BEBEE9CB-83B0-4DCC-8132-B0AAA55EAC96") IWICPlanarFormatConverter : IWICBitmapSource {
  virtual HRESULT __stdcall Initialize(IWICBitmapSource**, int, const GUID&, WICBitmapDitherType, IWICPalette*, double, WICBitmapPaletteType) = 0;
  virtual HRESULT __stdcall CanConvert(const GUID*, int, const GUID&, int*) = 0;
};

cominterface("00000302-a8f2-4877-ba0a-fd2b6645fb94") IWICBitmapScaler : IWICBitmapSource {
  virtual HRESULT __stdcall Initialize(IWICBitmapSource*, int, int, WICBitmapInterpolationMode) = 0;
};

cominterface("E4FBCF03-223D-4e81-9333-D635556DD1B5") IWICBitmapClipper : IWICBitmapSource {
  virtual HRESULT __stdcall Initialize(IWICBitmapSource*, const RECT*) = 0;
};

cominterface("5009834F-2D6A-41ce-9E1B-17C5AFF7A782") IWICBitmapFlipRotator : IWICBitmapSource {
  virtual HRESULT __stdcall Initialize(IWICBitmapSource*, WICBitmapTransformOptions) = 0;
};

cominterface("00000123-a8f2-4877-ba0a-fd2b6645fb94") IWICBitmapLock : IUnknown {
  virtual HRESULT __stdcall GetSize(int*, int*) = 0;
  virtual HRESULT __stdcall GetStride(int*) = 0;
  virtual HRESULT __stdcall GetDataPointer(int*, void**) = 0;
  virtual HRESULT __stdcall GetPixelFormat(GUID*) = 0;
};

cominterface("00000121-a8f2-4877-ba0a-fd2b6645fb94") IWICBitmap : IWICBitmapSource {
  virtual HRESULT __stdcall Lock(const RECT*, int, IWICBitmapLock**) = 0;
  virtual HRESULT __stdcall SetPalette(IWICPalette*) = 0;
  virtual HRESULT __stdcall SetResolution(double, double) = 0;
};

cominterface("3C613A02-34B2-44ea-9A7C-45AEA9C6FD6D") IWICColorContext : IUnknown {
  virtual HRESULT __stdcall InitializeFromFilename(const wchar_t*) = 0;
  virtual HRESULT __stdcall InitializeFromMemory(const void*, int) = 0;
  virtual HRESULT __stdcall InitializeFromExifColorSpace(int) = 0;
  virtual HRESULT __stdcall GetType(WICColorContextType*) = 0;
  virtual HRESULT __stdcall GetProfileBytes(int, void*, int*) = 0;
  virtual HRESULT __stdcall GetExifColorSpace(int*) = 0;
};

cominterface("B66F034F-D0E2-40ab-B436-6DE39E321A94") IWICColorTransform : IWICBitmapSource {
  virtual HRESULT __stdcall Initialize(IWICBitmapSource*, IWICColorContext*, IWICColorContext*, const GUID&) = 0;
};

cominterface("30989668-E1C9-4597-B395-458EEDB808DF") IWICMetadataQueryReader : IUnknown {
  virtual HRESULT __stdcall GetContainerFormat(GUID*) = 0;
  virtual HRESULT __stdcall GetLocation(int, wchar_t*, int*) = 0;
  virtual HRESULT __stdcall GetMetadataByName(const wchar_t*, void*) = 0;
  virtual HRESULT __stdcall GetEnumerator(IEnumString**) = 0;
};

cominterface("A721791A-0DEF-4d06-BD91-2118BF1DB10B") IWICMetadataQueryWriter : IWICMetadataQueryReader {
  virtual HRESULT __stdcall SetMetadataByName(const wchar_t*, const void*) = 0;
  virtual HRESULT __stdcall RemoveMetadataByName(const wchar_t*) = 0;
};

cominterface("B84E2C09-78C9-4AC4-8BD3-524AE1663A2F") IWICFastMetadataEncoder : IUnknown {
  virtual HRESULT __stdcall Commit() = 0;
  virtual HRESULT __stdcall GetMetadataQueryWriter(IWICMetadataQueryWriter**) = 0;
};

cominterface("135FF860-22B7-4ddf-B0F6-218F4F299A43") IWICStream : IStream {
  virtual HRESULT __stdcall InitializeFromIStream(IStream*) = 0;
  virtual HRESULT __stdcall InitializeFromFilename(const wchar_t*, int) = 0;
  virtual HRESULT __stdcall InitializeFromMemory(void*, int) = 0;
  virtual HRESULT __stdcall InitializeFromIStreamRegion(IStream*, size_t, size_t) = 0;
};

cominterface("DC2BB46D-3F07-481E-8625-220C4AEDBB33") IWICEnumMetadataItem : IUnknown {
  virtual HRESULT __stdcall Next(int, void*, void*, void*, int*) = 0;
  virtual HRESULT __stdcall Skip(int) = 0;
  virtual HRESULT __stdcall Reset() = 0;
  virtual HRESULT __stdcall Clone(IWICEnumMetadataItem**) = 0;
};

cominterface("00000105-a8f2-4877-ba0a-fd2b6645fb94") IWICBitmapFrameEncode : IUnknown {
  virtual HRESULT __stdcall Initialize(void*) = 0;
  virtual HRESULT __stdcall SetSize(int, int) = 0;
  virtual HRESULT __stdcall SetResolution(double, double) = 0;
  virtual HRESULT __stdcall SetPixelFormat(GUID*) = 0;
  virtual HRESULT __stdcall SetColorContexts(int, IWICColorContext**) = 0;
  virtual HRESULT __stdcall SetPalette(IWICPalette*) = 0;
  virtual HRESULT __stdcall SetThumbnail(IWICBitmapSource*) = 0;
  virtual HRESULT __stdcall WritePixels(int, int, int, void*) = 0;
  virtual HRESULT __stdcall WriteSource(IWICBitmapSource*, RECT*) = 0;
  virtual HRESULT __stdcall Commit() = 0;
  virtual HRESULT __stdcall GetMetadataQueryWriter(IWICMetadataQueryWriter**) = 0;
};

cominterface("94C9B4EE-A09F-4f92-8A1E-4A9BCE7E76FB") IWICBitmapEncoderInfo;
cominterface("00000103-a8f2-4877-ba0a-fd2b6645fb94") IWICBitmapEncoder : IUnknown {
  virtual HRESULT __stdcall Initialize(IStream*, WICBitmapEncoderCacheOption) = 0;
  virtual HRESULT __stdcall GetContainerFormat(GUID*) = 0;
  virtual HRESULT __stdcall GetEncoderInfo(IWICBitmapEncoderInfo**) = 0;
  virtual HRESULT __stdcall SetColorContexts(int, IWICColorContext**) = 0;
  virtual HRESULT __stdcall SetPalette(IWICPalette*) = 0;
  virtual HRESULT __stdcall SetThumbnail(IWICBitmapSource*) = 0;
  virtual HRESULT __stdcall SetPreview(IWICBitmapSource*) = 0;
  virtual HRESULT __stdcall CreateNewFrame(IWICBitmapFrameEncode**, void**) = 0;
  virtual HRESULT __stdcall Commit() = 0;
  virtual HRESULT __stdcall GetMetadataQueryWriter(IWICMetadataQueryWriter**) = 0;
};

struct WICBitmapPlane {
  GUID Format;
  void* pbBuffer;
  int cbStride, cbBufferSize;
};

struct WICImageParameters {
  D2D1_PIXEL_FORMAT PixelFormat;
  float DpiX, DpiY, Top, Left;
  uint32_t PixelWidth, PixelHeight;
};

cominterface("F928B7B8-2221-40C1-B72E-7E82F1974D1A") IWICPlanarBitmapFrameEncode : IUnknown {
  virtual HRESULT __stdcall WritePixels(int, WICBitmapPlane*, int) = 0;
  virtual HRESULT __stdcall WriteSource(IWICBitmapSource**, int, RECT*) = 0;
};

cominterface("04C75BF8-3CE1-473B-ACC5-3CC4F5E94999") IWICImageEncoder : IUnknown {
  virtual HRESULT __stdcall WriteFrame(ID2D1Image*, IWICBitmapFrameEncode*, const WICImageParameters*) = 0;
  virtual HRESULT __stdcall WriteFrameThumbnail(ID2D1Image*, IWICBitmapFrameEncode*, const WICImageParameters*) = 0;
  virtual HRESULT __stdcall WriteThumbnail(ID2D1Image*, IWICBitmapEncoder*, const WICImageParameters*) = 0;
};

cominterface("3B16811B-6A43-4ec9-B713-3D5A0C13B940") IWICBitmapSourceTransform : IUnknown {
  virtual HRESULT __stdcall CopyPixels(const RECT*, int, int, GUID*, WICBitmapTransformOptions, int, int, void*) = 0;
  virtual HRESULT __stdcall GetClosestSize(int*, int*) = 0;
  virtual HRESULT __stdcall GetClosestPixelFormat(GUID*) = 0;
  virtual HRESULT __stdcall DoesSupportTransform(WICBitmapTransformOptions, int*) = 0;
};

cominterface("3B16811B-6A43-4ec9-A813-3D930C13B940") IWICBitmapFrameDecode : IWICBitmapSource {
  virtual HRESULT __stdcall GetMetadataQueryReader(IWICMetadataQueryReader**) = 0;
  virtual HRESULT __stdcall GetColorContexts(int, IWICColorContext**, int*) = 0;
  virtual HRESULT __stdcall GetThumbnail(IWICBitmapSource**) = 0;
};

cominterface("D8CD007F-D08F-4191-9BFC-236EA7F0E4B5") IWICBitmapDecoderInfo;
cominterface("9EDDE9E7-8DEE-47ea-99DF-E6FAF2ED44BF") IWICBitmapDecoder : IUnknown {
  virtual HRESULT __stdcall QueryCapability(IStream*, int*) = 0;
  virtual HRESULT __stdcall Initialize(IStream*, WICDecodeOptions) = 0;
  virtual HRESULT __stdcall GetContainerFormat(GUID*) = 0;
  virtual HRESULT __stdcall GetDecoderInfo(IWICBitmapDecoderInfo**) = 0;
  virtual HRESULT __stdcall CopyPalette(IWICPalette*) = 0;
  virtual HRESULT __stdcall GetMetadataQueryReader(IWICMetadataQueryReader**) = 0;
  virtual HRESULT __stdcall GetPreview(IWICBitmapSource**) = 0;
  virtual HRESULT __stdcall GetColorContexts(int, IWICColorContext**, int*) = 0;
  virtual HRESULT __stdcall GetThumbnail(IWICBitmapSource**) = 0;
  virtual HRESULT __stdcall GetFrameCount(int*) = 0;
  virtual HRESULT __stdcall GetFrame(int, IWICBitmapFrameDecode**) = 0;
};

struct WICBitmapPlaneDescription {
  GUID Format;
  int Width, Height;
};

cominterface("3AFF9CCE-BE95-4303-B927-E7D16FF4A613") IWICPlanarBitmapSourceTransform : IUnknown {
  virtual HRESULT __stdcall DoesSupportTransform(int*, int*, WICBitmapTransformOptions, WICPlanarOptions, const GUID*, WICBitmapPlaneDescription*, int, int*) = 0;
  virtual HRESULT __stdcall CopyPixels(const RECT*, int, int, WICBitmapTransformOptions, WICPlanarOptions, const WICBitmapPlane*, int) = 0;
};

cominterface("DAAC296F-7AA5-4dbf-8D15-225C5976F891") IWICProgressiveLevelControl : IUnknown {
  virtual HRESULT __stdcall GetLevelCount(int*) = 0;
  virtual HRESULT __stdcall GetCurrentLevel(int*) = 0;
  virtual HRESULT __stdcall SetCurrentLevel(int) = 0;
};

cominterface("4776F9CD-9517-45FA-BF24-E89C5EC5C60C") IWICProgressCallback : IUnknown {
  virtual HRESULT __stdcall Notify(int, WICProgressOperation, double) = 0;
};

cominterface("64C1024E-C3CF-4462-8078-88C2B11C46D9") IWICBitmapCodecProgressNotification : IUnknown {
  virtual HRESULT __stdcall RegisterProgressNotification(void*, void*, int) = 0;
};

cominterface("23BC3F0A-698B-4357-886B-F24D50671334") IWICComponentInfo : IUnknown {
  virtual HRESULT __stdcall GetComponentType(WICComponentType*) = 0;
  virtual HRESULT __stdcall GetCLSID(GUID*) = 0;
  virtual HRESULT __stdcall GetSigningStatus(int*) = 0;
  virtual HRESULT __stdcall GetAuthor(int, wchar_t*, int*) = 0;
  virtual HRESULT __stdcall GetVendorGUID(GUID*) = 0;
  virtual HRESULT __stdcall GetVersion(int, wchar_t*, int*) = 0;
  virtual HRESULT __stdcall GetSpecVersion(int, wchar_t*, int*) = 0;
  virtual HRESULT __stdcall GetFriendlyName(int, wchar_t*, int*) = 0;
};

cominterface("9F34FB65-13F4-4f15-BC57-3726B5E53D9F") IWICFormatConverterInfo : IWICComponentInfo {
  virtual HRESULT __stdcall GetPixelFormats(int, GUID*, int*) = 0;
  virtual HRESULT __stdcall CreateInstance(IWICFormatConverter**) = 0;
};

cominterface("E87A44C4-B76E-4c47-8B09-298EB12A2714") IWICBitmapCodecInfo : IWICComponentInfo {
  virtual HRESULT __stdcall GetContainerFormat(GUID*) = 0;
  virtual HRESULT __stdcall GetPixelFormats(int, GUID*, int*) = 0;
  virtual HRESULT __stdcall GetColorManagementVersion(int, wchar_t*, int*) = 0;
  virtual HRESULT __stdcall GetDeviceManufacturer(int, wchar_t*, int*) = 0;
  virtual HRESULT __stdcall GetDeviceModels(int, wchar_t*, int*) = 0;
  virtual HRESULT __stdcall GetMimeTypes(int, wchar_t*, int*) = 0;
  virtual HRESULT __stdcall GetFileExtensions(int, wchar_t*, int*) = 0;
  virtual HRESULT __stdcall DoesSupportAnimation(int*) = 0;
  virtual HRESULT __stdcall DoesSupportChromakey(int*) = 0;
  virtual HRESULT __stdcall DoesSupportLossless(int*) = 0;
  virtual HRESULT __stdcall DoesSupportMultiframe(int*) = 0;
  virtual HRESULT __stdcall MatchesMimeType(const wchar_t*, int*) = 0;
};

cominterface("94C9B4EE-A09F-4f92-8A1E-4A9BCE7E76FB") IWICBitmapEncoderInfo : IWICBitmapCodecInfo {
  virtual HRESULT __stdcall CreateInstance(IWICBitmapEncoder**) = 0;
};

struct WICBitmapPattern {
  uint64_t Position;
  uint32_t Length;
  void* Pattern;
  void* Mask;
  int EndOfStream;
};

cominterface("D8CD007F-D08F-4191-9BFC-236EA7F0E4B5") IWICBitmapDecoderInfo : IWICBitmapCodecInfo {
  virtual HRESULT __stdcall GetPatterns(int, WICBitmapPattern*, int*, int*) = 0;
  virtual HRESULT __stdcall MatchesPattern(IStream*, int*) = 0;
  virtual HRESULT __stdcall CreateInstance(IWICBitmapDecoder**) = 0;
};

cominterface("E8EDA601-3D48-431a-AB44-69059BE88BBE") IWICPixelFormatInfo : IWICComponentInfo {
  virtual HRESULT __stdcall GetFormatGUID(GUID*) = 0;
  virtual HRESULT __stdcall GetColorContext(IWICColorContext**) = 0;
  virtual HRESULT __stdcall GetBitsPerPixel(int*) = 0;
  virtual HRESULT __stdcall GetChannelCount(int*) = 0;
  virtual HRESULT __stdcall GetChannelMask(int, int, void*, int*) = 0;
};

cominterface("A9DB33A2-AF5F-43C7-B679-74F5984B5AA4") IWICPixelFormatInfo2 : IWICPixelFormatInfo {
  virtual HRESULT __stdcall SupportsTransparency(int*) = 0;
  virtual HRESULT __stdcall GetNumericRepresentation(WICPixelFormatNumericRepresentation*) = 0;
};

cominterface("ec5ec8a9-c395-4314-9c77-54d7a935ff70") IWICImagingFactory : IUnknown {
  virtual HRESULT __stdcall CreateDecoderFromFilename(const wchar_t*, const GUID*, int, WICDecodeOptions, IWICBitmapDecoder**) = 0;
  virtual HRESULT __stdcall CreateDecoderFromStream(IStream*, const GUID*, WICDecodeOptions, IWICBitmapDecoder**) = 0;
  virtual HRESULT __stdcall CreateDecoderFromFileHandle(uint64_t, const GUID*, WICDecodeOptions, IWICBitmapDecoder**) = 0;
  virtual HRESULT __stdcall CreateComponentInfo(const GUID&, IWICComponentInfo**) = 0;
  virtual HRESULT __stdcall CreateDecoder(const GUID&, const GUID*, IWICBitmapDecoder**) = 0;
  virtual HRESULT __stdcall CreateEncoder(const GUID&, const GUID*, IWICBitmapEncoder**) = 0;
  virtual HRESULT __stdcall CreatePalette(IWICPalette**) = 0;
  virtual HRESULT __stdcall CreateFormatConverter(IWICFormatConverter**) = 0;
  virtual HRESULT __stdcall CreateBitmapScaler(IWICBitmapScaler**) = 0;
  virtual HRESULT __stdcall CreateBitmapClipper(IWICBitmapClipper**) = 0;
  virtual HRESULT __stdcall CreateBitmapFlipRotator(IWICBitmapFlipRotator**) = 0;
  virtual HRESULT __stdcall CreateStream(IWICStream**) = 0;
  virtual HRESULT __stdcall CreateColorContext(IWICColorContext**) = 0;
  virtual HRESULT __stdcall CreateColorTransformer(IWICColorTransform**) = 0;
  virtual HRESULT __stdcall CreateBitmap(int, int, const GUID&, WICBitmapCreateCacheOption, IWICBitmap**) = 0;
  virtual HRESULT __stdcall CreateBitmapFromSource(IWICBitmapSource*, WICBitmapCreateCacheOption, IWICBitmap**) = 0;
  virtual HRESULT __stdcall CreateBitmapFromSourceRect(IWICBitmapSource*, int, int, int, int, IWICBitmap**) = 0;
  virtual HRESULT __stdcall CreateBitmapFromMemory(int, int, const GUID&, int, int, void*, IWICBitmap**) = 0;
  virtual HRESULT __stdcall CreateBitmapFromHBITMAP(HANDLE, HANDLE, WICBitmapAlphaChannelOption, IWICBitmap**) = 0;
  virtual HRESULT __stdcall CreateBitmapFromHICON(HANDLE, IWICBitmap**) = 0;
  virtual HRESULT __stdcall CreateComponentEnumerator(int, int, void**) = 0;
  virtual HRESULT __stdcall CreateFastMetadataEncoderFromDecoder(IWICBitmapDecoder*, IWICFastMetadataEncoder**) = 0;
  virtual HRESULT __stdcall CreateFastMetadataEncoderFromFrameDecode(IWICBitmapFrameDecode*, IWICFastMetadataEncoder**) = 0;
  virtual HRESULT __stdcall CreateQueryWriter(const GUID&, const GUID*, IWICMetadataQueryWriter**) = 0;
  virtual HRESULT __stdcall CreateQueryWriterFromReader(IWICMetadataQueryReader*, const GUID*, IWICMetadataQueryWriter**) = 0;
};

cominterface("7B816B45-1996-4476-B132-DE9E247C8AF0") IWICImagingFactory2 : IWICImagingFactory {
  virtual HRESULT __stdcall CreateImageEncoder(ID2D1Device*, IWICImageEncoder**) = 0;
};

cominterface("95c75a6e-3e8c-4ec2-85a8-aebcc551e59b") IWICDevelopRawNotificationCallback : IUnknown {
  virtual HRESULT __stdcall Notify(int) = 0;
};

HRESULT __stdcall CoCreateInstance(const GUID&, IUnknown*, int, const GUID&, void**);

__ywlib_exportcend;
#endif
