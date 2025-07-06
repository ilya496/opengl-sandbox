#include "Window.h"
#include "windowsx.h"
#include "Input.h"
#include < iostream> ;

Window* Window::Create(int width, int height, const std::string& title)
{
	Window* window = new Window(width, height, title);
	if (window->Init())
		return window;

	return nullptr;
}

Window::Window(int width, int height, const std::string& title)
	: m_Width(width), m_Height(height),	m_Title(title.begin(), title.end()),
	m_HInstance(GetModuleHandle(nullptr))
{
}

Window::~Window()
{
	if (m_Hwnd)
		DestroyWindow(m_Hwnd);
}

bool Window::Init()
{
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = m_HInstance;
	wc.lpszClassName = L"WindowClass";

	RegisterClass(&wc);

	RECT rect = { 0, 0, m_Width, m_Height };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	m_Hwnd = CreateWindowEx(
		0,
		L"WindowClass",
		m_Title.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		nullptr, nullptr, m_HInstance, this
	);

	if (!m_Hwnd)
		return false;

	ShowWindow(m_Hwnd, SW_SHOW);
	return true;
}

void Window::ProcessMessages()
{
	MSG msg = {};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			m_ShouldClose = true;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//m_MouseDeltaX = m_MouseX - m_LastMouseX;
	//m_MouseDeltaY = m_MouseY - m_LastMouseY;

	//m_LastMouseX = m_MouseX;
	//m_LastMouseY = m_MouseY;
}

bool Window::ShouldClose() const
{
	return m_ShouldClose;
}

//bool Window::IsKeyDown(unsigned int vk) const
//{
//	return vk < 256 ? m_Keys[vk] : false;
//}
//
//bool Window::IsMouseButtonDown(int button) const
//{
//	return (button >= 0 && button < 5) ? m_MouseButtons[button] : false;
//}
//
//math::ivec2 Window::GetMouseDelta() const
//{
//	return { m_MouseDeltaX, m_MouseDeltaY };
//}
//
//math::ivec2 Window::GetMousePosition() const
//{
//	return { m_MouseX, m_MouseY };
//}

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* window = nullptr;

	if (uMsg == WM_NCCREATE)
	{
		CREATESTRUCT* create = reinterpret_cast<CREATESTRUCT*>(lParam);
		window = reinterpret_cast<Window*>(create->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		window->m_Hwnd = hwnd;
	}
	else
	{
		window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (window)
	{
		return window->HandleMessage(uMsg, wParam, lParam);
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT Window::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		m_ShouldClose = true;
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		Input::OnKeyEvent((int)wParam, true);
		break;

	case WM_KEYUP:
	case WM_SYSKEYUP:
		Input::OnKeyEvent((int)wParam, false);
		break;

	case WM_MOUSEMOVE:
		Input::OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;

	case WM_LBUTTONDOWN:
		Input::OnMouseButtonEvent(MouseButton::Left, true);
		break;
	case WM_LBUTTONUP:
		Input::OnMouseButtonEvent(MouseButton::Left, false);
		break;

	case WM_RBUTTONDOWN:
		Input::OnMouseButtonEvent(MouseButton::Right, true);
		break;
	case WM_RBUTTONUP:
		Input::OnMouseButtonEvent(MouseButton::Right, false);
		break;

	case WM_MBUTTONDOWN:
		Input::OnMouseButtonEvent(MouseButton::Middle, true);
		break;
	case WM_MBUTTONUP:
		Input::OnMouseButtonEvent(MouseButton::Middle, false);
		break;

	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	{
		WORD mouseButton = GET_XBUTTON_WPARAM(wParam);
		bool pressed = (uMsg == WM_XBUTTONDOWN);

		if (mouseButton == XBUTTON1)
			Input::OnMouseButtonEvent(MouseButton::X1, pressed);
		else if (mouseButton == XBUTTON2)
			Input::OnMouseButtonEvent(MouseButton::X2, pressed);

		break;
	}

	case WM_MOUSEWHEEL:
	{
		int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		std::cout << "Wheel scrolled: " << delta << "\n";
		Input::OnMouseWheel(delta);
		break;
	}

	case WM_CHAR:
		Input::OnCharInput((wchar_t)wParam);
		break;

	}

	return DefWindowProc(m_Hwnd, uMsg, wParam, lParam);
}