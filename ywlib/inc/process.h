#pragma once
#include <inc/vcruntime.h>

#ifndef __ywlib_import
extern "C" {
uintptr_t __cdecl _beginthreadex(void*, uint32_t, uint32_t(__stdcall*)(void*), void*, uint32_t, uint32_t*);
}
namespace std {
using ::_beginthreadex;
}
#endif
