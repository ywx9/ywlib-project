#pragma once
#include <inc/vcruntime.h>

#ifndef __ywlib_import
export extern "C" union __declspec(intrin_type) alignas(8) __m64 {
  uint64_t m64_u64;
  float m64_f32[2];
  int8_t m64_i8[8];
  int16_t m64_i16[4];
  int32_t m64_i32[2];
  int64_t m64_i64;
  uint8_t m64_u8[8];
  uint16_t m64_u16[4];
  uint32_t m64_u32[2];
};
#endif
