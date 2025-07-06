#include "opengl.h"

PFNGLCOLOR3FPROC pglColor3f = NULL;
PFNGLBEGINPROC pglBegin = NULL;
PFNGLENDPROC pglEnd = NULL;
PFNGLVERTEX2FPROC pglVertex2f = NULL;
PFNGLMATRIXMODEPROC pglMatrixMode = NULL;
PFNGLLOADIDENTITYPROC pglLoadIdentity = NULL;
PFNGLORTHOPROC pglOrtho = NULL;
PFNGLTEXCOORD2FPROC pglTexCoord2f = NULL;

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
PFNGLGETACTIVEUNIFORMPROC pglGetActiveUniform = NULL;
PFNGLENABLEPROC pglEnable = NULL;
PFNGLGENTEXTURESPROC pglGenTextures = NULL;
PFNGLBINDTEXTUREPROC pglBindTexture = NULL;
PFNGLTEXIMAGE2DPROC pglTexImage2D = NULL;
PFNGLTEXPARAMETERIPROC pglTexParameteri = NULL;
PFNGLBLENDFUNCPROC pglBlendFunc = NULL;

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
    pglColor3f = (PFNGLCOLOR3FPROC)GetProcAddress(ogl32, "glColor3f");
    pglBegin = (PFNGLBEGINPROC)GetProcAddress(ogl32, "glBegin");
    pglEnd = (PFNGLENDPROC)GetProcAddress(ogl32, "glEnd");
    pglVertex2f = (PFNGLVERTEX2FPROC)GetProcAddress(ogl32, "glVertex2f");
    pglMatrixMode = (PFNGLMATRIXMODEPROC)GetProcAddress(ogl32, "glMatrixMode");
    pglLoadIdentity = (PFNGLLOADIDENTITYPROC)GetProcAddress(ogl32, "glLoadIdentity");
    pglOrtho = (PFNGLORTHOPROC)GetProcAddress(ogl32, "glOrtho");
    pglTexCoord2f = (PFNGLTEXCOORD2FPROC)GetProcAddress(ogl32, "glTexCoord2f");
    pglTexImage2D = (PFNGLTEXIMAGE2DPROC)GetProcAddress(ogl32, "glTexImage2D");
    pglTexParameteri = (PFNGLTEXPARAMETERIPROC)GetProcAddress(ogl32, "glTexParameteri");
    pglEnable = (PFNGLENABLEPROC)GetProcAddress(ogl32, "glEnable");
    pglBlendFunc = (PFNGLBLENDFUNCPROC)GetProcAddress(ogl32, "glBlendFunc");
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
    pglGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)wglGetProcAddress("glGetActiveUniform");
    //pglEnable = (PFNGLENABLEPROC)wglGetProcAddress("glEnable");
    pglGenTextures = (PFNGLGENTEXTURESPROC)wglGetProcAddress("glGenTextures");
    pglBindTexture = (PFNGLBINDTEXTUREPROC)wglGetProcAddress("glBindTexture");
    //pglBlendFunc = (PFNGLBLENDFUNCPROC)wglGetProcAddress("glBlendFunc");
    //pglTexImage2D = (PFNGLTEXIMAGE2DPROC)wglGetProcAddress("glTexImage2D");
    //pglTexParameteri = (PFNGLTEXPARAMETERIPROC)wglGetProcAddress("glTexParameteri");
}