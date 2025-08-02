#pragma once

#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
#define EXTERN_C_BEGIN \
    extern "C"         \
    {
#define EXTERN_C_END }
#else
#define EXTERN_C_BEGIN
#define EXTERN_C_END
#endif // __cplusplus

#ifdef DEBUG
#ifdef _MSC_VER
#define DBG_BREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
#define DBG_BREAK() __builtin_trap()
#else
#define DBG_BREAK() (*(volatile int*) 0 = 0)
#endif // _MSC_VER
#else
#define DBG_BREAK()
#endif // DEBUG

#ifdef DEBUG
#define ASSERT(x) if (!(x)) DBG_BREAK();
#else
#define ASSERT(x)
#endif // DEBUG


typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef signed char      i8;
typedef signed short     i16;
typedef signed int       i32;
typedef signed long long i64;

typedef float  f32;
typedef double f64;


#define ALLOCATE(type, size) (type)malloc(size)
#define FREE(ptr) free(ptr)
