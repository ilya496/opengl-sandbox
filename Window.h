#pragma once

#include <windows.h>
#include <string>
#include "math/math.h"

class Window {
public:
    ~Window();

public:
    static Window* Create(int width, int height, const std::string& title);

    void ProcessMessages();
    bool ShouldClose() const;

    HWND GetHandle() const { return m_Hwnd; }

    bool IsKeyDown(unsigned int vk) const;
    bool IsMouseButtonDown(int button) const;
    math::ivec2 GetMouseDelta() const;
    math::ivec2 GetMousePosition() const;

private:
    Window(int width, int height, const std::string& title);
    bool Init();
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    HWND m_Hwnd = nullptr;
    HINSTANCE m_HInstance = nullptr;
    std::wstring m_Title;
    int m_Width;
    int m_Height;
    bool m_ShouldClose = false;

    bool m_Keys[256] = {};
    bool m_MouseButtons[5] = {};

    int m_MouseX = 0, m_MouseY = 0;
    int m_LastMouseX = 0, m_LastMouseY = 0;
    int m_MouseDeltaX = 0, m_MouseDeltaY = 0;
};