#include "GLFWController.hpp"
#include <iostream>
#include <functional>

#include "Utils/Console.hpp"

#include "Events/ApplicationEvent.hpp"

OpenMIMO::GLFWController::GLFWController(EventDispatcher* dispatcher, const WindowProps& props)
{
    m_Width = props.Width;
    m_Height = props.Height;
    m_Title = props.Title;
    m_EventDispatcher = dispatcher;

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
    glfwSetWindowUserPointer(m_Window, m_EventDispatcher);
    RegisterCallbacks();
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

void OpenMIMO::GLFWController::RegisterCallbacks()
{
    glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow* window, int iconify)
    {
        EventDispatcher* dispatcher = reinterpret_cast<EventDispatcher*>(glfwGetWindowUserPointer(window));
        //iconify == GLFW_FALSE ? Console::Log("Window Restored\n") : Console::Log("Window Minimized\n");
        if(iconify == GLFW_FALSE)
        {
            WindowRestoreEvent e;
            dispatcher->Dispatch(e);
        }
        else
        {
            WindowMinimizeEvent e;
            dispatcher->Dispatch(e);
        }
    });
    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
    {
        EventDispatcher* dispatcher = reinterpret_cast<EventDispatcher*>(glfwGetWindowUserPointer(window));
        WindowCloseEvent e;
        dispatcher->Dispatch(e);
    });
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
        EventDispatcher* dispatcher = reinterpret_cast<EventDispatcher*>(glfwGetWindowUserPointer(window));
        WindowResizeEvent e((uint32_t) width, (uint32_t) height);;
        dispatcher->Dispatch(e);
    });
    glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
        EventDispatcher* dispatcher = reinterpret_cast<EventDispatcher*>(glfwGetWindowUserPointer(window));
        FramebufferResizeEvent e((uint32_t) width, (uint32_t) height);
        dispatcher->Dispatch(e);
    });
}
