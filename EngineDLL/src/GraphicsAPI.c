#include "GraphicsAPI.h"

#include <Graphics/Graphics.h>

bool API_CreateGraphics(GfxHandle* pHandle, const GfxInitProps* pInitProps)
{
    return Graphics_CreateGraphics(pHandle, pInitProps);
}

void API_DestroyGraphics(GfxHandle* pHandle)
{
    Graphics_DestroyGraphics(pHandle);
}

void API_SetCurrentGraphics(GfxHandle handle)
{
    Graphics_SetCurrentGraphics(handle);
}

void API_ClearColor(f32 r, f32 g, f32 b, f32 a)
{
    Graphics_ClearColor(r, g, b, a);
}

void API_SwapBuffers(GfxHandle handle)
{
    Graphics_SwapBuffers(handle);
}
