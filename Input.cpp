#include "Input.h"
#include <iostream>

std::unordered_map<int, bool> Input::s_CurrentKeys;
std::unordered_map<int, bool> Input::s_PreviousKeys;

bool Input::s_MouseButtons[(int)MouseButton::Count] = {};
math::ivec2 Input::s_MousePosition = {};
math::ivec2 Input::s_LastMousePosition = {};
math::ivec2 Input::s_MouseDelta = {};
int Input::s_MouseWheelDeltaRaw = 0;
int Input::s_MouseWheelDeltaFrame = 0;

std::wstring Input::s_TextBuffer;

void Input::Init(void* nativeWindowHandle) { /* optional */ }

void Input::Update()
{
    s_PreviousKeys = s_CurrentKeys;

    s_MouseDelta = s_MousePosition - s_LastMousePosition;
    s_LastMousePosition = s_MousePosition;

    s_MouseWheelDeltaFrame = s_MouseWheelDeltaRaw;
    s_MouseWheelDeltaRaw = 0;
}

bool Input::IsKeyDown(KeyCode key) { return s_CurrentKeys[(int)key]; }
bool Input::IsKeyPressed(KeyCode key) { return s_CurrentKeys[(int)key] && !s_PreviousKeys[(int)key]; }
bool Input::IsKeyReleased(KeyCode key) { return !s_CurrentKeys[(int)key] && s_PreviousKeys[(int)key]; }

bool Input::IsMouseButtonDown(MouseButton button) { return s_MouseButtons[(int)button]; }
math::ivec2 Input::GetMousePosition() { return s_MousePosition; }
math::ivec2 Input::GetMouseDelta() { return s_MouseDelta; }
int Input::GetMouseWheelDelta() { return s_MouseWheelDeltaFrame; }

void Input::OnKeyEvent(int key, bool down) { s_CurrentKeys[key] = down; }
void Input::OnMouseButtonEvent(MouseButton button, bool down) { s_MouseButtons[(int)button] = down; }
void Input::OnMouseMove(int x, int y) { s_MousePosition = { x, y }; }
void Input::OnMouseWheel(int delta) { s_MouseWheelDeltaRaw += delta; }

void Input::ClearTextBuffer() { s_TextBuffer.clear(); }
const std::wstring& Input::GetTextBuffer() { return s_TextBuffer; }
void Input::OnCharInput(wchar_t c) {
    if (c >= 32)
        s_TextBuffer.push_back(c); 
}

std::wstring Input::GetClipboardText()
{
    if (!OpenClipboard(nullptr))
        return L"";
    
    HANDLE hData = GetClipboardData(CF_UNICODETEXT);
    if (!hData)
    {
        CloseClipboard();
        return L"";
    }

    const wchar_t* text = static_cast<wchar_t*>(GlobalLock(hData));
    if (!text)
    {
        CloseClipboard();
        return L"";
    }

    std::wstring result(text);
    GlobalUnlock(hData);
    CloseClipboard();
    return result;
}

void Input::SetClipboardText(const std::wstring& text) 
{
    if (!OpenClipboard(nullptr)) return;

    EmptyClipboard();

    size_t bytes = (text.size() + 1) * sizeof(wchar_t);
    HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, bytes);
    if (!hGlobal)
    {
        CloseClipboard();
        return;
    }

    void* dest = GlobalLock(hGlobal);
    memcpy(dest, text.c_str(), bytes);
    GlobalUnlock(hGlobal);

    SetClipboardData(CF_UNICODETEXT, hGlobal);
    CloseClipboard();
}