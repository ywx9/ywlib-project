#pragma once
#include <inc/vcruntime.h>

extern "C++" {
namespace std { enum class align_val_t : size_t {}; }

namespace std {
struct nothrow_t {
  explicit nothrow_t() = default;
};
extern nothrow_t const nothrow;
}

_NODISCARD __declspec(allocator) void* __cdecl operator new(size_t Size);
_NODISCARD __declspec(allocator) void* __cdecl operator new(size_t Size, ::std::nothrow_t const&) noexcept;
_NODISCARD __declspec(allocator) void* __cdecl operator new[](size_t Size);
_NODISCARD __declspec(allocator) void* __cdecl operator new[](size_t Size, ::std::nothrow_t const&) noexcept;

void __cdecl operator delete(void* _Block) noexcept;
void __cdecl operator delete(void* _Block, ::std::nothrow_t const&) noexcept;
void __cdecl operator delete[](void* _Block) noexcept;
void __cdecl operator delete[](void* _Block, ::std::nothrow_t const&) noexcept;
void __cdecl operator delete(void* _Block, size_t Size) noexcept;
void __cdecl operator delete[](void* _Block, size_t Size) noexcept;

_NODISCARD __declspec(allocator) void* __cdecl operator new(size_t Size, ::std::align_val_t _Al);
_NODISCARD __declspec(allocator) void* __cdecl operator new(size_t Size, ::std::align_val_t _Al, ::std::nothrow_t const&) noexcept;
_NODISCARD __declspec(allocator) void* __cdecl operator new[](size_t Size, ::std::align_val_t _Al);
_NODISCARD __declspec(allocator) void* __cdecl operator new[](size_t Size, ::std::align_val_t _Al, ::std::nothrow_t const&) noexcept;

void __cdecl operator delete(void* _Block, ::std::align_val_t _Al) noexcept;
void __cdecl operator delete(void* _Block, ::std::align_val_t _Al, ::std::nothrow_t const&) noexcept;
void __cdecl operator delete[](void* _Block, ::std::align_val_t _Al) noexcept;
void __cdecl operator delete[](void* _Block, ::std::align_val_t _Al, ::std::nothrow_t const&) noexcept;
void __cdecl operator delete(void* _Block, size_t Size, ::std::align_val_t _Al) noexcept;
void __cdecl operator delete[](void* _Block, size_t Size, ::std::align_val_t _Al) noexcept;

_NODISCARD _MSVC_CONSTEXPR inline void* __cdecl operator new(size_t Size, void* _Where) noexcept {
  (void)Size;
  return _Where;
}
inline void __cdecl operator delete(void*, void*) noexcept { return; }

_NODISCARD inline void* __cdecl operator new[](size_t Size, void* _Where) noexcept {
  (void)Size;
  return _Where;
}
inline void __cdecl operator delete[](void*, void*) noexcept {}
}
