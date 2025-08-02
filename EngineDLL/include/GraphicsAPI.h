#pragma once

#include "common.h"

EXTERN_C_BEGIN

DLL_API bool API_CreateGraphics(GfxHandle* pHandle, const GfxInitProps* pInitProps);
DLL_API void API_DestroyGraphics(GfxHandle* pHandle);
DLL_API void API_SetCurrentGraphics(GfxHandle handle);
DLL_API void API_ClearColor(f32 r, f32 g, f32 b, f32 a);

EXTERN_C_END