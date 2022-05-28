#include "GLFWController.hpp"

OpenMIMO::GLFWController::GLFWController(const WindowProps& props)
{
    m_Width = props.Width;
    m_Height = props.Height;
    m_Title = props.Title;

    /* Initialize the library */
    if (!glfwInit())
        exit(1);

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
    if (!m_Window)
    {
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(m_Window);

    glfwSetErrorCallback([](int error, const char* description){
        fprintf(stderr, "Glfw Error %d: %s\n", error, description);
    });
}

OpenMIMO::GLFWController::~GLFWController()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

bool OpenMIMO::GLFWController::ShouldClose() const
{
    return glfwWindowShouldClose(m_Window);
}

uint32_t OpenMIMO::GLFWController::GetWidth() const
{
    return m_Width;
}

uint32_t OpenMIMO::GLFWController::GetHeight() const
{
    return m_Height;
}

std::any OpenMIMO::GLFWController::GetNativeWindow() const
{
    return m_Window;
}

void OpenMIMO::GLFWController::Update()
{
    int width, height;
    glfwPollEvents();
    glfwGetFramebufferSize(m_Window, &width, &height);
    m_Width = width;
    m_Height = height;
}

void OpenMIMO::GLFWController::Present()
{
    glfwSwapBuffers(m_Window);
}
