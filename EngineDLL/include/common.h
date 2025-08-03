#pragma once


#ifdef PLATFORM_WINDOWS
#ifdef ENGINE_DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif // ENGINE_DLL_EXPORT
#else
#define DLL_API
#endif // PLATFORM_WINDOWS

#include "../../EngineLib/API.h"

