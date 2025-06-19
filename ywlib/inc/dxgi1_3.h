#pragma once
#include <inc/dxgi1_2.h>

#ifndef __ywlib_import
__ywlib_exportc;

HRESULT __stdcall CreateDXGIFactory2(int Flags, const GUID& riid, void** ppFactory);

__ywlib_exportcend;
#endif
