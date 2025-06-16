#pragma once
#include <inc/dxgi.h>

#ifndef __ywlib_import
__ywlib_exportc;

// elder definitions than D3D11

enum class D3D_DRIVER_TYPE {
  D3D_DRIVER_TYPE_UNKNOWN,
  D3D_DRIVER_TYPE_HARDWARE,
  D3D_DRIVER_TYPE_REFERENCE,
  D3D_DRIVER_TYPE_NULL,
  D3D_DRIVER_TYPE_SOFTWARE,
  D3D_DRIVER_TYPE_WARP,
};
using enum D3D_DRIVER_TYPE;

enum class D3D_FEATURE_LEVEL {
  D3D_FEATURE_LEVEL_1_0_CORE = 0x1000,
  D3D_FEATURE_LEVEL_9_1 = 0x9100,
  D3D_FEATURE_LEVEL_9_2 = 0x9200,
  D3D_FEATURE_LEVEL_9_3 = 0x9300,
  D3D_FEATURE_LEVEL_10_0 = 0xa000,
  D3D_FEATURE_LEVEL_10_1 = 0xa100,
  D3D_FEATURE_LEVEL_11_0 = 0xb000,
  D3D_FEATURE_LEVEL_11_1 = 0xb100,
  D3D_FEATURE_LEVEL_12_0 = 0xc000,
  D3D_FEATURE_LEVEL_12_1 = 0xc100,
  D3D_FEATURE_LEVEL_12_2 = 0xc200
};
using enum D3D_FEATURE_LEVEL;

cominterface("8BA5FB08-5195-40e2-AC58-0D989C3A0102") ID3D10Blob : IUnknown {
  virtual void* __stdcall GetBufferPointer() = 0;
  virtual size_t __stdcall GetBufferSize() = 0;
};

HRESULT __stdcall D3DCompile(const void*, size_t, const char*, const void*, void*, const char*, const char*, unsigned, unsigned, ID3D10Blob**, ID3D10Blob**);

// enums (d3d11)

enum class D3D11_DEPTH_WRITE_MASK {
  D3D11_DEPTH_WRITE_MASK_ZERO,
  D3D11_DEPTH_WRITE_MASK_ALL,
};
using enum D3D11_DEPTH_WRITE_MASK;

enum class D3D11_COMPARISON_FUNC {
  D3D11_COMPARISON_NEVER = 1,
  D3D11_COMPARISON_LESS = 2,
  D3D11_COMPARISON_EQUAL = 3,
  D3D11_COMPARISON_LESS_EQUAL = 4,
  D3D11_COMPARISON_GREATER = 5,
  D3D11_COMPARISON_NOT_EQUAL = 6,
  D3D11_COMPARISON_GREATER_EQUAL = 7,
  D3D11_COMPARISON_ALWAYS = 8
};
using enum D3D11_COMPARISON_FUNC;

enum class D3D11_STENCIL_OP {
  D3D11_STENCIL_OP_KEEP = 1,
  D3D11_STENCIL_OP_ZERO = 2,
  D3D11_STENCIL_OP_REPLACE = 3,
  D3D11_STENCIL_OP_INCR_SAT = 4,
  D3D11_STENCIL_OP_DECR_SAT = 5,
  D3D11_STENCIL_OP_INVERT = 6,
  D3D11_STENCIL_OP_INCR = 7,
  D3D11_STENCIL_OP_DECR = 8
};
using enum D3D11_STENCIL_OP;

enum class D3D11_BIND_FLAG {
  D3D11_BIND_VERTEX_BUFFER = 0x1L,
  D3D11_BIND_INDEX_BUFFER = 0x2L,
  D3D11_BIND_CONSTANT_BUFFER = 0x4L,
  D3D11_BIND_SHADER_RESOURCE = 0x8L,
  D3D11_BIND_STREAM_OUTPUT = 0x10L,
  D3D11_BIND_RENDER_TARGET = 0x20L,
  D3D11_BIND_DEPTH_STENCIL = 0x40L,
  D3D11_BIND_UNORDERED_ACCESS = 0x80L,
  D3D11_BIND_DECODER = 0x200L,
  D3D11_BIND_VIDEO_ENCODER = 0x400L
};
using enum D3D11_BIND_FLAG;
extern "C++" constexpr auto operator~(D3D11_BIND_FLAG a) noexcept { return D3D11_BIND_FLAG(~static_cast<int>(a)); }
extern "C++" constexpr auto operator|(D3D11_BIND_FLAG a, D3D11_BIND_FLAG b) noexcept { return D3D11_BIND_FLAG(static_cast<int>(a) | static_cast<int>(b)); }
extern "C++" constexpr auto operator&(D3D11_BIND_FLAG a, D3D11_BIND_FLAG b) noexcept { return D3D11_BIND_FLAG(static_cast<int>(a) & static_cast<int>(b)); }
extern "C++" constexpr auto operator^(D3D11_BIND_FLAG a, D3D11_BIND_FLAG b) noexcept { return D3D11_BIND_FLAG(static_cast<int>(a) ^ static_cast<int>(b)); }

enum class D3D11_BLEND {
  D3D11_BLEND_ZERO = 1,
  D3D11_BLEND_ONE = 2,
  D3D11_BLEND_SRC_COLOR = 3,
  D3D11_BLEND_INV_SRC_COLOR = 4,
  D3D11_BLEND_SRC_ALPHA = 5,
  D3D11_BLEND_INV_SRC_ALPHA = 6,
  D3D11_BLEND_DEST_ALPHA = 7,
  D3D11_BLEND_INV_DEST_ALPHA = 8,
  D3D11_BLEND_DEST_COLOR = 9,
  D3D11_BLEND_INV_DEST_COLOR = 10,
  D3D11_BLEND_SRC_ALPHA_SAT = 11,
  D3D11_BLEND_BLEND_FACTOR = 14,
  D3D11_BLEND_INV_BLEND_FACTOR = 15,
  D3D11_BLEND_SRC1_COLOR = 16,
  D3D11_BLEND_INV_SRC1_COLOR = 17,
  D3D11_BLEND_SRC1_ALPHA = 18,
  D3D11_BLEND_INV_SRC1_ALPHA = 19
};
using enum D3D11_BLEND;

enum class D3D11_BLEND_OP {
  D3D11_BLEND_OP_ADD = 1,
  D3D11_BLEND_OP_SUBTRACT = 2,
  D3D11_BLEND_OP_REV_SUBTRACT = 3,
  D3D11_BLEND_OP_MIN = 4,
  D3D11_BLEND_OP_MAX = 5
};
using enum D3D11_BLEND_OP;

enum class D3D11_CPU_ACCESS_FLAG {
  D3D11_CPU_ACCESS_WRITE = 0x10000,
  D3D11_CPU_ACCESS_READ = 0x20000,
};
using enum D3D11_CPU_ACCESS_FLAG;

enum class D3D11_CULL_MODE {
  D3D11_CULL_NONE = 1,
  D3D11_CULL_FRONT = 2,
  D3D11_CULL_BACK = 3
};
using enum D3D11_CULL_MODE;

enum class D3D11_FEATURE {
  D3D11_FEATURE_THREADING,
  D3D11_FEATURE_DOUBLES,
  D3D11_FEATURE_FORMAT_SUPPORT,
  D3D11_FEATURE_FORMAT_SUPPORT2,
  D3D11_FEATURE_D3D10_X_HARDWARE_OPTIONS,
  D3D11_FEATURE_D3D11_OPTIONS,
  D3D11_FEATURE_ARCHITECTURE_INFO,
  D3D11_FEATURE_D3D9_OPTIONS,
  D3D11_FEATURE_SHADER_MIN_PRECISION_SUPPORT,
  D3D11_FEATURE_D3D9_SHADOW_SUPPORT,
  D3D11_FEATURE_D3D11_OPTIONS1,
  D3D11_FEATURE_D3D9_SIMPLE_INSTANCING_SUPPORT,
  D3D11_FEATURE_MARKER_SUPPORT,
  D3D11_FEATURE_D3D9_OPTIONS1,
  D3D11_FEATURE_D3D11_OPTIONS2,
  D3D11_FEATURE_D3D11_OPTIONS3,
  D3D11_FEATURE_GPU_VIRTUAL_ADDRESS_SUPPORT,
  D3D11_FEATURE_D3D11_OPTIONS4,
  D3D11_FEATURE_SHADER_CACHE,
  D3D11_FEATURE_D3D11_OPTIONS5,
  D3D11_FEATURE_DISPLAYABLE,
};
using enum D3D11_FEATURE;

enum class D3D11_FILL_MODE {
  D3D11_FILL_WIREFRAME = 2,
  D3D11_FILL_SOLID = 3
};
using enum D3D11_FILL_MODE;

enum class D3D11_FILTER {
  D3D11_FILTER_MIN_MAG_MIP_POINT = 0,
  D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR = 0x1,
  D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x4,
  D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR = 0x5,
  D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT = 0x10,
  D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x11,
  D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT = 0x14,
  D3D11_FILTER_MIN_MAG_MIP_LINEAR = 0x15,
  D3D11_FILTER_ANISOTROPIC = 0x55,
  D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT = 0x80,
  D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR = 0x81,
  D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x84,
  D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR = 0x85,
  D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT = 0x90,
  D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x91,
  D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT = 0x94,
  D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR = 0x95,
  D3D11_FILTER_COMPARISON_ANISOTROPIC = 0xd5,
  D3D11_FILTER_MINIMUM_MIN_MAG_MIP_POINT = 0x100,
  D3D11_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR = 0x101,
  D3D11_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x104,
  D3D11_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR = 0x105,
  D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT = 0x110,
  D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x111,
  D3D11_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT = 0x114,
  D3D11_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR = 0x115,
  D3D11_FILTER_MINIMUM_ANISOTROPIC = 0x155,
  D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT = 0x180,
  D3D11_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR = 0x181,
  D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x184,
  D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR = 0x185,
  D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT = 0x190,
  D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x191,
  D3D11_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT = 0x194,
  D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR = 0x195,
  D3D11_FILTER_MAXIMUM_ANISOTROPIC = 0x1d5
};
using enum D3D11_FILTER;

enum class D3D11_RESOURCE_DIMENSION {
  D3D11_RESOURCE_DIMENSION_UNKNOWN,
  D3D11_RESOURCE_DIMENSION_BUFFER,
  D3D11_RESOURCE_DIMENSION_TEXTURE1D,
  D3D11_RESOURCE_DIMENSION_TEXTURE2D,
  D3D11_RESOURCE_DIMENSION_TEXTURE3D,
};
using enum D3D11_RESOURCE_DIMENSION;

enum class D3D11_RESOURCE_MISC_FLAG {
  D3D11_RESOURCE_MISC_GENERATE_MIPS = 0x1,
  D3D11_RESOURCE_MISC_SHARED = 0x2,
  D3D11_RESOURCE_MISC_TEXTURECUBE = 0x4,
  D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS = 0x10,
  D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS = 0x20,
  D3D11_RESOURCE_MISC_BUFFER_STRUCTURED = 0x40,
  D3D11_RESOURCE_MISC_RESOURCE_CLAMP = 0x80,
  D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX = 0x100,
  D3D11_RESOURCE_MISC_GDI_COMPATIBLE = 0x200,
  D3D11_RESOURCE_MISC_SHARED_NTHANDLE = 0x800,
  D3D11_RESOURCE_MISC_RESTRICTED_CONTENT = 0x1000,
  D3D11_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE = 0x2000,
  D3D11_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE_DRIVER = 0x4000,
  D3D11_RESOURCE_MISC_GUARDED = 0x8000,
  D3D11_RESOURCE_MISC_TILE_POOL = 0x20000,
  D3D11_RESOURCE_MISC_TILED = 0x40000,
  D3D11_RESOURCE_MISC_HW_PROTECTED = 0x80000,
  D3D11_RESOURCE_MISC_SHARED_DISPLAYABLE = 0x100000,
  D3D11_RESOURCE_MISC_SHARED_EXCLUSIVE_WRITER = 0x200000,
};
using enum D3D11_RESOURCE_MISC_FLAG;
extern "C++" constexpr auto operator~(D3D11_RESOURCE_MISC_FLAG a) noexcept { return D3D11_RESOURCE_MISC_FLAG(~static_cast<int>(a)); }
extern "C++" constexpr auto operator|(D3D11_RESOURCE_MISC_FLAG a, D3D11_RESOURCE_MISC_FLAG b) noexcept { return D3D11_RESOURCE_MISC_FLAG(static_cast<int>(a) | static_cast<int>(b)); }
extern "C++" constexpr auto operator&(D3D11_RESOURCE_MISC_FLAG a, D3D11_RESOURCE_MISC_FLAG b) noexcept { return D3D11_RESOURCE_MISC_FLAG(static_cast<int>(a) & static_cast<int>(b)); }
extern "C++" constexpr auto operator^(D3D11_RESOURCE_MISC_FLAG a, D3D11_RESOURCE_MISC_FLAG b) noexcept { return D3D11_RESOURCE_MISC_FLAG(static_cast<int>(a) ^ static_cast<int>(b)); }

enum class D3D11_USAGE {
  D3D11_USAGE_DEFAULT,
  D3D11_USAGE_IMMUTABLE,
  D3D11_USAGE_DYNAMIC,
  D3D11_USAGE_STAGING,
};
using enum D3D11_USAGE;

enum class D3D11_SRV_DIMENSION {
  D3D11_SRV_DIMENSION_UNKNOWN,
  D3D11_SRV_DIMENSION_BUFFER,
  D3D11_SRV_DIMENSION_TEXTURE1D,
  D3D11_SRV_DIMENSION_TEXTURE1DARRAY,
  D3D11_SRV_DIMENSION_TEXTURE2D,
  D3D11_SRV_DIMENSION_TEXTURE2DARRAY,
  D3D11_SRV_DIMENSION_TEXTURE2DMS,
  D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY,
  D3D11_SRV_DIMENSION_TEXTURE3D,
  D3D11_SRV_DIMENSION_TEXTURECUBE,
  D3D11_SRV_DIMENSION_TEXTURECUBEARRAY,
  D3D11_SRV_DIMENSION_BUFFEREX,
};
using enum D3D11_SRV_DIMENSION;

enum class D3D11_RTV_DIMENSION {
  D3D11_RTV_DIMENSION_UNKNOWN,
  D3D11_RTV_DIMENSION_BUFFER,
  D3D11_RTV_DIMENSION_TEXTURE1D,
  D3D11_RTV_DIMENSION_TEXTURE1DARRAY,
  D3D11_RTV_DIMENSION_TEXTURE2D,
  D3D11_RTV_DIMENSION_TEXTURE2DARRAY,
  D3D11_RTV_DIMENSION_TEXTURE2DMS,
  D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY,
  D3D11_RTV_DIMENSION_TEXTURE3D,
};
using enum D3D11_RTV_DIMENSION;

enum class D3D11_DSV_DIMENSION {
  D3D11_DSV_DIMENSION_UNKNOWN,
  D3D11_DSV_DIMENSION_TEXTURE1D,
  D3D11_DSV_DIMENSION_TEXTURE1DARRAY,
  D3D11_DSV_DIMENSION_TEXTURE2D,
  D3D11_DSV_DIMENSION_TEXTURE2DARRAY,
  D3D11_DSV_DIMENSION_TEXTURE2DMS,
  D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY,
};
using enum D3D11_DSV_DIMENSION;

enum class D3D11_UAV_DIMENSION {
  D3D11_UAV_DIMENSION_UNKNOWN = 0,
  D3D11_UAV_DIMENSION_BUFFER = 1,
  D3D11_UAV_DIMENSION_TEXTURE1D = 2,
  D3D11_UAV_DIMENSION_TEXTURE1DARRAY = 3,
  D3D11_UAV_DIMENSION_TEXTURE2D = 4,
  D3D11_UAV_DIMENSION_TEXTURE2DARRAY = 5,
  D3D11_UAV_DIMENSION_TEXTURE3D = 8
};
using enum D3D11_UAV_DIMENSION;

enum class D3D11_TEXTURE_ADDRESS_MODE {
  D3D11_TEXTURE_ADDRESS_WRAP = 1,
  D3D11_TEXTURE_ADDRESS_MIRROR = 2,
  D3D11_TEXTURE_ADDRESS_CLAMP = 3,
  D3D11_TEXTURE_ADDRESS_BORDER = 4,
  D3D11_TEXTURE_ADDRESS_MIRROR_ONCE = 5
};
using enum D3D11_TEXTURE_ADDRESS_MODE;

enum class D3D11_MAP {
  D3D11_MAP_READ = 1,
  D3D11_MAP_WRITE = 2,
  D3D11_MAP_READ_WRITE = 3,
  D3D11_MAP_WRITE_DISCARD = 4,
  D3D11_MAP_WRITE_NO_OVERWRITE = 5
};
using enum D3D11_MAP;

enum D3D11_PRIMITIVE_TOPOLOGY {
  D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED = 0,
  D3D11_PRIMITIVE_TOPOLOGY_POINTLIST = 1,
  D3D11_PRIMITIVE_TOPOLOGY_LINELIST = 2,
  D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP = 3,
  D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST = 4,
  D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP = 5,
  D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ = 10,
  D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ = 11,
  D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ = 12,
  D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ = 13,
};
using enum D3D11_PRIMITIVE_TOPOLOGY;

enum class D3D11_DEVICE_CONTEXT_TYPE {
  D3D11_DEVICE_CONTEXT_IMMEDIATE = 0,
  D3D11_DEVICE_CONTEXT_DEFERRED = 1
};
using enum D3D11_DEVICE_CONTEXT_TYPE;

enum class D3D11_INPUT_CLASSIFICATION {
  D3D11_INPUT_PER_VERTEX_DATA = 0,
  D3D11_INPUT_PER_INSTANCE_DATA = 1
};
using enum D3D11_INPUT_CLASSIFICATION;

cominterface("db6f6ddb-ac77-4e88-8253-819df9bbf140") ID3D11Device;
cominterface("1841e5c8-16b0-489b-bcc8-44cfb0d5deae") ID3D11DeviceChild : IUnknown {
  virtual void __stdcall GetDevice(ID3D11Device**) = 0;
  virtual HRESULT __stdcall GetPrivateData(const GUID&, int*, void*) = 0;
  virtual HRESULT __stdcall SetPrivateData(const GUID&, int, const void*) = 0;
  virtual HRESULT __stdcall SetPrivateDataInterface(const GUID&, const IUnknown*) = 0;
};

struct D3D11_DEPTH_STENCILOP_DESC {
  D3D11_STENCIL_OP StencilFailOp;
  D3D11_STENCIL_OP StencilDepthFailOp;
  D3D11_STENCIL_OP StencilPassOp;
  D3D11_COMPARISON_FUNC StencilFunc;
};

struct D3D11_DEPTH_STENCIL_DESC {
  int DepthEnable;
  D3D11_DEPTH_WRITE_MASK DepthWriteMask;
  D3D11_COMPARISON_FUNC DepthFunc;
  int StencilEnable;
  uint8_t StencilReadMask;
  uint8_t StencilWriteMask;
  D3D11_DEPTH_STENCILOP_DESC FrontFace;
  D3D11_DEPTH_STENCILOP_DESC BackFace;
};

cominterface("03823efb-8d8f-4e1c-9aa2-f64bb2cbfdf1") ID3D11DepthStencilState : ID3D11DeviceChild {
  virtual void __stdcall GetDesc(D3D11_DEPTH_STENCIL_DESC*) = 0;
};

struct D3D11_RENDER_TARGET_BLEND_DESC {
  int BlendEnable;
  D3D11_BLEND SrcBlend, DestBlend;
  D3D11_BLEND_OP BlendOp;
  D3D11_BLEND SrcBlendAlpha, DestBlendAlpha;
  D3D11_BLEND_OP BlendOpAlpha;
  uint8_t RenderTargetWriteMask;
};

struct D3D11_BLEND_DESC {
  int AlphaToCoverageEnable, IndependentBlendEnable;
  D3D11_RENDER_TARGET_BLEND_DESC RenderTarget[8];
};

cominterface("75b68faa-347d-4159-8f45-a0640f01cd9a") ID3D11BlendState : ID3D11DeviceChild {
  virtual void __stdcall GetDesc(D3D11_BLEND_DESC*) = 0;
};

struct D3D11_RASTERIZER_DESC {
  D3D11_FILL_MODE FillMode;
  D3D11_CULL_MODE CullMode;
  int FrontCounterClockwise, DepthBias;
  float DepthBiasClamp, SlopeScaledDepthBias;
  int DepthClipEnable, ScissorEnable, MultisampleEnable, AntialiasedLineEnable;
};

cominterface("9bb4ab81-ab1a-4d8f-b506-fc04200b6ee7") ID3D11RasterizerState : ID3D11DeviceChild {
  virtual void __stdcall GetDesc(D3D11_RASTERIZER_DESC*) = 0;
};

cominterface("dc8e63f3-d12b-4952-b47b-5e45026a862d") ID3D11Resource : ID3D11DeviceChild {
  virtual void __stdcall GetType(D3D11_RESOURCE_DIMENSION*) = 0;
  virtual void __stdcall SetEvictionPriority(int) = 0;
  virtual int __stdcall GetEvictionPriority() = 0;
};

struct D3D11_BUFFER_DESC {
  int ByteWidth;
  D3D11_USAGE Usage;
  D3D11_BIND_FLAG BindFlags;
  D3D11_CPU_ACCESS_FLAG CPUAccessFlags;
  D3D11_RESOURCE_MISC_FLAG MiscFlags;
  int StructureByteStride;
};

cominterface("48570b85-d1ee-4fcd-a250-eb350722b037") ID3D11Buffer : ID3D11Resource {
  virtual void __stdcall GetDesc(D3D11_BUFFER_DESC*) = 0;
};

struct D3D11_TEXTURE1D_DESC {
  int Width, MipLevels, ArraySize;
  DXGI_FORMAT Format;
  D3D11_USAGE Usage;
  int BindFlags, CPUAccessFlags, MiscFlags;
};

cominterface("f8fb5c27-c6b3-4f75-a4c8-439af2ef564c") ID3D11Texture1D : ID3D11Resource {
  virtual void __stdcall GetDesc(D3D11_TEXTURE1D_DESC*) = 0;
};

struct D3D11_TEXTURE2D_DESC {
  int Width, Height, MipLevels, ArraySize;
  DXGI_FORMAT Format;
  DXGI_SAMPLE_DESC SampleDesc;
  D3D11_USAGE Usage;
  D3D11_BIND_FLAG BindFlags;
  D3D11_CPU_ACCESS_FLAG CPUAccessFlags;
  D3D11_RESOURCE_MISC_FLAG MiscFlags;
};

cominterface("6f15aaf2-d208-4e89-9ab4-489535d34f9c") ID3D11Texture2D : ID3D11Resource {
  virtual void __stdcall GetDesc(D3D11_TEXTURE2D_DESC*) = 0;
};

struct D3D11_TEXTURE3D_DESC {
  int Width, Height, Depth, MipLevels;
  DXGI_FORMAT Format;
  D3D11_USAGE Usage;
  int BindFlags, CPUAccessFlags, MiscFlags;
};

cominterface("037e866e-f56d-4357-a8af-9dabbe6e250e") ID3D11Texture3D : ID3D11Resource {
  virtual void __stdcall GetDesc(D3D11_TEXTURE3D_DESC*) = 0;
};

cominterface("839d1216-bb2e-412b-b7f4-a9dbebe08ed1") ID3D11View : ID3D11DeviceChild {
  virtual void __stdcall GetResource(ID3D11Resource**) = 0;
};

struct D3D11_BUFFER_SRV {
  union {
    int FirstElement, ElementOffset;
  };
  union {
    int NumElements, ElementWidth;
  };
};

struct D3D11_TEX1D_SRV {
  int MostDetailedMip, MipLevels;
};

struct D3D11_TEX1D_ARRAY_SRV {
  int MostDetailedMip, MipLevels, FirstArraySlice, ArraySize;
};

struct D3D11_TEX2D_SRV {
  int MostDetailedMip, MipLevels;
};

struct D3D11_TEX2D_ARRAY_SRV {
  int MostDetailedMip, MipLevels, FirstArraySlice, ArraySize;
};

struct D3D11_TEX3D_SRV {
  int MostDetailedMip, MipLevels;
};

struct D3D11_TEXCUBE_SRV {
  int MostDetailedMip, MipLevels;
};

struct D3D11_TEXCUBE_ARRAY_SRV {
  int MostDetailedMip, MipLevels, First2DArrayFace, NumCubes;
};

struct D3D11_TEX2DMS_SRV {
  int UnusedField_NothingToDefine;
};

struct D3D11_TEX2DMS_ARRAY_SRV {
  int FirstArraySlice, ArraySize;
};

struct D3D11_BUFFEREX_SRV {
  int FirstElement, NumElements, Flags;
};

struct D3D11_SHADER_RESOURCE_VIEW_DESC {
  DXGI_FORMAT Format;
  D3D11_SRV_DIMENSION ViewDimension;
  union {
    D3D11_BUFFER_SRV Buffer;
    D3D11_TEX1D_SRV Texture1D;
    D3D11_TEX1D_ARRAY_SRV Texture1DArray;
    D3D11_TEX2D_SRV Texture2D;
    D3D11_TEX2D_ARRAY_SRV Texture2DArray;
    D3D11_TEX2DMS_SRV Texture2DMS;
    D3D11_TEX2DMS_ARRAY_SRV Texture2DMSArray;
    D3D11_TEX3D_SRV Texture3D;
    D3D11_TEXCUBE_SRV TextureCube;
    D3D11_TEXCUBE_ARRAY_SRV TextureCubeArray;
    D3D11_BUFFEREX_SRV BufferEx;
  };
};

cominterface("b0e06fe0-8192-4e1a-b1ca-36d7414710b2") ID3D11ShaderResourceView : ID3D11View {
  virtual void __stdcall GetDesc(D3D11_SHADER_RESOURCE_VIEW_DESC*) = 0;
};

struct D3D11_BUFFER_RTV {
  union {
    int FirstElement, ElementOffset;
  };
  union {
    int NumElements, ElementWidth;
  };
};

struct D3D11_TEX1D_RTV {
  int MipSlice;
};

struct D3D11_TEX1D_ARRAY_RTV {
  int MipSlice, FirstArraySlice, ArraySize;
};

struct D3D11_TEX2D_RTV {
  int MipSlice;
};

struct D3D11_TEX2DMS_RTV {
  int UnusedField_NothingToDefine;
};

struct D3D11_TEX2D_ARRAY_RTV {
  int MipSlice, FirstArraySlice, ArraySize;
};

struct D3D11_TEX2DMS_ARRAY_RTV {
  int FirstArraySlice, ArraySize;
};

struct D3D11_TEX3D_RTV {
  int MipSlice, FirstWSlice, WSize;
};

struct D3D11_RENDER_TARGET_VIEW_DESC {
  DXGI_FORMAT Format;
  D3D11_RTV_DIMENSION ViewDimension;
  union {
    D3D11_BUFFER_RTV Buffer;
    D3D11_TEX1D_RTV Texture1D;
    D3D11_TEX1D_ARRAY_RTV Texture1DArray;
    D3D11_TEX2D_RTV Texture2D;
    D3D11_TEX2D_ARRAY_RTV Texture2DArray;
    D3D11_TEX2DMS_RTV Texture2DMS;
    D3D11_TEX2DMS_ARRAY_RTV Texture2DMSArray;
    D3D11_TEX3D_RTV Texture3D;
  };
};

cominterface("dfdba067-0b8d-4865-875b-d7b4516cc164") ID3D11RenderTargetView : ID3D11View {
  virtual void __stdcall GetDesc(D3D11_RENDER_TARGET_VIEW_DESC*) = 0;
};

struct D3D11_TEX1D_DSV {
  int MipSlice;
};

struct D3D11_TEX1D_ARRAY_DSV {
  int MipSlice, FirstArraySlice, ArraySize;
};

struct D3D11_TEX2D_DSV {
  int MipSlice;
};

struct D3D11_TEX2D_ARRAY_DSV {
  int MipSlice, FirstArraySlice, ArraySize;
};

struct D3D11_TEX2DMS_DSV {
  int UnusedField_NothingToDefine;
};

struct D3D11_TEX2DMS_ARRAY_DSV {
  int FirstArraySlice, ArraySize;
};

struct D3D11_DEPTH_STENCIL_VIEW_DESC {
  DXGI_FORMAT Format;
  D3D11_DSV_DIMENSION ViewDimension;
  int Flags;
  union {
    D3D11_TEX1D_DSV Texture1D;
    D3D11_TEX1D_ARRAY_DSV Texture1DArray;
    D3D11_TEX2D_DSV Texture2D;
    D3D11_TEX2D_ARRAY_DSV Texture2DArray;
    D3D11_TEX2DMS_DSV Texture2DMS;
    D3D11_TEX2DMS_ARRAY_DSV Texture2DMSArray;
  };
};

cominterface("9fdac92a-1876-48c3-afad-25b94f84a9b6") ID3D11DepthStencilView : ID3D11View {
  virtual void __stdcall GetDesc(D3D11_DEPTH_STENCIL_VIEW_DESC*) = 0;
};

struct D3D11_BUFFER_UAV {
  int FirstElement, NumElements, Flags;
};

struct D3D11_TEX1D_UAV {
  int MipSlice;
};

struct D3D11_TEX1D_ARRAY_UAV {
  int MipSlice, FirstArraySlice, ArraySize;
};

struct D3D11_TEX2D_UAV {
  int MipSlice;
};

struct D3D11_TEX2D_ARRAY_UAV {
  int MipSlice, FirstArraySlice, ArraySize;
};

struct D3D11_TEX3D_UAV {
  int MipSlice, FirstWSlice, WSize;
};

struct D3D11_UNORDERED_ACCESS_VIEW_DESC {
  DXGI_FORMAT Format;
  D3D11_UAV_DIMENSION ViewDimension;
  union {
    D3D11_BUFFER_UAV Buffer;
    D3D11_TEX1D_UAV Texture1D;
    D3D11_TEX1D_ARRAY_UAV Texture1DArray;
    D3D11_TEX2D_UAV Texture2D;
    D3D11_TEX2D_ARRAY_UAV Texture2DArray;
    D3D11_TEX3D_UAV Texture3D;
  };
};

cominterface("28acf509-7f5c-48f6-8611-f316010a6380") ID3D11UnorderedAccessView : ID3D11View {
  virtual void __stdcall GetDesc(D3D11_UNORDERED_ACCESS_VIEW_DESC*) = 0;
};

cominterface("3b301d64-d678-4289-8897-22f8928b72f3") ID3D11VertexShader : ID3D11DeviceChild{};
cominterface("8e5c6061-628a-4c8e-8264-bbe45cb3d5dd") ID3D11HullShader : ID3D11DeviceChild{};
cominterface("f582c508-0f36-490c-9977-31eece268cfa") ID3D11DomainShader : ID3D11DeviceChild{};
cominterface("38325b96-effb-4022-ba02-2e795b70275c") ID3D11GeometryShader : ID3D11DeviceChild{};
cominterface("ea82e40d-51dc-4f33-93d4-db7c9125ae8c") ID3D11PixelShader : ID3D11DeviceChild{};
cominterface("4f5b196e-c2bd-495e-bd01-1fded38e4969") ID3D11ComputeShader : ID3D11DeviceChild{};
cominterface("e4819ddc-4cf0-4025-bd26-5de82a3e07b7") ID3D11InputLayout : ID3D11DeviceChild{};

struct D3D11_SAMPLER_DESC {
  D3D11_FILTER Filter;
  D3D11_TEXTURE_ADDRESS_MODE AddressU;
  D3D11_TEXTURE_ADDRESS_MODE AddressV;
  D3D11_TEXTURE_ADDRESS_MODE AddressW;
  float MipLODBias;
  int MaxAnisotropy;
  D3D11_COMPARISON_FUNC ComparisonFunc;
  float BorderColor[4], MinLOD, MaxLOD;
};

cominterface("da6fea51-564c-4487-9810-f0d0f9b4e3a5") ID3D11SamplerState : ID3D11DeviceChild {
  virtual void __stdcall GetDesc(D3D11_SAMPLER_DESC*) = 0;
};

cominterface("4b35d0cd-1e15-4258-9c98-1b1333f6dd3b") ID3D11Asynchronous : ID3D11DeviceChild {
  virtual int __stdcall GetDataSize() = 0;
};

cominterface("d6c00747-87b7-425e-b84d-44d108560afd") ID3D11Query : ID3D11Asynchronous {
  virtual void __stdcall GetDesc(void*) = 0;
};

cominterface("9eb576dd-9f77-4d86-81aa-8bab5fe490e2") ID3D11Predicate : ID3D11Query{};

cominterface("6e8c49fb-a371-4770-b440-29086022b741") ID3D11Counter : ID3D11Asynchronous {
  virtual void __stdcall GetDesc(void*) = 0;
};

cominterface("ddf57cba-9543-46e4-a12b-f207a0fe7fed") ID3D11ClassLinkage;
cominterface("a6cd7faa-b0b7-4a2f-9436-8662a65797cb") ID3D11ClassInstance : ID3D11DeviceChild {
  virtual void __stdcall GetClassLinkage(ID3D11ClassLinkage**) = 0;
  virtual void __stdcall GetDesc(void*) = 0;
  virtual void __stdcall GetInstanceName(char*, size_t*) = 0;
  virtual void __stdcall GetTypeName(char*, size_t*) = 0;
};

cominterface("ddf57cba-9543-46e4-a12b-f207a0fe7fed") ID3D11ClassLinkage : ID3D11DeviceChild {
  virtual HRESULT __stdcall GetClassInstance(const char*, int, ID3D11ClassInstance**) = 0;
  virtual HRESULT __stdcall CreateClassInstance(const char*, int, int, int, int, ID3D11ClassInstance**) = 0;
};

cominterface("a24bc4d1-769e-43f7-8013-98ff566c18e2") ID3D11CommandList : ID3D11DeviceChild {
  virtual int __stdcall GetContextFlags() = 0;
};

struct D3D11_MAPPED_SUBRESOURCE {
  void* pData;
  int RowPitch, DepthPitch;
};

struct D3D11_VIEWPORT {
  float TopLeftX, TopLeftY, Width, Height, MinDepth, MaxDepth;
};

struct D3D11_BOX {
  int left, top, front, right, bottom, back;
};

cominterface("c0bfa96c-e089-44fb-8eaf-26f8796190da") ID3D11DeviceContext : ID3D11DeviceChild {
  virtual void __stdcall VSSetConstantBuffers(int, int, ID3D11Buffer* const*) = 0;
  virtual void __stdcall PSSetShaderResources(int, int, ID3D11ShaderResourceView* const*) = 0;
  virtual void __stdcall PSSetShader(ID3D11PixelShader*, ID3D11ClassInstance* const*, int) = 0;
  virtual void __stdcall PSSetSamplers(int, int, ID3D11SamplerState* const*) = 0;
  virtual void __stdcall VSSetShader(ID3D11VertexShader*, ID3D11ClassInstance* const*, int) = 0;
  virtual void __stdcall DrawIndexed(int, int, int) = 0;
  virtual void __stdcall Draw(int, int) = 0;
  virtual HRESULT __stdcall Map(ID3D11Resource*, int, D3D11_MAP, int, D3D11_MAPPED_SUBRESOURCE*) = 0;
  virtual void __stdcall Unmap(ID3D11Resource*, int) = 0;
  virtual void __stdcall PSSetConstantBuffers(int, int, ID3D11Buffer* const*) = 0;
  virtual void __stdcall IASetInputLayout(ID3D11InputLayout*) = 0;
  virtual void __stdcall IASetVertexBuffers(int, int, ID3D11Buffer* const*, const int*, const int*) = 0;
  virtual void __stdcall IASetIndexBuffer(ID3D11Buffer*, DXGI_FORMAT, int) = 0;
  virtual void __stdcall DrawIndexedInstanced(int, int, int, int, int) = 0;
  virtual void __stdcall DrawInstanced(int, int, int, int) = 0;
  virtual void __stdcall GSSetConstantBuffers(int, int, ID3D11Buffer* const*) = 0;
  virtual void __stdcall GSSetShader(ID3D11GeometryShader*, ID3D11ClassInstance* const*, int) = 0;
  virtual void __stdcall IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY) = 0;
  virtual void __stdcall VSSetShaderResources(int, int, ID3D11ShaderResourceView* const*) = 0;
  virtual void __stdcall VSSetSamplers(int, int, ID3D11SamplerState* const*) = 0;
  virtual void __stdcall Begin(ID3D11Asynchronous*) = 0;
  virtual void __stdcall End(ID3D11Asynchronous*) = 0;
  virtual HRESULT __stdcall GetData(ID3D11Asynchronous*, void*, int, int) = 0;
  virtual void __stdcall SetPredication(ID3D11Predicate*, int) = 0;
  virtual void __stdcall GSSetShaderResources(int, int, ID3D11ShaderResourceView* const*) = 0;
  virtual void __stdcall GSSetSamplers(int, int, ID3D11SamplerState* const*) = 0;
  virtual void __stdcall OMSetRenderTargets(int, ID3D11RenderTargetView* const*, ID3D11DepthStencilView*) = 0;
  virtual void __stdcall OMSetRenderTargetsAndUnorderedAccessViews(int, ID3D11RenderTargetView* const*, ID3D11DepthStencilView*, int, int, ID3D11UnorderedAccessView* const*, const int*) = 0;
  virtual void __stdcall OMSetBlendState(ID3D11BlendState*, const float[4], int) = 0;
  virtual void __stdcall OMSetDepthStencilState(ID3D11DepthStencilState*, int) = 0;
  virtual void __stdcall SOSetTargets(int, ID3D11Buffer* const*, const int*) = 0;
  virtual void __stdcall DrawAuto() = 0;
  virtual void __stdcall DrawIndexedInstancedIndirect(ID3D11Buffer*, int) = 0;
  virtual void __stdcall DrawInstancedIndirect(ID3D11Buffer*, int) = 0;
  virtual void __stdcall Dispatch(int, int, int) = 0;
  virtual void __stdcall DispatchIndirect(ID3D11Buffer*, int) = 0;
  virtual void __stdcall RSSetState(ID3D11RasterizerState*) = 0;
  virtual void __stdcall RSSetViewports(int, const void*) = 0;
  virtual void __stdcall RSSetScissorRects(int, const RECT*) = 0;
  virtual void __stdcall CopySubresourceRegion(ID3D11Resource*, int, int, int, int, ID3D11Resource*, int, const D3D11_BOX*) = 0;
  virtual void __stdcall CopyResource(ID3D11Resource*, ID3D11Resource*) = 0;
  virtual void __stdcall UpdateSubresource(ID3D11Resource*, int, const D3D11_BOX*, const void*, int, int) = 0;
  virtual void __stdcall CopyStructureCount(ID3D11Buffer*, int, ID3D11UnorderedAccessView*) = 0;
  virtual void __stdcall ClearRenderTargetView(ID3D11RenderTargetView*, const float[4]) = 0;
  virtual void __stdcall ClearUnorderedAccessViewUint(ID3D11UnorderedAccessView*, const int[4]) = 0;
  virtual void __stdcall ClearUnorderedAccessViewFloat(ID3D11UnorderedAccessView*, const float[4]) = 0;
  virtual void __stdcall ClearDepthStencilView(ID3D11DepthStencilView*, int, float, int8_t) = 0;
  virtual void __stdcall GenerateMips(ID3D11ShaderResourceView*) = 0;
  virtual void __stdcall SetResourceMinLOD(ID3D11Resource*, float) = 0;
  virtual float __stdcall GetResourceMinLOD(ID3D11Resource*) = 0;
  virtual void __stdcall ResolveSubresource(ID3D11Resource*, int, ID3D11Resource*, int, DXGI_FORMAT) = 0;
  virtual void __stdcall ExecuteCommandList(ID3D11CommandList*, int) = 0;
  virtual void __stdcall HSSetShaderResources(int, int, ID3D11ShaderResourceView* const*) = 0;
  virtual void __stdcall HSSetShader(ID3D11HullShader*, ID3D11ClassInstance* const*, int) = 0;
  virtual void __stdcall HSSetSamplers(int, int, ID3D11SamplerState* const*) = 0;
  virtual void __stdcall HSSetConstantBuffers(int, int, ID3D11Buffer* const*) = 0;
  virtual void __stdcall DSSetShaderResources(int, int, ID3D11ShaderResourceView* const*) = 0;
  virtual void __stdcall DSSetShader(ID3D11DomainShader*, ID3D11ClassInstance* const*, int NumClassInstances) = 0;
  virtual void __stdcall DSSetSamplers(int, int, ID3D11SamplerState* const*) = 0;
  virtual void __stdcall DSSetConstantBuffers(int, int, ID3D11Buffer* const*) = 0;
  virtual void __stdcall CSSetShaderResources(int, int, ID3D11ShaderResourceView* const*) = 0;
  virtual void __stdcall CSSetUnorderedAccessViews(int, int, ID3D11UnorderedAccessView* const*, const int*) = 0;
  virtual void __stdcall CSSetShader(ID3D11ComputeShader*, ID3D11ClassInstance* const*, int) = 0;
  virtual void __stdcall CSSetSamplers(int, int, ID3D11SamplerState* const*) = 0;
  virtual void __stdcall CSSetConstantBuffers(int, int, ID3D11Buffer* const*) = 0;
  virtual void __stdcall VSGetConstantBuffers(int, int, ID3D11Buffer**) = 0;
  virtual void __stdcall PSGetShaderResources(int, int, ID3D11ShaderResourceView**) = 0;
  virtual void __stdcall PSGetShader(ID3D11PixelShader**, ID3D11ClassInstance**, int*) = 0;
  virtual void __stdcall PSGetSamplers(int, int, ID3D11SamplerState**) = 0;
  virtual void __stdcall VSGetShader(ID3D11VertexShader**, ID3D11ClassInstance**, int*) = 0;
  virtual void __stdcall PSGetConstantBuffers(int, int, ID3D11Buffer**) = 0;
  virtual void __stdcall IAGetInputLayout(ID3D11InputLayout**) = 0;
  virtual void __stdcall IAGetVertexBuffers(int, int, ID3D11Buffer**, int*, int*) = 0;
  virtual void __stdcall IAGetIndexBuffer(ID3D11Buffer**, DXGI_FORMAT*, int*) = 0;
  virtual void __stdcall GSGetConstantBuffers(int, int, ID3D11Buffer**) = 0;
  virtual void __stdcall GSGetShader(ID3D11GeometryShader**, ID3D11ClassInstance**, int*) = 0;
  virtual void __stdcall IAGetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY*) = 0;
  virtual void __stdcall VSGetShaderResources(int, int, ID3D11ShaderResourceView**) = 0;
  virtual void __stdcall VSGetSamplers(int, int, ID3D11SamplerState**) = 0;
  virtual void __stdcall GetPredication(ID3D11Predicate**, int*) = 0;
  virtual void __stdcall GSGetShaderResources(int, int, ID3D11ShaderResourceView**) = 0;
  virtual void __stdcall GSGetSamplers(int, int, ID3D11SamplerState**) = 0;
  virtual void __stdcall OMGetRenderTargets(int, ID3D11RenderTargetView**, ID3D11DepthStencilView**) = 0;
  virtual void __stdcall OMGetRenderTargetsAndUnorderedAccessViews(int, ID3D11RenderTargetView**, ID3D11DepthStencilView**, int, int, ID3D11UnorderedAccessView**) = 0;
  virtual void __stdcall OMGetBlendState(ID3D11BlendState**, float[4], int*) = 0;
  virtual void __stdcall OMGetDepthStencilState(ID3D11DepthStencilState**, int*) = 0;
  virtual void __stdcall SOGetTargets(int, ID3D11Buffer**) = 0;
  virtual void __stdcall RSGetState(ID3D11RasterizerState**) = 0;
  virtual void __stdcall RSGetViewports(int*, D3D11_VIEWPORT*) = 0;
  virtual void __stdcall RSGetScissorRects(int*, RECT*) = 0;
  virtual void __stdcall HSGetShaderResources(int, int, ID3D11ShaderResourceView**) = 0;
  virtual void __stdcall HSGetShader(ID3D11HullShader**, ID3D11ClassInstance**, int*) = 0;
  virtual void __stdcall HSGetSamplers(int, int, ID3D11SamplerState**) = 0;
  virtual void __stdcall HSGetConstantBuffers(int, int, ID3D11Buffer**) = 0;
  virtual void __stdcall DSGetShaderResources(int, int, ID3D11ShaderResourceView**) = 0;
  virtual void __stdcall DSGetShader(ID3D11DomainShader**, ID3D11ClassInstance**, int*) = 0;
  virtual void __stdcall DSGetSamplers(int, int, ID3D11SamplerState**) = 0;
  virtual void __stdcall DSGetConstantBuffers(int, int, ID3D11Buffer**) = 0;
  virtual void __stdcall CSGetShaderResources(int, int, ID3D11ShaderResourceView**) = 0;
  virtual void __stdcall CSGetUnorderedAccessViews(int, int, ID3D11UnorderedAccessView**) = 0;
  virtual void __stdcall CSGetShader(ID3D11ComputeShader**, ID3D11ClassInstance**, int*) = 0;
  virtual void __stdcall CSGetSamplers(int, int, ID3D11SamplerState**) = 0;
  virtual void __stdcall CSGetConstantBuffers(int, int, ID3D11Buffer**) = 0;
  virtual void __stdcall ClearState() = 0;
  virtual void __stdcall Flush() = 0;
  virtual D3D11_DEVICE_CONTEXT_TYPE __stdcall GetType() = 0;
  virtual int __stdcall GetContextFlags() = 0;
  virtual HRESULT __stdcall FinishCommandList(int, ID3D11CommandList**) = 0;
};

struct D3D11_SUBRESOURCE_DATA {
  const void* pSysMem;
  int SysMemPitch, SysMemSlicePitch;
};

struct D3D11_INPUT_ELEMENT_DESC {
  const char* SemanticName;
  int SemanticIndex;
  DXGI_FORMAT Format;
  int InputSlot, AlignedByteOffset;
  D3D11_INPUT_CLASSIFICATION InputSlotClass;
  int InstanceDataStepRate;
};

cominterface("db6f6ddb-ac77-4e88-8253-819df9bbf140") ID3D11Device : IUnknown {
  virtual HRESULT __stdcall CreateBuffer(const D3D11_BUFFER_DESC*, const D3D11_SUBRESOURCE_DATA*, ID3D11Buffer**) = 0;
  virtual HRESULT __stdcall CreateTexture1D(const D3D11_TEXTURE1D_DESC*, const D3D11_SUBRESOURCE_DATA*, ID3D11Texture1D**) = 0;
  virtual HRESULT __stdcall CreateTexture2D(const D3D11_TEXTURE2D_DESC*, const D3D11_SUBRESOURCE_DATA*, ID3D11Texture2D**) = 0;
  virtual HRESULT __stdcall CreateTexture3D(const D3D11_TEXTURE3D_DESC*, const D3D11_SUBRESOURCE_DATA*, ID3D11Texture3D**) = 0;
  virtual HRESULT __stdcall CreateShaderResourceView(ID3D11Resource*, const D3D11_SHADER_RESOURCE_VIEW_DESC*, ID3D11ShaderResourceView**) = 0;
  virtual HRESULT __stdcall CreateUnorderedAccessView(ID3D11Resource*, const D3D11_UNORDERED_ACCESS_VIEW_DESC*, ID3D11UnorderedAccessView**) = 0;
  virtual HRESULT __stdcall CreateRenderTargetView(ID3D11Resource*, const D3D11_RENDER_TARGET_VIEW_DESC*, ID3D11RenderTargetView**) = 0;
  virtual HRESULT __stdcall CreateDepthStencilView(ID3D11Resource*, const D3D11_DEPTH_STENCIL_VIEW_DESC*, ID3D11DepthStencilView**) = 0;
  virtual HRESULT __stdcall CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC*, int, const void*, size_t, ID3D11InputLayout**) = 0;
  virtual HRESULT __stdcall CreateVertexShader(const void*, size_t, ID3D11ClassLinkage*, ID3D11VertexShader**) = 0;
  virtual HRESULT __stdcall CreateGeometryShader(const void*, size_t, ID3D11ClassLinkage*, ID3D11GeometryShader**) = 0;
  virtual HRESULT __stdcall CreateGeometryShaderWithStreamOutput(const void*, size_t, const void*, int, const int*, int, int, ID3D11ClassLinkage*, ID3D11GeometryShader**) = 0;
  virtual HRESULT __stdcall CreatePixelShader(const void*, size_t, ID3D11ClassLinkage*, ID3D11PixelShader**) = 0;
  virtual HRESULT __stdcall CreateHullShader(const void*, size_t, ID3D11ClassLinkage*, ID3D11HullShader**) = 0;
  virtual HRESULT __stdcall CreateDomainShader(const void*, size_t, ID3D11ClassLinkage*, ID3D11DomainShader**) = 0;
  virtual HRESULT __stdcall CreateComputeShader(const void*, size_t, ID3D11ClassLinkage*, ID3D11ComputeShader**) = 0;
  virtual HRESULT __stdcall CreateClassLinkage(ID3D11ClassLinkage**) = 0;
  virtual HRESULT __stdcall CreateBlendState(const D3D11_BLEND_DESC*, ID3D11BlendState**) = 0;
  virtual HRESULT __stdcall CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC*, ID3D11DepthStencilState**) = 0;
  virtual HRESULT __stdcall CreateRasterizerState(const D3D11_RASTERIZER_DESC*, ID3D11RasterizerState**) = 0;
  virtual HRESULT __stdcall CreateSamplerState(const D3D11_SAMPLER_DESC*, ID3D11SamplerState**) = 0;
  virtual HRESULT __stdcall CreateQuery(const void*, ID3D11Query**) = 0;
  virtual HRESULT __stdcall CreatePredicate(const void*, ID3D11Predicate**) = 0;
  virtual HRESULT __stdcall CreateCounter(const void*, ID3D11Counter**) = 0;
  virtual HRESULT __stdcall CreateDeferredContext(int, ID3D11DeviceContext**) = 0;
  virtual HRESULT __stdcall OpenSharedResource(void*, const GUID&, void**) = 0;
  virtual HRESULT __stdcall CheckFormatSupport(DXGI_FORMAT, int*) = 0;
  virtual HRESULT __stdcall CheckMultisampleQualityLevels(DXGI_FORMAT, int, int*) = 0;
  virtual void __stdcall CheckCounterInfo(void*) = 0;
  virtual HRESULT __stdcall CheckCounter(const void*, void*, int*, char*, int*, char*, int*, char*, int*) = 0;
  virtual HRESULT __stdcall CheckFeatureSupport(D3D11_FEATURE, void*, int) = 0;
  virtual HRESULT __stdcall GetPrivateData(const GUID&, int*, void*) = 0;
  virtual HRESULT __stdcall SetPrivateData(const GUID&, int, const void*) = 0;
  virtual HRESULT __stdcall SetPrivateDataInterface(const GUID&, const IUnknown*) = 0;
  virtual D3D_FEATURE_LEVEL __stdcall GetFeatureLevel() = 0;
  virtual int __stdcall GetCreationFlags() = 0;
  virtual HRESULT __stdcall GetDeviceRemovedReason() = 0;
  virtual void __stdcall GetImmediateContext(ID3D11DeviceContext**) = 0;
  virtual HRESULT __stdcall SetExceptionMode(int) = 0;
  virtual int __stdcall GetExceptionMode() = 0;
};

HRESULT __stdcall D3D11CreateDevice(IDXGIAdapter*, D3D_DRIVER_TYPE, HANDLE, int, const D3D_FEATURE_LEVEL*, int, int, ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**);

__ywlib_exportcend;
#endif
