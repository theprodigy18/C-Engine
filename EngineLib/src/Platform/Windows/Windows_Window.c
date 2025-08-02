#include "pch.h"
#include "Platform/Windows/Windows_Window.h"


#pragma region INTERNAL

static bool s_isInitialized = false;
static HINSTANCE s_hInstance = NULL;
static u32 s_windowCount = 0;

static wchar_t* ConvertUtf8ToUtf16(const char* pUtf8)
{
	i32 utf8Len = MultiByteToWideChar(CP_UTF8, 0, pUtf8, -1, NULL, 0);
	wchar_t* pUtf16 = ALLOCATE_ARRAY(wchar_t, utf8Len);
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

#pragma endregion


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

	FREE(title);

	if (!hwnd)
	{
		ASSERT(false);
		return false;
	}

	WndHandle handle = ALLOCATE_SINGLE(_WndHandle);
    ASSERT(handle);
    handle->hwnd = hwnd;
	handle->hdc = GetDC(hwnd);

	*pHandle = handle;
    ++s_windowCount;

	return true;
}

void Platform_DestroyWindow(WndHandle* pHandle)
{
	WndHandle handle = *pHandle;

	if (handle)
	{
		ReleaseDC(handle->hwnd, handle->hdc);
        DestroyWindow(handle->hwnd);
        FREE(handle);
	}

	*pHandle = NULL;
	--s_windowCount;

	if (s_windowCount == 0)
	{
		UnregisterClassW(L"GameEngine", s_hInstance);
		s_hInstance = NULL;
		s_isInitialized = false;
	}
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

void Platform_ShowWindow(WndHandle handle)
{
	ShowWindow(handle->hwnd, SW_SHOW);
	UpdateWindow(handle->hwnd);
}

void Platform_HideWindow(WndHandle handle)
{
	ShowWindow(handle->hwnd, SW_HIDE);
}

void Platform_SwapBuffers(WndHandle handle)
{
	SwapBuffers(handle->hdc);
}
