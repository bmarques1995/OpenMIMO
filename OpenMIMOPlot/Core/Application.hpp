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

class Application
{
private:
    WindowController* m_WindowController;
    GraphicsContext* m_GraphicsContext;
    ImGUILayer* m_ImGUILayer;
    ImPlotLayer* m_ImPlotLayer;

    GraphicsInjector* m_GraphicsInjector;
    LayerStack m_LayerStack;
public:
    Application();
    ~Application();
    void Run();

    void PushLayer(Layer* layer);
	void PushOverlay(Layer* overlay);
};

#endif
