#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <stdio.h>
#include <iostream>
#include <random>
#include <complex>
#include "ImplementationGraphicsAPI/Window/GLFW/GLFWController.hpp"
#include "ImplementationGraphicsAPI/ImGUI/GLFWGL4/GLFWGL4ImGUILayer.hpp"
#include "Core/ImGUILayer.hpp"
#include "Core/ImPlotLayer.hpp"
#include "ImplementationGraphicsAPI/Graphics/GL4/GL4Context.hpp"
#include "Core/GraphicsInjector.hpp"
#include "Core/LayerStack.hpp"

#include "Events/EventDispatcher.hpp"
#include "Events/ApplicationEvent.hpp"

namespace OpenMIMO
{
    class Application
    {
    private:
        WindowController* m_WindowController;
        GraphicsContext* m_GraphicsContext;
        ImGUILayer* m_ImGUILayer;
        ImPlotLayer* m_ImPlotLayer;

        GraphicsInjector* m_GraphicsInjector;
        LayerStack m_LayerStack;
        EventDispatcher* m_EventDispatcher;

        void OnClose(const Event& eventHandler);
        void OnWindowResize(const Event& eventHandler);
        void OnFramebufferResize(const Event& eventHandler);
        void OnMinimize(const Event& eventHandler);
        void OnRestore(const Event& eventHandler);

    public:
        Application();
        ~Application();
        void Run();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
    };
}

#endif
