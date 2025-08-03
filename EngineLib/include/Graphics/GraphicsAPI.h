#pragma once

#include "../Platform/WindowAPI.h"

EXTERN_C_BEGIN

typedef struct _GfxHandle* GfxHandle;

typedef struct _GfxInitProps
{
    WndHandle wndHandle;
} GfxInitProps;

EXTERN_C_END