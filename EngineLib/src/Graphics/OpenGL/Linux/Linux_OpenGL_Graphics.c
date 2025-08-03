#include "Platform/Window.h"
#include "common.h"
#include "pch.h"
#include "Platform/Linux/Linux_Window.h"
#include <EGL/egl.h>
#include "Graphics/OpenGL/Linux/Linux_OpenGL_Graphics.h"

#pragma region INTERNAL
#define LoadGLFunction(type, name)          \
    name = (type) eglGetProcAddress(#name); \
    ASSERT_MSG(name, "Failed to load OpenGL function: %s" #name);

#pragma region GLFunctionProcs
static PFNGLCREATEPROGRAMPROC           glCreateProgram;
static PFNGLCREATESHADERPROC            glCreateShader;
static PFNGLGETUNIFORMLOCATIONPROC      glGetUniformLocation;
static PFNGLUNIFORM1FPROC               glUniform1f;
static PFNGLUNIFORM2FVPROC              glUniform2fv;
static PFNGLUNIFORM3FVPROC              glUniform3fv;
static PFNGLUNIFORM1IPROC               glUniform1i;
static PFNGLUNIFORMMATRIX4FVPROC        glUniformMatrix4fv;
static PFNGLVERTEXATTRIBDIVISORPROC     glVertexAttribDivisor;
static PFNGLBUFFERSUBDATAPROC           glBufferSubData;
static PFNGLDRAWARRAYSINSTANCEDPROC     glDrawArraysInstanced;
static PFNGLBINDFRAMEBUFFERPROC         glBindFramebuffer;
static PFNGLCHECKFRAMEBUFFERSTATUSPROC  glCheckFramebufferStatus;
static PFNGLGENFRAMEBUFFERSPROC         glGenFramebuffers;
static PFNGLFRAMEBUFFERTEXTURE2DPROC    glFramebufferTexture2D;
static PFNGLDRAWBUFFERSPROC             glDrawBuffers;
static PFNGLDELETEFRAMEBUFFERSPROC      glDeleteFramebuffers;
static PFNGLBLENDFUNCIPROC              glBlendFunci;
static PFNGLCLEARBUFFERFVPROC           glClearBufferfv;
static PFNGLSHADERSOURCEPROC            glShaderSource;
static PFNGLCOMPILESHADERPROC           glCompileShader;
static PFNGLGETSHADERIVPROC             glGetShaderiv;
static PFNGLGETSHADERINFOLOGPROC        glGetShaderInfoLog;
static PFNGLATTACHSHADERPROC            glAttachShader;
static PFNGLLINKPROGRAMPROC             glLinkProgram;
static PFNGLVALIDATEPROGRAMPROC         glValidateProgram;
static PFNGLGETPROGRAMIVPROC            glGetProgramiv;
static PFNGLGETPROGRAMINFOLOGPROC       glGetProgramInfoLog;
static PFNGLGENBUFFERSPROC              glGenBuffers;
static PFNGLGENVERTEXARRAYSPROC         glGenVertexArrays;
static PFNGLGETATTRIBLOCATIONPROC       glGetAttribLocation;
static PFNGLBINDVERTEXARRAYPROC         glBindVertexArray;
static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
static PFNGLVERTEXATTRIBPOINTERPROC     glVertexAttribPointer;
static PFNGLBINDBUFFERPROC              glBindBuffer;
static PFNGLBINDBUFFERBASEPROC          glBindBufferBase;
static PFNGLBUFFERDATAPROC              glBufferData;
static PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv;
static PFNGLUSEPROGRAMPROC              glUseProgram;
static PFNGLDELETEVERTEXARRAYSPROC      glDeleteVertexArrays;
static PFNGLDELETEBUFFERSPROC           glDeleteBuffers;
static PFNGLDELETEPROGRAMPROC           glDeleteProgram;
static PFNGLDETACHSHADERPROC            glDetachShader;
static PFNGLDELETESHADERPROC            glDeleteShader;
static PFNGLDRAWELEMENTSINSTANCEDPROC   glDrawElementsInstanced;
static PFNGLGENERATEMIPMAPPROC          glGenerateMipmap;
static PFNGLDEBUGMESSAGECALLBACKPROC    glDebugMessageCallback;

void LoadOpenGLFunctions()
{
    LoadGLFunction(PFNGLCREATEPROGRAMPROC, glCreateProgram);
    LoadGLFunction(PFNGLCREATESHADERPROC, glCreateShader);
    LoadGLFunction(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation);
    LoadGLFunction(PFNGLUNIFORM1FPROC, glUniform1f);
    LoadGLFunction(PFNGLUNIFORM2FVPROC, glUniform2fv);
    LoadGLFunction(PFNGLUNIFORM3FVPROC, glUniform3fv);
    LoadGLFunction(PFNGLUNIFORM1IPROC, glUniform1i);
    LoadGLFunction(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv);
    LoadGLFunction(PFNGLVERTEXATTRIBDIVISORPROC, glVertexAttribDivisor);
    LoadGLFunction(PFNGLBUFFERSUBDATAPROC, glBufferSubData);
    LoadGLFunction(PFNGLDRAWARRAYSINSTANCEDPROC, glDrawArraysInstanced);
    LoadGLFunction(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer);
    LoadGLFunction(PFNGLCHECKFRAMEBUFFERSTATUSPROC, glCheckFramebufferStatus);
    LoadGLFunction(PFNGLGENFRAMEBUFFERSPROC, glGenFramebuffers);
    LoadGLFunction(PFNGLFRAMEBUFFERTEXTURE2DPROC, glFramebufferTexture2D);
    LoadGLFunction(PFNGLDRAWBUFFERSPROC, glDrawBuffers);
    LoadGLFunction(PFNGLDELETEFRAMEBUFFERSPROC, glDeleteFramebuffers);
    LoadGLFunction(PFNGLBLENDFUNCIPROC, glBlendFunci);
    LoadGLFunction(PFNGLCLEARBUFFERFVPROC, glClearBufferfv);
    LoadGLFunction(PFNGLSHADERSOURCEPROC, glShaderSource);
    LoadGLFunction(PFNGLCOMPILESHADERPROC, glCompileShader);
    LoadGLFunction(PFNGLGETSHADERIVPROC, glGetShaderiv);
    LoadGLFunction(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog);
    LoadGLFunction(PFNGLATTACHSHADERPROC, glAttachShader);
    LoadGLFunction(PFNGLLINKPROGRAMPROC, glLinkProgram);
    LoadGLFunction(PFNGLVALIDATEPROGRAMPROC, glValidateProgram);
    LoadGLFunction(PFNGLGETPROGRAMIVPROC, glGetProgramiv);
    LoadGLFunction(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog);
    LoadGLFunction(PFNGLGENBUFFERSPROC, glGenBuffers);
    LoadGLFunction(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays);
    LoadGLFunction(PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation);
    LoadGLFunction(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray);
    LoadGLFunction(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray);
    LoadGLFunction(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer);
    LoadGLFunction(PFNGLBINDBUFFERPROC, glBindBuffer);
    LoadGLFunction(PFNGLBINDBUFFERBASEPROC, glBindBufferBase);
    LoadGLFunction(PFNGLBUFFERDATAPROC, glBufferData);
    LoadGLFunction(PFNGLGETVERTEXATTRIBPOINTERVPROC, glGetVertexAttribPointerv);
    LoadGLFunction(PFNGLUSEPROGRAMPROC, glUseProgram);
    LoadGLFunction(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays);
    LoadGLFunction(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);
    LoadGLFunction(PFNGLDELETEPROGRAMPROC, glDeleteProgram);
    LoadGLFunction(PFNGLDETACHSHADERPROC, glDetachShader);
    LoadGLFunction(PFNGLDELETESHADERPROC, glDeleteShader);
    LoadGLFunction(PFNGLDRAWELEMENTSINSTANCEDPROC, glDrawElementsInstanced);
    LoadGLFunction(PFNGLGENERATEMIPMAPPROC, glGenerateMipmap);
    LoadGLFunction(PFNGLDEBUGMESSAGECALLBACKPROC, glDebugMessageCallback);
}
#pragma endregion

void GLDebugCallback(GLenum source, GLenum type, GLuint id,
                     GLenum severity, GLsizei length, const GLchar* message,
                     const void* userParam)
{
    if (severity == GL_DEBUG_SEVERITY_LOW ||
        severity == GL_DEBUG_SEVERITY_MEDIUM ||
        severity == GL_DEBUG_SEVERITY_HIGH)
    {
        ASSERT_MSG(false, "OpenGL error: %s", message);
    }
    else
    {
        LOG_TRACE((char*) message);
    }
}

static bool       s_isInitialized = false;
static EGLDisplay s_eglDisplay    = NULL;

#pragma endregion

bool Graphics_CreateGraphics(GfxHandle* pHandle, const GfxInitProps* pInitProps)
{
    *pHandle = NULL;

    if (!s_isInitialized)
    {

        s_eglDisplay = eglGetDisplay((EGLNativeDisplayType) pInitProps->wndHandle->pDisplay);

        eglInitialize(s_eglDisplay, NULL, NULL);

        WndInitProps dummyProps;
        dummyProps.title  = "DUMMY";
        dummyProps.width  = 1280;
        dummyProps.height = 720;

        WndHandle dummyHandle = NULL;
        if (!Platform_CreateWindow(&dummyHandle, &dummyProps))
        {
            ASSERT(false);
            return false;
        }

        const EGLint configAttribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,    // setara PFD_DRAW_TO_WINDOW
            EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT, // atau EGL_OPENGL_BIT jika pakai full GL
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 24,  // setara cDepthBits
            EGL_STENCIL_SIZE, 8, // setara cStencilBits
            EGL_NONE};

        EGLConfig config = NULL;
        EGLint    numConfigs;
        eglChooseConfig(s_eglDisplay, configAttribs, &config, 1, &numConfigs);

        EGLSurface dummySurface = eglCreateWindowSurface(s_eglDisplay, config,
                                                         dummyHandle->window, NULL);
        eglBindAPI(EGL_OPENGL_API);

        const EGLint contextAttribs[] = {
            EGL_CONTEXT_MAJOR_VERSION_KHR, 4,
            EGL_CONTEXT_MINOR_VERSION_KHR, 3,
            EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
            EGL_CONTEXT_FLAGS_KHR, EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR,
            EGL_NONE};

        EGLContext dummyContext = eglCreateContext(s_eglDisplay, config, EGL_NO_CONTEXT, contextAttribs);

        if (!dummyContext)
        {
            ASSERT(false);
            return false;
        }

        eglMakeCurrent(s_eglDisplay, dummySurface, dummySurface, dummyContext);

        LoadOpenGLFunctions();

        glDebugMessageCallback(&GLDebugCallback, NULL);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glEnable(GL_DEBUG_OUTPUT);

        eglMakeCurrent(s_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglDestroyContext(s_eglDisplay, dummyContext);
        eglDestroySurface(s_eglDisplay, dummySurface);

        Platform_DestroyWindow(&dummyHandle);
        s_isInitialized = true;
    }

    WndHandle wndHandle = pInitProps->wndHandle;

    const EGLint configAttribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_STENCIL_SIZE, 8,
        EGL_NONE};

    EGLConfig config;
    EGLint    numConfigs;
    if (!eglChooseConfig(s_eglDisplay, configAttribs, &config, 1, &numConfigs) || numConfigs == 0)
    {
        ASSERT_MSG(false, "Failed to choose EGL config.");
        return false;
    }

    EGLSurface surface = eglCreateWindowSurface(s_eglDisplay, config, wndHandle->window, NULL);
    if (surface == EGL_NO_SURFACE)
    {
        ASSERT_MSG(false, "Failed to create EGL window surface.")
    }

    const EGLint contextAttribs[] = {
        EGL_CONTEXT_MAJOR_VERSION_KHR, 4,
        EGL_CONTEXT_MINOR_VERSION_KHR, 3,
        EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
        EGL_CONTEXT_FLAGS_KHR, EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR,
        EGL_NONE};

    EGLContext context = eglCreateContext(s_eglDisplay, config, EGL_NO_CONTEXT, contextAttribs);
    if (context == EGL_NO_CONTEXT)
    {
        ASSERT_MSG(false, "Failed to create EGL OpenGL context");
        return false;
    }

    if (!eglMakeCurrent(s_eglDisplay, surface, surface, context))
    {
        ASSERT_MSG(false, "Failed to make EGL context current");
        return false;
    }

    XWindowAttributes attrs;
    XGetWindowAttributes(wndHandle->pDisplay, wndHandle->window, &attrs);
    glViewport(0, 0, attrs.width, attrs.height);

    GfxHandle handle = ALLOCATE_SINGLE(_GfxHandle);
    ASSERT(handle);
    handle->display = s_eglDisplay;
    handle->surface = surface;
    handle->context = context;

    *pHandle = handle;

    return true;
}

void Graphics_SetCurrentGraphics(GfxHandle handle)
{
    eglMakeCurrent(s_eglDisplay, handle->surface, handle->surface, handle->context);
}

void Graphics_ClearColor(f32 r, f32 g, f32 b, f32 a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics_DestroyGraphics(GfxHandle* pHandle)
{
    GfxHandle handle = *pHandle;
    if (handle)
    {
        eglMakeCurrent(s_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglDestroyContext(s_eglDisplay, handle->context);
        eglDestroySurface(s_eglDisplay, handle->surface);
        FREE(handle);
    }

    *pHandle = NULL;
}

void Graphics_SwapBuffers(GfxHandle handle)
{
    eglSwapBuffers(s_eglDisplay, handle->surface);
}