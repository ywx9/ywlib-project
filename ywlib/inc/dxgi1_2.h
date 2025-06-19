#pragma once
#include <inc/dxgi.h>
#ifndef __ywlib_import
__ywlib_exportc;

// MARK: ENUMS

enum class DXGI_ALPHA_MODE {
  DXGI_ALPHA_MODE_UNSPECIFIED,
  DXGI_ALPHA_MODE_PREMULTIPLIED,
  DXGI_ALPHA_MODE_STRAIGHT,
  DXGI_ALPHA_MODE_IGNORE,
};
using enum DXGI_ALPHA_MODE;

enum class DXGI_COMPUTE_PREEMPTION_GRANULARITY {
  DXGI_COMPUTE_PREEMPTION_DMA_BUFFER_BOUNDARY,
  DXGI_COMPUTE_PREEMPTION_DISPATCH_BOUNDARY,
  DXGI_COMPUTE_PREEMPTION_THREAD_GROUP_BOUNDARY,
  DXGI_COMPUTE_PREEMPTION_THREAD_BOUNDARY,
  DXGI_COMPUTE_PREEMPTION_INSTRUCTION_BOUNDARY,
};
using enum DXGI_COMPUTE_PREEMPTION_GRANULARITY;

enum class DXGI_GRAPHICS_PREEMPTION_GRANULARITY {
  DXGI_GRAPHICS_PREEMPTION_DMA_BUFFER_BOUNDARY,
  DXGI_GRAPHICS_PREEMPTION_PRIMITIVE_BOUNDARY,
  DXGI_GRAPHICS_PREEMPTION_TRIANGLE_BOUNDARY,
  DXGI_GRAPHICS_PREEMPTION_PIXEL_BOUNDARY,
  DXGI_GRAPHICS_PREEMPTION_INSTRUCTION_BOUNDARY,
};
using enum DXGI_GRAPHICS_PREEMPTION_GRANULARITY;

enum class DXGI_OFFER_RESOURCE_PRIORITY {
  DXGI_OFFER_RESOURCE_PRIORITY_LOW,
  DXGI_OFFER_RESOURCE_PRIORITY_NORMAL,
  DXGI_OFFER_RESOURCE_PRIORITY_HIGH,
};
using enum DXGI_OFFER_RESOURCE_PRIORITY;

enum class DXGI_OUTDUPL_POINTER_SHAPE_TYPE {
  DXGI_OUTDUPL_POINTER_SHAPE_TYPE_MONOCHROME   = 0x1,
  DXGI_OUTDUPL_POINTER_SHAPE_TYPE_COLOR        = 0x2,
  DXGI_OUTDUPL_POINTER_SHAPE_TYPE_MASKED_COLOR = 0x4
};
using enum DXGI_OUTDUPL_POINTER_SHAPE_TYPE;
constexpr auto operator~(DXGI_OUTDUPL_POINTER_SHAPE_TYPE a) { return DXGI_OUTDUPL_POINTER_SHAPE_TYPE(~static_cast<int>(a)); }
constexpr auto operator|(DXGI_OUTDUPL_POINTER_SHAPE_TYPE a, DXGI_OUTDUPL_POINTER_SHAPE_TYPE b) { return DXGI_OUTDUPL_POINTER_SHAPE_TYPE(static_cast<int>(a) | static_cast<int>(b)); }
constexpr auto operator&(DXGI_OUTDUPL_POINTER_SHAPE_TYPE a, DXGI_OUTDUPL_POINTER_SHAPE_TYPE b) { return DXGI_OUTDUPL_POINTER_SHAPE_TYPE(static_cast<int>(a) & static_cast<int>(b)); }
constexpr auto operator^(DXGI_OUTDUPL_POINTER_SHAPE_TYPE a, DXGI_OUTDUPL_POINTER_SHAPE_TYPE b) { return DXGI_OUTDUPL_POINTER_SHAPE_TYPE(static_cast<int>(a) ^ static_cast<int>(b)); }

// MARK: STRUCTS

cominterface("05008617-fbfd-4051-a790-144884b4f6a9") IDXGIDevice2 : IDXGIDevice1 {
  virtual HRESULT __stdcall OfferResources(uint32_t, IDXGIResource* const*, DXGI_OFFER_RESOURCE_PRIORITY) = 0;
  virtual HRESULT __stdcall ReclaimResources(uint32_t, IDXGIResource* const*, BOOL*)                      = 0;
  virtual HRESULT __stdcall EnqueueSetEvent(void*)                                                        = 0;
};

cominterface("ea9dbf1a-c88e-4486-854a-98aa0138f30c") IDXGIDisplayControl : IUnknown {
  virtual BOOL __stdcall IsStereoEnabled()      = 0;
  virtual void __stdcall SetStereoEnabled(BOOL) = 0;
};

cominterface("aba496dd-b617-4cb8-a866-bc44d7eb1fa2") IDXGISurface2 : IDXGISurface1 {
  virtual HRESULT __stdcall GetResource(const GUID&, void**, uint32_t*) = 0;
};

struct SECURITY_ATTRIBUTES {
  uint32_t nLength;
  void* lpSecurityDescriptor;
  BOOL bInheritHandle;
};

cominterface("30961379-4609-4a41-998e-54fe567ee0c1") IDXGIResource1 : IDXGIResource {
  virtual HRESULT __stdcall CreateSubresourceSurface(uint32_t, IDXGISurface2**)                              = 0;
  virtual HRESULT __stdcall CreateSharedHandle(const SECURITY_ATTRIBUTES*, uint32_t, const wchar_t*, void**) = 0;
};

struct DXGI_OUTDUPL_MOVE_RECT {
  POINT SourcePoint;
  RECT DestinationRect;
};

struct DXGI_OUTDUPL_DESC {
  DXGI_MODE_DESC ModeDesc;
  DXGI_MODE_ROTATION Rotation;
  BOOL DesktopImageInSystemMemory;
};

struct DXGI_OUTDUPL_POINTER_POSITION {
  POINT Position;
  BOOL Visible;
};

struct DXGI_OUTDUPL_FRAME_INFO {
  int64_t LastPresentTime;
  int64_t LastMouseUpdateTime;
  uint32_t AccumulatedFrames;
  BOOL RectsCoalesced;
  BOOL ProtectedContentMaskedOut;
  DXGI_OUTDUPL_POINTER_POSITION PointerPosition;
  uint32_t TotalMetadataBufferSize;
  uint32_t PointerShapeBufferSize;
};

struct DXGI_OUTDUPL_POINTER_SHAPE_INFO {
  uint32_t Type;
  uint32_t Width;
  uint32_t Height;
  uint32_t Pitch;
  POINT HotSpot;
};

cominterface("191cfac3-a341-470d-b26e-a864f428319c") IDXGIOutputDuplication : IDXGIObject {
  virtual void __stdcall GetDesc(DXGI_OUTDUPL_DESC*)                                                           = 0;
  virtual HRESULT __stdcall AcquireNextFrame(uint32_t, DXGI_OUTDUPL_FRAME_INFO*, IDXGIResource**)              = 0;
  virtual HRESULT __stdcall GetFrameDirtyRects(uint32_t, RECT*, uint32_t*)                                     = 0;
  virtual HRESULT __stdcall GetFrameMoveRects(uint32_t, DXGI_OUTDUPL_MOVE_RECT*, uint32_t*)                    = 0;
  virtual HRESULT __stdcall GetFramePointerShape(uint32_t, void*, uint32_t*, DXGI_OUTDUPL_POINTER_SHAPE_INFO*) = 0;
  virtual HRESULT __stdcall MapDesktopSurface(DXGI_MAPPED_RECT*)                                               = 0;
  virtual HRESULT __stdcall UnMapDesktopSurface()                                                              = 0;
  virtual HRESULT __stdcall ReleaseFrame()                                                                     = 0;
};

typedef struct DXGI_MODE_DESC1 {
  uint32_t Width;
  uint32_t Height;
  DXGI_RATIONAL RefreshRate;
  DXGI_FORMAT Format;
  DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;
  DXGI_MODE_SCALING Scaling;
  BOOL Stereo;
} DXGI_MODE_DESC1;

typedef enum DXGI_SCALING {
  DXGI_SCALING_STRETCH              = 0,
  DXGI_SCALING_NONE                 = 1,
  DXGI_SCALING_ASPECT_RATIO_STRETCH = 2
} DXGI_SCALING;

typedef struct DXGI_SWAP_CHAIN_DESC1 {
  uint32_t Width;
  uint32_t Height;
  DXGI_FORMAT Format;
  BOOL Stereo;
  DXGI_SAMPLE_DESC SampleDesc;
  DXGI_USAGE BufferUsage;
  uint32_t BufferCount;
  DXGI_SCALING Scaling;
  DXGI_SWAP_EFFECT SwapEffect;
  DXGI_ALPHA_MODE AlphaMode;
  DXGI_SWAP_CHAIN_FLAG Flags;
} DXGI_SWAP_CHAIN_DESC1;

typedef struct DXGI_SWAP_CHAIN_FULLSCREEN_DESC {
  DXGI_RATIONAL RefreshRate;
  DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;
  DXGI_MODE_SCALING Scaling;
  BOOL Windowed;
} DXGI_SWAP_CHAIN_FULLSCREEN_DESC;

typedef struct DXGI_PRESENT_PARAMETERS {
  uint32_t DirtyRectsCount;
  RECT* pDirtyRects;
  RECT* pScrollRect;
  POINT* pScrollOffset;
} DXGI_PRESENT_PARAMETERS;

cominterface("790a45f7-0d42-4876-983a-0a55cfe6f4aa") IDXGISwapChain1 : IDXGISwapChain {
  virtual HRESULT __stdcall GetDesc1(DXGI_SWAP_CHAIN_DESC1*)                             = 0;
  virtual HRESULT __stdcall GetFullscreenDesc(DXGI_SWAP_CHAIN_FULLSCREEN_DESC*)          = 0;
  virtual HRESULT __stdcall GetHwnd(HANDLE*)                                            = 0;
  virtual HRESULT __stdcall GetCoreWindow(const GUID&, void**)                           = 0;
  virtual HRESULT __stdcall Present1(uint32_t, uint32_t, const DXGI_PRESENT_PARAMETERS*) = 0;
  virtual BOOL __stdcall IsTemporaryMonoSupported()                                      = 0;
  virtual HRESULT __stdcall GetRestrictToOutput(IDXGIOutput**)                           = 0;
  virtual HRESULT __stdcall SetBackgroundColor(const DXGI_RGBA*)                         = 0;
  virtual HRESULT __stdcall GetBackgroundColor(DXGI_RGBA*)                               = 0;
  virtual HRESULT __stdcall SetRotation(DXGI_MODE_ROTATION)                              = 0;
  virtual HRESULT __stdcall GetRotation(DXGI_MODE_ROTATION*)                             = 0;
};

cominterface("50c83a1c-e072-4c48-87b0-3630fa36a6d0") IDXGIFactory2 : IDXGIFactory1 {
  virtual BOOL __stdcall IsWindowedStereoEnabled()                                                                                                                            = 0;
  virtual HRESULT __stdcall CreateSwapChainForHwnd(IUnknown*, HANDLE, const DXGI_SWAP_CHAIN_DESC1*, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC*, IDXGIOutput*, IDXGISwapChain1**) = 0;
  virtual HRESULT __stdcall CreateSwapChainForCoreWindow(IUnknown*, IUnknown*, const DXGI_SWAP_CHAIN_DESC1*, IDXGIOutput*, IDXGISwapChain1**)                                 = 0;
  virtual HRESULT __stdcall GetSharedResourceAdapterLuid(void*, LUID*)                                                                                                        = 0;
  virtual HRESULT __stdcall RegisterStereoStatusWindow(HANDLE, uint32_t, uint32_t*)                                                                                          = 0;
  virtual HRESULT __stdcall RegisterStereoStatusEvent(void*, uint32_t*)                                                                                                       = 0;
  virtual void __stdcall UnregisterStereoStatus(uint32_t)                                                                                                                     = 0;
  virtual HRESULT __stdcall RegisterOcclusionStatusWindow(HANDLE, uint32_t, uint32_t*)                                                                                       = 0;
  virtual HRESULT __stdcall RegisterOcclusionStatusEvent(void*, uint32_t*)                                                                                                    = 0;
  virtual void __stdcall UnregisterOcclusionStatus(uint32_t)                                                                                                                  = 0;
  virtual HRESULT __stdcall CreateSwapChainForComposition(IUnknown*, const DXGI_SWAP_CHAIN_DESC1*, IDXGIOutput*, IDXGISwapChain1**)                                           = 0;
};

struct DXGI_ADAPTER_DESC2 {
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
  DXGI_GRAPHICS_PREEMPTION_GRANULARITY GraphicsPreemptionGranularity;
  DXGI_COMPUTE_PREEMPTION_GRANULARITY ComputePreemptionGranularity;
};

cominterface("0AA1AE0A-FA0E-4B84-8644-E05FF8E5ACB5") IDXGIAdapter2 : IDXGIAdapter1 {
  virtual HRESULT __stdcall GetDesc2(DXGI_ADAPTER_DESC2*) = 0;
};

cominterface("00cddea8-939b-4b83-a340-a685226666cc") IDXGIOutput1 : IDXGIOutput {
  virtual HRESULT __stdcall GetDisplayModeList1(DXGI_FORMAT, uint32_t, uint32_t*, DXGI_MODE_DESC1*)       = 0;
  virtual HRESULT __stdcall FindClosestMatchingMode1(const DXGI_MODE_DESC1*, DXGI_MODE_DESC1*, IUnknown*) = 0;
  virtual HRESULT __stdcall GetDisplaySurfaceData1(IDXGIResource*)                                        = 0;
  virtual HRESULT __stdcall DuplicateOutput(IUnknown*, IDXGIOutputDuplication**)                          = 0;
};

__ywlib_exportcend;
#endif
