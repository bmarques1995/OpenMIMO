#include "WIN32D3D11ImGUILayer.hpp"

#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_dx11.h"
#include "imgui.h"
#include "implot.h"

OpenMIMO::WIN32D3D11ImGUILayer::WIN32D3D11ImGUILayer(HWND window, ID3D11Device* device, ID3D11DeviceContext* deviceContext) :
    m_Window(window), m_Device(device), m_DeviceContext(deviceContext)
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

OpenMIMO::WIN32D3D11ImGUILayer::~WIN32D3D11ImGUILayer()
{
    m_Window = nullptr;
    m_Device = nullptr;
    m_DeviceContext = nullptr;
}

void OpenMIMO::WIN32D3D11ImGUILayer::OnAttach()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsLight();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(m_Window);
    ImGui_ImplDX11_Init(m_Device, m_DeviceContext);
}

void OpenMIMO::WIN32D3D11ImGUILayer::OnDetach()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void OpenMIMO::WIN32D3D11ImGUILayer::OnUpdate()
{
}

void OpenMIMO::WIN32D3D11ImGUILayer::BeginFrame()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void OpenMIMO::WIN32D3D11ImGUILayer::EndFrame()
{
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}