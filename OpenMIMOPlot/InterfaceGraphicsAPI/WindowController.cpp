// #include "WindowController.hpp"
// #include <cstdlib>

// WindowController::WindowController()
// {
//     /* Initialize the library */
//     if (!glfwInit())
//         exit(1);

//     /* Create a windowed mode window and its OpenGL context */
//     m_Window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//     if (!m_Window)
//     {
//         glfwTerminate();
//         exit(1);
//     }

//     glfwMakeContextCurrent(m_Window);
// }

// WindowController::~WindowController()
// {
//     glfwDestroyWindow(m_Window);
//     glfwTerminate();
// }

// int WindowController::GetWidth()
// {
//     return m_Width;
// }

// int WindowController::GetHeight()
// {
//     return m_Height;
// }

// GLFWwindow* WindowController::GetNativeWindow()
// {
//     return m_Window;
// }

// bool WindowController::ShouldClose()
// {
//     return glfwWindowShouldClose(m_Window);
// }

// void WindowController::Update()
// {
//     glfwPollEvents();
//     glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);

//     glfwSwapBuffers(m_Window);
// }
