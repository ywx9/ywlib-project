#pragma once
#include <inc/xmmintrin.h>

#ifndef __ywlib_import
extern "C" {

union __declspec(intrin_type) alignas(16) __m128i {
  int8_t m128i_i8[16];
  int16_t m128i_i16[8];
  int32_t m128i_i32[4];
  int64_t m128i_i64[2];
  uint8_t m128i_u8[16];
  uint16_t m128i_u16[8];
  uint32_t m128i_u32[4];
  uint64_t m128i_u64[2];
};

struct __declspec(intrin_type) alignas(16) __m128d {
  double m128d_f64[2];
};

__m128d _mm_add_sd(__m128d A, __m128d B);
__m128d _mm_add_pd(__m128d A, __m128d B);
__m128d _mm_sub_sd(__m128d A, __m128d B);
__m128d _mm_sub_pd(__m128d A, __m128d B);
__m128d _mm_mul_sd(__m128d A, __m128d B);
__m128d _mm_mul_pd(__m128d A, __m128d B);
__m128d _mm_sqrt_sd(__m128d A, __m128d B);
__m128d _mm_sqrt_pd(__m128d A);
__m128d _mm_div_sd(__m128d A, __m128d B);
__m128d _mm_div_pd(__m128d A, __m128d B);
__m128d _mm_min_sd(__m128d A, __m128d B);
__m128d _mm_min_pd(__m128d A, __m128d B);
__m128d _mm_max_sd(__m128d A, __m128d B);
__m128d _mm_max_pd(__m128d A, __m128d B);

__m128d _mm_and_pd(__m128d A, __m128d B);
__m128d _mm_andnot_pd(__m128d A, __m128d B);
__m128d _mm_or_pd(__m128d A, __m128d B);
__m128d _mm_xor_pd(__m128d A, __m128d B);

__m128d _mm_cmpeq_sd(__m128d A, __m128d B);
__m128d _mm_cmpeq_pd(__m128d A, __m128d B);
__m128d _mm_cmplt_sd(__m128d A, __m128d B);
__m128d _mm_cmplt_pd(__m128d A, __m128d B);
__m128d _mm_cmple_sd(__m128d A, __m128d B);
__m128d _mm_cmple_pd(__m128d A, __m128d B);
__m128d _mm_cmpgt_sd(__m128d A, __m128d B);
__m128d _mm_cmpgt_pd(__m128d A, __m128d B);
__m128d _mm_cmpge_sd(__m128d A, __m128d B);
__m128d _mm_cmpge_pd(__m128d A, __m128d B);
__m128d _mm_cmpneq_sd(__m128d A, __m128d B);
__m128d _mm_cmpneq_pd(__m128d A, __m128d B);
__m128d _mm_cmpnlt_sd(__m128d A, __m128d B);
__m128d _mm_cmpnlt_pd(__m128d A, __m128d B);
__m128d _mm_cmpnle_sd(__m128d A, __m128d B);
__m128d _mm_cmpnle_pd(__m128d A, __m128d B);
__m128d _mm_cmpngt_sd(__m128d A, __m128d B);
__m128d _mm_cmpngt_pd(__m128d A, __m128d B);
__m128d _mm_cmpnge_sd(__m128d A, __m128d B);
__m128d _mm_cmpnge_pd(__m128d A, __m128d B);
__m128d _mm_cmpord_pd(__m128d A, __m128d B);
__m128d _mm_cmpord_sd(__m128d A, __m128d B);
__m128d _mm_cmpunord_pd(__m128d A, __m128d B);
__m128d _mm_cmpunord_sd(__m128d A, __m128d B);

int _mm_comieq_sd(__m128d A, __m128d B);
int _mm_comilt_sd(__m128d A, __m128d B);
int _mm_comile_sd(__m128d A, __m128d B);
int _mm_comigt_sd(__m128d A, __m128d B);
int _mm_comige_sd(__m128d A, __m128d B);
int _mm_comineq_sd(__m128d A, __m128d B);
int _mm_ucomieq_sd(__m128d A, __m128d B);
int _mm_ucomilt_sd(__m128d A, __m128d B);
int _mm_ucomile_sd(__m128d A, __m128d B);
int _mm_ucomigt_sd(__m128d A, __m128d B);
int _mm_ucomige_sd(__m128d A, __m128d B);
int _mm_ucomineq_sd(__m128d A, __m128d B);

__m128d _mm_cvtepi32_pd(__m128i A);
__m128i _mm_cvtpd_epi32(__m128d A);
__m128i _mm_cvttpd_epi32(__m128d A);
__m128 _mm_cvtepi32_ps(__m128i A);
__m128i _mm_cvtps_epi32(__m128 A);
__m128i _mm_cvttps_epi32(__m128 A);
__m128 _mm_cvtpd_ps(__m128d A);
__m128d _mm_cvtps_pd(__m128 A);
__m128 _mm_cvtsd_ss(__m128 A, __m128d B);
__m128d _mm_cvtss_sd(__m128d A, __m128 B);

int _mm_cvtsd_si32(__m128d A);
int _mm_cvttsd_si32(__m128d A);
__m128d _mm_cvtsi32_sd(__m128d A, int B);

__m128d _mm_unpackhi_pd(__m128d A, __m128d B);
__m128d _mm_unpacklo_pd(__m128d A, __m128d B);
int _mm_movemask_pd(__m128d A);
__m128d _mm_shuffle_pd(__m128d A, __m128d B, int _I);

__m128d _mm_load_pd(double const* _Dp);
__m128d _mm_load1_pd(double const* _Dp);
__m128d _mm_loadr_pd(double const* _Dp);
__m128d _mm_loadu_pd(double const* _Dp);
__m128d _mm_load_sd(double const* _Dp);
__m128d _mm_loadh_pd(__m128d A, double const* _Dp);
__m128d _mm_loadl_pd(__m128d A, double const* _Dp);

__m128d _mm_set_sd(double _W);
__m128d _mm_set1_pd(double A);
__m128d _mm_set_pd(double _Z, double _Y);
__m128d _mm_setr_pd(double _Y, double _Z);
__m128d _mm_setzero_pd(void);
__m128d _mm_move_sd(__m128d A, __m128d B);

void _mm_store_sd(double* _Dp, __m128d A);
void _mm_store1_pd(double* _Dp, __m128d A);
void _mm_store_pd(double* _Dp, __m128d A);
void _mm_storeu_pd(double* _Dp, __m128d A);
void _mm_storer_pd(double* _Dp, __m128d A);
void _mm_storeh_pd(double* _Dp, __m128d A);
void _mm_storel_pd(double* _Dp, __m128d A);

#define _mm_set_pd1(a) _mm_set1_pd(a)
#define _mm_load_pd1(p) _mm_load1_pd(p)
#define _mm_store_pd1(p, a) _mm_store1_pd((p), (a))

__m128i _mm_add_epi8(__m128i A, __m128i B);
__m128i _mm_add_epi16(__m128i A, __m128i B);
__m128i _mm_add_epi32(__m128i A, __m128i B);
__m128i _mm_add_epi64(__m128i A, __m128i B);
__m128i _mm_adds_epi8(__m128i A, __m128i B);
__m128i _mm_adds_epi16(__m128i A, __m128i B);
__m128i _mm_adds_epu8(__m128i A, __m128i B);
__m128i _mm_adds_epu16(__m128i A, __m128i B);
__m128i _mm_avg_epu8(__m128i A, __m128i B);
__m128i _mm_avg_epu16(__m128i A, __m128i B);
__m128i _mm_madd_epi16(__m128i A, __m128i B);
__m128i _mm_max_epi16(__m128i A, __m128i B);
__m128i _mm_max_epu8(__m128i A, __m128i B);
__m128i _mm_min_epi16(__m128i A, __m128i B);
__m128i _mm_min_epu8(__m128i A, __m128i B);
__m128i _mm_mulhi_epi16(__m128i A, __m128i B);
__m128i _mm_mulhi_epu16(__m128i A, __m128i B);
__m128i _mm_mullo_epi16(__m128i A, __m128i B);
__m128i _mm_mul_epu32(__m128i A, __m128i B);
__m128i _mm_sad_epu8(__m128i A, __m128i B);
__m128i _mm_sub_epi8(__m128i A, __m128i B);
__m128i _mm_sub_epi16(__m128i A, __m128i B);
__m128i _mm_sub_epi32(__m128i A, __m128i B);
__m128i _mm_sub_epi64(__m128i A, __m128i B);
__m128i _mm_subs_epi8(__m128i A, __m128i B);
__m128i _mm_subs_epi16(__m128i A, __m128i B);
__m128i _mm_subs_epu8(__m128i A, __m128i B);
__m128i _mm_subs_epu16(__m128i A, __m128i B);

__m128i _mm_and_si128(__m128i A, __m128i B);
__m128i _mm_andnot_si128(__m128i A, __m128i B);
__m128i _mm_or_si128(__m128i A, __m128i B);
__m128i _mm_xor_si128(__m128i A, __m128i B);

__m128i _mm_slli_si128(__m128i A, int _Imm);
#define _mm_bslli_si128 _mm_slli_si128
__m128i _mm_slli_epi16(__m128i A, int _Count);
__m128i _mm_sll_epi16(__m128i A, __m128i _Count);
__m128i _mm_slli_epi32(__m128i A, int _Count);
__m128i _mm_sll_epi32(__m128i A, __m128i _Count);
__m128i _mm_slli_epi64(__m128i A, int _Count);
__m128i _mm_sll_epi64(__m128i A, __m128i _Count);
__m128i _mm_srai_epi16(__m128i A, int _Count);
__m128i _mm_sra_epi16(__m128i A, __m128i _Count);
__m128i _mm_srai_epi32(__m128i A, int _Count);
__m128i _mm_sra_epi32(__m128i A, __m128i _Count);
__m128i _mm_srli_si128(__m128i A, int _Imm);
#define _mm_bsrli_si128 _mm_srli_si128
__m128i _mm_srli_epi16(__m128i A, int _Count);
__m128i _mm_srl_epi16(__m128i A, __m128i _Count);
__m128i _mm_srli_epi32(__m128i A, int _Count);
__m128i _mm_srl_epi32(__m128i A, __m128i _Count);
__m128i _mm_srli_epi64(__m128i A, int _Count);
__m128i _mm_srl_epi64(__m128i A, __m128i _Count);

__m128i _mm_cmpeq_epi8(__m128i A, __m128i B);
__m128i _mm_cmpeq_epi16(__m128i A, __m128i B);
__m128i _mm_cmpeq_epi32(__m128i A, __m128i B);
__m128i _mm_cmpgt_epi8(__m128i A, __m128i B);
__m128i _mm_cmpgt_epi16(__m128i A, __m128i B);
__m128i _mm_cmpgt_epi32(__m128i A, __m128i B);
__m128i _mm_cmplt_epi8(__m128i A, __m128i B);
__m128i _mm_cmplt_epi16(__m128i A, __m128i B);
__m128i _mm_cmplt_epi32(__m128i A, __m128i B);

__m128i _mm_cvtsi32_si128(int A);
int _mm_cvtsi128_si32(__m128i A);

__m128i _mm_packs_epi16(__m128i A, __m128i B);
__m128i _mm_packs_epi32(__m128i A, __m128i B);
__m128i _mm_packus_epi16(__m128i A, __m128i B);
int _mm_extract_epi16(__m128i A, int _Imm);
__m128i _mm_insert_epi16(__m128i A, int B, int _Imm);
int _mm_movemask_epi8(__m128i A);
__m128i _mm_shuffle_epi32(__m128i A, int _Imm);
__m128i _mm_shufflehi_epi16(__m128i A, int _Imm);
__m128i _mm_shufflelo_epi16(__m128i A, int _Imm);
__m128i _mm_unpackhi_epi8(__m128i A, __m128i B);
__m128i _mm_unpackhi_epi16(__m128i A, __m128i B);
__m128i _mm_unpackhi_epi32(__m128i A, __m128i B);
__m128i _mm_unpackhi_epi64(__m128i A, __m128i B);
__m128i _mm_unpacklo_epi8(__m128i A, __m128i B);
__m128i _mm_unpacklo_epi16(__m128i A, __m128i B);
__m128i _mm_unpacklo_epi32(__m128i A, __m128i B);
__m128i _mm_unpacklo_epi64(__m128i A, __m128i B);

__m128i _mm_load_si128(__m128i const* _P);
__m128i _mm_loadu_si128(__m128i const* _P);
__m128i _mm_loadl_epi64(__m128i const* _P);

__m128i _mm_set_epi64x(int64_t _I1, int64_t _I0);
__m128i _mm_set_epi32(int _I3, int _I2, int _I1, int _I0);
__m128i _mm_set_epi16(short _W7, short _W6, short _W5, short _W4, short _W3, short _W2, short _W1, short _W0);
__m128i _mm_set_epi8(char B15, char B14, char B13, char B12, char B11, char B10, char B9, char B8, char B7, char B6, char B5, char B4, char B3, char B2, char B1, char B0);
__m128i _mm_set1_epi64x(int64_t i);
__m128i _mm_set1_epi32(int _I);
__m128i _mm_set1_epi16(short _W);
__m128i _mm_set1_epi8(char B);
__m128i _mm_setl_epi64(__m128i _Q);
__m128i _mm_setr_epi32(int _I0, int _I1, int _I2, int _I3);
__m128i _mm_setr_epi16(short _W0, short _W1, short _W2, short _W3, short _W4, short _W5, short _W6, short _W7);
__m128i _mm_setr_epi8(char B15, char B14, char B13, char B12, char B11, char B10, char B9, char B8, char B7, char B6, char B5, char B4, char B3, char B2, char B1, char B0);
__m128i _mm_setzero_si128(void);

void _mm_store_si128(__m128i* _P, __m128i B);
void _mm_storeu_si128(__m128i* _P, __m128i B);
void _mm_storel_epi64(__m128i* _P, __m128i _Q);
void _mm_maskmoveu_si128(__m128i _D, __m128i _N, char* _P);

__m128i _mm_move_epi64(__m128i _Q);

void _mm_stream_pd(double* _Dp, __m128d A);
void _mm_stream_si128(__m128i* _P, __m128i A);
void _mm_clflush(void const* _P);
void _mm_lfence(void);
void _mm_mfence(void);
void _mm_stream_si32(int* _P, int _I);
void _mm_pause(void);

double _mm_cvtsd_f64(__m128d A);

__m128 _mm_castpd_ps(__m128d);
__m128i _mm_castpd_si128(__m128d);
__m128d _mm_castps_pd(__m128);
__m128i _mm_castps_si128(__m128);
__m128 _mm_castsi128_ps(__m128i);
__m128d _mm_castsi128_pd(__m128i);

int64_t _mm_cvtsd_si64(__m128d);
int64_t _mm_cvttsd_si64(__m128d);
__m128d _mm_cvtsi64_sd(__m128d, int64_t);
__m128i _mm_cvtsi64_si128(int64_t);
int64_t _mm_cvtsi128_si64(__m128i);
}
#endif
