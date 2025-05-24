#pragma once

#include <windows.h>
#include <functional>

class Window {
public:
    Window(const wchar_t* title, int width, int height);
    ~Window();

    void Run();
    HWND GetHWND() const;
    HDC  GetHDC()  const;

    void SetRenderCallback(std::function<void()> fn);
    void SetResizeCallback(std::function<void(int, int)> fn);

private:
    HWND m_Hwnd;
    HDC  m_Hdc;

    std::function<void()> onRender;
    std::function<void(int, int)> onResize;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
};