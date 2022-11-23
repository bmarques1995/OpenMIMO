#include "GL4Context.hpp"

OpenMIMO::GL4Context::GL4Context(GLFWwindow* window) :
    m_Window(window)
{
    int status = gladLoadGL(glfwGetProcAddress);
}
OpenMIMO::GL4Context::~GL4Context()
{
    m_Window = nullptr;
}

void OpenMIMO::GL4Context::Update()
{
    glClearColor(m_ClearColor[0] * m_ClearColor[3], m_ClearColor[1] * m_ClearColor[3], m_ClearColor[2] * m_ClearColor[3], m_ClearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenMIMO::GL4Context::SetViewport(uint32_t width, uint32_t height)
{
    if((width > 0) && (height > 0))
        glViewport(0, 0, width, height);
}

void OpenMIMO::GL4Context::SetClearColor(float x, float y, float z, float w = 1.0f)
{
    m_ClearColor[0] = x;
    m_ClearColor[1] = y;
    m_ClearColor[2] = z;
    m_ClearColor[3] = w;
}

std::any OpenMIMO::GL4Context::GetComponentConstructor() const
{
    return m_GLSLVersion.data();
}

void OpenMIMO::GL4Context::Present()
{
    glfwSwapBuffers(m_Window);
}
