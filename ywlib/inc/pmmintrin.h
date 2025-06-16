#pragma once
#include <inc/emmintrin.h>

#ifndef __ywlib_import
__ywlib_exportc;

extern __m128 _mm_addsub_ps(__m128, __m128);
extern __m128 _mm_hadd_ps(__m128, __m128);
extern __m128 _mm_hsub_ps(__m128, __m128);
extern __m128 _mm_movehdup_ps(__m128);
extern __m128 _mm_moveldup_ps(__m128);

extern __m128d _mm_addsub_pd(__m128d, __m128d);
extern __m128d _mm_hadd_pd(__m128d, __m128d);
extern __m128d _mm_hsub_pd(__m128d, __m128d);
extern __m128d _mm_loaddup_pd(const double*);
extern __m128d _mm_movedup_pd(__m128d);

extern __m128i _mm_lddqu_si128(const __m128i*);

extern void _mm_monitor(const void*, unsigned, unsigned);
extern void _mm_mwait(unsigned, unsigned);

__ywlib_exportcend;
#endif
