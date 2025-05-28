#include "opengl.h"

PFNGLCLEARPROC pglClear = NULL;
PFNGLCLEARCOLORPROC pglClearColor = NULL;
PFNGLVIEWPORTPROC pglViewport = NULL;
PFNGLGENBUFFERSPROC pglGenBuffers = NULL;
PFNGLDELETEBUFFERSPROC pglDeleteBuffers = NULL;
PFNGLBINDBUFFERPROC pglBindBuffer = NULL;
PFNGLBUFFERDATAPROC pglBufferData = NULL;
PFNGLGENVERTEXARRAYSPROC pglGenVertexArrays = NULL;
PFNGLBINDVERTEXARRAYPROC pglBindVertexArray = NULL;
PFNGLVERTEXATTRIBPOINTERPROC pglVertexAttribPointer = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC pglEnableVertexAttribArray = NULL;
PFNGLDRAWELEMENTSPROC pglDrawElements = NULL;
PFNGLDRAWARRAYSPROC pglDrawArrays = NULL;
PFNGLCREATEPROGRAMPROC pglCreateProgram = NULL;
PFNGLUSEPROGRAMPROC pglUseProgram = NULL;
PFNGLDELETEPROGRAMPROC pglDeleteProgram = NULL;
PFNGLLINKPROGRAMPROC pglLinkProgram = NULL;
PFNGLVALIDATEPROGRAMPROC pglValidateProgram = NULL;
PFNGLCREATESHADERPROC pglCreateShader = NULL;
PFNGLSHADERSOURCEPROC pglShaderSource = NULL;
PFNGLCOMPILESHADERPROC pglCompileShader = NULL;
PFNGLATTACHSHADERPROC pglAttachShader = NULL;
PFNGLDELETESHADERPROC pglDeleteShader = NULL;
PFNGLGETUNIFORMLOCATIONPROC pglGetUniformLocation = NULL;
PFNGLGETSHADERIVPROC pglGetShaderiv = NULL;
PFNGLGETPROGRAMIVPROC pglGetProgramiv = NULL;
PFNGLGETSHADERINFOLOGPROC pglGetShaderInfoLog = NULL;
PFNGLGETPROGRAMINFOLOGPROC pglGetProgramInfoLog = NULL;
PFNGLUNIFORM1FPROC pglUniform1f = NULL;
PFNGLUNIFORM3FPROC pglUniform3f = NULL;
PFNGLUNIFORM4FPROC pglUniform4f = NULL;
PFNGLUNIFORM1IPROC pglUniform1i = NULL;
PFNGLUNIFORM3FVPROC pglUniform3fv = NULL;
PFNGLUNIFORMMATRIX4FVPROC pglUniformMatrix4fv = NULL;

void LoadCoreOpenGLFunctions() {
    HMODULE ogl32 = LoadLibrary(L"opengl32.dll");
    if (!ogl32) {
        MessageBox(0, L"Failed to load opengl32.dll", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    pglClear = (PFNGLCLEARPROC)GetProcAddress(ogl32, "glClear");
    pglClearColor = (PFNGLCLEARCOLORPROC)GetProcAddress(ogl32, "glClearColor");
    pglViewport = (PFNGLVIEWPORTPROC)GetProcAddress(ogl32, "glViewport");
    pglDrawArrays = (PFNGLDRAWARRAYSPROC)GetProcAddress(ogl32, "glDrawArrays");
    pglDrawElements = (PFNGLDRAWELEMENTSPROC)GetProcAddress(ogl32, "glDrawElements");
}

void LoadOpenGLFunctions() {
    LoadCoreOpenGLFunctions();

    pglGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
    pglBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
    pglBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
    pglDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
    pglGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
    pglBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
    pglVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
    pglEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
    pglCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
    pglUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
    pglDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
    pglLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
    pglValidateProgram = (PFNGLVALIDATEPROGRAMPROC)wglGetProcAddress("glValidateProgram");
    pglCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
    pglShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
    pglCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
    pglAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
    pglDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
    pglGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
    pglGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
    pglGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
    pglGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
    pglGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
    pglUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
    pglUniform3f = (PFNGLUNIFORM3FPROC)wglGetProcAddress("glUniform3f");
    pglUniform4f = (PFNGLUNIFORM4FPROC)wglGetProcAddress("glUniform4f");
    pglUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
    pglUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
    pglUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
}