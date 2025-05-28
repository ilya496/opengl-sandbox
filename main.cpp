#include <chrono>
#include <iostream>

#include "Window.h"
#include "opengl.h"
#include "Shader.h"
#include "GLContext.h"
#include "math/math.h"
#include "Buffer.h"

static auto gStartTime = std::chrono::high_resolution_clock::now();

//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) 
int main()
{

    Window window(L"GL Window", 800, 800);

    HDC hdc = window.GetHDC();
    HGLRC hglrc = CreateOpenGLContext(hdc);
    if (!hglrc)
    {
        MessageBox(NULL, L"Failed to create OpenGL 4.1 context.", L"Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    LoadOpenGLFunctions();
    GLuint vao;
    Shader shader = LoadShaderFromFile("basic.vert", "basic.frag");

    float vertices[] =
    {
         -0.5f, -0.5f * float(std::sqrt(3)) / 3,
         0.5f, -0.5f * float(std::sqrt(3)) / 3,
         0.0f, 0.5f * float(std::sqrt(3)) * 2 / 3
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    BufferLayout layout({ 
        { ShaderDataType::Float2, "position" }
    });
    VertexBuffer vbo(vertices, sizeof(vertices));
    vbo.SetLayout(layout);

    window.SetRenderCallback([&]() {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        auto now = std::chrono::high_resolution_clock::now();
        float elapsedSeconds = std::chrono::duration<float>(now - gStartTime).count();

        shader.Bind();
        shader.Set1f("uTime", elapsedSeconds);

        glBindVertexArray(vao);
        vbo.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

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

    math::mat2 m2;
    std::cout << m2 << '\n';

    math::mat3 m3;
    std::cout << m3 << '\n';

    math::mat4 m4;
    std::cout << m4 << '\n';

    window.Run();
    return 0;
}