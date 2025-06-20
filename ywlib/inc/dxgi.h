#pragma once
#include <inc/windows.h>
#define cominterface(id) struct __declspec(uuid(id)) __declspec(novtable)
#ifndef __ywlib_import
__ywlib_exportc;

// MARK: BEFORE DXGI

using LUID = int64_t;

typedef struct _GUID {
  uint32_t Data1;
  uint16_t Data2, Data3;
  uint8_t Data4[8];
} GUID;

struct FILETIME {
  uint32_t dwLowDateTime;
  uint32_t dwHighDateTime;
};

struct STATSTG {
  wchar_t* pwcsName;
  uint32_t type;
  uint64_t cbSize;
  FILETIME mtime;
  FILETIME ctime;
  FILETIME atime;
  uint32_t grfMode;
  uint32_t grfLocksSupported;
  GUID clsid;
  uint32_t grfStateBits;
  uint32_t reserved;
};

extern "C++" struct __declspec(uuid("00000000-0000-0000-C000-000000000046")) __declspec(novtable) IUnknown {
  virtual HRESULT __stdcall QueryInterface(const GUID&, void**) = 0;
  virtual int __stdcall AddRef()                                = 0;
  virtual int __stdcall Release()                               = 0;
  template<typename Com> HRESULT __stdcall QueryInterface(Com** pp) { return QueryInterface(__uuidof(Com), (void**)pp); }
};

cominterface("00000101-0000-0000-C000-000000000046") IEnumString : IUnknown {
  virtual HRESULT __stdcall Next(uint32_t, wchar_t*, uint32_t*) = 0;
  virtual HRESULT __stdcall Skip(uint32_t)                      = 0;
  virtual HRESULT __stdcall Reset()                             = 0;
  virtual HRESULT __stdcall Clone(IEnumString**)                = 0;
};

cominterface("0c733a30-2a1c-11ce-ade5-00aa0044773d") ISequentialStream : IUnknown {
  virtual HRESULT __stdcall Read(void*, uint32_t, uint32_t*)        = 0;
  virtual HRESULT __stdcall Write(const void*, uint32_t, uint32_t*) = 0;
};

cominterface("0000000c-0000-0000-C000-000000000046") IStream : public ISequentialStream {
  virtual HRESULT __stdcall Seek(int64_t, uint32_t, uint64_t*)               = 0;
  virtual HRESULT __stdcall SetSize(uint64_t)                                = 0;
  virtual HRESULT __stdcall CopyTo(IStream*, uint64_t, uint64_t*, uint64_t*) = 0;
  virtual HRESULT __stdcall Commit(uint32_t)                                 = 0;
  virtual HRESULT __stdcall Revert()                                         = 0;
  virtual HRESULT __stdcall LockRegion(uint64_t, uint64_t, uint32_t)         = 0;
  virtual HRESULT __stdcall UnlockRegion(uint64_t, uint64_t, uint32_t)       = 0;
  virtual HRESULT __stdcall Stat(STATSTG*, uint32_t)                         = 0;
  virtual HRESULT __stdcall Clone(IStream**)                                 = 0;
};

// MARK: ENUMS

enum class DXGI_ADAPTER_FLAG {
  DXGI_ADAPTER_FLAG_NONE,
  DXGI_ADAPTER_FLAG_REMOTE,
  DXGI_ADAPTER_FLAG_SOFTWARE,
};
using enum DXGI_ADAPTER_FLAG;

enum class DXGI_FORMAT : uint32_t {
  DXGI_FORMAT_UNKNOWN,
  DXGI_FORMAT_R32G32B32A32_TYPELESS,
  DXGI_FORMAT_R32G32B32A32_FLOAT,
  DXGI_FORMAT_R32G32B32A32_UINT,
  DXGI_FORMAT_R32G32B32A32_SINT,
  DXGI_FORMAT_R32G32B32_TYPELESS,
  DXGI_FORMAT_R32G32B32_FLOAT,
  DXGI_FORMAT_R32G32B32_UINT,
  DXGI_FORMAT_R32G32B32_SINT,
  DXGI_FORMAT_R16G16B16A16_TYPELESS,
  DXGI_FORMAT_R16G16B16A16_FLOAT,
  DXGI_FORMAT_R16G16B16A16_UNORM,
  DXGI_FORMAT_R16G16B16A16_UINT,
  DXGI_FORMAT_R16G16B16A16_SNORM,
  DXGI_FORMAT_R16G16B16A16_SINT,
  DXGI_FORMAT_R32G32_TYPELESS,
  DXGI_FORMAT_R32G32_FLOAT,
  DXGI_FORMAT_R32G32_UINT,
  DXGI_FORMAT_R32G32_SINT,
  DXGI_FORMAT_R32G8X24_TYPELESS,
  DXGI_FORMAT_D32_FLOAT_S8X24_UINT,
  DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS,
  DXGI_FORMAT_X32_TYPELESS_G8X24_UINT,
  DXGI_FORMAT_R10G10B10A2_TYPELESS,
  DXGI_FORMAT_R10G10B10A2_UNORM,
  DXGI_FORMAT_R10G10B10A2_UINT,
  DXGI_FORMAT_R11G11B10_FLOAT,
  DXGI_FORMAT_R8G8B8A8_TYPELESS,
  DXGI_FORMAT_R8G8B8A8_UNORM,
  DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
  DXGI_FORMAT_R8G8B8A8_UINT,
  DXGI_FORMAT_R8G8B8A8_SNORM,
  DXGI_FORMAT_R8G8B8A8_SINT,
  DXGI_FORMAT_R16G16_TYPELESS,
  DXGI_FORMAT_R16G16_FLOAT,
  DXGI_FORMAT_R16G16_UNORM,
  DXGI_FORMAT_R16G16_UINT,
  DXGI_FORMAT_R16G16_SNORM,
  DXGI_FORMAT_R16G16_SINT,
  DXGI_FORMAT_R32_TYPELESS,
  DXGI_FORMAT_D32_FLOAT,
  DXGI_FORMAT_R32_FLOAT,
  DXGI_FORMAT_R32_UINT,
  DXGI_FORMAT_R32_SINT,
  DXGI_FORMAT_R24G8_TYPELESS,
  DXGI_FORMAT_D24_UNORM_S8_UINT,
  DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
  DXGI_FORMAT_X24_TYPELESS_G8_UINT,
  DXGI_FORMAT_R8G8_TYPELESS,
  DXGI_FORMAT_R8G8_UNORM,
  DXGI_FORMAT_R8G8_UINT,
  DXGI_FORMAT_R8G8_SNORM,
  DXGI_FORMAT_R8G8_SINT,
  DXGI_FORMAT_R16_TYPELESS,
  DXGI_FORMAT_R16_FLOAT,
  DXGI_FORMAT_D16_UNORM,
  DXGI_FORMAT_R16_UNORM,
  DXGI_FORMAT_R16_UINT,
  DXGI_FORMAT_R16_SNORM,
  DXGI_FORMAT_R16_SINT,
  DXGI_FORMAT_R8_TYPELESS,
  DXGI_FORMAT_R8_UNORM,
  DXGI_FORMAT_R8_UINT,
  DXGI_FORMAT_R8_SNORM,
  DXGI_FORMAT_R8_SINT,
  DXGI_FORMAT_A8_UNORM,
  DXGI_FORMAT_R1_UNORM,
  DXGI_FORMAT_R9G9B9E5_SHAREDEXP,
  DXGI_FORMAT_R8G8_B8G8_UNORM,
  DXGI_FORMAT_G8R8_G8B8_UNORM,
  DXGI_FORMAT_BC1_TYPELESS,
  DXGI_FORMAT_BC1_UNORM,
  DXGI_FORMAT_BC1_UNORM_SRGB,
  DXGI_FORMAT_BC2_TYPELESS,
  DXGI_FORMAT_BC2_UNORM,
  DXGI_FORMAT_BC2_UNORM_SRGB,
  DXGI_FORMAT_BC3_TYPELESS,
  DXGI_FORMAT_BC3_UNORM,
  DXGI_FORMAT_BC3_UNORM_SRGB,
  DXGI_FORMAT_BC4_TYPELESS,
  DXGI_FORMAT_BC4_UNORM,
  DXGI_FORMAT_BC4_SNORM,
  DXGI_FORMAT_BC5_TYPELESS,
  DXGI_FORMAT_BC5_UNORM,
  DXGI_FORMAT_BC5_SNORM,
  DXGI_FORMAT_B5G6R5_UNORM,
  DXGI_FORMAT_B5G5R5A1_UNORM,
  DXGI_FORMAT_B8G8R8A8_UNORM,
  DXGI_FORMAT_B8G8R8X8_UNORM,
  DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM,
  DXGI_FORMAT_B8G8R8A8_TYPELESS,
  DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,
  DXGI_FORMAT_B8G8R8X8_TYPELESS,
  DXGI_FORMAT_B8G8R8X8_UNORM_SRGB,
  DXGI_FORMAT_BC6H_TYPELESS,
  DXGI_FORMAT_BC6H_UF16,
  DXGI_FORMAT_BC6H_SF16,
  DXGI_FORMAT_BC7_TYPELESS,
  DXGI_FORMAT_BC7_UNORM,
  DXGI_FORMAT_BC7_UNORM_SRGB,
  DXGI_FORMAT_AYUV,
  DXGI_FORMAT_Y410,
  DXGI_FORMAT_Y416,
  DXGI_FORMAT_NV12,
  DXGI_FORMAT_P010,
  DXGI_FORMAT_P016,
  DXGI_FORMAT_420_OPAQUE,
  DXGI_FORMAT_YUY2,
  DXGI_FORMAT_Y210,
  DXGI_FORMAT_Y216,
  DXGI_FORMAT_NV11,
  DXGI_FORMAT_AI44,
  DXGI_FORMAT_IA44,
  DXGI_FORMAT_P8,
  DXGI_FORMAT_A8P8,
  DXGI_FORMAT_B4G4R4A4_UNORM,
  DXGI_FORMAT_P208                                    = 130,
  DXGI_FORMAT_V208                                    = 131,
  DXGI_FORMAT_V408                                    = 132,
  DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE         = 189,
  DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE = 190,
};
using enum DXGI_FORMAT;

enum DXGI_MODE_ROTATION {
  DXGI_MODE_ROTATION_UNSPECIFIED,
  DXGI_MODE_ROTATION_IDENTITY,
  DXGI_MODE_ROTATION_ROTATE90,
  DXGI_MODE_ROTATION_ROTATE180,
  DXGI_MODE_ROTATION_ROTATE270,
};
using enum DXGI_MODE_ROTATION;

enum class DXGI_MODE_SCALING {
  DXGI_MODE_SCALING_UNSPECIFIED,
  DXGI_MODE_SCALING_CENTERED,
  DXGI_MODE_SCALING_STRETCHED,
};
using enum DXGI_MODE_SCALING;

enum class DXGI_MODE_SCANLINE_ORDER {
  DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
  DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE,
  DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST,
  DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST,
};
using enum DXGI_MODE_SCANLINE_ORDER;

enum class DXGI_RESIDENCY {
  DXGI_RESIDENCY_FULLY_RESIDENT,
  DXGI_RESIDENCY_RESIDENT_IN_SHARED_MEMORY,
  DXGI_RESIDENCY_EVICTED_TO_DISK,
};
using enum DXGI_RESIDENCY;

enum class DXGI_SWAP_EFFECT {
  DXGI_SWAP_EFFECT_DISCARD,
  DXGI_SWAP_EFFECT_SEQUENTIAL,
  DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
  DXGI_SWAP_EFFECT_FLIP_DISCARD,
};
using enum DXGI_SWAP_EFFECT;

enum class DXGI_SWAP_CHAIN_FLAG {
  DXGI_SWAP_CHAIN_FLAG_NONPREROTATED                          = 1,
  DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH                      = 2,
  DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE                         = 4,
  DXGI_SWAP_CHAIN_FLAG_RESTRICTED_CONTENT                     = 8,
  DXGI_SWAP_CHAIN_FLAG_RESTRICT_SHARED_RESOURCE_DRIVER        = 16,
  DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY                           = 32,
  DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT          = 64,
  DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER                       = 128,
  DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO                       = 256,
  DXGI_SWAP_CHAIN_FLAG_YUV_VIDEO                              = 512,
  DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED                           = 1024,
  DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING                          = 2048,
  DXGI_SWAP_CHAIN_FLAG_RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS = 4096
};
using enum DXGI_SWAP_CHAIN_FLAG;
extern "C++" constexpr auto operator~(DXGI_SWAP_CHAIN_FLAG f) noexcept { return DXGI_SWAP_CHAIN_FLAG(~uint32_t(f)); }
extern "C++" constexpr auto operator|(DXGI_SWAP_CHAIN_FLAG a, DXGI_SWAP_CHAIN_FLAG b) noexcept { return DXGI_SWAP_CHAIN_FLAG(uint32_t(a) | uint32_t(b)); }
extern "C++" constexpr auto operator&(DXGI_SWAP_CHAIN_FLAG a, DXGI_SWAP_CHAIN_FLAG b) noexcept { return DXGI_SWAP_CHAIN_FLAG(uint32_t(a) & uint32_t(b)); }
extern "C++" constexpr auto operator^(DXGI_SWAP_CHAIN_FLAG a, DXGI_SWAP_CHAIN_FLAG b) noexcept { return DXGI_SWAP_CHAIN_FLAG(uint32_t(a) ^ uint32_t(b)); }

enum class DXGI_USAGE {
  DXGI_USAGE_SHADER_INPUT         = 0x00000010UL,
  DXGI_USAGE_RENDER_TARGET_OUTPUT = 0x00000020UL,
  DXGI_USAGE_BACK_BUFFER          = 0x00000040UL,
  DXGI_USAGE_SHARED               = 0x00000080UL,
  DXGI_USAGE_READ_ONLY            = 0x00000100UL,
  DXGI_USAGE_DISCARD_ON_PRESENT   = 0x00000200UL,
  DXGI_USAGE_UNORDERED_ACCESS     = 0x00000400UL
};
using enum DXGI_USAGE;
extern "C++" constexpr auto operator~(DXGI_USAGE u) noexcept { return DXGI_USAGE(~uint32_t(u)); }
extern "C++" constexpr auto operator|(DXGI_USAGE a, DXGI_USAGE b) noexcept { return DXGI_USAGE(uint32_t(a) | uint32_t(b)); }
extern "C++" constexpr auto operator&(DXGI_USAGE a, DXGI_USAGE b) noexcept { return DXGI_USAGE(uint32_t(a) & uint32_t(b)); }
extern "C++" constexpr auto operator^(DXGI_USAGE a, DXGI_USAGE b) noexcept { return DXGI_USAGE(uint32_t(a) ^ uint32_t(b)); }

// MARK: STRUCTS

struct DXGI_FRAME_STATISTICS {
  uint32_t PresentCount;
  uint32_t PresentRefreshCount;
  uint32_t SyncRefreshCount;
  uint64_t SyncQPCTime;
  uint64_t SyncGPUTime;
};

struct DXGI_MAPPED_RECT {
  int32_t Pitch;
  void* pBits;
};

struct DXGI_ADAPTER_DESC {
  wchar_t Description[128];
  uint32_t VendorId;
  uint32_t DeviceId;
  uint32_t SubSysId;
  uint32_t Revision;
  uint64_t DedicatedVideoMemory;
  uint64_t DedicatedSystemMemory;
  uint64_t SharedSystemMemory;
  LUID AdapterLuid;
};

struct DXGI_OUTPUT_DESC {
  wchar_t DeviceName[32];
  RECT DesktopCoordinates;
  BOOL AttachedToDesktop;
  DXGI_MODE_ROTATION Rotation;
  HANDLE Monitor;
};

struct DXGI_SHARED_RESOURCE {
  HANDLE Handle;
};

struct DXGI_SAMPLE_DESC {
  uint32_t Count;
  uint32_t Quality;
};

struct DXGI_SURFACE_DESC {
  uint32_t Width;
  uint32_t Height;
  DXGI_FORMAT Format;
  DXGI_SAMPLE_DESC SampleDesc;
};

struct DXGI_RATIONAL {
  uint32_t Numerator;
  uint32_t Denominator;
};

struct DXGI_MODE_DESC {
  uint32_t Width;
  uint32_t Height;
  DXGI_RATIONAL RefreshRate;
  DXGI_FORMAT Format;
  DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;
  DXGI_MODE_SCALING Scaling;
};

struct DXGI_SWAP_CHAIN_DESC {
  DXGI_MODE_DESC BufferDesc;
  DXGI_SAMPLE_DESC SampleDesc;
  DXGI_USAGE BufferUsage;
  uint32_t BufferCount;
  HANDLE OutputWindow;
  BOOL Windowed;
  DXGI_SWAP_EFFECT SwapEffect;
  uint32_t Flags;
};

cominterface("aec22fb8-76f3-4639-9be0-28eb43a67a2e") IDXGIObject : IUnknown {
  virtual HRESULT __stdcall SetPrivateData(const GUID&, uint32_t, const void*)    = 0;
  virtual HRESULT __stdcall SetPrivateDataInterface(const GUID&, const IUnknown*) = 0;
  virtual HRESULT __stdcall GetPrivateData(const GUID&, uint32_t*, void*)         = 0;
  virtual HRESULT __stdcall GetParent(const GUID&, void**)                        = 0;
};

cominterface("3d3e0379-f9de-4d58-bb6c-18d62992f1a6") IDXGIDeviceSubObject : IDXGIObject {
  virtual HRESULT __stdcall GetDevice(const GUID&, void**) = 0;
};

cominterface("035f3ab4-482e-4e50-b41f-8a7f8bd8960b") IDXGIResource : IDXGIDeviceSubObject {
  virtual HRESULT __stdcall GetSharedHandle(void**)        = 0;
  virtual HRESULT __stdcall GetUsage(DXGI_USAGE*)          = 0;
  virtual HRESULT __stdcall SetEvictionPriority(uint32_t)  = 0;
  virtual HRESULT __stdcall GetEvictionPriority(uint32_t*) = 0;
};

cominterface("9d8e1289-d7b3-465f-8126-250e349af85d") IDXGIKeyedMutex : IDXGIDeviceSubObject {
  virtual HRESULT __stdcall AcquireSync(uint64_t, uint32_t) = 0;
  virtual HRESULT __stdcall ReleaseSync(uint64_t)           = 0;
};

cominterface("cafcb56c-6ac3-4889-bf47-9e23bbd260ec") IDXGISurface : IDXGIDeviceSubObject {
  virtual HRESULT __stdcall GetDesc(DXGI_SURFACE_DESC*)      = 0;
  virtual HRESULT __stdcall Map(DXGI_MAPPED_RECT*, uint32_t) = 0;
  virtual HRESULT __stdcall Unmap()                          = 0;
};

cominterface("4AE63092-6327-4c1b-80AE-BFE12EA32B86") IDXGISurface1 : IDXGISurface {
  virtual HRESULT __stdcall GetDC(BOOL, HANDLE*) = 0;
  virtual HRESULT __stdcall ReleaseDC(RECT*)     = 0;
};

struct DXGI_RGB {
  float r;
  float g;
  float b;
};

struct DXGI_RGBA {
  float r;
  float g;
  float b;
  float a;
};

struct DXGI_GAMMA_CONTROL {
  DXGI_RGB Scale;
  DXGI_RGB Offset;
  DXGI_RGB GammaCurve[1025];
};

struct DXGI_GAMMA_CONTROL_CAPABILITIES {
  BOOL ScaleAndOffsetSupported;
  float MaxConvertedValue;
  float MinConvertedValue;
  uint32_t NumGammaControlPoints;
  float ControlPointPositions[1025];
};

cominterface("ae02eedb-c735-4690-8d52-5a8dc20213aa") IDXGIOutput : IDXGIObject {
  virtual HRESULT __stdcall GetDesc(DXGI_OUTPUT_DESC*)                                                 = 0;
  virtual HRESULT __stdcall GetDisplayModeList(DXGI_FORMAT, uint32_t, uint32_t*, DXGI_MODE_DESC*)      = 0;
  virtual HRESULT __stdcall FindClosestMatchingMode(const DXGI_MODE_DESC*, DXGI_MODE_DESC*, IUnknown*) = 0;
  virtual HRESULT __stdcall WaitForVBlank()                                                            = 0;
  virtual HRESULT __stdcall TakeOwnership(IUnknown*, BOOL)                                             = 0;
  virtual void __stdcall ReleaseOwnership()                                                            = 0;
  virtual HRESULT __stdcall GetGammaControlCapabilities(DXGI_GAMMA_CONTROL_CAPABILITIES*)              = 0;
  virtual HRESULT __stdcall SetGammaControl(const DXGI_GAMMA_CONTROL*)                                 = 0;
  virtual HRESULT __stdcall GetGammaControl(DXGI_GAMMA_CONTROL*)                                       = 0;
  virtual HRESULT __stdcall SetDisplaySurface(IDXGISurface*)                                           = 0;
  virtual HRESULT __stdcall GetDisplaySurfaceData(IDXGISurface*)                                       = 0;
  virtual HRESULT __stdcall GetFrameStatistics(DXGI_FRAME_STATISTICS*)                                 = 0;
};

cominterface("2411e7e1-12ac-4ccf-bd14-9798e8534dc0") IDXGIAdapter : IDXGIObject {
  virtual HRESULT __stdcall EnumOutputs(uint32_t, IDXGIOutput**)         = 0;
  virtual HRESULT __stdcall GetDesc(DXGI_ADAPTER_DESC*)                  = 0;
  virtual HRESULT __stdcall CheckInterfaceSupport(const GUID&, int64_t*) = 0;
};

cominterface("310d36a0-d2e7-4c0a-aa04-6a9d23b8886a") IDXGISwapChain : IDXGIDeviceSubObject {
  virtual HRESULT __stdcall Present(uint32_t, uint32_t)                    = 0;
  virtual HRESULT __stdcall GetBuffer(uint32_t, const GUID&, void**)       = 0;
  virtual HRESULT __stdcall SetFullscreenState(BOOL, IDXGIOutput*)         = 0;
  virtual HRESULT __stdcall GetFullscreenState(BOOL*, IDXGIOutput**)       = 0;
  virtual HRESULT __stdcall GetDesc(DXGI_SWAP_CHAIN_DESC*)                 = 0;
  virtual HRESULT __stdcall ResizeBuffers(int, int, int, DXGI_FORMAT, int) = 0;
  virtual HRESULT __stdcall ResizeTarget(const DXGI_MODE_DESC*)            = 0;
  virtual HRESULT __stdcall GetContainingOutput(IDXGIOutput**)             = 0;
  virtual HRESULT __stdcall GetFrameStatistics(DXGI_FRAME_STATISTICS*)     = 0;
  virtual HRESULT __stdcall GetLastPresentCount(uint32_t*)                 = 0;
};

cominterface("7b7166ec-21c7-44ae-b21a-c9ae321ae369") IDXGIFactory : IDXGIObject {
  virtual HRESULT __stdcall EnumAdapters(uint32_t, IDXGIAdapter**)                              = 0;
  virtual HRESULT __stdcall MakeWindowAssociation(HANDLE, uint32_t)                             = 0;
  virtual HRESULT __stdcall GetWindowAssociation(HANDLE*)                                       = 0;
  virtual HRESULT __stdcall CreateSwapChain(IUnknown*, DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**) = 0;
  virtual HRESULT __stdcall CreateSoftwareAdapter(HANDLE, IDXGIAdapter**)                       = 0;
};

HRESULT __stdcall CreateDXGIFactory1(const GUID&, void**);

cominterface("54ec77fa-1377-44e6-8c32-88fd5f44c84c") IDXGIDevice : IDXGIObject {
  virtual HRESULT __stdcall GetAdapter(IDXGIAdapter**)                                                                                 = 0;
  virtual HRESULT __stdcall CreateSurface(const DXGI_SURFACE_DESC*, uint32_t, DXGI_USAGE, const DXGI_SHARED_RESOURCE*, IDXGISurface**) = 0;
  virtual HRESULT __stdcall QueryResourceResidency(IUnknown* const*, DXGI_RESIDENCY*, uint32_t)                                        = 0;
  virtual HRESULT __stdcall SetGPUThreadPriority(int)                                                                                  = 0;
  virtual HRESULT __stdcall GetGPUThreadPriority(int*)                                                                                 = 0;
};

struct DXGI_ADAPTER_DESC1 {
  wchar_t Description[128];
  uint32_t VendorId;
  uint32_t DeviceId;
  uint32_t SubSysId;
  uint32_t Revision;
  uint64_t DedicatedVideoMemory;
  uint64_t DedicatedSystemMemory;
  uint64_t SharedSystemMemory;
  LUID AdapterLuid;
  uint32_t Flags;
};

struct DXGI_DISPLAY_COLOR_SPACE {
  float PrimaryCoordinates[8][2];
  float WhitePoints[16][2];
};

cominterface("29038f61-3839-4626-91fd-086879011a05") IDXGIAdapter1 : IDXGIAdapter {
  virtual HRESULT __stdcall GetDesc1(DXGI_ADAPTER_DESC1*) = 0;
};

cominterface("77db970f-6276-48ba-ba28-070143b4392c") IDXGIDevice1 : IDXGIDevice {
  virtual HRESULT __stdcall SetMaximumFrameLatency(uint32_t)  = 0;
  virtual HRESULT __stdcall GetMaximumFrameLatency(uint32_t*) = 0;
};

cominterface("770aae78-f26f-4dba-a829-253c83d1b387") IDXGIFactory1 : IDXGIFactory {
  virtual HRESULT __stdcall EnumAdapters1(uint32_t, IDXGIAdapter1**) = 0;
  virtual BOOL __stdcall IsCurrent()                                 = 0;
};

__ywlib_exportcend;
#endif
