#pragma once
#include <inc/smmintrin.h>

#ifndef __ywlib_import
__ywlib_exportc;

extern __m128i _mm_cmpistrm(__m128i, __m128i, const int);
extern int _mm_cmpistri(__m128i, __m128i, const int);

extern __m128i _mm_cmpestrm(__m128i, int, __m128i, int, const int);
extern int _mm_cmpestri(__m128i, int, __m128i, int, const int);

extern int _mm_cmpistrz(__m128i, __m128i, const int);
extern int _mm_cmpistrc(__m128i, __m128i, const int);
extern int _mm_cmpistrs(__m128i, __m128i, const int);
extern int _mm_cmpistro(__m128i, __m128i, const int);
extern int _mm_cmpistra(__m128i, __m128i, const int);

extern int _mm_cmpestrz(__m128i, int, __m128i, int, const int);
extern int _mm_cmpestrc(__m128i, int, __m128i, int, const int);
extern int _mm_cmpestrs(__m128i, int, __m128i, int, const int);
extern int _mm_cmpestro(__m128i, int, __m128i, int, const int);
extern int _mm_cmpestra(__m128i, int, __m128i, int, const int);

extern __m128i _mm_cmpgt_epi64(__m128i, __m128i);

extern int _mm_popcnt_u32(unsigned int);
extern __int64 _mm_popcnt_u64(unsigned __int64);

extern unsigned int _mm_crc32_u8(unsigned int, unsigned char);
extern unsigned int _mm_crc32_u16(unsigned int, unsigned short);
extern unsigned int _mm_crc32_u32(unsigned int, unsigned int);
extern unsigned __int64 _mm_crc32_u64(unsigned __int64, unsigned __int64);

__ywlib_exportcend;
#endif
