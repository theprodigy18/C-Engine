#include "pch.h"
#include "Platform/Linux/Linux_Window.h"

#pragma region INTERNAL
static bool     s_isInitalized = false;
static Display* s_pDisplay     = NULL;
static Atom     s_wmDelete     = 0;
#pragma endregion

bool Platform_CreateWindow(WndHandle* pHandle, const WndInitProps* pInitProps)
{
    *pHandle = NULL;

    if (!s_isInitalized)
    {
        XInitThreads();
        s_pDisplay = XOpenDisplay(NULL);
        ASSERT(s_pDisplay);

        s_wmDelete = XInternAtom(s_pDisplay, "WM_DELETE_WINDOW", False);

        s_isInitalized = true;
    }

    i32    screen = XDefaultScreen(s_pDisplay);
    Window root   = XRootWindow(s_pDisplay, screen);

    Visual* visual = DefaultVisual(s_pDisplay, screen);

    XSetWindowAttributes swa;
    swa.event_mask = ExposureMask | KeyPressMask;

    Window window = XCreateWindow(s_pDisplay, root,
                                  0, 0, pInitProps->width, pInitProps->height,
                                  0, CopyFromParent, InputOutput, visual,
                                  CWEventMask, &swa);

    if (!window)
    {
        ASSERT(false);
        return false;
    }

    XStoreName(s_pDisplay, window, pInitProps->title);
    XSetWMProtocols(s_pDisplay, window, &s_wmDelete, 1);

    WndHandle handle = ALLOCATE_SINGLE(_WndHandle);
    handle->pDisplay = s_pDisplay;
    handle->window   = window;

    *pHandle = handle;

    return true;
}

void Platform_DestroyWindow(WndHandle* pHandle)
{
    WndHandle handle = *pHandle;

    if (handle)
    {
        XDestroyWindow(s_pDisplay, handle->window);
        FREE(handle);
    }

    *pHandle = NULL;
}

bool Platform_PollEvents()
{
    while (XPending(s_pDisplay))
    {
        XEvent event;
        XNextEvent(s_pDisplay, &event);

        switch (event.type)
        {
        case ClientMessage:
            if ((Atom) event.xclient.data.l[0] == s_wmDelete)
                return false;
            break;

        default:
            break;
        }
    }

    return true;
}

void Platform_ShowWindow(WndHandle handle)
{
    XMapWindow(s_pDisplay, handle->window);
    XFlush(s_pDisplay);
}
void Platform_HideWindow(WndHandle handle)
{
    XUnmapWindow(s_pDisplay, handle->window);
    XFlush(s_pDisplay);
}
