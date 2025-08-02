#include "PlatformAPI.h"

#include <Platform/Window.h>

bool API_CreateWindow(WndHandle* pHandle, const WndInitProps* pInitProps)
{
	return Platform_CreateWindow(pHandle, pInitProps);
}


void API_DestroyWindow(WndHandle* pHandle)
{
    Platform_DestroyWindow(pHandle);
}

bool API_PollEvents()
{
	return Platform_PollEvents();
}