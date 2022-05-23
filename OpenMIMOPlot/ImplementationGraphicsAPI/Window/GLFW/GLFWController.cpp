#include "GLFWController.hpp"

GLFWController::GLFWController(const WindowProps& props)
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

GLFWController::~GLFWController()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

bool GLFWController::ShouldClose() const
{
    return glfwWindowShouldClose(m_Window);
}

uint32_t GLFWController::GetWidth() const
{
    return m_Width;
}

uint32_t GLFWController::GetHeight() const
{
    return m_Height;
}

std::any GLFWController::GetNativeWindow() const
{
    return m_Window;
}

void GLFWController::Update()
{
    int width, height;
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
    glfwGetFramebufferSize(m_Window, &width, &height);
    m_Width = width;
    m_Height = height;
}