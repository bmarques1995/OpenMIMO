#include "WIN32D3D11ImGUILayer.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "implot.h"

WIN32D3D11ImGUILayer::WIN32D3D11ImGUILayer()
{
    poles[0] = { -3,0 };
    poles[1] = { -5,2 };
    poles[2] = { -5,-2 };

    for (size_t i = 0; i < 3; i++)
    {
        real_poles[i] = poles[i].real();
        imag_poles[i] = poles[i].imag();
    }
}

WIN32D3D11ImGUILayer::~WIN32D3D11ImGUILayer()
{
    
}

void WIN32D3D11ImGUILayer::OnAttach()
{
    
}

void WIN32D3D11ImGUILayer::OnDetach()
{
    
}

void WIN32D3D11ImGUILayer::OnUpdate()
{
    
}

void WIN32D3D11ImGUILayer::BeginFrame()
{
    
}

void WIN32D3D11ImGUILayer::EndFrame()
{
    
}