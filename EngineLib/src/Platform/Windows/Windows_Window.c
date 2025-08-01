#include "pch.h"
#include "Platform/Window.h"

#define WIN32_LEAN_AND_MEAN
#define NO_MIN_MAX
#include <Windows.h>

static bool s_isInitialized = false;
static HINSTANCE s_hInstance = NULL;

typedef struct _WndHandle
{
	HWND hwnd;
} _WndHandle;

static wchar_t* ConvertUtf8ToUtf16(const char* pUtf8)
{
	i32 utf8Len = MultiByteToWideChar(CP_UTF8, 0, pUtf8, -1, NULL, 0);
	wchar_t* pUtf16 = (wchar_t*)malloc(utf8Len * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, pUtf8, -1, pUtf16, utf8Len);
	return pUtf16;
}

static LRESULT CALLBACK InternalWndCallback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
	{
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
        default:
			break;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}


bool Platform_CreateWindow(WndHandle* pHandle, const WndInitProps* pInitProps)
{
	*pHandle = NULL;

	if (!s_isInitialized)
	{
		s_hInstance = GetModuleHandleW(NULL);
        ASSERT(s_hInstance);

		WNDCLASSEXW wcex;
		ZeroMemory(&wcex, sizeof(wcex));
		wcex.cbSize = sizeof(wcex);
		wcex.style = CS_OWNDC;
		wcex.lpfnWndProc = InternalWndCallback;
		wcex.hInstance = s_hInstance;
		wcex.hCursor = LoadCursorW(NULL, IDC_ARROW);
		wcex.hIcon = LoadIconW(NULL, IDI_APPLICATION);
		wcex.hIconSm = LoadIconW(NULL, IDI_APPLICATION);
		wcex.lpszClassName = L"GameEngine";
		wcex.lpszMenuName = NULL;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;

		if (!RegisterClassExW(&wcex))
		{
			ASSERT(false);
            return false;
		}

		SetProcessDPIAware();

		s_isInitialized = true;
	}

	const wchar_t* title = ConvertUtf8ToUtf16(pInitProps->title);

	HWND hwnd = CreateWindowExW(
		0,
        L"GameEngine",
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		pInitProps->width,
		pInitProps->height,
		NULL,
		NULL,
		s_hInstance,
		NULL
    );

	free(title);

	if (!hwnd)
	{
		ASSERT(false);
		return false;
	}

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	WndHandle handle = (WndHandle*)malloc(sizeof(WndHandle));
    ASSERT(handle);
    handle->hwnd = hwnd;

	*pHandle = handle;

	return true;
}

void Platform_DestroyWindow(WndHandle* pHandle)
{
	WndHandle handle = *pHandle;

	if (handle)
	{
        DestroyWindow(handle->hwnd);
        free(handle);
	}

	*pHandle = NULL;
}

bool Platform_PollEvents()
{
    MSG msg;
    while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
    {
		if (msg.message == WM_QUIT)
		{
            return false;
		}

        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

	return true;
}
