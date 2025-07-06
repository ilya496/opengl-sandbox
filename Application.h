#pragma once

#include "Window.h"
#include "GLContext.h"

class Application
{
public:
	Application();
	~Application();

public:
	void Run();

private:
	void Init();
	void ShutDown();

	Window* m_Window;
	GLContext* m_Context;
};