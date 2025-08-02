#pragma once

#include "common.h"

EXTERN_C_BEGIN

DLL_API bool API_CreateWindow(WndHandle* pHandle, const WndInitProps* pInitProps);
DLL_API void API_DestroyWindow(WndHandle* pHandle);
DLL_API bool API_PollEvents();

EXTERN_C_END