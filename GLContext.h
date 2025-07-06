#pragma once

#include <windows.h>

#define WGL_CONTEXT_MAJOR_VERSION_ARB   0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB   0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB    0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x0001

// See https://www.khronos.org/registry/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt for all values
#define WGL_DRAW_TO_WINDOW_ARB                    0x2001
#define WGL_SUPPORT_OPENGL_ARB                    0x2010
#define WGL_DOUBLE_BUFFER_ARB                     0x2011
#define WGL_PIXEL_TYPE_ARB                        0x2013
#define WGL_COLOR_BITS_ARB                        0x2014
#define WGL_DEPTH_BITS_ARB                        0x2022
#define WGL_STENCIL_BITS_ARB                      0x2023
#define WGL_TYPE_RGBA_ARB                         0x202B

HGLRC CreateTrampolineContext(HDC hdc);
HGLRC CreateOpenGLContext(HDC hdc);
bool InitGLContext(HDC hdc);

class GLContext 
{
public:
	static GLContext* Create(HWND hwnd);
	~GLContext();

public:
	void MakeCurrent();
	void SwapBuffers();

private:
	GLContext(HWND hwnd);
	bool Init();

	HWND m_Hwnd;
	HDC m_Hdc;
	HGLRC m_Context;

	HGLRC m_DummyContext = nullptr;
};