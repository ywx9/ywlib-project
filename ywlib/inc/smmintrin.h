#pragma once
#include <inc/tmmintrin.h>

#define _mm_ceil_pd(val) _mm_round_pd((val), 2)
#define _mm_ceil_sd(dst, val) _mm_round_sd((dst), (val), 2)

#define _mm_floor_pd(val) _mm_round_pd((val), 1)
#define _mm_floor_sd(dst, val) _mm_round_sd((dst), (val), 1)

#define _mm_ceil_ps(val) _mm_round_ps((val), 2)
#define _mm_ceil_ss(dst, val) _mm_round_ss((dst), (val), 2)

#define _mm_floor_ps(val) _mm_round_ps((val), 1)
#define _mm_floor_ss(dst, val) _mm_round_ss((dst), (val), 1)

#define _mm_test_all_zeros(mask, val) _mm_testz_si128((mask), (val))
#define _mm_test_all_ones(val) _mm_testc_si128((val), _mm_cmpeq_epi32((val), (val)))
#define _mm_test_mix_ones_zeros(mask, val) _mm_testnzc_si128((mask), (val))

#ifndef __ywlib_import
__ywlib_exportc;

extern __m128 _mm_blend_ps(__m128, __m128, const int);
extern __m128d _mm_blend_pd(__m128d, __m128d, const int);
extern __m128i _mm_blend_epi16(__m128i, __m128i, const int);

extern __m128 _mm_blendv_ps(__m128, __m128, __m128);
extern __m128d _mm_blendv_pd(__m128d, __m128d, __m128d);
extern __m128i _mm_blendv_epi8(__m128i, __m128i, __m128i mask);

extern __m128 _mm_dp_ps(__m128, __m128, const int);
extern __m128d _mm_dp_pd(__m128d, __m128d, const int);

extern __m128i _mm_cmpeq_epi64(__m128i, __m128i);

extern __m128i _mm_min_epi8(__m128i, __m128i);
extern __m128i _mm_min_epu16(__m128i, __m128i);
extern __m128i _mm_min_epi32(__m128i, __m128i);
extern __m128i _mm_min_epu32(__m128i, __m128i);

extern __m128i _mm_max_epi8(__m128i, __m128i);
extern __m128i _mm_max_epu16(__m128i, __m128i);
extern __m128i _mm_max_epi32(__m128i, __m128i);
extern __m128i _mm_max_epu32(__m128i, __m128i);

extern __m128i _mm_mullo_epi32(__m128i, __m128i);

extern __m128i _mm_mul_epi32(__m128i, __m128i);

extern int _mm_testz_si128(__m128i, __m128i);
extern int _mm_testc_si128(__m128i, __m128i);
extern int _mm_testnzc_si128(__m128i, __m128i);

extern __m128 _mm_insert_ps(__m128, __m128, const int);
extern __m128i _mm_insert_epi8(__m128i, int, const int);
extern __m128i _mm_insert_epi32(__m128i, int, const int);
extern __m128i _mm_insert_epi64(__m128i, __int64, const int);

extern int _mm_extract_ps(__m128, const int);
extern int _mm_extract_epi8(__m128i, const int);
extern int _mm_extract_epi32(__m128i, const int);
extern __int64 _mm_extract_epi64(__m128i, const int);

extern __m128i _mm_minpos_epu16(__m128i);

extern __m128d _mm_round_pd(__m128d, int );
extern __m128d _mm_round_sd(__m128d, __m128d, int );
extern __m128 _mm_round_ps(__m128, int );
extern __m128 _mm_round_ss(__m128, __m128, int );

extern __m128i _mm_cvtepi8_epi32(__m128i);
extern __m128i _mm_cvtepi16_epi32(__m128i);
extern __m128i _mm_cvtepi8_epi64(__m128i);
extern __m128i _mm_cvtepi32_epi64(__m128i);
extern __m128i _mm_cvtepi16_epi64(__m128i);
extern __m128i _mm_cvtepi8_epi16(__m128i);

extern __m128i _mm_cvtepu8_epi32(__m128i);
extern __m128i _mm_cvtepu16_epi32(__m128i);
extern __m128i _mm_cvtepu8_epi64(__m128i);
extern __m128i _mm_cvtepu32_epi64(__m128i);
extern __m128i _mm_cvtepu16_epi64(__m128i);
extern __m128i _mm_cvtepu8_epi16(__m128i);

extern __m128i _mm_packus_epi32(__m128i, __m128i);
extern __m128i _mm_mpsadbw_epu8(__m128i , __m128i , const int);

extern __m128i _mm_stream_load_si128(const __m128i*);

__ywlib_exportcend;
#endif;
