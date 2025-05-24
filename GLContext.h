#pragma once

#include <windows.h>

#define WGL_CONTEXT_MAJOR_VERSION_ARB   0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB   0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB    0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x0001

HGLRC CreateTrampolineContext(HDC hdc);
HGLRC CreateOpenGLContext(HDC hdc);
bool InitGLContext(HDC hdc);