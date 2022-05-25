#include "Application.hpp"

#include "imgui.h"
#include <iostream>

using std::cout;

Application::Application()
{
    m_GraphicsInjector = new GraphicsInjector();

    std::pair<std::string_view, std::string_view> APIs = {"GLFW", "GL4"};
    GraphicsStartup startup =  m_GraphicsInjector->GetGraphics(APIs);

    m_WindowController = startup.Controller;
    m_GraphicsContext = startup.Context;
    m_ImGUILayer = startup.Layer;
    m_ImPlotLayer = new ImPlotLayer();

    cout << (size_t)m_WindowController << " " << (size_t) m_GraphicsInjector <<"\n";

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
    delete m_GraphicsInjector;
}

void Application::Run()
{
    while (!m_WindowController->ShouldClose())
    {		
        m_WindowController->Update();
        m_GraphicsContext->Update();
        m_ImGUILayer->BeginFrame();
        for (Layer* layer : m_LayerStack)
			layer->OnUpdate();
        m_ImGUILayer->OnUpdate();
        m_ImGUILayer->EndFrame();
        m_WindowController->Present();
    }
}

void Application::PushLayer(Layer* layer)
{
    m_LayerStack.PushLayer(layer);
}

void Application::PushOverlay(Layer* overlay)
{
    m_LayerStack.PushOverlay(overlay);
}
