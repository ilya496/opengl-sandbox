#include "Window.h"
#include "GLContext.h" 

static Window* g_WindowInstance = nullptr;

Window::Window(const wchar_t* title, int width, int height) {
    g_WindowInstance = this;

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = L"MyWindowClass";

    RegisterClass(&wc);

    m_Hwnd = CreateWindowEx(
        0, wc.lpszClassName, title, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        nullptr, nullptr, GetModuleHandle(nullptr), nullptr
    );

    ShowWindow(m_Hwnd, SW_SHOW);
    m_Hdc = GetDC(m_Hwnd);

    CreateOpenGLContext(m_Hdc);
}

Window::~Window() {
    ReleaseDC(m_Hwnd, m_Hdc);
    DestroyWindow(m_Hwnd);
}

void Window::Run() {
    MSG msg = {};
    while (true) {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                return;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (onRender) {
            onRender();
        }

        InvalidateRect(m_Hwnd, nullptr, FALSE);
    }
}

void Window::SetRenderCallback(std::function<void()> fn) {
    onRender = fn;
}
void Window::SetResizeCallback(std::function<void(int, int)> fn) {
    onResize = fn;
}

HWND Window::GetHWND() const { return m_Hwnd; }
HDC  Window::GetHDC()  const { return m_Hdc; }

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_PAINT:
        if (g_WindowInstance->onRender) g_WindowInstance->onRender();
        break;
    case WM_SIZE:
        if (g_WindowInstance->onResize) {
            int width = LOWORD(lp);
            int height = HIWORD(lp);
            g_WindowInstance->onResize(width, height);
        }

        InvalidateRect(hwnd, NULL, FALSE);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}
