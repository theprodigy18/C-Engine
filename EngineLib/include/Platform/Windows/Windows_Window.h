#pragma once

#include "Platform/Window.h"

#define WIN32_LEAN_AND_MEAN
#define NO_MIN_MAX
#include <Windows.h>

typedef struct _WndHandle
{
    HWND hwnd;
    HDC  hdc;
} _WndHandle;