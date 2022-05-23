#include "GL4Context.hpp"
#include <GLFW/glfw3.h>

GL4Context::GL4Context(const WindowController* windowController) :
    m_WindowController(windowController)
{
    int status = gladLoadGL(glfwGetProcAddress);
}
GL4Context::~GL4Context()
{
    m_WindowController = nullptr;
}

void GL4Context::Update()
{
    glViewport(0, 0, m_WindowController->GetWidth(), m_WindowController->GetHeight());
    glClearColor(m_ClearColor[0] * m_ClearColor[3], m_ClearColor[1] * m_ClearColor[3], m_ClearColor[2] * m_ClearColor[3], m_ClearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GL4Context::SetClearColor(float x, float y, float z, float w = 1.0f)
{
    m_ClearColor[0] = x;
    m_ClearColor[1] = y;
    m_ClearColor[2] = z;
    m_ClearColor[3] = w;
}

std::any GL4Context::GetComponentConstructor() const
{
    return m_GLSLVersion.data();
}
