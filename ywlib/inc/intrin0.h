#pragma once
#include <inc/vcruntime.h>

extern "C" {

int64_t _InterlockedCompareExchange64(volatile int64_t*, int64_t, int64_t);
char _InterlockedExchange8(volatile char*, char);
int64_t _InterlockedExchange64(volatile int64_t*, int64_t);
long _InterlockedExchangeAdd(volatile long*, long);
int64_t _InterlockedExchangeAdd64(volatile int64_t*, int64_t);
long _InterlockedOr(volatile long*, long);

uint8_t _addcarry_u64(uint8_t, uint64_t, uint64_t, uint64_t*);
uint8_t _subborrow_u64(uint8_t, uint64_t, uint64_t, uint64_t*);
uint32_t _tzcnt_u32(uint32_t);
uint64_t _udiv128(uint64_t, uint64_t, uint64_t, uint64_t*);

char __iso_volatile_load8(const volatile char*);
int64_t __iso_volatile_load64(const volatile int64_t*);
void __iso_volatile_store64(volatile int64_t*, int64_t);
uint32_t __lzcnt(uint32_t);
uint64_t __lzcnt64(uint64_t);
uint64_t __shiftleft128(uint64_t, uint64_t, uint8_t);
uint64_t __shiftright128(uint64_t, uint64_t, uint8_t);
}
