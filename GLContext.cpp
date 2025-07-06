#include <iostream>

#include "GLContext.h"
#include "opengl.h"

typedef HGLRC (WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hdc, HGLRC hShareContext, const int* attribList);
typedef BOOL(WINAPI* PFNWGLCHOOSEPIXELFORMATARBPROC)(HDC hdc, const int* piAttribIList, 
    const FLOAT* pfAttribFList, UINT nMaxFormats, int* piFormats, UINT* nNumFormats);

/*
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
*/

GLContext* GLContext::Create(HWND hwnd)
{
    GLContext* context = new GLContext(hwnd);
    if (context->Init())
        return context;

    return nullptr;
}

GLContext::GLContext(HWND hwnd)
    : m_Hwnd(hwnd), m_Hdc(GetDC(hwnd)), m_Context(nullptr)
{
}


GLContext::~GLContext()
{
    if (m_Context)
    {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(m_Context);
    }

    if (m_Hdc)
        ReleaseDC(m_Hwnd, m_Hdc);
}

bool GLContext::Init()
{
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0,0,0,0,0,0,0,0,0,0,0,0,0,
        24, 8, 0,
        PFD_MAIN_PLANE, 0, 0, 0, 0,
    };

    int pixelFormat = ChoosePixelFormat(m_Hdc, &pfd);
    SetPixelFormat(m_Hdc, pixelFormat, &pfd);

    m_DummyContext = wglCreateContext(m_Hdc);
    wglMakeCurrent(m_Hdc, m_DummyContext);

    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB =
        (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB =
        (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

    if (!wglChoosePixelFormatARB || !wglCreateContextAttribsARB)
    {
        std::cerr << "Required WGL extensions not supported.\n";
        return false;
    }
    int attribs[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        0
    };

    int pf;
    UINT numFormats;
    wglChoosePixelFormatARB(m_Hdc, attribs, nullptr, 1, &pf, &numFormats);
    PIXELFORMATDESCRIPTOR realPFD;
    DescribePixelFormat(m_Hdc, pf, sizeof(realPFD), &realPFD);
    SetPixelFormat(m_Hdc, pf, &realPFD);
    
    int ctxAttribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 1,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    m_Context = wglCreateContextAttribsARB(m_Hdc, nullptr, ctxAttribs);
    if (!m_Context)
    {
        std::cerr << "Failed to create OpenGL 4.1 context.\n";
        return false;
    }

    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(m_DummyContext);

    wglMakeCurrent(m_Hdc, m_Context);

    LoadOpenGLFunctions();

    return true;
}


void GLContext::MakeCurrent()
{
    wglMakeCurrent(m_Hdc, m_Context);
}

void GLContext::SwapBuffers()
{
    ::SwapBuffers(m_Hdc);
}