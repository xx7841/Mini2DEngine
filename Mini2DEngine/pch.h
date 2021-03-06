#pragma once
#pragma warning(disable : 4172)

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#if defined(DEBUG) || defined(_DEBUG)
#ifndef D3D_DEBUG_INFO
#define D3D_DEBUG_INFO
#endif
#endif

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#ifdef UNICODE
#define tstring wstring
#define TOSTRING(value) std::to_wstring(value)
#else
#define tstring string
#define TOSTRING(value) std::to_string(value)
#endif

#pragma comment(lib, "d2d1.lib")			
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "WindowsCodecs.lib")

#include <map>
#include <ctime>
#include <vector>
#include <math.h>
#include <string>
#include <tchar.h>
#include <assert.h>
#include <windows.h>
#include <algorithm>
#include <functional>

#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <d2d1helper.h>