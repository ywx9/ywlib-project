#pragma once
#include <inc/pmmintrin.h>

#ifndef __ywlib_import
__ywlib_exportc;

extern __m128i _mm_hadd_epi16(__m128i, __m128i);
extern __m128i _mm_hadd_epi32(__m128i, __m128i);
extern __m128i _mm_hadds_epi16(__m128i, __m128i);

extern __m128i _mm_hsub_epi16(__m128i, __m128i);
extern __m128i _mm_hsub_epi32(__m128i, __m128i);
extern __m128i _mm_hsubs_epi16(__m128i, __m128i);

extern __m128i _mm_maddubs_epi16(__m128i, __m128i);

extern __m128i _mm_mulhrs_epi16(__m128i, __m128i);

extern __m128i _mm_shuffle_epi8(__m128i, __m128i);

extern __m128i _mm_sign_epi8(__m128i, __m128i);
extern __m128i _mm_sign_epi16(__m128i, __m128i);
extern __m128i _mm_sign_epi32(__m128i, __m128i);

extern __m128i _mm_alignr_epi8(__m128i, __m128i, int);

extern __m128i _mm_abs_epi8(__m128i);
extern __m128i _mm_abs_epi16(__m128i);
extern __m128i _mm_abs_epi32(__m128i);

__ywlib_exportcend;
#endif
