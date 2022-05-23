/*
#include "GraphicsContext.hpp"

GraphicsContext::GraphicsContext(const WindowController* windowController) :
    m_WindowController(windowController)
{
    int status = gladLoadGL(glfwGetProcAddress);
}

GraphicsContext::~GraphicsContext()
{
    m_WindowController = nullptr;
}

void GraphicsContext::SetClearColor(float x, float y, float z, float w)
{
    m_ClearColor[0] = x;
    m_ClearColor[1] = y;
    m_ClearColor[2] = z;
    m_ClearColor[3] = w;
}

void GraphicsContext::Update()
{
    glViewport(0, 0, m_WindowController->GetWidth(), m_WindowController->GetHeight());
    glClearColor(m_ClearColor[0] * m_ClearColor[3], m_ClearColor[1] * m_ClearColor[3], m_ClearColor[2] * m_ClearColor[3], m_ClearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

std::any GraphicsContext::GetComponentConstructor()
{
    return m_GLSLVersion.data();
}
*/
