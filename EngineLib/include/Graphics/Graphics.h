#pragma once

#include "GraphicsAPI.h"

EXTERN_C_BEGIN

bool Graphics_CreateGraphics(GfxHandle* pHandle, const GfxInitProps* pInitProps);

void Graphics_SetCurrentGraphics(GfxHandle handle);

void Graphics_ClearColor(f32 r, f32 g, f32 b, f32 a);

void Graphics_DestroyGraphics(GfxHandle* pHandle);

void Graphics_SwapBuffers(GfxHandle handle);

EXTERN_C_END
