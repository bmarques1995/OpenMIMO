#include "Application.hpp"
#include "ApplicationStarter.hpp"

#include "imgui.h"
#include <iostream>

#include "Utils/Console.hpp"

void OpenMIMO::Application::OnClose(const Event& eventHandler)
{
    m_WindowController->ReceiveCloseEvent(true);
}

void OpenMIMO::Application::OnWindowResize(const Event& eventHandler)
{
    std::pair<uint32_t, uint32_t> dimensions = std::any_cast<std::pair<uint32_t, uint32_t>>(eventHandler.GetEventData());
    m_WindowController->ResetWindowDimensions(dimensions.first, dimensions.second);
    m_GraphicsContext->SetViewport(dimensions.first, dimensions.second);
}

void OpenMIMO::Application::OnFramebufferResize(const Event& eventHandler)
{
    std::pair<uint32_t, uint32_t> dimensions = std::any_cast<std::pair<uint32_t, uint32_t>>(eventHandler.GetEventData());
    m_WindowController->ResetWindowDimensions(dimensions.first, dimensions.second);
    m_GraphicsContext->SetViewport(dimensions.first, dimensions.second);
}

void OpenMIMO::Application::OnMinimize(const Event& eventHandler)
{
    m_Minimized = std::any_cast<bool>(eventHandler.GetEventData());
}

OpenMIMO::Application::Application()
{
    ConsoleWrapper::Init();
    
    ConsoleWrapper::Debug("Teste de Debug {}", 6);
    ConsoleWrapper::Log("Teste de Log {}, {}", 3, "E aí panacas");
    
    ConsoleWrapper::Warn("Teste de Warn {}", 3);
    ConsoleWrapper::Error("Teste de Error {}", 3);
    ConsoleWrapper::Critical("Teste de Critical {}", 39);
    std::list<FunctionStarter> m_Starter;
    m_Starter.push_back(FunctionStarter(std::bind(&Application::OnClose, this, std::placeholders::_1), EventType::WindowCloseEvent));
    m_Starter.push_back(FunctionStarter(std::bind(&Application::OnWindowResize, this, std::placeholders::_1), EventType::WindowResizeEvent));
    m_Starter.push_back(FunctionStarter(std::bind(&Application::OnMinimize, this, std::placeholders::_1), EventType::WindowMinimizeEvent));
    m_Starter.push_back(FunctionStarter(std::bind(&Application::OnFramebufferResize, this, std::placeholders::_1), EventType::FramebufferResizeEvent));
    m_GraphicsInjector = new GraphicsInjector();

    m_EventDispatcher = new EventDispatcher(m_Starter);

    ApplicationStarter::BuildStarter();

    json startupJson = ApplicationStarter::GetStartupJson();

    WindowProps props(960, 540, "OpenMIMOPlot");

    std::pair<std::string, std::string> APIs = { startupJson["WindowAPI"].get<std::string>() , startupJson["GraphicsAPI"].get<std::string>() };
    GraphicsStartup startup =  m_GraphicsInjector->GetGraphics(APIs, m_EventDispatcher, props);

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

    ImVec4 clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    m_GraphicsContext->SetClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

    m_ImGUILayer->OnAttach();
    m_ImPlotLayer->OnAttach();
}

OpenMIMO::Application::~Application()
{
    m_ImPlotLayer->OnDetach();
    m_ImGUILayer->OnDetach();
    ConsoleWrapper::End();

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
