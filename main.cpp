#include <chrono>
#include "Window.h"
#include "opengl.h"
#include "Shader.h"
#include "GLContext.h"
#include "math/math.h"
#include <iostream>

static auto gStartTime = std::chrono::high_resolution_clock::now();

//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) 
int main()
{

    Window window(L"GL Window", 800, 600);

    HDC hdc = window.GetHDC();
    HGLRC hglrc = CreateOpenGLContext(hdc);
    if (!hglrc) 
    {
        MessageBox(NULL, L"Failed to create OpenGL 4.1 context.", L"Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    LoadOpenGLFunctions();
    GLuint vao;
    GLuint vbo;
    Shader shader = LoadShaderFromFile("basic.vert", "basic.frag");

    float diamond[] = 
    {
         0.0f,  0.0f,  // center
         0.0f,  0.75f, // top
         0.25f, 0.0f,  // right
         0.0f, -0.75f, // bottom
        -0.25f, 0.0f,  // left
         0.0f,  0.75f  // back to top to close
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(diamond), diamond, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    window.SetRenderCallback([&]() {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        auto now = std::chrono::high_resolution_clock::now();
        float elapsedSeconds = std::chrono::duration<float>(now - gStartTime).count();

        shader.Bind();
        shader.Set1f("uTime", elapsedSeconds);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

        SwapBuffers(window.GetHDC());
        });

    window.SetResizeCallback([](int width, int height) {
        width = max(width, 1);
        height = max(height, 1);
        glViewport(0, 0, width, height);
        });

    math::vec2 v1(1.0f, 2.5f), v2(3.0f, 4.0f);
    math::vec2 result = v1 + v2;
    std::cout << result << std::endl;

    window.Run();
    return 0;
}