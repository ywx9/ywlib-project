#pragma once
#include <inc/vcruntime.h>

#ifdef __ywlib_export
#define _calloc_dbg(c, s, ...) calloc(c, s)
#define _malloc_dbg(s, ...) malloc(s)
#endif
