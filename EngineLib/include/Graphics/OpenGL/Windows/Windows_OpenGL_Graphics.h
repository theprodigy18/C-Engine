#pragma once

#include "Graphics/Graphics.h"

#include <opengl/glcorearb.h>
#include <opengl/glext.h>
#include <opengl/wglext.h>

#include <gl/GL.h>


typedef struct _GfxHandle
{
    HDC   hdc;
    HGLRC context;
} _GfxHandle;
