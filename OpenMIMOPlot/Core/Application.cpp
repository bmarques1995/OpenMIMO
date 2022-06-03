#include "Application.hpp"
#include "ApplicationStarter.hpp"

#include "imgui.h"
#include <iostream>

#include "Utils/Console.hpp"

void OpenMIMO::Application::OnClose(const Event& eventHandler)
{
    Console::Log(eventHandler.GetEventInfo());
    Console::Log("\n");
}

void OpenMIMO::Application::OnWindowResize(const Event& eventHandler)
{
    std::pair<uint32_t, uint32_t> dimensions = std::any_cast<std::pair<uint32_t, uint32_t>>(eventHandler.GetEventData());
    m_GraphicsContext->SetViewport(dimensions.first, dimensions.second);
}

void OpenMIMO::Application::OnFramebufferResize(const Event& eventHandler)
{
    Console::Log(eventHandler.GetEventInfo());
    Console::Log("\n");
}

void OpenMIMO::Application::OnMinimize(const Event& eventHandler)
{
    Console::Log(eventHandler.GetEventInfo());
    Console::Log("\n");
}

void OpenMIMO::Application::OnRestore(const Event& eventHandler)
{
    Console::Log(eventHandler.GetEventInfo());
    Console::Log("\n");
}

OpenMIMO::Application::Application()
{
    std::list<FunctionStarter> m_Starter;
    m_Starter.push_back(FunctionStarter(std::bind(&Application::OnClose, this, std::placeholders::_1), EventType::WindowCloseEvent));
    m_Starter.push_back(FunctionStarter(std::bind(&Application::OnWindowResize, this, std::placeholders::_1), EventType::WindowResizeEvent));
    m_Starter.push_back(FunctionStarter(std::bind(&Application::OnMinimize, this, std::placeholders::_1), EventType::WindowMinimizeEvent));
    m_Starter.push_back(FunctionStarter(std::bind(&Application::OnRestore, this, std::placeholders::_1), EventType::WindowRestoreEvent));
    m_Starter.push_back(FunctionStarter(std::bind(&Application::OnFramebufferResize, this, std::placeholders::_1), EventType::FramebufferResizeEvent));
    m_GraphicsInjector = new GraphicsInjector();

    m_EventDispatcher = new EventDispatcher(m_Starter);

    ApplicationStarter::BuildStarter();

    json startupJson = ApplicationStarter::GetStartupJson();

    std::pair<std::string, std::string> APIs = { startupJson["WindowAPI"].get<std::string>() , startupJson["GraphicsAPI"].get<std::string>() };
    GraphicsStartup startup =  m_GraphicsInjector->GetGraphics(APIs, m_EventDispatcher);

    m_WindowController = startup.Controller;
    m_GraphicsContext = startup.Context;
    m_ImGUILayer = startup.Layer;
    m_ImPlotLayer = new ImPlotLayer();

    if (m_WindowController == nullptr)
        exit(1);

    if (m_GraphicsContext == nullptr)
        exit(2);

    if (m_ImGUILayer == nullptr)
        exit(3);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    m_GraphicsContext->SetClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

    m_ImGUILayer->OnAttach();
    m_ImPlotLayer->OnAttach();
}

OpenMIMO::Application::~Application()
{
    m_ImPlotLayer->OnDetach();
    m_ImGUILayer->OnDetach();

    delete m_ImPlotLayer;
    delete m_ImGUILayer;
    delete m_GraphicsContext;
    delete m_WindowController;
    delete m_GraphicsInjector;
}

void OpenMIMO::Application::Run()
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
        m_GraphicsContext->Present();
    }
}

void OpenMIMO::Application::PushLayer(Layer* layer)
{
    m_LayerStack.PushLayer(layer);
}

void OpenMIMO::Application::PushOverlay(Layer* overlay)
{
    m_LayerStack.PushOverlay(overlay);
}
