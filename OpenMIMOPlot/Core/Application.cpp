#include "Application.hpp"

#include "imgui.h"

Application::Application()
{
    m_WindowController = new GLFWController();
    m_GraphicsContext = new GL4Context(m_WindowController);
    m_ImGUILayer = new GLFWGL4ImGUILayer(std::any_cast<GLFWwindow*>(m_WindowController->GetNativeWindow()));
    m_ImPlotLayer = new ImPlotLayer();

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    m_GraphicsContext->SetClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

    m_ImGUILayer->OnAttach();
    m_ImPlotLayer->OnAttach();
}

Application::~Application()
{
    m_ImPlotLayer->OnDetach();
    m_ImGUILayer->OnDetach();

    delete m_ImPlotLayer;
    delete m_ImGUILayer;
    delete m_GraphicsContext;
    delete m_WindowController;
}

void Application::Run()
{
    while (!m_WindowController->ShouldClose())
    {
        m_WindowController->Update();
        m_GraphicsContext->Update();
        m_ImGUILayer->BeginFrame();
        m_ImGUILayer->OnUpdate();
        m_ImGUILayer->EndFrame();
        m_WindowController->Present();
    }
}
