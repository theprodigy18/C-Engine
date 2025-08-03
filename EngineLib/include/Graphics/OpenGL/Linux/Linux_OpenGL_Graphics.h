#pragma once

#include "Graphics/Graphics.h"

#include <EGL/eglplatform.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <GL/gl.h>

typedef struct _GfxHandle
{
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
} _GfxHandle;
