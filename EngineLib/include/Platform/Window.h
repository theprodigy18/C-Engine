#pragma once

#include "WindowAPI.h"

EXTERN_C_BEGIN

bool Platform_CreateWindow(WndHandle* pHandle, const WndInitProps* pInitProps);

void Platform_DestroyWindow(WndHandle* pHandle);

bool Platform_PollEvents();


EXTERN_C_END

