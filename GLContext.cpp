#include "GLContext.h"
#include "opengl.h"

typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int*);
static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;

HGLRC CreateTrampolineContext(HDC hdc) {
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR), 1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 0,
        PFD_MAIN_PLANE, 0, 0, 0, 0, 0
    };

    int pixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pixelFormat, &pfd);
    return wglCreateContext(hdc);
}

HGLRC CreateOpenGLContext(HDC hdc) {
    HGLRC trampolineContext = CreateTrampolineContext(hdc);
    wglMakeCurrent(hdc, trampolineContext);

    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)
        wglGetProcAddress("wglCreateContextAttribsARB");

    if (!wglCreateContextAttribsARB) {
        MessageBox(NULL, L"Failed to load wglCreateContextAttribsARB", L"Error", MB_OK | MB_ICONERROR);
        return NULL;
    }

    const int attribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 1,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    HGLRC modernContext = wglCreateContextAttribsARB(hdc, 0, attribs);

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(trampolineContext);
    wglMakeCurrent(hdc, modernContext);

    return modernContext;
}

bool InitGLContext(HDC hdc) {
    HGLRC hglrc = CreateOpenGLContext(hdc);
    if (!hglrc) {
        return false;
    }

    LoadOpenGLFunctions();
    return true;
}
