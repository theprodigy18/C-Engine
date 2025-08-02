#pragma once

#include "WindowAPI.h"

EXTERN_C_BEGIN

bool Platform_CreateWindow(WndHandle* pHandle, const WndInitProps* pInitProps);

void Platform_DestroyWindow(WndHandle* pHandle);

bool Platform_PollEvents();

void Platform_ShowWindow(WndHandle handle);
void Platform_HideWindow(WndHandle handle);

void Platform_SwapBuffers(WndHandle handle);

EXTERN_C_END
