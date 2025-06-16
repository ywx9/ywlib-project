#pragma once
#include <inc/nmmintrin.h>

#ifndef __ywlib_import
__ywlib_exportc;

extern __m128i _mm_aesdec_si128(__m128i, __m128i);
extern __m128i _mm_aesdeclast_si128(__m128i, __m128i);
extern __m128i _mm_aesenc_si128(__m128i, __m128i);
extern __m128i _mm_aesenclast_si128(__m128i, __m128i);
extern __m128i _mm_aesimc_si128(__m128i);
extern __m128i _mm_aeskeygenassist_si128(__m128i, const int);
extern __m128i _mm_clmulepi64_si128(__m128i, __m128i, const int);

__ywlib_exportcend;
#endif
