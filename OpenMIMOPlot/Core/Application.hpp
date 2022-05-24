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
#include "GraphicsInjector.hpp"


class Application
{
private:
    WindowController* m_WindowController;
    GraphicsContext* m_GraphicsContext;
    ImGUILayer* m_ImGUILayer;
    ImPlotLayer* m_ImPlotLayer;

    GraphicsInjector* m_GraphicsInjector;
    
public:
    Application();
    ~Application();
    void Run();
};

#endif
