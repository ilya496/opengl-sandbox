#pragma once

#include <unordered_map>
#include "math/math.h"
#include "windows.h"

enum class KeyCode : int
{
	A = 'A', B = 'B', C = 'C', D = 'D', E = 'E', F = 'F', G = 'G', H = 'H',
	I = 'I', J = 'J', K = 'K', L = 'L', M = 'M', N = 'N', O = 'O', P = 'P',
	Q = 'Q', R = 'R', S = 'S', T = 'T', U = 'U', V = 'V', W = 'W', X = 'X',
	Y = 'Y', Z = 'Z',

	Num0 = '0', Num1 = '1', Num2 = '2', Num3 = '3', Num4 = '4',
	Num5 = '5', Num6 = '6', Num7 = '7', Num8 = '8', Num9 = '9',

	Space = VK_SPACE,
	Enter = VK_RETURN,
	Tab = VK_TAB,
	Backspace = VK_BACK,
	Escape = VK_ESCAPE,

	Left = VK_LEFT,
	Right = VK_RIGHT,
	Up = VK_UP,
	Down = VK_DOWN,

	Shift = VK_SHIFT,
	Ctrl = VK_CONTROL,
	Alt = VK_MENU,

	F1 = VK_F1, F2 = VK_F2, F3 = VK_F3, F4 = VK_F4,
	F5 = VK_F5, F6 = VK_F6, F7 = VK_F7, F8 = VK_F8,
	F9 = VK_F9, F10 = VK_F10, F11 = VK_F11, F12 = VK_F12,
};


enum class MouseButton : int
{
	Left = 0,
	Right,
	Middle,
	X1,
	X2,
	Count
};

class Input
{
public:
	static void Init(void* nativeWindowHandle);
	static void Update();

	static bool IsKeyDown(KeyCode key);
	static bool IsKeyPressed(KeyCode key);
	static bool IsKeyReleased(KeyCode key);

	static bool IsMouseButtonDown(MouseButton button);
	static math::ivec2 GetMousePosition();
	static math::ivec2 GetMouseDelta();
	static int GetMouseWheelDelta();

	static void OnKeyEvent(int key, bool down);
	static void OnMouseButtonEvent(MouseButton button, bool down);
	static void OnMouseMove(int x, int y);
	static void OnMouseWheel(int delta);

	static void ClearTextBuffer();
	static const std::wstring& GetTextBuffer();
	static void OnCharInput(wchar_t c);

	static std::wstring GetClipboardText();
	static void SetClipboardText(const std::wstring& text);

private:
	static std::unordered_map<int, bool> s_CurrentKeys;
	static std::unordered_map<int, bool> s_PreviousKeys;

	static bool s_MouseButtons[(int)MouseButton::Count];
	static math::ivec2 s_MousePosition;
	static math::ivec2 s_LastMousePosition;
	static math::ivec2 s_MouseDelta;
	static int s_MouseWheelDeltaRaw;
	static int s_MouseWheelDeltaFrame;

	static std::wstring s_TextBuffer;
};