#pragma once

#if defined(WIN32) || defined(_WIN32)
#define PLATFORM_STRING Windows
#define CBCALL __cdecl
#else
#define PLATFORM_STRING NoWindows
#define CBCALL
#endif
