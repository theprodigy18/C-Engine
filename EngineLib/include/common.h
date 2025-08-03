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

#include "log.h"

#ifdef DEBUG
#define ASSERT(x) \
    if (!(x)) DBG_BREAK()
#define ASSERT_MSG(x, ...)      \
    if (!(x))                   \
    {                           \
        LOG_ERROR(__VA_ARGS__); \
        DBG_BREAK();            \
    }
#else
#define ASSERT(x)
#define ASSERT_MSG(x, ...)
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

#define ALLOCATE(T, size) (T) malloc(size)
#define ALLOCATE_SINGLE(T) (T*) malloc(sizeof(T))
#define ALLOCATE_ARRAY(T, count) (T*) malloc(count * sizeof(T))
#define ALLOCATE_SINGLE_ZEROED(T) (T*) calloc(1, sizeof(T))
#define ALLOCATE_ARRAY_ZEROED(T, count) (T*) calloc(count, sizeof(T))
#define ZERO_MEM(ptr) memset(ptr, 0, sizeof(*ptr))
#define ZERO_MEM_ARRAY(ptr, count) memset(ptr, 0, count * sizeof(*ptr))
#define FREE(ptr) free(ptr)
