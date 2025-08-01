#pragma once


EXTERN_C_BEGIN


typedef struct _WndHandle* WndHandle;

typedef struct _WndInitProps
{
    char* title;
	i32 width;
	i32 height;
} WndInitProps;



bool Platform_CreateWindow(WndHandle* pHandle, const WndInitProps* pInitProps);

void Platform_DestroyWindow(WndHandle* pHandle);

bool Platform_PollEvents();

EXTERN_C_END

